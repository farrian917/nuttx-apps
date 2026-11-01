/* T2 Genesis v1: ROM loading/validation milestone for STM32H743 NuttX.
 * This is NOT a 68000/Z80/VDP emulator yet.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <nuttx/video/fb.h>
#include "t2gen_boot.h"
#ifdef CONFIG_GAMES_T2GEN_V043_NATIVE_ONLY
#include "t2gen_native43.h"
#endif
#ifdef CONFIG_GAMES_T2GEN_MUSASHI
#include "t2gen_musashi.h"
#include "t2gen_render.h"
#endif

/* V0.43.3: force completion of buffered writes at diagnostic boundaries.
 * A DSB can narrow down an imprecise BusFault but cannot guarantee that
 * the stacked PC identifies the originating write on Cortex-M7.
 */
#ifdef CONFIG_GAMES_T2GEN_V043_NATIVE_ONLY
static inline void t2gen_v0433_dsb(void)
{
#if defined(__arm__) || defined(__thumb__)
  __asm__ volatile("dsb sy" ::: "memory");
#else
  __sync_synchronize();
#endif
}
#define V0433_MARK(label) do { \
  t2gen_v0433_dsb(); \
  printf("T2GEN V0.43.3: %s\n", (label)); \
  fflush(stdout); \
  t2gen_v0433_dsb(); \
} while (0)
#else
#define V0433_MARK(label) do { } while (0)
#endif

/* V0.43.5: internal-memory phase marker, inspectable via GDB.
 * This static object resides in the ordinary linked .bss, not the ROM
 * buffer allocated from external SDRAM. No kernel modifications required.
 */
static volatile uint32_t g_t2gen_v0435_phase;


static void t2gen_v0435_phase(uint32_t phase)
{
  g_t2gen_v0435_phase = phase;
  t2gen_v0433_dsb();
}


/* V0.43.7: application-only external SDRAM destructive test of a NEW
 * temporary allocation. Never touch LTDC framebuffer or existing ROM.
 * Buffer is freed before the ROM is allocated.
 */
#define T2_SDRAM_TEST_BYTES (1024u * 1024u)
#define T2_SDRAM_BASE 0xc0000000u
#define T2_SDRAM_END  0xc2000000u
static volatile uint32_t g_t2gen_v0437_stage;
static volatile uintptr_t g_t2gen_v0437_address;
static volatile uint32_t g_t2gen_v0437_expected;
static volatile uint32_t g_t2gen_v0437_actual;

static uint32_t t2gen_v0437_pattern(unsigned pattern, uint32_t index)
{
  switch (pattern)
    {
      case 0: return 0x00000000u;
      case 1: return 0xffffffffu;
      case 2: return 0xaaaaaaaau;
      case 3: return 0x55555555u;
      case 4: return index ^ 0x91e10da5u;
      default: return (index * 1664525u) + 1013904223u;
    }
}

