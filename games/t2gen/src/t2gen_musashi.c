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
#if defined(CONFIG_GAMES_T2GEN_V08_NATIVE_SYNC_CHECK) || defined(CONFIG_GAMES_T2GEN_V010_NATIVE_CMP_EXEC)
#include "t2gen_native_sync.h"
#endif
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


/* V0.3: observational per-frame trace for native-game reverse engineering.
 * Snapshot occurs on scanline wrap, before controller sampling and VBlank.
 * RAM is 68000 byte-addressed and hashed in canonical byte order.
 * Does not modify emulator execution, memory, interrupts or input.
 */
#ifdef CONFIG_GAMES_T2GEN_NATIVE_TRACE
#ifndef CONFIG_GAMES_T2GEN_NATIVE_TRACE_STRIDE
#define CONFIG_GAMES_T2GEN_NATIVE_TRACE_STRIDE 60
#endif
static uint32_t t2gen_native_ram_hash(const uint8_t *ram)
{
  uint32_t h = 2166136261u;
  for (unsigned i = 0; i < RAM_SIZE; i++)
    {
      h ^= ram[i];
      h *= 16777619u;
    }
  return h;
}

/* V0.4: deterministic, optional scripted controller stimulus.
 * Bit mapping: UP=01 DOWN=02 LEFT=04 RIGHT=08 A=10 B=20 C=40 START=80.
 * Apply at frame boundary after xbox_poll(), before next emulated frame.
 */
#ifdef CONFIG_GAMES_T2GEN_V04_SCRIPT_INPUT
static uint8_t t2gen_v04_script(uint32_t frame)
{
  if (frame >= 120u && frame < 125u) return PAD_START;
  if (frame >= 240u && frame < 360u) return PAD_RIGHT;
  if (frame >= 360u && frame < 420u) return PAD_RIGHT | PAD_B;
  if (frame >= 420u && frame < 480u) return PAD_LEFT;
  if (frame >= 480u && frame < 540u) return PAD_A;
  return 0;
}
#endif

/* Record bounded per-frame changed RAM bytes, including their offsets.
 * Output first 16 changes in ascending address order; count all changes.
 * Comparing snapshots does not alter emulated RAM.
 */
#ifdef CONFIG_GAMES_T2GEN_V04_RAM_DIFF
static uint8_t g_v04_previous_ram[RAM_SIZE];
static void t2gen_v04_ram_diff(uint32_t frame)
{
  uint32_t changes = 0;
  for (uint32_t i = 0; i < RAM_SIZE; i++)
    {
      uint8_t now = g.ram[i];
      if (g_v04_previous_ram[i] != now)
        {
          if (changes < 16u)
            printf("T2GEN V0.4 RAM: frame=%lu addr=FF%04lX old=%02X new=%02X\n",
                   (unsigned long)frame, (unsigned long)i,
                   (unsigned)g_v04_previous_ram[i], (unsigned)now);
          changes++;
          g_v04_previous_ram[i] = now;
        }
    }
  printf("T2GEN V0.4 RAM_SUM: frame=%lu changed=%lu shown=%lu\n",
         (unsigned long)frame, (unsigned long)changes,
         (unsigned long)(changes < 16u ? changes : 16u));
}
#endif

#ifdef CONFIG_GAMES_T2GEN_V04_PC_PROFILE
static uint32_t g_v04_pc_hits[4];
static const uint32_t g_v04_pc_targets[4] =
  {0x00a12eu, 0x00a134u, 0x006120u, 0x006126u};
static void t2gen_v04_pc_sample(uint32_t pc)
{
  for (unsigned i = 0; i < 4; i++)
    if (pc == g_v04_pc_targets[i]) g_v04_pc_hits[i]++;
}
static void t2gen_v04_pc_report(uint32_t frame)
{
  printf("T2GEN V0.4 PC: frame=%lu A12E=%lu A134=%lu 6120=%lu 6126=%lu\n",
         (unsigned long)frame,
         (unsigned long)g_v04_pc_hits[0],
         (unsigned long)g_v04_pc_hits[1],
         (unsigned long)g_v04_pc_hits[2],
         (unsigned long)g_v04_pc_hits[3]);
  memset(g_v04_pc_hits, 0, sizeof(g_v04_pc_hits));
}
#endif

static void t2gen_native_trace_frame(uint32_t frame, uint32_t cycles)
{
  if ((frame % CONFIG_GAMES_T2GEN_NATIVE_TRACE_STRIDE) != 0u)
    return;
  printf("T2GEN V0.3 REF: frame=%lu cycles=%lu PC=%08lx SR=%04lx "
         "D0=%08lx D1=%08lx A0=%08lx A7=%08lx "
         "RAM_FNV=%08lx VDP_WR=%lu PAD=%02x\n",
         (unsigned long)frame, (unsigned long)cycles,
         (unsigned long)m68k_get_reg(NULL, M68K_REG_PC),
         (unsigned long)m68k_get_reg(NULL, M68K_REG_SR),
         (unsigned long)m68k_get_reg(NULL, M68K_REG_D0),
         (unsigned long)m68k_get_reg(NULL, M68K_REG_D1),
         (unsigned long)m68k_get_reg(NULL, M68K_REG_A0),
         (unsigned long)m68k_get_reg(NULL, M68K_REG_A7),
         (unsigned long)t2gen_native_ram_hash(g.ram),
         (unsigned long)g.vdp_writes, (unsigned)g_buttons);
}
#endif


