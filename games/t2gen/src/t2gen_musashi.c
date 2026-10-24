#include <sys/time.h>
/* T2GEN v4: Musashi adapter, not a full Genesis emulator.
 * Requires upstream Musashi m68kcpu.c, m68kops.c and headers.
 * No framebuffer rendering or audio in this milestone.
 */
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "m68k.h"
#include "t2gen_musashi.h"
#include "t2gen_render.h"

#include <errno.h>
#include <stdio.h>
#include "musashi/m68kops.h"
#include <syslog.h>
#include "t2gen_vdp.h"
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <nuttx/input/xbox-controller.h>


#define RAM_SIZE 65536u
struct genesis_s {
 const uint8_t *rom; size_t romlen;
 uint8_t *ram;
 uint32_t reads,writes,io_reads,vdp_writes,vdp_ctrl,vdp_data,unmapped;
 uint32_t first_vdp_pc;
};
static struct genesis_s g;
/* V9.7: NuttX Xbox controller -> Genesis 3-button port 1.
 * Based on NX2D V19's /dev/xboxa nonblocking buttonstate interface.
 * Controller sampling happens once per emulated frame, not on every IO read.
 */
#define PAD_UP    (1u << 0)
#define PAD_DOWN  (1u << 1)
#define PAD_LEFT  (1u << 2)
#define PAD_RIGHT (1u << 3)
#define PAD_A     (1u << 4)
#define PAD_B     (1u << 5)
#define PAD_C     (1u << 6)
#define PAD_START (1u << 7)
static int g_xbox_fd = -1;
static uint8_t g_buttons;
static uint8_t g_pad_data = 0x40u;
static uint8_t g_pad_ctrl = 0x40u;
static uint32_t g_pad_frame;
static uint32_t g_pad_reads;
static uint32_t g_xbox_samples;
static uint32_t g_xbox_errors;

static void xbox_open(void)
{
  g_xbox_fd = open("/dev/xboxa", O_RDONLY | O_NONBLOCK);
  if (g_xbox_fd < 0)
    printf("T2GEN V9.7: /dev/xboxa unavailable errno=%d (pad idle)\n", errno);
  else
    printf("T2GEN V9.7: Xbox connected /dev/xboxa\n");
}

static void xbox_poll(void)
{
  struct xbox_controller_buttonstate_s pad;
  ssize_t n;
  uint8_t buttons = 0;
  if (g_xbox_fd < 0) return;
  n = read(g_xbox_fd, &pad, sizeof(pad));
  if (n < 0)
    {
      if (errno == EAGAIN || errno == EINTR) return;
      if (++g_xbox_errors == 1u)
        printf("T2GEN V9.7: Xbox read error errno=%d\n", errno);
      g_buttons = 0;
      return;
    }
  if ((size_t)n != sizeof(pad)) return;
  if (pad.dpad_up || pad.stick_left_y < -8000) buttons |= PAD_UP;
  if (pad.dpad_down || pad.stick_left_y > 8000) buttons |= PAD_DOWN;
  if (pad.dpad_left || pad.stick_left_x < -8000) buttons |= PAD_LEFT;
  if (pad.dpad_right || pad.stick_left_x > 8000) buttons |= PAD_RIGHT;
  if (pad.a) buttons |= PAD_A;
  if (pad.b) buttons |= PAD_B;
  if (pad.x) buttons |= PAD_C;
  if (pad.start) buttons |= PAD_START;
  g_buttons = buttons;
  g_xbox_samples++;
}

