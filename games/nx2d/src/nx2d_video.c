#include "nx2d.h"
#include <nuttx/video/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
static void rect(struct nx2d_video_s *v, int x, int y, int w, int h,
                 uint16_t color)
{
  if (x < 0) { w += x; x = 0; }
  if (y < 0) { h += y; y = 0; }
  if (x + w > (int)v->width) w = (int)v->width - x;
  if (y + h > (int)v->height) h = (int)v->height - y;
  if (w <= 0 || h <= 0) return;
  for (int j = 0; j < h; j++)
    {
      uint16_t *row = (uint16_t *)((uint8_t *)v->pixels +
                        (size_t)(y + j) * v->stride) + x;
      for (int i = 0; i < w; i++) row[i] = color;
    }
}
int nx2d_video_open(struct nx2d_video_s *v, const char *path)
{
  struct fb_videoinfo_s vi;
  struct fb_planeinfo_s pi;
  memset(v, 0, sizeof(*v));
  v->fd = -1;
  v->fd = open(path, O_RDWR);
  if (v->fd < 0) return -1;
  if (ioctl(v->fd, FBIOGET_VIDEOINFO, (unsigned long)(uintptr_t)&vi) < 0 ||
      ioctl(v->fd, FBIOGET_PLANEINFO, (unsigned long)(uintptr_t)&pi) < 0)
    goto fail;
  if (pi.bpp != 16 || vi.xres < NX2D_W || vi.yres < NX2D_H ||
      pi.stride < vi.xres * 2 || pi.fblen < pi.stride * vi.yres)
    { errno = ENOTSUP; goto fail; }
  v->width = vi.xres;
  v->height = vi.yres;
  v->stride = pi.stride;
  v->maplen = pi.fblen;
  v->map = mmap(NULL, v->maplen, PROT_READ | PROT_WRITE, MAP_SHARED, v->fd, 0);
  if (v->map == MAP_FAILED) { v->map = NULL; goto fail; }
  v->pixels = (uint16_t *)v->map;
  return 0;
fail:
  close(v->fd);
  v->fd = -1;
  return -1;
}
void nx2d_video_close(struct nx2d_video_s *v)
{
  if (v->map) munmap(v->map, v->maplen);
  if (v->fd >= 0) close(v->fd);
}
void nx2d_video_draw(struct nx2d_video_s *v, const struct nx2d_game_s *g)
{
  /* 320x224 viewport centered in a larger framebuffer, no scaling yet. */
  int ox = ((int)v->width - NX2D_W) / 2;
  int oy = ((int)v->height - NX2D_H) / 2;
  rect(v, ox, oy, NX2D_W, NX2D_H, 0x3d9f); /* sky */
  for (int i = 0; i < NX2D_WORLD_W; i += 64)
    {
      int sx = i - g->camera;
      if (sx > -40 && sx < NX2D_W)
        rect(v, ox + sx, oy + 125, 30, 67, 0x8410);
    }
  rect(v, ox, oy + 192, NX2D_W, 32, 0x4a45);
  for (int i = 0; i < NX2D_WORLD_W; i += 32)
    {
      int sx = i - g->camera;
      if (sx >= -32 && sx < NX2D_W)
        rect(v, ox + sx, oy + 192, 2, 32, 0x738e);
    }
  int px = (g->x >> 16) - g->camera;
  int py = (g->y >> 16);
  rect(v, ox + px, oy + py, 16, 32, 0xf800);
  rect(v, ox + px + 3, oy + py + 3, 10, 8, 0xffc0);
  /* If CPU D-cache is enabled, your LTDC memory region must be coherent
   * (MPU non-cacheable or explicit clean). This baseline does not do it.
   */
}