/* V0.5: instruction-accurate target observation. No serial I/O inside
 * Musashi's instruction callback: bounded ring of 32 observations.
 * The callback sees the PC before executing that instruction.
 */
#ifdef CONFIG_GAMES_T2GEN_V05_TARGET_TRACE
#define V05_OBS_MAX 32u
struct v05_obs_s
{
  uint32_t frame, pc, d0, d1, a0, a7;
  uint16_t sr, ram03b0, ram0222;
  uint8_t pad;
};
static struct v05_obs_s g_v05_obs[V05_OBS_MAX];
static uint32_t g_v05_count;
static uint32_t g_v05_total[6];
static const uint32_t g_v05_target[6] =
  {0x00a12eu, 0x00a134u, 0x006120u, 0x006126u, 0x00a0e4u, 0x00dffeu};
static void t2gen_v05_hook(unsigned int pc)
{
  for (unsigned j = 0; j < 6; j++)
    {
      if (pc != g_v05_target[j]) continue;
      g_v05_total[j]++;
      if (g_v05_count >= V05_OBS_MAX) return;
      struct v05_obs_s *o = &g_v05_obs[g_v05_count++];
      o->frame = g_pad_frame;
      o->pc = pc;
      o->d0 = m68k_get_reg(NULL, M68K_REG_D0);
      o->d1 = m68k_get_reg(NULL, M68K_REG_D1);
      o->a0 = m68k_get_reg(NULL, M68K_REG_A0);
      o->a7 = m68k_get_reg(NULL, M68K_REG_A7);
      o->sr = (uint16_t)m68k_get_reg(NULL, M68K_REG_SR);
      o->ram03b0 = ((uint16_t)g.ram[0x03b0] << 8) | g.ram[0x03b1];
      o->ram0222 = ((uint16_t)g.ram[0x0222] << 8) | g.ram[0x0223];
      o->pad = g_buttons;
      return;
    }
}
static void t2gen_v05_report(void)
{
  for (uint32_t i = 0; i < g_v05_count; i++)
    {
      const struct v05_obs_s *o = &g_v05_obs[i];
      printf("T2GEN V0.5 TARGET: frame=%lu PC=%06lx D0=%08lx D1=%08lx "
             "A0=%08lx A7=%08lx SR=%04x RAM03B0=%04x RAM0222=%04x PAD=%02x\n",
             (unsigned long)o->frame, (unsigned long)o->pc,
             (unsigned long)o->d0, (unsigned long)o->d1,
             (unsigned long)o->a0, (unsigned long)o->a7,
             (unsigned)o->sr, (unsigned)o->ram03b0,
             (unsigned)o->ram0222, (unsigned)o->pad);
    }
  printf("T2GEN V0.5 TARGET_COUNTS: A12E=%lu A134=%lu 6120=%lu "
         "6126=%lu A0E4=%lu DFFE=%lu captured=%lu\n",
         (unsigned long)g_v05_total[0], (unsigned long)g_v05_total[1],
         (unsigned long)g_v05_total[2], (unsigned long)g_v05_total[3],
         (unsigned long)g_v05_total[4], (unsigned long)g_v05_total[5],
         (unsigned long)g_v05_count);
}
#endif

/* V0.6: bounded transition tracing. Capture before execution, never print
 * from Musashi's instruction callback. prev_pc is the previous instruction
 * observed, NOT necessarily a caller or return address.
 */
#ifdef CONFIG_GAMES_T2GEN_V06_FLOW_TRACE
#define V06_TARGETS 6u
#define V06_MAX_EVENTS 96u
#define V06_PER_TARGET_PHASE 4u
struct v06_event_s
{
  uint32_t frame, prev_pc, pc, d0, d1, a0, a7;
  uint16_t sr, sync03b0, sync0222, stack0;
  uint8_t phase, target, kind, pad;
};
static struct v06_event_s g_v06_events[V06_MAX_EVENTS];
static uint8_t g_v06_limits[3][V06_TARGETS][2];
static uint32_t g_v06_n, g_v06_prev_pc;
static bool g_v06_have_prev;
static uint32_t g_v06_entry[V06_TARGETS], g_v06_exit[V06_TARGETS];
static const uint32_t g_v06_targets[V06_TARGETS] =
  {0xa12eu, 0xa134u, 0x6120u, 0x6126u, 0xa0e4u, 0xdffeu};