static uint8_t pad_read(void)
{
  bool th = (g_pad_data & 0x40u) != 0u;
  uint8_t bits = th ? 0x3fu : 0x33u;
  /* TH=1: bit0 U,1 D,2 L,3 R,4 B,5 C.
   * TH=0: bit0 U,1 D,4 A,5 START; bits2/3 forced low.
   * Buttons are active-low. */
  if (g_buttons & PAD_UP) bits &= (uint8_t)~0x01u;
  if (g_buttons & PAD_DOWN) bits &= (uint8_t)~0x02u;
  if (th)
    {
      if (g_buttons & PAD_LEFT) bits &= (uint8_t)~0x04u;
      if (g_buttons & PAD_RIGHT) bits &= (uint8_t)~0x08u;
      if (g_buttons & PAD_B) bits &= (uint8_t)~0x10u;
      if (g_buttons & PAD_C) bits &= (uint8_t)~0x20u;
    }
  else
    {
      if (g_buttons & PAD_A) bits &= (uint8_t)~0x10u;
      if (g_buttons & PAD_START) bits &= (uint8_t)~0x20u;
    }
  g_pad_reads++;
  return (uint8_t)(0x80u | (th ? 0x40u : 0u) | bits);
}

/* V8.3: bounded bus tracing. No changes to bus write behavior. */
/* V8.5: targeted investigation of the logo-to-game wait loops. */
static uint32_t g_v85_ram_watch_count;
static void __attribute__((unused)) v85_watch_ram(uint32_t a, uint32_t value, unsigned bits)
{
  uint32_t start = a & 0x00ffffffu;
  uint32_t end = start + bits / 8u;
  if ((start <= 0xff03b1u && end > 0xff03b0u) ||
      (start <= 0xff0223u && end > 0xff0222u) ||
      (start <= 0xff0007u && end > 0xff0006u))
    {
      g_v85_ram_watch_count++;
      if (g_v85_ram_watch_count <= 48u ||
          (g_v85_ram_watch_count % 256u) == 0u)
        printf("T2GEN V8.5 RAM WATCH[%lu]: PC=%06lX addr=%06lX bits=%u value=%08lX\n",
               (unsigned long)g_v85_ram_watch_count,
               (unsigned long)m68k_get_reg(NULL,M68K_REG_PC),
               (unsigned long)start, bits, (unsigned long)value);
    }
}
static void v85_loop_state(uint32_t pc, uint32_t cycles, uint32_t slice)
{
  uint16_t w03b0 = ((uint16_t)g.ram[0x03b0] << 8) | g.ram[0x03b1];
  uint16_t w0222 = ((uint16_t)g.ram[0x0222] << 8) | g.ram[0x0223];
  uint16_t w0006 = ((uint16_t)g.ram[0x0006] << 8) | g.ram[0x0007];
  printf("T2GEN V8.5 WAIT: slice=%lu cycles=%lu PC=%06lX D1=%08lX SR=%04lX FF03B0=%04X FF0222=%04X FF0006=%04X\n",
         (unsigned long)slice, (unsigned long)cycles, (unsigned long)pc,
         (unsigned long)m68k_get_reg(NULL,M68K_REG_D1),
         (unsigned long)m68k_get_reg(NULL,M68K_REG_SR),
         w03b0, w0222, w0006);
}
static uint32_t g_trace_long_count;
static uint32_t g_trace_word_count;
static uint32_t g_trace_long_nonzero;
static uint32_t g_trace_word_nonzero;
static uint32_t g_trace_long_vdp;
static uint32_t g_trace_word_vdp;
static uint32_t g_trace_long_ram;
static uint32_t g_trace_word_ram;
static uint32_t g_trace_long_other;
static uint32_t g_trace_word_other;
static void t2gen_trace_rom(const uint8_t *rom, size_t len)
{
  static const uint32_t addresses[] = {0x00025cu, 0x004ab0u, 0x00eb02u, 0x00aa0eu};
  unsigned j;
  for (j = 0; j < sizeof(addresses) / sizeof(addresses[0]); j++)
    {
      uint32_t a = addresses[j];
      unsigned i;
      printf("T2GEN V8.3 ROM %06lX:", (unsigned long)a);
      for (i = 0; i < 16 && (size_t)a + i < len; i++)
        printf(" %02X", (unsigned)rom[a + i]);
      printf("\n");
    }
  if (len >= 0x4abau)
    {
      uint32_t imm = ((uint32_t)rom[0x4ab2] << 24) |
                     ((uint32_t)rom[0x4ab3] << 16) |
                     ((uint32_t)rom[0x4ab4] << 8) | rom[0x4ab5];
      uint32_t dst = ((uint32_t)rom[0x4ab6] << 24) |
                     ((uint32_t)rom[0x4ab7] << 16) |
                     ((uint32_t)rom[0x4ab8] << 8) | rom[0x4ab9];
      if (len >= 0x4abau && rom[0x4ab0] == 0x23 && rom[0x4ab1] == 0xfc)
        printf("T2GEN V8.3 DECODE 004AB0: MOVE.L #$%08lX,$%08lX\n",
               (unsigned long)imm, (unsigned long)dst);
    }
}

