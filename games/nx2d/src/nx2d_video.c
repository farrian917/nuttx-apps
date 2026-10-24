#include "nx2d.h"
#include "nx2d_tilemap.h"
#include "nx2d_sprite.h"
#include "nx2d_level_demo.h"
#include <nuttx/video/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* L8 palette: 3 red bits, 3 green bits, 2 blue bits. */
static struct nx2d_sprite_s g_player_sprite;
static bool g_sprite_loaded;
static uint16_t g_xmap[1024];
static uint32_t g_scaled_words[256] __attribute__((aligned(8)));
static uint8_t *const g_scaled_row = (uint8_t *)g_scaled_words;
/* 0=memcpy, 1=word32, 2=unroll, 3=rowcopy, 4=burst16, 5=packed,
 * 6=ratio (exact 5:16 horizontal scaling), 7=ratio16 (16-word writes), 8=ratio64 (aligned 64-bit writes). */
static unsigned g_scaler_mode;
static const char *nx2d_scaler_name(unsigned mode)
{
  static const char *const names[] = {"memcpy", "word32", "unroll", "rowcopy", "burst16", "packed", "ratio", "ratio16", "ratio64"};
  return names[mode < 9 ? mode : 6];
}
static void nx2d_copy_words(uint8_t *dst, const uint32_t *src);
static void nx2d_copy_unrolled(uint8_t *dst, const uint32_t *src)
{
  uint32_t *d = (uint32_t *)(void *)dst;
  for (unsigned i = 0; i < 256; i += 8)
    {
      d[i] = src[i]; d[i+1] = src[i+1];
      d[i+2] = src[i+2]; d[i+3] = src[i+3];
      d[i+4] = src[i+4]; d[i+5] = src[i+5];
      d[i+6] = src[i+6]; d[i+7] = src[i+7];
    }
}
/* 16-word sequential store burst; compare against the 8-word unroll. */
static void nx2d_copy_burst16(uint8_t *dst, const uint32_t *src)
{
  uint32_t *d = (uint32_t *)(void *)dst;
  for (unsigned i = 0; i < 256; i += 16)
    {
      d[i+0] = src[i+0]; d[i+1] = src[i+1];
      d[i+2] = src[i+2]; d[i+3] = src[i+3];
      d[i+4] = src[i+4]; d[i+5] = src[i+5];
      d[i+6] = src[i+6]; d[i+7] = src[i+7];
      d[i+8] = src[i+8]; d[i+9] = src[i+9];
      d[i+10] = src[i+10]; d[i+11] = src[i+11];
      d[i+12] = src[i+12]; d[i+13] = src[i+13];
      d[i+14] = src[i+14]; d[i+15] = src[i+15];
    }
}
/* Pack four output pixels directly into a word from the source row.
 * This avoids the intermediate byte expansion pass; only done once per
 * distinct logical source row, then reused for all duplicate output rows.
 */
/* Experimental 64-bit sequential SDRAM stores. Both pointers must be
 * 8-byte aligned. This path is for benchmarking only: actual throughput
 * depends on MPU attributes, FMC bus arbitration and LTDC activity.
 * No cache/MPU settings are changed here. */
static void nx2d_copy_words64(uint8_t *dst, const uint32_t *src)
{
  if ((((uintptr_t)dst | (uintptr_t)src) & 7u) != 0)
    {
      nx2d_copy_burst16(dst, src);
      return;
    }

  uint64_t *d = (uint64_t *)(void *)dst;
  const uint64_t *s = (const uint64_t *)(const void *)src;
  for (unsigned i = 0; i < 128; i += 8)
    {
      d[i+0] = s[i+0]; d[i+1] = s[i+1];
      d[i+2] = s[i+2]; d[i+3] = s[i+3];
      d[i+4] = s[i+4]; d[i+5] = s[i+5];
      d[i+6] = s[i+6]; d[i+7] = s[i+7];
    }
}