static int t2gen_v06_index(uint32_t pc)
{
  for (unsigned i = 0; i < V06_TARGETS; i++)
    if (pc == g_v06_targets[i]) return (int)i;
  return -1;
}
static unsigned t2gen_v06_phase(uint32_t frame)
{
  if (frame < 60u) return 0u;
  if (frame >= 1320u && frame < 1500u) return 1u;
  return 2u;
}
static void t2gen_v06_capture(unsigned phase, unsigned target,
                             unsigned kind, uint32_t prev, uint32_t pc)
{
  struct v06_event_s *e;
  uint32_t sp;
  if (g_v06_n >= V06_MAX_EVENTS ||
      g_v06_limits[phase][target][kind] >= V06_PER_TARGET_PHASE)
    return;
  g_v06_limits[phase][target][kind]++;
  e = &g_v06_events[g_v06_n++];
  e->frame = g_pad_frame;
  e->prev_pc = prev;
  e->pc = pc;
  e->phase = (uint8_t)phase;
  e->target = (uint8_t)target;
  e->kind = (uint8_t)kind;
  e->pad = g_buttons;
  e->d0 = m68k_get_reg(NULL, M68K_REG_D0);
  e->d1 = m68k_get_reg(NULL, M68K_REG_D1);
  e->a0 = m68k_get_reg(NULL, M68K_REG_A0);
  e->a7 = m68k_get_reg(NULL, M68K_REG_A7);
  e->sr = (uint16_t)m68k_get_reg(NULL, M68K_REG_SR);
  e->sync03b0 = ((uint16_t)g.ram[0x3b0] << 8) | g.ram[0x3b1];
  e->sync0222 = ((uint16_t)g.ram[0x222] << 8) | g.ram[0x223];
  sp = e->a7;
  e->stack0 = ((sp & 0xff0000u) == 0xff0000u &&
               (sp & 0xffffu) != 0xffffu) ?
    (uint16_t)(((uint16_t)g.ram[sp & 0xffffu] << 8) |
                g.ram[(sp + 1u) & 0xffffu]) : 0xffffu;
}
static void t2gen_v06_hook(unsigned int pc)
{
  int now = t2gen_v06_index(pc);
  int before = g_v06_have_prev ? t2gen_v06_index(g_v06_prev_pc) : -1;
  unsigned phase = t2gen_v06_phase(g_pad_frame);
#ifdef CONFIG_GAMES_T2GEN_V05_TARGET_TRACE
  t2gen_v05_hook(pc);
#endif
  if (now >= 0 && before != now)
    {
      g_v06_entry[now]++;
      t2gen_v06_capture(phase, (unsigned)now, 0u, g_v06_prev_pc, pc);
    }
  if (before >= 0 && now != before)
    {
      g_v06_exit[before]++;
      t2gen_v06_capture(phase, (unsigned)before, 1u, g_v06_prev_pc, pc);
    }
  g_v06_prev_pc = pc;
  g_v06_have_prev = true;
}
static void t2gen_v06_report(void)
{
  for (uint32_t i = 0; i < g_v06_n; i++)
    {
      const struct v06_event_s *e = &g_v06_events[i];
      printf("T2GEN V0.6 FLOW: phase=%u frame=%lu target=%06lx "
             "kind=%s prev=%06lx pc=%06lx D0=%08lx D1=%08lx "
             "A0=%08lx A7=%08lx SR=%04x SP_W=%04x "
             "FF03B0=%04x FF0222=%04x PAD=%02x\n",
             (unsigned)e->phase, (unsigned long)e->frame,
             (unsigned long)g_v06_targets[e->target],
             e->kind ? "EXIT" : "ENTER",
             (unsigned long)e->prev_pc, (unsigned long)e->pc,
             (unsigned long)e->d0, (unsigned long)e->d1,
             (unsigned long)e->a0, (unsigned long)e->a7,
             (unsigned)e->sr, (unsigned)e->stack0,
             (unsigned)e->sync03b0, (unsigned)e->sync0222,
             (unsigned)e->pad);
    }
  for (unsigned i = 0; i < V06_TARGETS; i++)
    printf("T2GEN V0.6 COUNTS: target=%06lx enter=%lu exit=%lu\n",
           (unsigned long)g_v06_targets[i],
           (unsigned long)g_v06_entry[i],
           (unsigned long)g_v06_exit[i]);
  printf("T2GEN V0.6 SUMMARY: captured=%lu max=%u "
         "phase0=frames0..59 phase1=1320..1499 phase2=other\n",
         (unsigned long)g_v06_n, V06_MAX_EVENTS);
}
#endif

/* V0.7: completed polling-loop episodes. No serial I/O in the hook.
 * A loop episode begins at its comparison instruction and completes only
 * when execution reaches the corresponding RTS. An IRQ or other detour is
 * treated as a suspension, not as proof that the loop completed.
 * Branches are counted by observing the compare->branch->compare sequence.
 */
