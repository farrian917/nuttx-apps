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
#ifdef CONFIG_GAMES_T2GEN_MUSASHI
#include "t2gen_musashi.h"
#include "t2gen_render.h"
#endif

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
int t2gen_main(int argc, char **argv)
{
  if (argc < 2 || argc > 5)
    {
      printf("Usage: t2gen ROM [ /dev/fb0 | none [ play | view:0-5 | bench_repeats:40-1000 [ bench_repeats:2-1000 ] ] ]\n");
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
  uint8_t *rom = malloc(len);
  if (!rom)
    {
      printf("T2GEN: malloc(%lu) failed; configure a heap in external SDRAM\n",
             (unsigned long)len);
      close(fd);
      return 1;
    }
  size_t pos = 0;
  while (pos < len)
    {
      ssize_t nr = read(fd, rom + pos, len - pos);
      if (nr < 0 && errno == EINTR) continue;
      if (nr <= 0)
        {
          printf("T2GEN: read failed/EOF at %lu errno=%d\n",
                 (unsigned long)pos, errno);
          free(rom);
          close(fd);
          return 1;
        }
      pos += (size_t)nr;
    }
  close(fd);
  printf("T2GEN V4: ROM loaded %lu bytes at %p\n", (unsigned long)len, rom);
  printf("T2GEN: CRC32=%08lx\n", (unsigned long)crc32_buf(rom, len));
  if (memcmp(rom + 0x100, "SEGA", 4) != 0)
    {
      printf("T2GEN: missing SEGA header at 0x100 (check ROM format)\n");
      free(rom);
      return 1;
    }
  field("system", rom + 0x100, 16);
  field("domestic title", rom + 0x120, 48);
  field("international title", rom + 0x150, 48);
  field("serial", rom + 0x180, 14);
  field("regions", rom + 0x1f0, 16);
  uint32_t sp = be32(rom);
  uint32_t pc = be32(rom + 4);
  uint32_t rom_start = be32(rom + 0x1a0);
  uint32_t rom_end = be32(rom + 0x1a4);
  printf("T2GEN: vectors SP=%08lx PC=%08lx\n",
         (unsigned long)sp, (unsigned long)pc);
  printf("T2GEN: ROM range %08lx..%08lx header checksum=%04x\n",
         (unsigned long)rom_start, (unsigned long)rom_end,
         (unsigned)be16(rom + 0x18e));
  if (pc >= len || (pc & 1u))
    {
      printf("T2GEN: reset vector outside ROM or unaligned\n");
      free(rom);
      return 1;
    }
  /* Conventional Genesis header checksum over words from 0x200 onward. */
  uint32_t sum = 0;
  for (size_t i = 0x200; i + 1 < len; i += 2)
    sum += be16(rom + i);
  printf("T2GEN: computed checksum=%04x (%s)\n",
         (unsigned)(sum & 0xffffu),
         ((sum & 0xffffu) == be16(rom + 0x18e)) ? "MATCH" : "MISMATCH");
  printf("T2GEN: ROM probe OK\n");
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
  t2gen_boot_probe(rom, len);
#endif
  if (!gameplay && argc >= 3 && strcmp(argv[2], "none") != 0)
    {
#ifdef CONFIG_GAMES_T2GEN_MUSASHI
      t2gen_vdp_dump_write_diagnostics();
  t2gen_vdp_dump_memory();
      if (t2gen_render_snapshot(argv[2]) < 0)
        printf("T2GEN V21: final snapshot render failed\n");
      if (bench_repeats != 0u)
        t2gen_render_benchmark(argv[2], bench_repeats);
#else
      display_probe(argv[2]);
#endif
    }

  free(rom);
  return 0;
}