static void nx2d_expand_packed(const uint8_t *src)
{
  for (unsigned i = 0; i < 256; ++i)
    {
      unsigned x = i * 4;
      g_scaled_words[i] = (uint32_t)src[g_xmap[x]] |
                           ((uint32_t)src[g_xmap[x+1]] << 8) |
                           ((uint32_t)src[g_xmap[x+2]] << 16) |
                           ((uint32_t)src[g_xmap[x+3]] << 24);
    }
}
/* Exact 320->1024 scaling: each group of five source pixels becomes
 * sixteen destination pixels. Four packed words per group, 64 groups.
 * The pattern follows floor(x * 320 / 1024) exactly:
 * 0,0,0,0, 1,1,1, 2,2,2, 3,3,3, 4,4,4.
 * Avoids 1024 lookup-table accesses and 1024 byte loads per scanline.
 */
static void nx2d_expand_ratio(const uint8_t *src)
{
  for (unsigned group = 0; group < 64; ++group)
    {
      const uint8_t *p = src + group * 5;
      uint32_t a = p[0], b = p[1], c = p[2], d = p[3], e = p[4];
      uint32_t *out = &g_scaled_words[group * 4];
      out[0] = a * 0x01010101u;
      out[1] = b | (b << 8) | (b << 16) | (c << 24);
      out[2] = c | (c << 8) | (d << 16) | (d << 24);
      out[3] = d | (e << 8) | (e << 16) | (e << 24);
    }
}

static void nx2d_scale_copy(uint8_t *dst, const uint8_t *prev,
                            bool duplicate)
{
  if (g_scaler_mode == 8)
    nx2d_copy_words64(dst, g_scaled_words);
  else if (g_scaler_mode == 3 && duplicate)
    memcpy(dst, prev, 1024);
  else if (g_scaler_mode == 0)
    memcpy(dst, g_scaled_row, 1024);
  else if (g_scaler_mode == 1)
    nx2d_copy_words(dst, g_scaled_words);
  else if (g_scaler_mode == 4 || g_scaler_mode == 7)
    nx2d_copy_burst16(dst, g_scaled_words);
  else
    nx2d_copy_unrolled(dst, g_scaled_words);
}

/* V20 DWT section counters. Single-threaded draw loop; read after frame wait. */
#if defined(__ARM_ARCH_7EM__) || defined(__ARM_ARCH_7M__)
# define NX2D_VIDEO_DWT_CTRL (*(volatile uint32_t *)0xe0001000)
# define NX2D_VIDEO_DWT_CYCCNT (*(volatile uint32_t *)0xe0001004)
static inline uint32_t nx2d_video_cycles(void)
{
  return NX2D_VIDEO_DWT_CYCCNT;
}
#else
static inline uint32_t nx2d_video_cycles(void) { return 0; }
#endif
struct nx2d_video_cycles_s
{
  uint64_t bg, map, objects, expand, fbwrite;
  uint32_t frames;
};
static struct nx2d_video_cycles_s g_v19_cycles;
void nx2d_video_profile_take(struct nx2d_video_cycles_s *out)
{
  *out = g_v19_cycles;
  memset(&g_v19_cycles, 0, sizeof(g_v19_cycles));
}
static uint64_t g_compose_us, g_scale_us;
static uint64_t g_bg_us, g_map_us, g_objects_us;
static uint64_t g_expand_us, g_write_us;
/* Cortex-M7 32-bit aligned stores, without aliasing the source bytes. */
static void nx2d_copy_words(uint8_t *dst, const uint32_t *src)
{
  uint32_t *d = (uint32_t *)(void *)dst;
  for (unsigned i = 0; i < 256; i++)
    d[i] = src[i];
}

static unsigned g_profile_frames;
static bool g_detailed_profile;
void nx2d_video_set_detailed_profile(bool enable)
{
  g_detailed_profile = enable;
}

static uint64_t nx2d_us(void)
{
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (uint64_t)ts.tv_sec * 1000000u +
         (uint64_t)ts.tv_nsec / 1000u;
}


/* Benchmark only the framebuffer returned by FBIOGET_PLANEINFO.
 * No direct access to the reserved DMA2D overlay is made.
 * Run once before gameplay: framebuffer content is overwritten temporarily.
 */