#ifdef CONFIG_GAMES_T2GEN_V07_EPISODES
#define V07_NLOOPS 3u
#define V07_PHASES 3u
#define V07_PER_PHASE 12u
#define V07_MAX_EVENTS (V07_NLOOPS * V07_PHASES * V07_PER_PHASE)
struct v07_episode_s
{
  uint32_t frame_begin, frame_end, pc_before, pc_after;
  uint32_t iterations, d0, d1, a7, return_pc;
  uint16_t sync_begin, sync_end, sr;
  uint8_t loop, phase, pad, return_valid;
};
static const uint32_t g_v07_cmp[V07_NLOOPS] = {0xa12eu, 0x6120u, 0xa0e4u};
static const uint32_t g_v07_branch[V07_NLOOPS] = {0xa134u, 0x6126u, 0xa0eau};
static const uint32_t g_v07_rts[V07_NLOOPS] = {0xa136u, 0x6128u, 0xa0ecu};
static struct v07_episode_s g_v07_events[V07_MAX_EVENTS];
static struct v07_episode_s g_v07_active[V07_NLOOPS];
static uint32_t g_v07_started[V07_NLOOPS], g_v07_completed[V07_NLOOPS];
static uint32_t g_v07_incomplete[V07_NLOOPS], g_v07_n;
static uint8_t g_v07_quota[V07_PHASES][V07_NLOOPS];
static bool g_v07_live[V07_NLOOPS];
static uint32_t g_v07_prev;
static bool g_v07_prev_valid;
static uint16_t t2gen_v07_word(unsigned off)
{
  return ((uint16_t)g.ram[off] << 8) | g.ram[off + 1u];
}
static uint16_t t2gen_v07_sync(unsigned loop)
{
  return t2gen_v07_word(loop == 2u ? 0x222u : 0x3b0u);
}
static unsigned t2gen_v07_phase(uint32_t frame)
{
  if (frame < 60u) return 0u;
  if (frame >= 1320u && frame < 1500u) return 1u;
  return 2u;
}
static void t2gen_v07_hook(unsigned int pc)
{
  unsigned i;
#ifdef CONFIG_GAMES_T2GEN_V05_TARGET_TRACE
  t2gen_v05_hook(pc);
#endif
  for (i = 0; i < V07_NLOOPS; i++)
    {
      struct v07_episode_s *e = &g_v07_active[i];
      if (pc == g_v07_cmp[i] && !g_v07_live[i])
        {
          memset(e, 0, sizeof(*e));
          e->loop = (uint8_t)i;
          e->phase = (uint8_t)t2gen_v07_phase(g_pad_frame);
          e->frame_begin = g_pad_frame;
          e->pc_before = g_v07_prev_valid ? g_v07_prev : 0xffffffffu;
          e->sync_begin = t2gen_v07_sync(i);
          e->d0 = m68k_get_reg(NULL, M68K_REG_D0);
          e->d1 = m68k_get_reg(NULL, M68K_REG_D1);
          e->a7 = m68k_get_reg(NULL, M68K_REG_A7);
          e->pad = g_buttons;
          g_v07_live[i] = true;
          g_v07_started[i]++;
        }
      else if (pc == g_v07_cmp[i] && g_v07_live[i] &&
               g_v07_prev_valid && g_v07_prev == g_v07_branch[i])
        {
          if (e->iterations != UINT32_MAX) e->iterations++;
        }
      else if (pc == g_v07_rts[i] && g_v07_live[i])
        {
          uint32_t sp = m68k_get_reg(NULL, M68K_REG_A7);
          e->frame_end = g_pad_frame;
          e->pc_after = pc;
          e->sync_end = t2gen_v07_sync(i);
          e->sr = (uint16_t)m68k_get_reg(NULL, M68K_REG_SR);
          /* Return address is a 32-bit big-endian stack value. */
          if ((sp & 0xff0000u) == 0xff0000u &&
              (sp & 0xffffu) <= 0xfffcu)
            {
              unsigned off = sp & 0xffffu;
              e->return_pc = ((uint32_t)g.ram[off] << 24) |
                             ((uint32_t)g.ram[off+1u] << 16) |
                             ((uint32_t)g.ram[off+2u] << 8) |
                             (uint32_t)g.ram[off+3u];
              e->return_valid = 1u;
            }
          if (g_v07_quota[e->phase][i] < V07_PER_PHASE &&
              g_v07_n < V07_MAX_EVENTS)
            {
              g_v07_events[g_v07_n++] = *e;
              g_v07_quota[e->phase][i]++;
            }
          g_v07_completed[i]++;
          g_v07_live[i] = false;
        }
    }
  g_v07_prev = pc;
  g_v07_prev_valid = true;
}
static void t2gen_v07_report(void)
{
  uint32_t n;
  for (n = 0; n < g_v07_n; n++)
    {
      const struct v07_episode_s *e = &g_v07_events[n];
      printf("T2GEN V0.7 EPISODE: loop=%06lx phase=%u "
             "begin=%lu end=%lu prev=%06lx rts=%06lx "
             "repeats=%lu sync=%04x->%04x D0=%08lx D1=%08lx "
             "A7=%08lx SR=%04x ret=%08lx valid=%u PAD=%02x\n",
             (unsigned long)g_v07_cmp[e->loop], (unsigned)e->phase,
             (unsigned long)e->frame_begin, (unsigned long)e->frame_end,
             (unsigned long)e->pc_before, (unsigned long)e->pc_after,
             (unsigned long)e->iterations, (unsigned)e->sync_begin,
             (unsigned)e->sync_end, (unsigned long)e->d0,
             (unsigned long)e->d1, (unsigned long)e->a7,
             (unsigned)e->sr, (unsigned long)e->return_pc,
             (unsigned)e->return_valid, (unsigned)e->pad);
    }
  for (unsigned i = 0; i < V07_NLOOPS; i++)
    {
      g_v07_incomplete[i] = g_v07_started[i] - g_v07_completed[i];
      printf("T2GEN V0.7 COUNTS: loop=%06lx started=%lu "
             "completed=%lu incomplete=%lu\n",
             (unsigned long)g_v07_cmp[i],
             (unsigned long)g_v07_started[i],
             (unsigned long)g_v07_completed[i],
             (unsigned long)g_v07_incomplete[i]);
    }
  printf("T2GEN V0.7 SUMMARY: captured=%lu capacity=%u\n",
         (unsigned long)g_v07_n, V07_MAX_EVENTS);
}
#endif


#ifdef CONFIG_GAMES_T2GEN_V08_NATIVE_SYNC_CHECK
/* V0.8.1: predict at CMP/TST entry, verify after execution at branch.
 * Hook is called before instruction execution. No Musashi state changes. */