static int t2gen_v0437_sdram_test(void)
{
  const size_t bytes = T2_SDRAM_TEST_BYTES;
  const uint32_t count = (uint32_t)(bytes / sizeof(uint32_t));
  uint32_t *buf = (uint32_t *)malloc(bytes);
  uintptr_t begin = (uintptr_t)buf;
  uintptr_t end = begin + bytes;
  printf("T2GEN V0.43.7: SDRAM test allocation=%p bytes=%lu\n",
         (void *)buf, (unsigned long)bytes);
  fflush(stdout);
  if (buf == NULL || begin < T2_SDRAM_BASE ||
      end < begin || end > T2_SDRAM_END)
    {
      printf("T2GEN V0.43.7: ERROR: test buffer is not in SDRAM\n");
      free(buf);
      return -1;
    }

  volatile uint32_t *v = (volatile uint32_t *)buf;
  for (unsigned pattern = 0; pattern < 6; pattern++)
    {
      g_t2gen_v0437_stage = 0x43710000u | pattern;
      t2gen_v0433_dsb();
      printf("T2GEN V0.43.7: pattern %u write start\n", pattern);
      fflush(stdout);
      for (uint32_t i = 0; i < count; i++)
        {
          v[i] = t2gen_v0437_pattern(pattern, i);
        }
      t2gen_v0433_dsb();
      g_t2gen_v0437_stage = 0x43720000u | pattern;
      printf("T2GEN V0.43.7: pattern %u verify start\n", pattern);
      fflush(stdout);
      for (uint32_t i = 0; i < count; i++)
        {
          uint32_t expected = t2gen_v0437_pattern(pattern, i);
          uint32_t actual = v[i];
          if (actual != expected)
            {
              g_t2gen_v0437_address = (uintptr_t)&v[i];
              g_t2gen_v0437_expected = expected;
              g_t2gen_v0437_actual = actual;
              g_t2gen_v0437_stage = 0x437e0000u | pattern;
              printf("T2GEN V0.43.7: FAIL addr=%p expected=%08lx actual=%08lx\n",
                     (void *)&v[i], (unsigned long)expected,
                     (unsigned long)actual);
              fflush(stdout);
              free(buf);
              return -1;
            }
        }
      t2gen_v0433_dsb();
      printf("T2GEN V0.43.7: pattern %u PASS\n", pattern);
      fflush(stdout);
    }
  g_t2gen_v0437_stage = 0x437fffffu;
  free(buf);
  t2gen_v0433_dsb();
  printf("T2GEN V0.43.7: SDRAM TEST PASS (1 MiB, 6 patterns)\n");
  fflush(stdout);
  return 0;
}

/* V0.43.10: 4 KiB AXI SRAM staging buffer, cache-line aligned.
 * Static storage avoids accidentally allocating from the SDRAM heap.
 * Verify actual address at runtime; no DMA assumptions about .bss.
 */
#define T2_V04310_CHUNK 4096u
static uint8_t g_t2gen_v04310_stagebuf[T2_V04310_CHUNK]
  __attribute__((aligned(32)));
static volatile uint32_t g_t2gen_v04310_read_offset;
static volatile uint32_t g_t2gen_v04310_read_phase;
static volatile uintptr_t g_t2gen_v04310_buffer_addr;

#define ROM_MAX (8u * 1024u * 1024u)
static uint32_t be32(const uint8_t *p)
{
  return ((uint32_t)p[0] << 24) | ((uint32_t)p[1] << 16) |
         ((uint32_t)p[2] << 8) | p[3];
}
static uint16_t be16(const uint8_t *p)
{
  return ((uint16_t)p[0] << 8) | p[1];
}
static uint32_t crc32_buf(const uint8_t *p, size_t len)
{
  uint32_t crc = 0xffffffffu;
  for (size_t i = 0; i < len; ++i)
    {
      crc ^= p[i];
      for (unsigned k = 0; k < 8; ++k)
        crc = (crc >> 1) ^ (0xedb88320u & (0u - (crc & 1u)));
    }
  return ~crc;
}
static void field(const char *label, const uint8_t *data, size_t n)
{
  char s[65];
  if (n > 64) n = 64;
  memcpy(s, data, n);
  s[n] = '\0';
  while (n && s[n-1] == ' ') s[--n] = '\0';
  printf("T2GEN: %s: %s\n", label, s);
}
/* V2: diagnostic 68000 reset disassembler, not an instruction executor. */
static void trace_reset(const uint8_t *rom, size_t len, uint32_t pc)
{
  printf("T2GEN V3: reset instruction trace (linear, no execution)\n");
  for (unsigned i = 0; i < 24 && pc + 1 < len; i++)
    {
      uint16_t op = be16(rom + pc);
      const char *kind = "unknown";
      unsigned words = 1;
      if (op == 0x4e71) kind = "NOP";
      else if (op == 0x4e75) kind = "RTS";
      else if (op == 0x4e73) kind = "RTE";
      else if (op == 0x4ef9) {kind = "JMP absolute.l"; words = 3;}
      else if (op == 0x4eb9) {kind = "JSR absolute.l"; words = 3;}
      else if ((op & 0xff00) == 0x6000)
        {kind = "BRA"; if ((op & 255) == 0) words = 2;}
      else if ((op & 0xff00) == 0x6100)
        {kind = "BSR"; if ((op & 255) == 0) words = 2;}
      else if ((op & 0xf000) == 0x7000) kind = "MOVEQ";
      else if ((op & 0xf100) == 0x5000) kind = "ADDQ/SUBQ family";
      else if ((op & 0xf000) == 0x3000) kind = "MOVE.W family";
      else if ((op & 0xf000) == 0x2000) kind = "MOVE.L family";
      else if ((op & 0xf000) == 0x1000) kind = "MOVE.B family";
      else if ((op & 0xffc0) == 0x4e80) kind = "JSR effective address";
      else if ((op & 0xffc0) == 0x4ec0) kind = "JMP effective address";
      printf("T2GEN TRACE: %06lx %04x %-24s", (unsigned long)pc, op, kind);
      for (unsigned w = 1; w < words && pc + 2*w + 1 < len; w++)
        printf(" %04x", be16(rom + pc + 2*w));
      printf("\n");
      pc += words * 2;
    }
  printf("T2GEN V3: trace is sequential decoding only; branches not followed\n");
}