void nx2d_video_set_scaler(struct nx2d_video_s *v, unsigned mode)
{
  g_scaler_mode = mode < 8 ? mode : 6;
  bool aligned = (((uintptr_t)v->pixels | v->stride) & 3u) == 0;
  if (!aligned && g_scaler_mode != 0)
    {
      printf("NX2D: unaligned framebuffer, falling back to memcpy\n");
      g_scaler_mode = 0;
    }
  printf("NX2D: game scaler=%s\n", nx2d_scaler_name(g_scaler_mode));
}

void nx2d_video_benchmark(struct nx2d_video_s *v, unsigned mode)
{
  g_scaler_mode = mode < 8 ? mode : 6;
  if (v->width != 1024 || v->height != 600 || v->stride < 1024)
    { printf("NX2D BENCH: unsupported geometry\n"); return; }
  for (unsigned i = 0; i < 256; ++i)
    g_scaled_words[i] = 0x55555555u ^ (i * 0x01010101u);
  bool aligned = (((uintptr_t)v->pixels | v->stride) & 3u) == 0;
  printf("NX2D BENCH: framebuffer=%p stride=%u backbuffer=%p aligned=%u\n",
         v->pixels, v->stride, v->backbuffer, aligned ? 1u : 0u);
  if (!aligned && g_scaler_mode != 0)
    { printf("NX2D BENCH: unaligned framebuffer; falling back to memcpy\n");
      g_scaler_mode = 0; }
  for (unsigned method = 0; method < (aligned ? 8u : 1u); ++method)
    {
      uint64_t best = UINT64_MAX, total = 0;
      for (unsigned trial = 0; trial < 4; ++trial)
        {
          uint64_t start = nx2d_us();
          for (unsigned y = 0; y < 600; ++y)
            {
              uint8_t *dst = v->pixels + (size_t)y * v->stride;
              if (method == 0)
                memcpy(dst, g_scaled_row, 1024);
              else if (method == 1)
                nx2d_copy_words(dst, g_scaled_words);
              else if (method == 2)
                nx2d_copy_unrolled(dst, g_scaled_words);
              else if (method == 3)
                {
                  if (y == 0) nx2d_copy_unrolled(dst, g_scaled_words);
                  else memcpy(dst, dst - v->stride, 1024);
                }
              else if (method == 4 || method == 7)
                nx2d_copy_burst16(dst, g_scaled_words);
              else
                nx2d_copy_unrolled(dst, g_scaled_words);
            }
          uint64_t elapsed = nx2d_us() - start;
          if (elapsed < best) best = elapsed;
          total += elapsed;
        }
      printf("NX2D BENCH: %s 614400B best=%lu us avg=%lu us "
             "effective=%lu KiB/s\n",
             nx2d_scaler_name(method),
             (unsigned long)best, (unsigned long)(total / 4),
             (unsigned long)(best ? (600ull * 1000000ull / best) : 0));
    }
  printf("NX2D BENCH: game scaler=%s\n",
         nx2d_scaler_name(g_scaler_mode));
}