#define V081_SAMPLES 6u
struct v081_sample_s
{
  uint32_t pc, frame, dn;
  uint16_t mem, sr_before, sr_after, predicted_ccr;
  uint8_t predicted_taken, actual_taken;
};
struct v081_check_s
{
  uint32_t predicted, compared, flags_mismatch, branch_mismatch;
  uint32_t branch_checked, branch_unresolved, missing_branch;
  uint32_t cmp_discontinuity, branch_discontinuity, irq_like, other_jump;
  uint32_t first_discontinuity_pc, first_discontinuity_sr, first_discontinuity_sp;
  uint32_t sample_count;
  struct v081_sample_s samples[V081_SAMPLES];
};
static struct v081_check_s g_v081_check[3];
static struct v081_sample_s g_v081_pending_sample[3];
static uint8_t g_v081_pending_compare[3];
static uint8_t g_v081_pending_branch[3];
/* V0.9 records discontinuities without changing original execution. */
static void t2gen_v09_discontinuity(struct v081_check_s *c,
                                    unsigned int pc, bool from_branch)
{
  uint16_t sr = (uint16_t)m68k_get_reg(NULL, M68K_REG_SR);
  uint32_t sp = m68k_get_reg(NULL, M68K_REG_SP);
  if (from_branch) c->branch_discontinuity++;
  else c->cmp_discontinuity++;
  /* A supervisor stack change and a new PC are IRQ-like, not proof of IRQ. */
  if ((sr & 0x2000u) && (pc < 0x100000u)) c->irq_like++;
  else c->other_jump++;
  if (!c->first_discontinuity_pc)
    {
      c->first_discontinuity_pc = pc;
      c->first_discontinuity_sr = sr;
      c->first_discontinuity_sp = sp;
    }
}

static void t2gen_v08_hook(unsigned int pc)
{
  unsigned i;
  for (i = 0; i < 3; i++)
    {
      struct v081_check_s *c = &g_v081_check[i];
      struct v081_sample_s *s = &g_v081_pending_sample[i];
      uint32_t cmp = g_v07_cmp[i];
      uint32_t branch = g_v07_branch[i];
      uint32_t rts = g_v07_rts[i];

      /* Validate the branch successor before handling a new comparison. */
      if (g_v081_pending_branch[i])
        {
          if (pc == cmp || pc == rts)
            {
              uint8_t actual = (uint8_t)(pc == cmp);
              c->branch_checked++;
              if (actual != s->predicted_taken)
                {
                  c->branch_mismatch++;
                  s->actual_taken = actual;
                  if (c->sample_count < V081_SAMPLES)
                    c->samples[c->sample_count++] = *s;
                }
            }
          else
            {
              c->branch_unresolved++; /* interrupt or unusual control flow */
              t2gen_v09_discontinuity(c, pc, true);
            }
          g_v081_pending_branch[i] = 0;
        }

      if (pc == branch && g_v081_pending_compare[i])
        {
          uint16_t sr = (uint16_t)m68k_get_reg(NULL, M68K_REG_SR);
          c->compared++;
          s->sr_after = sr;
          if ((sr & 0x1fu) != s->predicted_ccr)
            {
              c->flags_mismatch++;
              if (c->sample_count < V081_SAMPLES)
                c->samples[c->sample_count++] = *s;
            }
          g_v081_pending_compare[i] = 0;
          g_v081_pending_branch[i] = 1;
        }
      else if (pc == cmp)
        {
          uint16_t sr = (uint16_t)m68k_get_reg(NULL, M68K_REG_SR);
          uint32_t dn = (i == 0u) ? m68k_get_reg(NULL, M68K_REG_D1) :
                        m68k_get_reg(NULL, M68K_REG_D0);
          uint16_t w = t2gen_v07_sync(i);
          struct t2n_sync_result r = (i == 2u) ?
            t2n_tst_word(w, sr) : t2n_cmp_word(dn, w, sr);
          if (g_v081_pending_compare[i]) c->missing_branch++;
          s->pc = pc;
          s->frame = g_pad_frame;
          s->dn = dn;
          s->mem = w;
          s->sr_before = sr;
          s->sr_after = 0;
          s->predicted_ccr = r.ccr;
          s->predicted_taken = r.branch_taken;
          s->actual_taken = 0xffu;
          g_v081_pending_compare[i] = 1;
          c->predicted++;
        }
      else if (g_v081_pending_compare[i] && pc != branch)
        {
          /* Not a normal CMP/TST -> branch sequence (IRQ or detour). */
          g_v081_pending_compare[i] = 0;
          c->missing_branch++;
          t2gen_v09_discontinuity(c, pc, false);
        }
    }
  t2gen_v07_hook(pc);
}
#ifdef CONFIG_GAMES_T2GEN_V010_NATIVE_CMP_EXEC
extern unsigned long t2gen_v010_native_cmp_count(void);
#ifdef CONFIG_GAMES_T2GEN_V011_NATIVE_SYNC_EXEC
extern unsigned long t2gen_v011_native_cmp_d0_count(void);
extern unsigned long t2gen_v011_native_tst_count(void);
#ifdef CONFIG_GAMES_T2GEN_V015_PAIRED_SYNC
extern unsigned long t2gen_v016_paired_count(unsigned int i);
extern unsigned long t2gen_v016_paired_fallback(unsigned int i);
#endif
#ifdef CONFIG_GAMES_T2GEN_V018_ROUTINE_DISPATCH
#ifdef T2GEN_V022_PC_PROFILE
extern unsigned long t2gen_v022_total(void);
extern unsigned long t2gen_v022_overflow(void);
extern unsigned long t2gen_v022_opcode_count(unsigned int kind);
extern unsigned int t2gen_v022_top(unsigned int rank, unsigned long *pc,
                                  unsigned int *opcode, unsigned long *count);
