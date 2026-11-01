/* Real VDP-state tile renderer. No synthetic SEGA lettering or ROM graphics injection.
 * Initial snapshot: planes A/B, per-tile priority, H/V flip, CRAM, backdrop.
 * DMA, window, sprites and scroll remain unimplemented.
 */
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <nuttx/video/fb.h>
#include "t2gen_vdp_frame59.h"
#ifdef CONFIG_ARMV7M_DCACHE
#include <nuttx/cache.h>
#endif
static unsigned vr16(const uint8_t *m, unsigned a)
{
  return ((unsigned)m[a & 65535u] << 8) | m[(a + 1u) & 65535u];
}
static unsigned plane_pixel(const struct t2gen_vdp_frame59 *v,
                            unsigned base, unsigned width, unsigned height,
                            unsigned x, unsigned y, unsigned priority)
{
  unsigned col = (x / 8u) % width;
  unsigned row = (y / 8u) % height;
  unsigned attr = vr16(v->vram, base + 2u * (row * width + col));
  unsigned tile = attr & 0x7ffu;
  unsigned pal = (attr >> 13) & 3u;
  unsigned xx = x & 7u, yy = y & 7u;
  unsigned addr, val, nibble;
  if (((attr >> 15) & 1u) != priority) return 0u;
  if (attr & 0x0800u) xx = 7u - xx;
  if (attr & 0x1000u) yy = 7u - yy;
  addr = tile * 32u + yy * 4u + xx / 2u;
  val = v->vram[addr & 65535u];
  nibble = (xx & 1u) ? (val & 15u) : (val >> 4);
  return nibble ? 1u + pal * 16u + nibble : 0u;
}
int t2gen_vdp_frame59_render(const char *path, const struct t2gen_vdp_frame59 *v)
{
  struct fb_videoinfo_s vi;
  struct fb_planeinfo_s pi;
  struct fb_cmap_s cmap;
  uint8_t red[256], green[256], blue[256];
  unsigned x, y, p, sx, sy, i, width, height, aw, ah, bw, bh, ab, bb, back, visible;
  int fd;
  uint8_t *fb;
  if (!path || !v) return -1;
  fd = open(path, O_RDWR);
  if (fd < 0) { printf("T2GEN V0.59 VDP_RENDER: cannot open %s\n", path); return -1; }
  if (ioctl(fd, FBIOGET_VIDEOINFO, (unsigned long)(uintptr_t)&vi) < 0 ||
      ioctl(fd, FBIOGET_PLANEINFO, (unsigned long)(uintptr_t)&pi) < 0 ||
      vi.xres != 1024u || vi.yres != 600u || pi.bpp != 8u ||
      pi.stride < 1024u || pi.fblen < pi.stride * 600u || !pi.fbmem)
    { printf("T2GEN V0.59 VDP_RENDER: need 1024x600 L8 framebuffer\n"); close(fd); return -1; }
  /* Index 0 is backdrop. Indices 1..64 map Genesis palette entries 0..63. */
  memset(red, 0, sizeof(red)); memset(green, 0, sizeof(green)); memset(blue, 0, sizeof(blue));
  back = v->regs[7] & 63u;
  for (i = 0; i < 65u; ++i)
    {
      unsigned c = i ? i - 1u : back;
      unsigned w = ((unsigned)v->cram[c * 2u] << 8) | v->cram[c * 2u + 1u];
      red[i] = (uint8_t)(((w >> 1) & 7u) * 255u / 7u);
      green[i] = (uint8_t)(((w >> 5) & 7u) * 255u / 7u);
      blue[i] = (uint8_t)(((w >> 9) & 7u) * 255u / 7u);
    }
  memset(&cmap, 0, sizeof(cmap));
  cmap.first = 0; cmap.len = 65; cmap.red = red; cmap.green = green; cmap.blue = blue;
  if (ioctl(fd, FBIOPUT_CMAP, (unsigned long)(uintptr_t)&cmap) < 0)
    { printf("T2GEN V0.59 VDP_RENDER: FBIOPUT_CMAP failed; palette unavailable\n"); close(fd); return -1; }
  fb = (uint8_t *)pi.fbmem;
  for (y = 0; y < 600u; ++y) memset(fb + (size_t)y * pi.stride, 0, 1024u);
  width = (v->regs[12] & 1u) ? 320u : 256u;
  height = (v->regs[1] & 8u) ? 240u : 224u;
  aw = 32u << (v->regs[16] & 3u); bw = 32u << ((v->regs[16] >> 4) & 3u);
  ah = 32u << ((v->regs[16] >> 2) & 3u);
  bh = 32u << ((v->regs[16] >> 6) & 3u);
  if (aw > 128u) aw = 128u;
  if (bw > 128u) bw = 128u;
  if (ah > 128u) ah = 128u;
  if (bh > 128u) bh = 128u;
  ab = ((unsigned)(v->regs[2] & 0x38u)) << 10;
  bb = ((unsigned)(v->regs[4] & 0x07u)) << 13;
  visible = 0;
  /* No fake boot logo: pixels strictly come from emulated VDP memory. */
  for (y = 0; y < height; ++y)
    for (x = 0; x < width; ++x)
      {
        unsigned index = 0, q;
        /* Simplified fixed scroll. Back-to-front: B low, A low, B high, A high. */
        for (p = 0; p < 2u; ++p)
          {
            q = plane_pixel(v, bb, bw, bh, x, y, p);
            if (q) index = q;
            q = plane_pixel(v, ab, aw, ah, x, y, p);
            if (q) index = q;
          }
        if (index) ++visible;
        sx = (1024u - width * 2u) / 2u + x * 2u;
        sy = (600u - height * 2u) / 2u + y * 2u;
        fb[(size_t)sy * pi.stride + sx] = (uint8_t)index;
        fb[(size_t)sy * pi.stride + sx + 1u] = (uint8_t)index;
        fb[(size_t)(sy + 1u) * pi.stride + sx] = (uint8_t)index;
        fb[(size_t)(sy + 1u) * pi.stride + sx + 1u] = (uint8_t)index;
      }
#ifdef CONFIG_ARMV7M_DCACHE
  up_clean_dcache((uintptr_t)fb, (uintptr_t)fb + (size_t)pi.stride * 600u);
#endif
  printf("T2GEN V0.59 VDP_RENDER: %ux%u planeA=%04x planeB=%04x nontransparent=%u (no sprites/DMA/scroll)\n",
         width, height, ab, bb, visible);
  close(fd);
  return 0;
}