#define NX2D_ENEMY_VARIANTS 3
static struct nx2d_sprite_s g_enemy_sprites[NX2D_ENEMY_VARIANTS];
static bool g_enemy_loaded[NX2D_ENEMY_VARIANTS];
static int nx2d_palette(int fd)
{
  struct fb_cmap_s cmap;
  uint8_t r[256], g[256], b[256];
  for (unsigned i = 0; i < 256; i++)
    {
      r[i] = (uint8_t)(((i >> 5) & 7) * 255 / 7);
      g[i] = (uint8_t)(((i >> 2) & 7) * 255 / 7);
      b[i] = (uint8_t)((i & 3) * 255 / 3);
    }
  memset(&cmap, 0, sizeof(cmap));
  cmap.first = 0;
  cmap.len = 256;
  cmap.red = r;
  cmap.green = g;
  cmap.blue = b;
  return ioctl(fd, FBIOPUT_CMAP, (unsigned long)(uintptr_t)&cmap);
}
static uint8_t rgb565_to_l8(uint16_t c)
{
  unsigned r = (c >> 11) & 31;
  unsigned g = (c >> 5) & 63;
  unsigned b = c & 31;
  return (uint8_t)(((r * 7 / 31) << 5) |
                   ((g * 7 / 63) << 2) | (b * 3 / 31));
}
int nx2d_video_open(struct nx2d_video_s *v, const char *path)
{
  struct fb_videoinfo_s vi;
  struct fb_planeinfo_s pi;
  memset(v, 0, sizeof(*v));
  v->fd = -1;
  v->fd = open(path, O_RDWR);
  if (v->fd < 0)
    {
      printf("NX2D: open(%s) failed errno=%d\n", path, errno);
      return -1;
    }
  if (ioctl(v->fd, FBIOGET_VIDEOINFO,
            (unsigned long)(uintptr_t)&vi) < 0)
    {
      printf("NX2D: VIDEOINFO failed errno=%d\n", errno);
      goto fail;
    }
  if (ioctl(v->fd, FBIOGET_PLANEINFO,
            (unsigned long)(uintptr_t)&pi) < 0)
    {
      printf("NX2D: PLANEINFO failed errno=%d\n", errno);
      goto fail;
    }
  printf("NX2D: display=%ux%u bpp=%u stride=%lu fblen=%lu fbmem=%p\n",
         (unsigned)vi.xres, (unsigned)vi.yres, (unsigned)pi.bpp,
         (unsigned long)pi.stride, (unsigned long)pi.fblen,
         (void *)pi.fbmem);
  if (pi.bpp != 8 || vi.xres < NX2D_W || vi.yres < NX2D_H ||
      pi.stride < (size_t)vi.xres ||
      pi.fblen < (size_t)pi.stride * vi.yres)
    {
      printf("NX2D: unsupported framebuffer geometry/format\n");
      errno = ENOTSUP;
      goto fail;
    }
  g_sprite_loaded = nx2d_sprite_load(&g_player_sprite,
                                    "/mnt/sdcard/nx2d/player.nx2s") == 0;
  if (!g_sprite_loaded)
    printf("NX2D: sprite file unavailable; using rectangle fallback\n");
  for (unsigned i = 0; i < NX2D_ENEMY_VARIANTS; i++)
    {
      char filename[64];
      snprintf(filename, sizeof(filename),
               "/mnt/sdcard/nx2d/enemy%u.nx2s", i);
      g_enemy_loaded[i] = nx2d_sprite_load(&g_enemy_sprites[i],
                                            filename) == 0;
      if (!g_enemy_loaded[i])
        printf("NX2D: %s unavailable; procedural enemy fallback\n", filename);
    }
  if (vi.xres == 1024 && vi.yres == 600)
    for (unsigned x = 0; x < 1024; ++x)
      g_xmap[x] = (uint16_t)((x * NX2D_W) / 1024);
  g_compose_us = g_scale_us = 0;
  g_bg_us = g_map_us = g_objects_us = 0;
  g_expand_us = g_write_us = 0;
  g_profile_frames = 0;
  v->width = vi.xres;
  v->height = vi.yres;
  v->stride = pi.stride;
  v->maplen = pi.fblen;
  v->backbuffer = (uint8_t *)malloc(NX2D_W * NX2D_H);
  if (!v->backbuffer) { errno = ENOMEM; goto fail; }

  /* Flat-address-space NuttX builds commonly expose the LTDC buffer
   * directly. Do not use this pointer in protected/kernel builds unless
   * the framebuffer is explicitly accessible from userspace.
   */
#if defined(CONFIG_BUILD_FLAT)
  if (pi.fbmem != NULL)
    {
      v->pixels = (uint8_t *)pi.fbmem;
      if (nx2d_palette(v->fd) < 0)
        { printf("NX2D: FBIOPUT_CMAP failed errno=%d\n", errno); goto fail; }
      printf("NX2D: direct framebuffer access, L8 palette loaded\n");
      return 0;
    }
#endif
  v->map = mmap(NULL, v->maplen, PROT_READ | PROT_WRITE,
                MAP_SHARED, v->fd, 0);
  if (v->map == MAP_FAILED)
    {
      printf("NX2D: mmap failed errno=%d\n", errno);
      v->map = NULL;
      goto fail;
    }
  v->pixels = (uint8_t *)v->map;
  if (nx2d_palette(v->fd) < 0)
    { printf("NX2D: FBIOPUT_CMAP failed errno=%d\n", errno); goto fail; }
  return 0;
fail:
  free(v->backbuffer);
  v->backbuffer = NULL;
  if (v->map) munmap(v->map, v->maplen);
  close(v->fd);
  v->fd = -1;
  return -1;
}
void nx2d_video_close(struct nx2d_video_s *v)
{
  for (unsigned i = 0; i < NX2D_ENEMY_VARIANTS; i++)
    {
      nx2d_sprite_free(&g_enemy_sprites[i]);
      g_enemy_loaded[i] = false;
    }
  nx2d_sprite_free(&g_player_sprite);
  g_sprite_loaded = false;
  free(v->backbuffer);
  if (v->map) munmap(v->map, v->maplen);
  if (v->fd >= 0) close(v->fd);
}
/* All drawing is clipped to the 320x224 logical surface. */
static void logical_rect(struct nx2d_video_s *v, int x, int y,
                         int w, int h, uint16_t color)
{
  if (x < 0) { w += x; x = 0; }
  if (y < 0) { h += y; y = 0; }
  if (x + w > NX2D_W) w = NX2D_W - x;
  if (y + h > NX2D_H) h = NX2D_H - y;
  if (w <= 0 || h <= 0) return;
  uint8_t c = rgb565_to_l8(color);
  for (int j = 0; j < h; ++j)
    memset(v->backbuffer + (size_t)(y + j) * NX2D_W + x, c, (size_t)w);
}