#endif
#ifdef T2GEN_V021_OPCODE_PROFILE
extern unsigned long t2gen_v021_total(void);
extern unsigned long t2gen_v021_overflow(void);
extern unsigned long t2gen_v021_group(unsigned int i);
extern unsigned int t2gen_v021_top(unsigned int rank, unsigned int *opcode,
                                  unsigned long *count);
#endif
#ifdef T2GEN_V020_DIRECT_BRANCH
extern unsigned long t2gen_v020_direct_count(unsigned int i);
extern unsigned long t2gen_v020_fallback_count(unsigned int i);
#endif
#ifdef T2GEN_V019_PREDECODED_SYNC
extern unsigned long t2gen_v019_fast_count(unsigned int i);
extern unsigned long t2gen_v019_fallback_count(unsigned int i);
#endif
extern unsigned long t2gen_v018_followup_count(unsigned int i);
extern unsigned long t2gen_v018_exit_count(unsigned int i);
#endif
#ifdef CONFIG_GAMES_T2GEN_V017_NATIVE_SYNC_RTS
extern unsigned long t2gen_v017_rts_count(unsigned int i);
#endif
#ifdef CONFIG_GAMES_T2GEN_V012_NATIVE_BRANCH_EXEC
extern unsigned long t2gen_v012_branch_count(unsigned int i);
extern unsigned long t2gen_v012_branch_taken(unsigned int i);
#endif
#endif
#endif
static void t2gen_v08_report(void)
{

  unsigned i, j;
  for (i = 0; i < 3; i++)
    {
      struct v081_check_s *c = &g_v081_check[i];
      printf("T2GEN V0.8.1 NATIVE_CHECK: loop=%06lx predicted=%lu compared=%lu flags_mismatch=%lu branch_checked=%lu branch_mismatch=%lu branch_unresolved=%lu missing_branch=%lu\n",
             (unsigned long)g_v07_cmp[i],
             (unsigned long)c->predicted, (unsigned long)c->compared,
             (unsigned long)c->flags_mismatch, (unsigned long)c->branch_checked,
             (unsigned long)c->branch_mismatch,
             (unsigned long)c->branch_unresolved,
             (unsigned long)c->missing_branch);
      printf("T2GEN V0.9 DISCONTINUITY: loop=%06lx cmp=%lu branch=%lu irq_like=%lu other=%lu first_pc=%06lx first_sr=%04lx first_sp=%08lx\n",
             (unsigned long)g_v07_cmp[i],
             (unsigned long)c->cmp_discontinuity,
             (unsigned long)c->branch_discontinuity,
             (unsigned long)c->irq_like, (unsigned long)c->other_jump,
             (unsigned long)c->first_discontinuity_pc,
             (unsigned long)c->first_discontinuity_sr,
             (unsigned long)c->first_discontinuity_sp);
      for (j = 0; j < c->sample_count; j++)
        {
          const struct v081_sample_s *s = &c->samples[j];
          printf("T2GEN V0.8.1 MISMATCH: loop=%06lx frame=%lu pc=%06lx dn=%08lx mem=%04x sr_before=%04x sr_after=%04x expected_ccr=%02x expected_branch=%u actual_branch=%u\n",
                 (unsigned long)g_v07_cmp[i], (unsigned long)s->frame,
                 (unsigned long)s->pc, (unsigned long)s->dn,
                 (unsigned)s->mem, (unsigned)s->sr_before,
                 (unsigned)s->sr_after, (unsigned)s->predicted_ccr,
                 (unsigned)s->predicted_taken, (unsigned)s->actual_taken);
        }
    }
}
#endif

#ifdef T2GEN_V025_NATIVE_MOVEQ
extern unsigned long t2gen_v025_moveq_count(void);
extern unsigned long t2gen_v025_moveq_negative(void);
extern unsigned long t2gen_v025_moveq_zero(void);
#endif

/* V0.23 reporting must not depend on V0.8's optional diagnostics. */
#ifdef T2GEN_V024_NATIVE_DBF
extern unsigned long t2gen_v024_dbf_count(void);
extern unsigned long t2gen_v024_dbf_taken(void);
extern unsigned long t2gen_v024_dbf_expired(void);
#endif
#ifdef T2GEN_V023_NATIVE_5670
extern unsigned long t2gen_v023_tst_count(void);
extern unsigned long t2gen_v023_beq_count(void);
extern unsigned long t2gen_v023_beq_taken(void);
extern unsigned long t2gen_v023_fallback(unsigned int i);

static void t2gen_v023_report(void)
{
  printf("T2GEN V0.23 NATIVE_5670: tst=%lu beq=%lu taken=%lu fallback_tst=%lu fallback_beq=%lu\n",
         t2gen_v023_tst_count(), t2gen_v023_beq_count(),
         t2gen_v023_beq_taken(), t2gen_v023_fallback(0),
         t2gen_v023_fallback(1));
}
#endif

/* V0.5: observe a few candidate game-state words on each trace interval.
 * Values are hypotheses, not confirmed player coordinates or game state.
 */