static bool is_vdp(uint32_t a)
{
  a &= 0x00ffffffu;
  return a >= 0xc00000u && a <= 0xc0001fu;
}

static void vdp_count_write(uint32_t a)
{
  if (!g.vdp_writes)
    {
      g.first_vdp_pc =
        m68k_get_reg(NULL, M68K_REG_PC);
    }

  g.vdp_writes++;

  switch (a & 0x1cu)
    {
      case 0x00:
        g.vdp_data++;
        break;

      case 0x04:
        g.vdp_ctrl++;
        break;
    }
}

static void vdp_write16(uint32_t a, uint16_t value)
{
  vdp_count_write(a);

  switch (a & 0x1cu)
    {
      case 0x00:
        t2gen_vdp_write_data(value);
        break;

      case 0x04:
        t2gen_vdp_write_control(value);
        break;
    }
}

static uint16_t vdp_read16(uint32_t a)
{
  switch (a & 0x1cu)
    {
      case 0x00:
        return t2gen_vdp_read_data();

      case 0x04:
        return t2gen_vdp_read_control();

      default:
        return 0xffff;
    }
}



static unsigned r8(uint32_t a) {
 a &= 0xffffffu;
 if (a < g.romlen) return g.rom[a];
 if (a >= 0xff0000u) return g.ram[a & 0xffffu];
 if (a >= 0xa10000u && a <= 0xa1001fu) {
  g.io_reads++;
  if (a == 0xa10001u) return 0xa0; /* hardware version byte */
  if (a == 0xa10003u) return pad_read();
  if (a == 0xa10009u) return g_pad_ctrl;
  return 0xff;
 }
 if (a == 0xc00004u || a == 0xc00005u) return a & 1u ? 0x00 : 0x34;
 if (a == 0xa11100u || a == 0xa11101u) return 0;
 if (a == 0xa11200u || a == 0xa11201u) return 0;
 g.unmapped++; return 0xff;
}
static void w8(uint32_t a,unsigned v) {
 a &= 0xffffffu;
 if (a >= 0xff0000u) {g.ram[a & 0xffffu]=(uint8_t)v;return;}
//  if (a >= 0xc00000u && a <= 0xc0001fu) {
//   if (!g.vdp_writes) g.first_vdp_pc=m68k_get_reg(NULL,M68K_REG_PC);
//   g.vdp_writes++;
//   if ((a&~3u)==0xc00000u) g.vdp_data++;
//   if ((a&~3u)==0xc00004u) g.vdp_ctrl++;
//   return;
//  }
if (a == 0xa10003u) {g_pad_data=(uint8_t)v;return;}
 if (a == 0xa10009u) {g_pad_ctrl=(uint8_t)v;return;}
if (is_vdp(a))
  {
    vdp_count_write(a);
    /* TODO: implement correct 8-bit VDP port semantics. */
    return;
  }
 /* Z80 reset/bus-request and PSG are acknowledged but not emulated. */
 if ((a>=0xa00000u && a<=0xa0ffffu) || (a>=0xa10000u && a<=0xa1001fu) ||
     (a>=0xa11100u && a<=0xa11201u)) return;
 g.unmapped++;
}
unsigned int m68k_read_memory_8(unsigned int address) {g.reads++;return r8(address);}
unsigned int m68k_read_memory_16(unsigned int address) {
 uint32_t a=address & 0xffffffu;
 g.reads++;
 if (a < g.romlen && (size_t)a + 1u < g.romlen)
   return ((unsigned)g.rom[a] << 8) | g.rom[a + 1u];
 if (a >= 0xff0000u)
   return ((unsigned)g.ram[a & 0xffffu] << 8) |
          g.ram[(a + 1u) & 0xffffu];
 if (is_vdp(a) && !(a & 1u)) return vdp_read16(a);
 return (r8(a)<<8)|r8(a+1);
}
unsigned int m68k_read_memory_32(unsigned int address) {
 uint32_t a=address & 0xffffffu;
 g.reads++;
 if (a < g.romlen && (size_t)a + 3u < g.romlen)
   return ((uint32_t)g.rom[a] << 24) | ((uint32_t)g.rom[a+1u] << 16) |
          ((uint32_t)g.rom[a+2u] << 8) | g.rom[a+3u];
 if (a >= 0xff0000u)
   return ((uint32_t)g.ram[a & 0xffffu] << 24) |
          ((uint32_t)g.ram[(a+1u) & 0xffffu] << 16) |
          ((uint32_t)g.ram[(a+2u) & 0xffffu] << 8) |
          g.ram[(a+3u) & 0xffffu];
 if (is_vdp(a) && !(a & 1u))
   return ((uint32_t)vdp_read16(a)<<16)|vdp_read16(a+2);
 return ((uint32_t)r8(a)<<24)|((uint32_t)r8(a+1)<<16)|
        ((uint32_t)r8(a+2)<<8)|r8(a+3);
}
void m68k_write_memory_8(unsigned int address,unsigned int value) {g.writes++;w8(address,value);}
void m68k_write_memory_16(unsigned int address,unsigned int value) {
 uint32_t a=address & 0xffffffu;
 g.writes++;
 
 g_trace_word_count++;
 if (value != 0) g_trace_word_nonzero++;
 if (is_vdp(a)) g_trace_word_vdp++;
 else if (a >= 0xff0000u) g_trace_word_ram++;
 else g_trace_word_other++;
 if (0 && (g_trace_word_count <= 16u ||
     (is_vdp(a) && value != 0 && g_trace_word_count <= 128u)))
   printf("T2GEN V8.3 WRITE16[%lu] PC=%06lX addr=%06lX val=%04X vdp=%u\n",
          (unsigned long)g_trace_word_count,
          (unsigned long)m68k_get_reg(NULL,M68K_REG_PC),
          (unsigned long)a, (unsigned)(value & 0xffffu), (unsigned)is_vdp(a));
 if (a >= 0xff0000u) {
   g.ram[a & 0xffffu] = (uint8_t)(value >> 8);
   g.ram[(a+1u) & 0xffffu] = (uint8_t)value;
   return;
 }
 if (is_vdp(a) && !(a & 1u)) {vdp_write16(a,(uint16_t)value);return;}
 w8(a,value>>8);w8(a+1,value);
}
void m68k_write_memory_32(unsigned int address,unsigned int value) {
 uint32_t a=address & 0xffffffu;
 g.writes++;
 
 g_trace_long_count++;
 if (value != 0) g_trace_long_nonzero++;
 if (is_vdp(a)) g_trace_long_vdp++;
 else if (a >= 0xff0000u) g_trace_long_ram++;
 else g_trace_long_other++;
 if (0 && (g_trace_long_count <= 32u ||
     (is_vdp(a) && value != 0 && g_trace_long_count <= 128u)))
   printf("T2GEN V8.3 WRITE32[%lu] PC=%06lX addr=%06lX val=%08lX vdp=%u\n",
          (unsigned long)g_trace_long_count,
          (unsigned long)m68k_get_reg(NULL,M68K_REG_PC),
          (unsigned long)a, (unsigned long)value, (unsigned)is_vdp(a));
 if (a >= 0xff0000u) {
   g.ram[a & 0xffffu] = (uint8_t)(value >> 24);
   g.ram[(a+1u) & 0xffffu] = (uint8_t)(value >> 16);
   g.ram[(a+2u) & 0xffffu] = (uint8_t)(value >> 8);
   g.ram[(a+3u) & 0xffffu] = (uint8_t)value;
   return;
 }
 if (is_vdp(a) && !(a & 1u)) {
   vdp_write16(a,(uint16_t)(value>>16));
   vdp_write16(a+2,(uint16_t)value);
   return;
 }
 w8(a,value>>24);w8(a+1,value>>16);
 w8(a+2,value>>8);w8(a+3,value);
}
/* Some Musashi builds use disassembler read callbacks. */
unsigned int m68k_read_disassembler_8(unsigned int a){return r8(a);}
unsigned int m68k_read_disassembler_16(unsigned int a){return (r8(a)<<8)|r8(a+1);}
unsigned int m68k_read_disassembler_32(unsigned int a){return (r8(a)<<24)|(r8(a+1)<<16)|(r8(a+2)<<8)|r8(a+3);}
static uint16_t genesis_dma_read16(uint32_t a)
{
  /* DMA reads ROM or 68K RAM; unmapped sources return open bus. */
  a &= 0xffffffu;
  if (a + 1 < g.romlen)
    return ((uint16_t)g.rom[a] << 8) | g.rom[a + 1];
  if (a >= 0xff0000u)
    return ((uint16_t)g.ram[a & 0xffffu] << 8) |
           g.ram[(a + 1) & 0xffffu];
  return 0xffffu;
}