/* Two integer-only parallax layers, directly in the logical L8 surface.
 * RGB332 indices are nonzero; no SD-card assets are required. */
/* Original background for A/B timing and visual verification. */
static void nx2d_parallax_classic(uint8_t *dst, int camera)
{
  uint8_t far_top[NX2D_W], near_top[NX2D_W];
  for (int x = 0; x < NX2D_W; ++x)
    {
      int farx = (x + camera / 4) % 128;
      int nearx = (x + camera / 2) % 96;
      if (farx < 0) farx += 128;
      if (nearx < 0) nearx += 96;
      int f = farx < 64 ? farx : 128 - farx;
      int n = nearx < 48 ? nearx : 96 - nearx;
      far_top[x] = (uint8_t)(164 - f / 2);
      near_top[x] = (uint8_t)(189 - n / 2);
    }
  for (int y = 0; y < NX2D_H; ++y)
    {
      uint8_t *row = dst + (size_t)y * NX2D_W;
      memset(row, (uint8_t)(0x23 + (y * 3 / NX2D_H)), NX2D_W);
      for (int x = 0; x < NX2D_W; ++x)
        {
          if (y >= far_top[x]) row[x] = 0x49;
          if (y >= near_top[x]) row[x] = 0x2c;
        }
    }
}

/* Same terrain and colors, but use contiguous row runs instead of
 * per-pixel conditional stores. The far/near ranges are unchanged. */
static void nx2d_parallax_spans(uint8_t *dst, int camera)
{
  uint8_t far_top[NX2D_W], near_top[NX2D_W];
  int faroff = camera / 4;
  int nearoff = camera / 2;
  for (int x = 0; x < NX2D_W; ++x)
    {
      int f = (x + faroff) % 128;
      int n = (x + nearoff) % 96;
      if (f < 0) f += 128;
      if (n < 0) n += 96;
      far_top[x] = (uint8_t)(164 - (f < 64 ? f : 128 - f) / 2);
      near_top[x] = (uint8_t)(189 - (n < 48 ? n : 96 - n) / 2);
    }
  for (int y = 0; y < NX2D_H; ++y)
    {
      uint8_t *row = dst + (size_t)y * NX2D_W;
      memset(row, (uint8_t)(0x23 + (y * 3 / NX2D_H)), NX2D_W);
      /* Terrain only starts at y=132 (far) and y=165 (near). */
      if (y >= 132)
        {
          int x = 0;
          while (x < NX2D_W)
            {
              while (x < NX2D_W && y < far_top[x]) ++x;
              int begin = x;
              while (x < NX2D_W && y >= far_top[x]) ++x;
              if (x > begin) memset(row + begin, 0x49, (size_t)(x - begin));
            }
        }
      if (y >= 165)
        {
          int x = 0;
          while (x < NX2D_W)
            {
              while (x < NX2D_W && y < near_top[x]) ++x;
              int begin = x;
              while (x < NX2D_W && y >= near_top[x]) ++x;
              if (x > begin) memset(row + begin, 0x2c, (size_t)(x - begin));
            }
        }
    }
}