#ifdef CONFIG_GAMES_T2GEN_V05_RAM_WORDS
static uint16_t t2gen_v05_ram16(unsigned offset)
{
  return ((uint16_t)g.ram[offset] << 8) | g.ram[offset + 1u];
}
static void t2gen_v05_ram_words(uint32_t frame)
{
  printf("T2GEN V0.5 WORDS: frame=%lu FF0006=%04x FF0112=%04x "
         "FF0156=%04x FF0222=%04x FF029C=%04x FF03B0=%04x "
         "FF03B8=%04x FF03BC=%04x FF2BCD=%04x\n",
         (unsigned long)frame,
         (unsigned)t2gen_v05_ram16(0x0006),
         (unsigned)t2gen_v05_ram16(0x0112),
         (unsigned)t2gen_v05_ram16(0x0156),
         (unsigned)t2gen_v05_ram16(0x0222),
         (unsigned)t2gen_v05_ram16(0x029c),
         (unsigned)t2gen_v05_ram16(0x03b0),
         (unsigned)t2gen_v05_ram16(0x03b8),
         (unsigned)t2gen_v05_ram16(0x03bc),
         (unsigned)t2gen_v05_ram16(0x2bcd));
}
#endif

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
#ifdef CONFIG_GAMES_T2GEN_V05_TARGET_TRACE
 memset(g_v05_total, 0, sizeof(g_v05_total));
 g_v05_count = 0;
#if !defined(CONFIG_GAMES_T2GEN_V06_FLOW_TRACE) && !defined(CONFIG_GAMES_T2GEN_V07_EPISODES)
 m68k_set_instr_hook_callback(t2gen_v05_hook);
#endif
#endif
#if defined(CONFIG_GAMES_T2GEN_V06_FLOW_TRACE) && !defined(CONFIG_GAMES_T2GEN_V07_EPISODES)
 memset(g_v06_limits, 0, sizeof(g_v06_limits));
 memset(g_v06_entry, 0, sizeof(g_v06_entry));
 memset(g_v06_exit, 0, sizeof(g_v06_exit));
 g_v06_n = 0;
 g_v06_have_prev = false;
 m68k_set_instr_hook_callback(t2gen_v06_hook);
#endif
#ifdef CONFIG_GAMES_T2GEN_V07_EPISODES
 memset(g_v07_started, 0, sizeof(g_v07_started));
 memset(g_v07_completed, 0, sizeof(g_v07_completed));
 memset(g_v07_quota, 0, sizeof(g_v07_quota));
 memset(g_v07_live, 0, sizeof(g_v07_live));
 g_v07_n = 0;
 g_v07_prev_valid = false;
#ifdef CONFIG_GAMES_T2GEN_V08_NATIVE_SYNC_CHECK
 memset(g_v081_check, 0, sizeof(g_v081_check));
 memset(g_v081_pending_sample, 0, sizeof(g_v081_pending_sample));
 memset(g_v081_pending_compare, 0, sizeof(g_v081_pending_compare));
 memset(g_v081_pending_branch, 0, sizeof(g_v081_pending_branch));
 m68k_set_instr_hook_callback(t2gen_v08_hook);
#else
 m68k_set_instr_hook_callback(t2gen_v07_hook);
#endif
#endif
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
#ifdef CONFIG_GAMES_T2GEN_V04_PC_PROFILE
      t2gen_v04_pc_sample(pc);
#endif
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
#ifdef CONFIG_GAMES_T2GEN_V04_SCRIPT_INPUT
              g_buttons = t2gen_v04_script(g_pad_frame);
#endif
#ifdef CONFIG_GAMES_T2GEN_NATIVE_TRACE
              t2gen_native_trace_frame(g_pad_frame, total_cycles);
#endif
#ifdef CONFIG_GAMES_T2GEN_V05_RAM_WORDS
              if ((g_pad_frame % CONFIG_GAMES_T2GEN_V05_INTERVAL) == 0u)
                t2gen_v05_ram_words(g_pad_frame);
#endif
#if defined(CONFIG_GAMES_T2GEN_V04_RAM_DIFF) || defined(CONFIG_GAMES_T2GEN_V04_PC_PROFILE)
              if ((g_pad_frame % CONFIG_GAMES_T2GEN_V04_INTERVAL) == 0u)
                {
#ifdef CONFIG_GAMES_T2GEN_V04_RAM_DIFF
                  t2gen_v04_ram_diff(g_pad_frame);
#endif
#ifdef CONFIG_GAMES_T2GEN_V04_PC_PROFILE
                  t2gen_v04_pc_report(g_pad_frame);
#endif
                }
#endif
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
#ifdef T2GEN_V022_PC_PROFILE
  {
    static const unsigned int tracked[4] = {0x4a79, 0x67f8, 0x51c8, 0x51cf};
    unsigned int i, op;
    unsigned long pc, count;
    printf("T2GEN V0.22 PC_PROFILE: total=%lu overflow=%lu\n",
           t2gen_v022_total(), t2gen_v022_overflow());
    for (i = 0; i < 4; i++)
      printf("T2GEN V0.22 OPCODE: opcode=%04X count=%lu\n",
             tracked[i], t2gen_v022_opcode_count(i));
    for (i = 0; i < 32; i++)
      if (t2gen_v022_top(i, &pc, &op, &count))
        printf("T2GEN V0.22 HOT_PC: rank=%u pc=%06lX opcode=%04X count=%lu\n",
               i + 1, pc, op, count);
  }
