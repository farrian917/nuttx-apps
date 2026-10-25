/* Native Cortex-M7 T2 graphics proof of concept. No Musashi, no 68000.
 * Uses ROM as a byte-oriented tile source; offsets are not verified game assets.
 * The generated tile map and moving marker are NOT Terminator 2 gameplay.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "t2gen_vdp.h"
#include "t2gen_render.h"

#define ROM_TILE_BYTES (32u * 256u)
#define ROM_OFFSET 0x200u
#define PLANE_A 0xe000u
#define PLANE_B 0xc000u
#define SAT_ADDR 0xd000u
static void be16(uint8_t *p, unsigned addr, uint16_t value)
{
  p[addr & 65535u] = (uint8_t)(value >> 8);
  p[(addr + 1u) & 65535u] = (uint8_t)value;
}

static int load_tiles(const char *path, struct t2gen_vdp_s *v)
{
  int fd = open(path, O_RDONLY);
  if (fd < 0) { printf("T2NATIVE: ROM open errno=%d\n", errno); return -1; }
  if (lseek(fd, ROM_OFFSET, SEEK_SET) < 0)
    { close(fd); return -1; }
  ssize_t n = read(fd, v->vram, ROM_TILE_BYTES);
  close(fd);
  if (n != (ssize_t)ROM_TILE_BYTES)
    { printf("T2NATIVE: ROM read %ld expected %u\n", (long)n, ROM_TILE_BYTES); return -1; }
  return 0;
}

static void make_scene(struct t2gen_vdp_s *v)
{
  /* H32, 32x32 tile planes; native tilemap construction. */
  v->reg[1] = 0x44; /* display enable */
  v->reg[2] = PLANE_A >> 10;
  v->reg[4] = PLANE_B >> 13;
  v->reg[5] = SAT_ADDR >> 9;
  v->reg[11] = 0;
  v->reg[12] = 0;
  v->reg[13] = 0x3e; /* H scroll table at 0xf800 */
  v->reg[16] = 0;
  v->reg[17] = 0;
  v->reg[18] = 0;
  for (unsigned i=0; i<64; i++)
    v->cram[i] = (uint16_t)((((i>>0)&7u)<<1) | (((i>>2)&7u)<<5) | (((i>>4)&7u)<<9));
  for (unsigned y=0; y<32; y++)
    for (unsigned x=0; x<32; x++)
      {
        unsigned i = y*32u+x;
        be16(v->vram, PLANE_A + i*2u, (uint16_t)(1u + ((x + y*7u) % 254u)));
        be16(v->vram, PLANE_B + i*2u, (uint16_t)(1u + ((x*3u + y*5u) % 254u)));
      }
  /* Synthetic 1x1 sprite at center; not a game character. */
  be16(v->vram, SAT_ADDR + 0u, 128u + 112u);
  be16(v->vram, SAT_ADDR + 2u, 0);
  be16(v->vram, SAT_ADDR + 4u, 1u);
  be16(v->vram, SAT_ADDR + 6u, 128u + 128u);
}


/* V0.2: Validate the exact ROM used as the reverse-engineering reference.
 * Read-only and intentionally independent of Motorola emulation.
 */
static int validate_reference_rom(const char *path)
{
  uint8_t hdr[512];
  uint8_t chunk[1024];
  uint32_t checksum = 0;
  uint32_t total = 0;
  int fd = open(path, O_RDONLY);
  if (fd < 0)
    {
      printf("T2NATIVE V0.2: ROM open errno=%d\n", errno);
      return -1;
    }
  ssize_t n = read(fd, hdr, sizeof(hdr));
  if (n != (ssize_t)sizeof(hdr))
    {
      printf("T2NATIVE V0.2: incomplete ROM header\n");
      close(fd);
      return -1;
    }
  uint32_t sp = ((uint32_t)hdr[0] << 24) |
                ((uint32_t)hdr[1] << 16) |
                ((uint32_t)hdr[2] << 8) | hdr[3];
  uint32_t pc = ((uint32_t)hdr[4] << 24) |
                ((uint32_t)hdr[5] << 16) |
                ((uint32_t)hdr[6] << 8) | hdr[7];
  uint16_t expected = ((uint16_t)hdr[0x18e] << 8) | hdr[0x18f];
  while ((n = read(fd, chunk, sizeof(chunk))) > 0)
    {
      if ((n & 1) != 0)
        {
          printf("T2NATIVE V0.2: odd-sized ROM chunk\n");
          close(fd);
          return -1;
        }
      for (ssize_t i = 0; i < n; i += 2)
        checksum += ((uint16_t)chunk[i] << 8) | chunk[i + 1];
      total += (uint32_t)n;
    }
  close(fd);
  if (n < 0)
    {
      printf("T2NATIVE V0.2: ROM read error\n");
      return -1;
    }
  printf("T2NATIVE V0.2 ROM: size=%lu SP=%08lx PC=%08lx checksum=%04lx header=%04x\n",
         (unsigned long)(total + sizeof(hdr)),
         (unsigned long)sp, (unsigned long)pc,
         (unsigned long)(checksum & 0xffffu), expected);
  if (total + sizeof(hdr) != 1048576u || sp != 0x01000000u ||
      pc != 0x00000200u || (checksum & 0xffffu) != expected ||
      expected != 0x336fu)
    {
      printf("T2NATIVE V0.2: unexpected ROM; exact-port reference rejected\n");
      return -1;
    }
  return 0;
}

int t2native_main(int argc, char **argv)
{
  const char *rom = argc > 1 ? argv[1] : "/mnt/t2.gen";
  const char *fb = argc > 2 ? argv[2] : "/dev/fb0";
  unsigned frames = argc > 3 ? (unsigned)strtoul(argv[3], NULL, 0) : 60u;
  if (frames > 600u) frames = 600u;
  if (validate_reference_rom(rom) < 0) return 1;
  t2gen_vdp_reset();
  struct t2gen_vdp_s *v = (struct t2gen_vdp_s *)(uintptr_t)t2gen_vdp_state();
  if (load_tiles(rom, v) < 0) return 1;
  make_scene(v);
  t2gen_render_set_view(0);
  printf("T2NATIVE V0.2: native ARM graphics prototype, ROM=%s frames=%u\n",rom,frames);
  printf("T2NATIVE: NO Motorola 68000, NO original game logic; tile offset 0x%X is illustrative\n", ROM_OFFSET);
  for (unsigned i=0; i<frames; i++)
    {
      /* Native animation: move synthetic sprite, no CPU emulation. */
      be16(v->vram, SAT_ADDR+6u, (uint16_t)(128u + 48u + (i % 160u)));
      if (t2gen_render_snapshot(fb) < 0)
        { printf("T2NATIVE: framebuffer render failed frame=%u\n",i); return 2; }
      usleep(33000);
    }
  t2gen_render_print_perf();
  printf("T2NATIVE V0.2: completed %u native renders\n",frames);
  return 0;
}