static unsigned g_bg_mode = 1;
void nx2d_video_set_background(unsigned mode)
{
  g_bg_mode = mode ? 1u : 0u;
  printf("NX2D: background=%s\n", g_bg_mode ? "spans" : "classic");
}

void nx2d_video_draw(struct nx2d_video_s *v, const struct nx2d_game_s *g)
{
  uint32_t c_bg0 = nx2d_video_cycles();
  uint64_t t0 = nx2d_us();
  /* Draw map in world coordinates into the 320x224 L8 backbuffer. */
  if (g_bg_mode) nx2d_parallax_spans(v->backbuffer, g->camera);
  else nx2d_parallax_classic(v->backbuffer, g->camera);
  uint64_t tbg = nx2d_us();
  uint32_t c_bg1 = nx2d_video_cycles();
  nx2d_tilemap_draw(&g_nx2d_demo_level, v->backbuffer,
                    NX2D_W, NX2D_W, NX2D_H, g->camera, 0);
  uint64_t tmap = nx2d_us();
  uint32_t c_map1 = nx2d_video_cycles();

  /* Player is positioned in world space and drawn in screen space. */
  int px = (g->x >> 16) - g->camera;
  int py = (g->y >> 16);
  if (g_sprite_loaded)
    {
      /* Frames: idle 0-1, run 2-7, jump 8-9, fire 10-11.
       * Timing is 60 Hz simulation ticks, not wall-clock draw calls.
       */
      unsigned frame;
      if (g->firing) frame = 10 + (g->ticks / 6) % 2;
      else if (!g->grounded) frame = 8 + (g->vy >= 0);
      else if (g->vx != 0) frame = 2 + (g->ticks / 5) % 6;
      else frame = (g->ticks / 30) % 2;
      nx2d_sprite_draw(&g_player_sprite, v->backbuffer,
                       NX2D_W, NX2D_W, NX2D_H, px, py,
                       frame, g->facing_left);
    }
  else
    {
      logical_rect(v, px, py, 16, 32, 0xf800);
      logical_rect(v, px + 3, py + 3, 10, 8, 0xffc0);
    }

  /* Projectiles and procedural enemy sprites: no extra SD assets needed. */
  for (unsigned i = 0; i < NX2D_MAX_BULLETS; i++)
    {
      const struct nx2d_bullet_s *b = &g->bullets[i];
      if (b->active)
        logical_rect(v, b->x - g->camera, b->y, 5, 3,
                     b->enemy ? 0xf800 : 0xffe0);
    }
  for (unsigned i = 0; i < NX2D_MAX_ENEMIES; i++)
    {
      const struct nx2d_enemy_s *e = &g->enemies[i];
      if (!e->active) continue;
      int ex = e->x - g->camera;
      if (ex < -16 || ex >= NX2D_W) continue;
      /* Variant chosen by enemy slot, no changes to enemy AI or hitboxes.
       * Frames 0-3 patrol, 4-7 attack, 8-9 hurt, 10-11 death.
       */
      unsigned variant = i % NX2D_ENEMY_VARIANTS;
      if (e->dying)
        {
          /* Fade out with shrinking flash while keeping the death pose. */
          int r = (24 - e->death_age) / 3;
          if (r > 0)
            logical_rect(v, ex + 8 - r, e->y + 16 - r,
                         2 * r, 2 * r, 0xffe0);
          continue;
        }
      if (g_enemy_loaded[variant])
        {
          unsigned frame;
          if (e->flash)
            frame = 8 + ((g->ticks / 3) & 1u);
          else if (e->cooldown > 45)
            frame = 4 + ((g->ticks / 5) & 3u);
          else
            frame = (g->ticks / 7 + i) & 3u;
          nx2d_sprite_draw(&g_enemy_sprites[variant], v->backbuffer,
                           NX2D_W, NX2D_W, NX2D_H, ex, e->y,
                           frame, e->direction < 0);
          continue;
        }
      /* Procedural 4-pose enemy animation, driven by simulation ticks.
       * Direction and flashing use existing game state. */
      unsigned pose = (g->ticks / 7 + i) & 3u;
      int stride = (pose == 0 || pose == 2) ? 0 : (pose == 1 ? 3 : -3);
      uint16_t body = e->flash ? 0xffff : 0x03e0;
      logical_rect(v, ex + 3, e->y, 10, 10,
                   e->flash ? 0xffff : 0x07e0);
      logical_rect(v, ex + 1, e->y + 10, 14, 14, body);
      logical_rect(v, ex + 2 + stride, e->y + 24, 5, 8, 0x001f);
      logical_rect(v, ex + 9 - stride, e->y + 24, 5, 8, 0x001f);
      logical_rect(v, ex + 5, e->y + 4, 6, 2, 0xf800);
      /* Gun and animated arm face the movement direction. */
      logical_rect(v, ex + (e->direction < 0 ? -5 : 13),
                   e->y + 13 + ((pose == 2) ? 1 : 0),
                   8, 3, 0x7bef);
    }
  /* Expanding explosion squares, no external art dependency. */
  for (unsigned i = 0; i < NX2D_MAX_EFFECTS; i++)
    {
      const struct nx2d_effect_s *fx = &g->effects[i];
      if (!fx->active) continue;
      int radius = fx->age < 9 ? fx->age + 2 : 20 - fx->age;
      if (radius < 1) radius = 1;
      logical_rect(v, fx->x - g->camera - radius,
                   fx->y - radius, radius * 2, radius * 2,
                   fx->age & 2 ? 0xf800 : 0xffe0);
      logical_rect(v, fx->x - g->camera - radius / 2,
                   fx->y - radius / 2, radius, radius, 0xffff);
    }
  /* V16 checkpoints: visible world-space posts. Activated posts glow. */
  for (unsigned i = 1; i <= 2; ++i)
    {
      const int world_x = i == 1 ? 600 : 1200;
      const int sy = 154;
      const int sx = world_x - g->camera;
      if (sx < -10 || sx >= NX2D_W) continue;
      const uint32_t pole = g->checkpoint >= i ? 0x07e0 : 0x7bef;
      logical_rect(v, sx + 3, sy, 2, 40, pole);
      logical_rect(v, sx + 5, sy + 2, 11, 7,
                   g->checkpoint >= i ? 0xffe0 : 0xf800);
    }

  /* V15 collectibles: simple animated 8x8 tokens, drawn in screen space.
   * A two-pixel highlight alternates every 8 simulation ticks. */
  for (unsigned i = 0; i < NX2D_MAX_PICKUPS; ++i)
    {
      const struct nx2d_pickup_s *p = &g->pickups[i];
      if (!p->active) continue;
      int sx = p->x - g->camera;
      if (sx < -8 || sx >= NX2D_W) continue;
      logical_rect(v, sx + 2, p->y, 4, 8, 0xffe0);
      logical_rect(v, sx, p->y + 2, 8, 4, 0xffe0);
      logical_rect(v, sx + ((g->ticks / 8) & 1u ? 4 : 2),
                   p->y + 2, 2, 2, 0xffff);
    }
  /* HUD: health, kills, selected weapon. */
  logical_rect(v, 0, 0, 112, 12, 0x0000);
  for (unsigned i = 0; i < g->hp; i++)
    logical_rect(v, 4 + (int)i * 13, 3, 10, 6, 0xf800);
  const uint16_t weapon_color[3] = {0x07ff, 0xffe0, 0xf81f};
  for (unsigned i = 0; i <= g->weapon; i++)
    logical_rect(v, 116 + (int)i * 10, 3, 7, 6,
                 weapon_color[g->weapon]);
  for (unsigned i = 0; i < g->kills; i++)
    logical_rect(v, 76 + (int)i * 5, 4, 3, 4, 0xffe0);

  /* Score progress: one gold marker per collected token.
   * Keep HUD writes bounded, even when more levels are added later. */
  logical_rect(v, 156, 0, 112, 12, 0x0000);
  unsigned shown = g->pickups_collected;
  if (shown > NX2D_MAX_PICKUPS) shown = NX2D_MAX_PICKUPS;
  for (unsigned i = 0; i < shown; ++i)
    logical_rect(v, 160 + (int)i * 10, 3, 7, 6, 0xffe0);

  uint64_t t1 = nx2d_us();
  uint32_t c_obj1 = nx2d_video_cycles();
  g_v19_cycles.bg += (uint32_t)(c_bg1 - c_bg0);
  g_v19_cycles.map += (uint32_t)(c_map1 - c_bg1);
  g_v19_cycles.objects += (uint32_t)(c_obj1 - c_map1);
  g_v19_cycles.frames++;
  g_bg_us += tbg - t0;
  g_map_us += tmap - tbg;
  g_objects_us += t1 - tmap;
  /* Precomputed X lookup and one expansion per unique source row.
   * DMA2D cannot perform this arbitrary nearest-neighbor scaling. */
  if (v->width != 1024 || v->height != 600) return;
  unsigned previous_sy = NX2D_H;
  uint64_t expand_ticks = 0, write_ticks = 0;
  uint32_t expand_cycles = 0, write_cycles = 0;
  for (unsigned y = 0; y < 600; ++y)
    {
      unsigned sy = y * NX2D_H / 600;
      uint8_t *dst = v->pixels + (size_t)y * v->stride;
      bool duplicate = sy == previous_sy;
      if (!duplicate)
        {
          const uint8_t *src = v->backbuffer + (size_t)sy * NX2D_W;
          uint32_t ca = nx2d_video_cycles();
          uint64_t ta = nx2d_us();
          if (g_scaler_mode == 5)
            nx2d_expand_packed(src);
          else if (g_scaler_mode == 6 || g_scaler_mode == 7 || g_scaler_mode == 8)
            nx2d_expand_ratio(src);
          else
            for (unsigned x = 0; x < 1024; ++x)
              g_scaled_row[x] = src[g_xmap[x]];
          expand_ticks += nx2d_us() - ta;
          expand_cycles += (uint32_t)(nx2d_video_cycles() - ca);
          previous_sy = sy;
        }
      const uint8_t *prev = y ? dst - v->stride : NULL;
      uint32_t cw = nx2d_video_cycles();
      uint64_t tw = nx2d_us();
      nx2d_scale_copy(dst, prev, duplicate && y != 0);
      write_ticks += nx2d_us() - tw;
      write_cycles += (uint32_t)(nx2d_video_cycles() - cw);
    }
  uint64_t t2 = nx2d_us();
  g_v19_cycles.expand += expand_cycles;
  g_v19_cycles.fbwrite += write_cycles;
  g_compose_us += t1 - t0;
  g_scale_us += t2 - t1;
  g_expand_us += expand_ticks;
  g_write_us += write_ticks;
  if (++g_profile_frames >= 120)
    {
      if (false && g_detailed_profile)
        {
      printf("NX2D PERF: bg=%lu map=%lu objects=%lu us avg/120\n",
             (unsigned long)(g_bg_us / g_profile_frames),
             (unsigned long)(g_map_us / g_profile_frames),
             (unsigned long)(g_objects_us / g_profile_frames));
      printf("NX2D PERF: compose=%lu us scale=%lu us render=%lu us avg/120\n",
             (unsigned long)(g_compose_us / g_profile_frames),
             (unsigned long)(g_scale_us / g_profile_frames),
             (unsigned long)((g_compose_us + g_scale_us) / g_profile_frames));
      printf("NX2D PERF: expand=%lu us fbwrite=%lu us avg/120 "
             "(timed sections include clock overhead)\n",
             (unsigned long)(g_expand_us / g_profile_frames),
             (unsigned long)(g_write_us / g_profile_frames));
        }
      g_profile_frames = 0;
      g_compose_us = g_scale_us = 0;
      g_bg_us = g_map_us = g_objects_us = 0;
  g_expand_us = g_write_us = 0;
    }
  /* Framebuffer must remain coherent with LTDC. */
}