void t2gen_musashi_probe(const uint8_t *rom,size_t len, const char *fbdev) {
 /* V13: explicit CPU-only benchmark mode. No framebuffer opened. */
 if (fbdev != NULL && strcmp(fbdev, "none") == 0) fbdev = NULL;
 memset(&g,0,sizeof(g));g.rom=rom;g.romlen=len;
 g_v85_ram_watch_count=0;
 g_trace_long_count=0; g_trace_word_count=0;
 g_trace_long_nonzero=0; g_trace_word_nonzero=0;
 g_trace_long_vdp=0; g_trace_word_vdp=0;
 g_trace_long_ram=0; g_trace_word_ram=0;
 g_trace_long_other=0; g_trace_word_other=0;
 t2gen_trace_rom(rom,len);
 if (len > 0xa138u)
   {
     unsigned j;
     static const uint32_t wait_pc[] = {0x00a12eu, 0x00a0e4u, 0x00a0eau, 0x006126u};
     for (j=0;j<4;j++)
       {
         unsigned k;
         printf("T2GEN V8.5 ROM %06lX:", (unsigned long)wait_pc[j]);
         for (k=0;k<12;k++) printf(" %02X",rom[wait_pc[j]+k]);
         printf("\n");
       }
     printf("T2GEN V8.5 DECODE A12E: CMP.W ($00FF03B0).L,D1; BEQ.S -8 (wait for RAM word change)\n");
     printf("T2GEN V8.5 DECODE A0E4: TST.W ($00FF0222).L; BNE.S -8 (wait for RAM word zero)\n");
   }
 g.ram=calloc(1,RAM_SIZE);
 if (!g.ram) {printf("T2GEN V4: 64KiB RAM allocation failed\n");return;}
 if (m68ki_alloc_tables() != 0)
  {
    printf("T2GEN: Musashi table allocation failed\n");
    free(g.ram);
    g.ram = NULL;
    return;
  }

  syslog(LOG_ERR,
       "Musashi instruction table: %p\n",
       (void *)m68ki_instruction_jump_table);

syslog(LOG_ERR,
       "Musashi cycle table: %p\n",
       (void *)m68ki_cycles);

printf("T2GEN: Musashi tables allocated\n");

t2gen_vdp_reset();
t2gen_vdp_set_dma_reader(genesis_dma_read16);
m68k_init();
m68k_set_cpu_type(M68K_CPU_TYPE_68000);
xbox_open();
m68k_pulse_reset();
 printf("T2GEN V4: Musashi reset PC=%06lx SP=%08lx\n",
  (unsigned long)m68k_get_reg(NULL,M68K_REG_PC),
  (unsigned long)m68k_get_reg(NULL,M68K_REG_SP));
 /* V8.4 diagnostic: approximate NTSC scanline timing (488 68K cycles
  * per scanline, 262 lines). Use a bounded run and keep IRQs conservative.
  * Interrupt line is asserted at VBlank and deasserted after a short
  * simulated interval. This is not full Genesis interrupt arbitration.
  */
 {
  const uint32_t cycles_per_line = 488u;
  const uint32_t lines_per_frame = 262u;
  const uint32_t cycle_limit = 300000000u; /* approximately 469 NTSC frames */
  uint32_t total_cycles = 0;
  uint32_t next_line_cycle = cycles_per_line;
  uint32_t line = 0;
  uint32_t last_pc = 0xffffffffu;
  uint32_t repeated_pc = 0;
  bool irq_asserted = false;
  unsigned slice = 0;
  uint32_t rendered_frames = 0;
  uint32_t failed_frames = 0;
  uint64_t cpu_us=0, render_us=0;
  struct timeval wall_start, wall_now, fps_start;
  uint32_t fps_frames = 0, fps_renders = 0;
  uint64_t fps_render_us_start = 0;
  gettimeofday(&wall_start, NULL);
  fps_start = wall_start;
  struct timeval t0,t1, cpu_t0;
  uint32_t render_max_us=0;
  printf("T2GEN V9.2: execution_limit=%lu cycles line_cycles=%lu (~%lu frames)\n",
         (unsigned long)cycle_limit, (unsigned long)cycles_per_line,
         (unsigned long)(cycle_limit / (cycles_per_line * lines_per_frame)));
  t2gen_vdp_set_scanline(0);
  while (total_cycles < cycle_limit)
    {
      uint32_t pc = m68k_get_reg(NULL, M68K_REG_PC);
      /* Time batches instead of each 488-cycle slice. */
      if ((slice & 255u)==0u) gettimeofday(&cpu_t0,NULL);
      int done = m68k_execute(488);
      if ((slice & 255u)==255u)
        {
          gettimeofday(&t1,NULL);
          cpu_us += (uint64_t)((int64_t)(t1.tv_sec-cpu_t0.tv_sec)*1000000ll +
                    (int64_t)(t1.tv_usec-cpu_t0.tv_usec));
        }
      if (done <= 0)
        {
          printf("T2GEN V7: CPU stalled slice=%u done=%d PC=%06lx\n",
                 slice, done, (unsigned long)pc);
          break;
        }
      total_cycles += (uint32_t)done;
      if (pc == last_pc)
        repeated_pc++;
      else
        repeated_pc = 0;
      last_pc = pc;
      if (0 && repeated_pc == 40u)
        {
          printf("T2GEN V7: repeated PC=%06lx opcode=%04x (sampled at slice boundaries)\n",
                 (unsigned long)pc,
                 (unsigned)m68k_read_disassembler_16(pc));
        }
      while (total_cycles >= next_line_cycle)
        {
          line = (line + 1u) % lines_per_frame;
          t2gen_vdp_set_scanline((uint16_t)line);
          if (line == 0u)
            {
              g_pad_frame++;
              fps_frames++;
              xbox_poll();
              if ((fps_frames % 300u) == 0u)
                {
                  gettimeofday(&wall_now, NULL);
                  uint64_t dt = (uint64_t)((int64_t)(wall_now.tv_sec - fps_start.tv_sec) * 1000000ll +
                                           (int64_t)(wall_now.tv_usec - fps_start.tv_usec));
                  if (dt)
                    printf("T2GEN V9.9 FPS: emu=%lu.%02lu render=%lu.%02lu (300 emulated frames)\n",
                           (unsigned long)(300000000ull / dt),
                           (unsigned long)((300000000ull % dt) * 100ull / dt),
                           (unsigned long)((uint64_t)fps_renders * 1000000ull / dt),
                           (unsigned long)(((uint64_t)fps_renders * 1000000ull % dt) * 100ull / dt));
                  printf("T2GEN V13 WINDOW: wall_ms=%llu render_ms=%llu render_share=%lu%% mode=%s\n",
                         (unsigned long long)(dt / 1000ull),
                         (unsigned long long)((render_us - fps_render_us_start) / 1000ull),
                         (unsigned long)(dt ? ((render_us - fps_render_us_start) * 100ull / dt) : 0ull),
                         fbdev ? "video" : "cpu-only");
                  fps_render_us_start = render_us;
                  fps_start = wall_now;
                  fps_renders = 0;
                }
            }
          /* V8.7: render every emulated VBlank for accurate palette
           * animation observation. No wall-clock pacing yet.
           */
          if (line == 224u && fbdev != NULL &&
              (t2gen_vdp_state()->frames % 3u) == 0u)
            {
              gettimeofday(&t0,NULL);
              int render_result=t2gen_render_snapshot(fbdev);
              gettimeofday(&t1,NULL);
              uint32_t elapsed=(uint32_t)((int64_t)(t1.tv_sec-t0.tv_sec)*1000000ll+
                                           (int64_t)(t1.tv_usec-t0.tv_usec));
              render_us += elapsed;
              if (elapsed > render_max_us) render_max_us=elapsed;
              if (render_result == 0)
                { rendered_frames++; fps_renders++; }
              else
                {
                  failed_frames++;
                  if (failed_frames <= 5u)
                    printf("T2GEN V9.8.2: render failure=%lu rc=%d; retrying\n",
                           (unsigned long)failed_frames, render_result);
                  /* Keep framebuffer path: allow CPU fallback and retry. */
                }
            }
          if (line == 224u && t2gen_vdp_irq_enabled())
            {
              m68k_set_irq(6);
              t2gen_vdp_note_irq();
              irq_asserted = true;
            }
          else if (irq_asserted && line == 225u)
            {
              m68k_set_irq(0);
              irq_asserted = false;
            }
          next_line_cycle += cycles_per_line;
        }
      if (0 && (slice % 5000u) == 0u &&
          (pc == 0x00a12eu || pc == 0x00a0e4u ||
           pc == 0x00a0eau || pc == 0x006126u))
        v85_loop_state(pc,total_cycles,slice);
      if ((slice % 50000u) == 0u || total_cycles >= cycle_limit)
        {
          printf("T2GEN V8.4: slice=%u cycles=%lu frame=%lu line=%lu PC=%06lx VDP=%lu unmapped=%lu\n",
                 slice, (unsigned long)total_cycles,
                 (unsigned long)(total_cycles / (cycles_per_line * lines_per_frame)),
                 (unsigned long)line,
                 (unsigned long)m68k_get_reg(NULL,M68K_REG_PC),
                 (unsigned long)g.vdp_writes, (unsigned long)g.unmapped);
        }
      slice++;
    }
  m68k_set_irq(0);
  gettimeofday(&wall_now, NULL);
  uint64_t wall_us = (uint64_t)((int64_t)(wall_now.tv_sec - wall_start.tv_sec) * 1000000ll +
                                (int64_t)(wall_now.tv_usec - wall_start.tv_usec));
  printf("T2GEN V13 MODE: %s\n", fbdev ? "video" : "cpu-only");
  printf("T2GEN V9.9 TOTAL: wall_ms=%llu emulated_frames=%lu rendered=%lu emu_fps=%lu.%02lu display_fps=%lu.%02lu\n",
         (unsigned long long)(wall_us / 1000ull),
         (unsigned long)(total_cycles / (cycles_per_line * lines_per_frame)),
         (unsigned long)rendered_frames,
         (unsigned long)(wall_us ? (uint64_t)(total_cycles / (cycles_per_line * lines_per_frame)) * 1000000ull / wall_us : 0),
         (unsigned long)(wall_us ? ((uint64_t)(total_cycles / (cycles_per_line * lines_per_frame)) * 1000000ull % wall_us) * 100ull / wall_us : 0),
         (unsigned long)(wall_us ? (uint64_t)rendered_frames * 1000000ull / wall_us : 0),
         (unsigned long)(wall_us ? ((uint64_t)rendered_frames * 1000000ull % wall_us) * 100ull / wall_us : 0));
  t2gen_render_print_perf();
  printf("T2GEN V9.2 PAD: reads=%lu frames=%lu data=%02x control=%02x\n",
         (unsigned long)g_pad_reads,(unsigned long)g_pad_frame,
         (unsigned)g_pad_data,(unsigned)g_pad_ctrl);
  printf("T2GEN V9.6 PERF: cpu_ms=%llu render_ms=%llu render_max_ms=%lu avg_render_ms=%lu frames=%lu\n",
         (unsigned long long)(cpu_us/1000u),
         (unsigned long long)(render_us/1000u),
         (unsigned long) (render_max_us/1000u),
         (unsigned long)(rendered_frames ? render_us/1000u/rendered_frames : 0u),
         (unsigned long)rendered_frames);
  printf("T2GEN V9.2: live_frames=%lu render_failures=%lu total_cycles=%lu\n",
         (unsigned long)rendered_frames, (unsigned long)failed_frames,
         (unsigned long)total_cycles);
 }
 printf("T2GEN V8.5: RAM watch writes=%lu; waiting loops are diagnostic only\n",
        (unsigned long)g_v85_ram_watch_count);
 printf("T2GEN V4: reads=%lu writes=%lu io=%lu vdp=%lu ctrl=%lu data=%lu first_vdp_pc=%06lx unmapped=%lu\n",
  (unsigned long)g.reads,(unsigned long)g.writes,(unsigned long)g.io_reads,
  (unsigned long)g.vdp_writes,(unsigned long)g.vdp_ctrl,(unsigned long)g.vdp_data,
  (unsigned long)g.first_vdp_pc,(unsigned long)g.unmapped);
 printf("T2GEN V8.3 BUS SUMMARY: write32=%lu nonzero=%lu vdp=%lu ram=%lu other=%lu\n",
        (unsigned long)g_trace_long_count, (unsigned long)g_trace_long_nonzero,
        (unsigned long)g_trace_long_vdp, (unsigned long)g_trace_long_ram,
        (unsigned long)g_trace_long_other);
 printf("T2GEN V8.3 BUS SUMMARY: write16=%lu nonzero=%lu vdp=%lu ram=%lu other=%lu\n",
        (unsigned long)g_trace_word_count, (unsigned long)g_trace_word_nonzero,
        (unsigned long)g_trace_word_vdp, (unsigned long)g_trace_word_ram,
        (unsigned long)g_trace_word_other);
 t2gen_vdp_dump();
 printf("T2GEN V9.1: live VBlank rendering; DMA approximate; no Z80 or audio\n");
 free(g.ram);g.ram=NULL;
}