#endif
#ifdef T2GEN_V021_OPCODE_PROFILE
  {
    unsigned int i, opcode;
    unsigned long count;
    printf("T2GEN V0.21 PROFILE: total=%lu overflow=%lu\n",
           t2gen_v021_total(), t2gen_v021_overflow());
    for (i = 0; i < 16; i++)
      printf("T2GEN V0.21 GROUP: high_nibble=%X count=%lu\n",
             i, t2gen_v021_group(i));
    for (i = 0; i < 24; i++)
      if (t2gen_v021_top(i, &opcode, &count))
        printf("T2GEN V0.21 TOP: rank=%u opcode=%04X count=%lu\n",
               i + 1, opcode, count);
  }
#endif
#ifdef CONFIG_GAMES_T2GEN_V05_TARGET_TRACE
  m68k_set_instr_hook_callback(NULL);
  t2gen_v05_report();
#endif
#if defined(CONFIG_GAMES_T2GEN_V06_FLOW_TRACE) && !defined(CONFIG_GAMES_T2GEN_V07_EPISODES)
  m68k_set_instr_hook_callback(NULL);
  t2gen_v06_report();
#endif
#ifdef CONFIG_GAMES_T2GEN_V07_EPISODES
  m68k_set_instr_hook_callback(NULL);
  t2gen_v07_report();
#ifdef CONFIG_GAMES_T2GEN_V08_NATIVE_SYNC_CHECK
  t2gen_v08_report();
#endif /* V08 checker */
#endif /* V07 episodes */
#ifdef T2GEN_V023_NATIVE_5670
  t2gen_v023_report();
#endif
#ifdef T2GEN_V025_NATIVE_MOVEQ
  printf("T2GEN V0.25 NATIVE_MOVEQ: executed=%lu negative=%lu zero=%lu\n",
         t2gen_v025_moveq_count(), t2gen_v025_moveq_negative(),
         t2gen_v025_moveq_zero());
#endif
#ifdef T2GEN_V024_NATIVE_DBF
  printf("T2GEN V0.24 NATIVE_DBF: executed=%lu taken=%lu expired=%lu\n",
         t2gen_v024_dbf_count(), t2gen_v024_dbf_taken(),
         t2gen_v024_dbf_expired());
#endif
#ifdef CONFIG_GAMES_T2GEN_V010_NATIVE_CMP_EXEC
  printf("T2GEN V0.10 NATIVE_EXEC: cmp_a12e=%lu\n",
         t2gen_v010_native_cmp_count());
#ifdef CONFIG_GAMES_T2GEN_V011_NATIVE_SYNC_EXEC
  printf("T2GEN V0.11 NATIVE_EXEC: cmp_6120=%lu tst_a0e4=%lu\n",
         t2gen_v011_native_cmp_d0_count(), t2gen_v011_native_tst_count());
#ifdef CONFIG_GAMES_T2GEN_V012_NATIVE_BRANCH_EXEC
  printf("T2GEN V0.12 NATIVE_BRANCH: a134=%lu taken=%lu 6126=%lu taken=%lu a0ea=%lu taken=%lu\n",
         t2gen_v012_branch_count(0), t2gen_v012_branch_taken(0),
         t2gen_v012_branch_count(1), t2gen_v012_branch_taken(1),
         t2gen_v012_branch_count(2), t2gen_v012_branch_taken(2));
#endif
#ifdef T2GEN_V020_DIRECT_BRANCH
  printf("T2GEN V0.20 DIRECT: a134=%lu fallback=%lu 6126=%lu fallback=%lu a0ea=%lu fallback=%lu\n",
         t2gen_v020_direct_count(0), t2gen_v020_fallback_count(0),
         t2gen_v020_direct_count(1), t2gen_v020_fallback_count(1),
         t2gen_v020_direct_count(2), t2gen_v020_fallback_count(2));
#endif
#ifdef T2GEN_V019_PREDECODED_SYNC
  printf("T2GEN V0.19 PREDECODE: a134=%lu fallback=%lu 6126=%lu fallback=%lu a0ea=%lu fallback=%lu\n",
         t2gen_v019_fast_count(0), t2gen_v019_fallback_count(0),
         t2gen_v019_fast_count(1), t2gen_v019_fallback_count(1),
         t2gen_v019_fast_count(2), t2gen_v019_fallback_count(2));
#endif
#ifdef CONFIG_GAMES_T2GEN_V018_ROUTINE_DISPATCH
  printf("T2GEN V0.18 ROUTINE: a12e=%lu exit=%lu 6120=%lu exit=%lu a0e4=%lu exit=%lu\n",
         t2gen_v018_followup_count(0), t2gen_v018_exit_count(0),
         t2gen_v018_followup_count(1), t2gen_v018_exit_count(1),
         t2gen_v018_followup_count(2), t2gen_v018_exit_count(2));
#endif
#ifdef CONFIG_GAMES_T2GEN_V017_NATIVE_SYNC_RTS
  printf("T2GEN V0.17 NATIVE_RTS: a136=%lu 6128=%lu a0ec=%lu\n",
         t2gen_v017_rts_count(0), t2gen_v017_rts_count(1),
         t2gen_v017_rts_count(2));
#endif
#ifdef CONFIG_GAMES_T2GEN_V015_PAIRED_SYNC
  printf("T2GEN V0.16 PAIRED: a134=%lu fallback=%lu 6126=%lu fallback=%lu a0ea=%lu fallback=%lu\n",
         t2gen_v016_paired_count(0), t2gen_v016_paired_fallback(0),
         t2gen_v016_paired_count(1), t2gen_v016_paired_fallback(1),
         t2gen_v016_paired_count(2), t2gen_v016_paired_fallback(2));
#endif
#endif
#endif
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