static int display_probe(const char *path)
{
  int fd = open(path, O_RDWR);
  if (fd < 0) { printf("T2GEN: framebuffer open errno=%d\n", errno); return -1; }
  struct fb_videoinfo_s vinfo;
  struct fb_planeinfo_s pinfo;
  if (ioctl(fd, FBIOGET_VIDEOINFO, (unsigned long)(uintptr_t)&vinfo) < 0 ||
      ioctl(fd, FBIOGET_PLANEINFO, (unsigned long)(uintptr_t)&pinfo) < 0)
    {printf("T2GEN: framebuffer ioctl failed errno=%d\n", errno); close(fd); return -1;}
  printf("T2GEN V3 FB: %ux%u fmt=%u bpp=%u stride=%lu mem=%p size=%lu\n",
         (unsigned)vinfo.xres, (unsigned)vinfo.yres, (unsigned)vinfo.fmt,
         (unsigned)pinfo.bpp, (unsigned long)pinfo.stride, pinfo.fbmem,
         (unsigned long)pinfo.fblen);
  if (vinfo.xres != 1024 || vinfo.yres != 600 || pinfo.bpp != 8 ||
      pinfo.stride < 1024 || pinfo.fblen < pinfo.stride * 600u || !pinfo.fbmem)
    {printf("T2GEN V3 FB: expected 1024x600 L8, no writes performed\n"); close(fd); return -1;}
  /* Non-destructive: framebuffer info only. No palette modification. */
  printf("T2GEN V3 FB: compatible L8 surface; display not modified\n");
  close(fd);
  return 0;
}
#ifdef CONFIG_GAMES_T2GEN_V043_NATIVE_ONLY

#endif
int t2gen_main(int argc, char **argv)
{
  t2gen_v0435_phase(0x43500001u);
  printf("T2GEN V0.43.10: AXI SRAM staged ROM reads\n");
  fflush(stdout);
  if (argc < 2 || argc > 5)
    {
      printf("Usage: t2gen ROM [ /dev/fb0 | none [ play | view:0-5 | bench_repeats:40-1000 [ bench_repeats:2-1000 ] ] ]\n");
      return 1;
    }
  if (argc > 1 && strcmp(argv[1], "--sdram-test") == 0)
    {
      return t2gen_v0437_sdram_test() != 0;
    }
  if (0 && t2gen_v0437_sdram_test() != 0)
    {
      return 1;
    }
  int fd = open(argv[1], O_RDONLY);
  if (fd < 0)
    {
      printf("T2GEN: open failed errno=%d\n", errno);
      return 1;
    }
  struct stat st;
  if (fstat(fd, &st) != 0 || st.st_size < 0x200 ||
      (uint64_t)st.st_size > ROM_MAX || (st.st_size & 1))
    {
      printf("T2GEN: invalid ROM size (expected even, 512..%u bytes)\n", ROM_MAX);
      close(fd);
      return 1;
    }
  size_t len = (size_t)st.st_size;
  V0433_MARK("before ROM malloc");
  uint8_t *rom = malloc(len);
  if (!rom)
    {
      printf("T2GEN: malloc(%lu) failed; configure a heap in external SDRAM\n",
             (unsigned long)len);
      close(fd);
      return 1;
    }
  V0433_MARK("after ROM malloc / before SD read");
  uintptr_t stageaddr = (uintptr_t)g_t2gen_v04310_stagebuf;
  g_t2gen_v04310_buffer_addr = stageaddr;
  g_t2gen_v04310_read_offset = 0;
  g_t2gen_v04310_read_phase = 0x43a00001u;
  t2gen_v0433_dsb();
  /* STM32H743 AXI SRAM: 0x24000000..0x2407ffff. */
  if ((stageaddr & 31u) != 0 || stageaddr < 0x24000000u ||
      stageaddr > 0x24080000u - T2_V04310_CHUNK)
    {
      printf("T2GEN V0.43.10: ERROR staging buffer not in AXI SRAM: %p\n",
             (void *)stageaddr);
      close(fd);
      free(rom);
      return 1;
    }
  printf("T2GEN V0.43.10: staged read buffer=%p bytes=%u\n",
         (void *)stageaddr, (unsigned)T2_V04310_CHUNK);
  fflush(stdout);
  size_t pos = 0;
  while (pos < len)
    {
      size_t wanted = len - pos;
      if (wanted > T2_V04310_CHUNK)
        wanted = T2_V04310_CHUNK;
      g_t2gen_v04310_read_phase = 0x43a00010u; /* entering read */
      t2gen_v0433_dsb();
      ssize_t nr = read(fd, g_t2gen_v04310_stagebuf, wanted);
      if (nr < 0 && errno == EINTR)
        continue;
      if (nr <= 0)
        {
          g_t2gen_v04310_read_phase = 0x43a0e001u;
          t2gen_v0433_dsb();
          printf("T2GEN V0.43.10: read failed/EOF at %lu errno=%d\n",
                 (unsigned long)pos, errno);
          free(rom);
          close(fd);
          return 1;
        }
      g_t2gen_v04310_read_phase = 0x43a00020u; /* read returned */
      t2gen_v0433_dsb();
      memcpy(rom + pos, g_t2gen_v04310_stagebuf, (size_t)nr);
      t2gen_v0433_dsb();
      pos += (size_t)nr;
      g_t2gen_v04310_read_offset = (uint32_t)pos;
      g_t2gen_v04310_read_phase = 0x43a00030u; /* copy completed */
      t2gen_v0433_dsb();
    }
  g_t2gen_v04310_read_phase = 0x43a00040u; /* ROM fully loaded */
  t2gen_v0433_dsb();
  t2gen_v0435_phase(0x43800010u);
  t2gen_v0433_dsb();
  t2gen_v0435_phase(0x43900010u); /* read complete */
  close(fd);
  t2gen_v0433_dsb();
  t2gen_v0435_phase(0x43900020u); /* close complete */
  uint32_t rom_crc = crc32_buf(rom, len);
  t2gen_v0433_dsb();
  t2gen_v0435_phase(0x43800020u);
  if (rom_crc != 0x2f75e896u)
    {
      t2gen_v0435_phase(0x4390e001u); /* CRC mismatch */
      free(rom);
      return 1;
    }
  t2gen_v0435_phase(0x43900030u); /* CRC verified */
  if (memcmp(rom + 0x100, "SEGA", 4) != 0)
    {
      printf("T2GEN: missing SEGA header at 0x100 (check ROM format)\n");
      free(rom);
      return 1;
    }
  /* V0.43.8: do not print ROM header strings or metadata.
   * Read the reset vectors and bounds only, using the existing helpers.
   */
  t2gen_v0435_phase(0x43800030u);
  uint32_t sp = be32(rom);
  uint32_t pc = be32(rom + 4);
  uint32_t rom_start = be32(rom + 0x1a0);
  uint32_t rom_end = be32(rom + 0x1a4);
  (void)sp;
  (void)rom_start;
  (void)rom_end;
  t2gen_v0433_dsb();
  t2gen_v0435_phase(0x43800040u);
  if (pc >= len || (pc & 1u))
    {
      printf("T2GEN: reset vector outside ROM or unaligned\n");
      free(rom);
      return 1;
    }
  /* V0.43.6: diagnostic checksum bypass. Do not access ROM or print
   * between the post-header checks and the next initialization stage.
   * This experiment isolates the checksum path from subsequent startup.
   * Remove this bypass once the fault has been identified.
   */
  t2gen_v0435_phase(0x43600010u); /* checksum intentionally skipped */
  t2gen_v0433_dsb();
  t2gen_v0435_phase(0x43600020u); /* barrier completed */
  t2gen_v0433_dsb();
  t2gen_v0435_phase(0x43800050u);
  t2gen_v0435_phase(0x43900050u); /* header validated */
#ifdef CONFIG_GAMES_T2GEN_MUSASHI
  /* V21.1: four-argument shorthand uses 6..1000 for benchmark repeats.
   * Values 0..5 remain the historical rendering view selection.
   * The five-argument form explicitly selects view and repeat count.
   */
  unsigned bench_repeats = 0;
  bool gameplay = false;
  if (argc >= 4 && strcmp(argv[3], "play") == 0)
    {
      if (argc != 4 || argc < 3 || strcmp(argv[2], "none") == 0)
        {
          printf("T2GEN V0.29: play requires a framebuffer: t2gen ROM /dev/fb0 play\n");
          free(rom);
          return 1;
        }
      gameplay = true;
    }
  if (argc >= 4 && !gameplay)
    {
      char *endptr = NULL;
      unsigned long arg = strtoul(argv[3], &endptr, 10);
      if (!argv[3][0] || !endptr || *endptr != '\0' ||
          arg > 1000ul)
        {
          printf("T2GEN V21.1: invalid view/repeats argument\n");
          free(rom);
          return 1;
        }
      if (argc == 4 && arg >= 6ul)
        {
          bench_repeats = (unsigned)arg;
          if (bench_repeats < 2u)
            {
              free(rom);
              return 1;
            }
        }
      else if (arg <= 5ul)
        t2gen_render_set_view((unsigned)arg);
      else
        {
          printf("T2GEN V21.1: view must be 0..5\n");
          free(rom);
          return 1;
        }
    }
  if (argc == 5)
    {
      char *endptr = NULL;
      unsigned long repeats = strtoul(argv[4], &endptr, 10);
      if (!argv[4][0] || !endptr || *endptr != '\0' ||
          repeats < 2ul || repeats > 1000ul)
        {
          printf("T2GEN V21.1: bench_repeats must be 2..1000\n");
          free(rom);
          return 1;
        }
      bench_repeats = (unsigned)repeats;
    }
  printf("T2GEN V21.1: view/benchmark parsed; bench_repeats=%u\n",
         bench_repeats);
  t2gen_musashi_set_gameplay(gameplay);
  t2gen_musashi_probe(rom, len, argc >= 3 ? argv[2] : NULL);
#else
#ifdef CONFIG_GAMES_T2GEN_V043_NATIVE_ONLY
  t2gen_v0435_phase(0x43900060u); /* entering native */
  t2gen_native43_probe(rom, len, argc >= 3 ? argv[2] : NULL);
  t2gen_v0435_phase(0x43900070u); /* returned from native */
  printf("T2GEN V0.43.9: native probe returned; phase=%08lx\n",
         (unsigned long)g_t2gen_v0435_phase);
#else
  t2gen_boot_probe(rom, len);
#endif
#endif
  if (argc >= 3 && strcmp(argv[2], "none") != 0
#ifdef CONFIG_GAMES_T2GEN_MUSASHI
      && !gameplay
#endif
     )
    {
#ifdef CONFIG_GAMES_T2GEN_MUSASHI
      t2gen_vdp_dump_write_diagnostics();
  t2gen_vdp_dump_memory();
      if (t2gen_render_snapshot(argv[2]) < 0)
        printf("T2GEN V21: final snapshot render failed\n");
      if (bench_repeats != 0u)
        t2gen_render_benchmark(argv[2], bench_repeats);
#else
      /* VDP snapshot was rendered during the native probe. */
#endif
    }

  free(rom);
  return 0;
}
