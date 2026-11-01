/* T2GEN V9.1: Genesis Mode 5 plane composition and debug views.
 * 1024x600 NuttX L8 framebuffer; no window plane or shadow/highlight.
 */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <nuttx/video/fb.h>
#ifdef CONFIG_ARMV7M_DCACHE
# include <nuttx/cache.h>
#endif
#include "t2gen_vdp.h"
#include "t2gen_render.h"
#define OUT_W 1024u
#define OUT_H 600u
#define SRC_H 224u

#ifdef CONFIG_STM32_DMA2D
/* Kernel-owned DMA2D helper added by patches/stm32_dma2d_t2gen.patch. */
extern int stm32_dma2d_t2gen_copy_l8x2(const void *source, void *dest,
                                         unsigned source_stride, unsigned dest_stride,
                                         unsigned width_bytes, unsigned height);
static uint8_t *g_dma_lines;
static bool g_dma_enabled;
#endif

/* 0=composite; 1=A; 2=B; 3=priority; 4=A+sprites; 5=B+sprites. */
static unsigned g_view;
void t2gen_render_set_view(unsigned view) { g_view = view <= 5u ? view : 0u; }

static uint16_t vrword(const struct t2gen_vdp_s *v, uint32_t addr)
{
  return ((uint16_t)v->vram[addr & 65535u] << 8) |
         v->vram[(addr + 1u) & 65535u];
}
/* V9.8: lazy 8x8 tile cache. Each tile is decoded at most once per
 * snapshot, avoiding hundreds of thousands of VRAM nibble extractions.
 * 2048 * 64 = 128 KiB; allocated from NuttX heap, not the framebuffer.
 */
#define T2GEN_TILE_COUNT 2048u
#define T2GEN_TILE_BYTES 64u
static uint8_t *g_tile_cache;
static uint16_t g_tile_stamp[T2GEN_TILE_COUNT];
static uint16_t g_tile_epoch;
static uint32_t g_tile_misses;
static bool g_cache_ready;

static void tile_cache_begin(void)
{
  if (!g_tile_cache)
    g_tile_cache = (uint8_t *)malloc(T2GEN_TILE_COUNT * T2GEN_TILE_BYTES);
  g_cache_ready = g_tile_cache != NULL;
  if (++g_tile_epoch == 0)
    {
      memset(g_tile_stamp, 0, sizeof(g_tile_stamp));
      g_tile_epoch = 1;
    }
}

static inline uint8_t tile_pixel(const struct t2gen_vdp_s *v,
                                 uint16_t entry, unsigned x, unsigned y)
{
  unsigned px = x & 7u, py = y & 7u;
  if (entry & 0x0800u) px = 7u - px;
  if (entry & 0x1000u) py = 7u - py;
  unsigned tile = entry & 0x07ffu;
  uint8_t pixel;
  if (g_cache_ready)
    {
      if (g_tile_stamp[tile] != g_tile_epoch)
        {
          uint8_t *out = g_tile_cache + tile * 64u;
          unsigned addr = tile * 32u;
          for (unsigned row = 0; row < 8u; ++row)
            for (unsigned col = 0; col < 4u; ++col)
              {
                uint8_t pair = v->vram[(addr + row * 4u + col) & 65535u];
                out[row * 8u + col * 2u] = pair >> 4;
                out[row * 8u + col * 2u + 1u] = pair & 15u;
              }
          g_tile_stamp[tile] = g_tile_epoch;
          ++g_tile_misses;
        }
      pixel = g_tile_cache[tile * 64u + py * 8u + px];
    }
  else
    {
      unsigned addr = (tile * 32u + py * 4u + (px >> 1)) & 65535u;
      uint8_t pair = v->vram[addr];
      pixel = (px & 1u) ? (pair & 15u) : (pair >> 4);
    }
  return pixel ? (uint8_t)((((entry >> 13) & 3u) << 4) | pixel) : 0;
}
/* V11: resolve a cached decoded tile row once per tile span rather than
 * calling tile_pixel() for each individual background pixel. */
static inline const uint8_t *tile_row_cached(const struct t2gen_vdp_s *v,
                                             uint16_t entry, unsigned y)
{
  unsigned tile = entry & 0x07ffu;
  unsigned py = y & 7u;
  if (entry & 0x1000u) py = 7u - py;
  if (g_tile_stamp[tile] != g_tile_epoch)
    {
      uint8_t *out = g_tile_cache + tile * 64u;
      unsigned addr = tile * 32u;
      for (unsigned row = 0; row < 8u; ++row)
        for (unsigned col = 0; col < 4u; ++col)
          {
            uint8_t pair = v->vram[(addr + row * 4u + col) & 65535u];
            out[row * 8u + col * 2u] = pair >> 4;
            out[row * 8u + col * 2u + 1u] = pair & 15u;
          }
      g_tile_stamp[tile] = g_tile_epoch;
      ++g_tile_misses;
    }
  return g_tile_cache + tile * 64u + py * 8u;
}
static inline uint8_t tile_row_pixel(const uint8_t *row,
                                      uint16_t entry, unsigned x)
{
  unsigned px = x & 7u;
  if (entry & 0x0800u) px = 7u - px;
  uint8_t pixel = row[px];
  return pixel ? (uint8_t)((((entry >> 13) & 3u) << 4) | pixel) : 0;
}
static unsigned plane_size(unsigned bits)
{
  static const unsigned sizes[4] = {32u, 64u, 128u, 128u};
  return sizes[bits & 3u];
}
static int16_t hscroll(const struct t2gen_vdp_s *v, unsigned plane, unsigned y)
{
  uint32_t base = ((uint32_t)(v->reg[13] & 0x3fu) << 10) & 65535u;
  unsigned mode = v->reg[11] & 3u;
  unsigned line = mode == 3u ? y : mode == 2u ? (y & ~7u) : 0u;
  /* Mode 1 is reserved; treat as full-screen scroll. */
  /* Horizontal scroll is an 11-bit signed displacement. */
  unsigned raw = vrword(v, base + 4u * line + 2u * plane) & 0x7ffu;
  return (int16_t)((raw ^ 0x400u) - 0x400u);
}
static int16_t vscroll(const struct t2gen_vdp_s *v, unsigned plane, unsigned x)
{
  unsigned column = (v->reg[11] & 4u) ? ((x >> 4) * 2u) : 0u;
  unsigned idx = (column + plane) % 40u;
  /* Vertical scroll is a 10-bit signed displacement. */
  unsigned raw = v->vsram[idx] & 0x3ffu;
  return (int16_t)((raw ^ 0x200u) - 0x200u);
}
static uint16_t plane_entry(const struct t2gen_vdp_s *v, unsigned plane,
                            unsigned x, unsigned y, unsigned cols,
                            unsigned rows)
{
  uint32_t base = plane == 0u ?
      (((uint32_t)(v->reg[2] & 0x38u) << 10) & 65535u) :
      (((uint32_t)(v->reg[4] & 7u) << 13) & 65535u);
  return vrword(v, base + 2u * (((y >> 3) & (rows - 1u)) * cols +
                                ((x >> 3) & (cols - 1u))));
}
/* Mode 5 window: register 3 selects name table, registers 17/18
 * select horizontal/vertical window side and position. Window replaces
 * plane A at selected screen coordinates, not an extra transparent layer.
 * Horizontal position units are 16 pixels, vertical units are 8 pixels.
 */
static bool window_active(const struct t2gen_vdp_s *v, unsigned x,
                          unsigned y, unsigned h40)
{
  unsigned hx=(v->reg[17]&0x1fu)*16u;
  unsigned vy=(v->reg[18]&0x1fu)*8u;
  bool h=(v->reg[17]&0x80u) ? x>=hx : x<hx;
  bool vert=(v->reg[18]&0x80u) ? y>=vy : y<vy;
  (void)h40;
  return h || vert;
}
static uint16_t window_entry(const struct t2gen_vdp_s *v,
                             unsigned x, unsigned y, unsigned h40)
{
  uint32_t base=((uint32_t)(v->reg[3] & (h40 ? 0x3cu : 0x3eu)) << 10) & 65535u;
  unsigned stride=h40 ? 64u : 32u;
  return vrword(v,base+2u*((y>>3)*stride+(x>>3)));
}
/* V12: rasterize each background as short decoded-tile spans.  Splitting
 * at tile edges AND 16-pixel vertical-scroll boundaries preserves the
 * previous column-scroll behavior, including non-tile-aligned H-scroll. */
/* V20: one 16-bit lane per plane pixel: low byte is palette index,
 * bit 8 is tile priority. The high bit remains set even for transparent
 * pixels, preserving the old separate-priority-buffer semantics. */
static void background_scanline(const struct t2gen_vdp_s *v,
                                unsigned plane, unsigned y, unsigned width,
                                unsigned cols, unsigned rows, int hs,
                                const int16_t *scroll, uint16_t *out)
{
  const unsigned xmask = cols * 8u - 1u;
  const unsigned ymask = rows * 8u - 1u;
  const uint32_t table_base = plane == 0u ?
      (((uint32_t)(v->reg[2] & 0x38u) << 10) & 65535u) :
      (((uint32_t)(v->reg[4] & 7u) << 13) & 65535u);
  unsigned x = 0;
  while (x < width)
    {
      unsigned sx = ((unsigned)((int)x - hs)) & xmask;
      unsigned sy = (y + (unsigned)scroll[x]) & ymask;
      unsigned n = 8u - (sx & 7u);
      unsigned remaining = 16u - (x & 15u);
      if (n > remaining) n = remaining;
      if (n > width - x) n = width - x;
      uint32_t offset = (((sy >> 3) & (rows - 1u)) * cols +
                         ((sx >> 3) & (cols - 1u))) << 1;
      uint16_t entry = vrword(v, table_base + offset);
      const uint16_t pal = (uint16_t)(((entry >> 13) & 3u) << 4);
      const uint16_t pri = (entry & 0x8000u) ? 0x0100u : 0u;
      if (g_cache_ready)
        {
          const uint8_t *row = tile_row_cached(v, entry, sy);
          unsigned tx = sx & 7u;
          if (entry & 0x0800u)
            for (unsigned k = 0; k < n; ++k)
              {
                uint8_t c = row[7u - tx - k];
                out[x + k] = pri | (c ? (pal | c) : 0u);
              }
          else
            for (unsigned k = 0; k < n; ++k)
              {
                uint8_t c = row[tx + k];
                out[x + k] = pri | (c ? (pal | c) : 0u);
              }
        }
      else
        for (unsigned k = 0; k < n; ++k)
          out[x + k] = pri | tile_pixel(v, entry, sx + k, sy);
      x += n;
    }
}

static void window_scanline(const struct t2gen_vdp_s *v, unsigned y,
                            unsigned x0, unsigned x1, unsigned h40,
                            uint16_t *out)
{
  unsigned x = x0;
  while (x < x1)
    {
      unsigned n = 8u - (x & 7u);
      if (n > x1 - x) n = x1 - x;
      uint16_t entry = window_entry(v, x, y, h40);
      const uint16_t pal = (uint16_t)(((entry >> 13) & 3u) << 4);
      const uint16_t pri = (entry & 0x8000u) ? 0x0100u : 0u;
      if (g_cache_ready)
        {
          const uint8_t *row = tile_row_cached(v, entry, y);
          unsigned tx = x & 7u;
          if (entry & 0x0800u)
            for (unsigned k = 0; k < n; ++k)
              {
                uint8_t c = row[7u - tx - k];
                out[x + k] = pri | (c ? (pal | c) : 0u);
              }
          else
            for (unsigned k = 0; k < n; ++k)
              {
                uint8_t c = row[tx + k];
                out[x + k] = pri | (c ? (pal | c) : 0u);
              }
        }
      else
        for (unsigned k = 0; k < n; ++k)
          out[x + k] = pri | tile_pixel(v, entry, x + k, y);
      x += n;
    }
}
struct sprite_s
{
  int x, y;
  unsigned w, h;
  uint16_t attr;
};
static unsigned read_sprites(const struct t2gen_vdp_s *v,
                             struct sprite_s *sprites, unsigned limit,
                             unsigned h40)
{
  uint32_t base = ((uint32_t)(v->reg[5] & (h40 ? 0x7eu : 0x7fu)) << 9) & 65535u;
  unsigned index = 0, count = 0;
  bool seen[80] = {false};
  while (count < limit && index < limit && !seen[index])
    {
      uint32_t a = base + index * 8u;
      uint16_t yw = vrword(v, a);
      uint16_t sl = vrword(v, a + 2u);
      struct sprite_s *s = &sprites[count++];
      s->y = (int)(yw & 0x1ffu) - 128;
      s->x = (int)(vrword(v, a + 6u) & 0x1ffu) - 128;
      s->w = (((sl >> 10) & 3u) + 1u) * 8u;
      s->h = (((sl >> 8) & 3u) + 1u) * 8u;
      s->attr = vrword(v, a + 4u);
      seen[index] = true;
      index = sl & 0x7fu;
      if (index == 0u) break;
    }
  return count;
}
static uint8_t sprite_pixel(const struct t2gen_vdp_s *v,
                            const struct sprite_s *s, unsigned x, unsigned y)
{
  if ((int)x < s->x || (int)y < s->y || x >= (unsigned)(s->x + (int)s->w) ||
      y >= (unsigned)(s->y + (int)s->h)) return 0;
  unsigned dx = (unsigned)((int)x - s->x), dy = (unsigned)((int)y - s->y);
  if (s->attr & 0x0800u) dx = s->w - 1u - dx;
  if (s->attr & 0x1000u) dy = s->h - 1u - dy;
  /* Genesis sprite patterns are arranged column-major. */
  unsigned tile = ((s->attr & 0x07ffu) +
                   (dx >> 3) * (s->h >> 3) + (dy >> 3)) & 0x07ffu;
  uint16_t entry = (uint16_t)((s->attr & 0x6000u) | tile);
  return tile_pixel(v, entry, dx, dy);
}
/* Keep framebuffer open across emulated frames. Avoid full-screen clearing,
 * per-pixel VDP scroll-table reads, and per-pixel sprite-list traversal.
 * The screen is 1024x600 L8, centered 2x with 256/320x224 input.
 */
static int g_fd = -1;
static struct fb_planeinfo_s g_pi;
static unsigned g_last_w;
static unsigned g_render_calls;
static unsigned g_render_attempts;
static uint64_t g_compose_us, g_transfer_us;
/* V18: measured stage totals, microseconds. */
static uint64_t g_v18_setup_us, g_v18_sprite_us, g_v18_bg_us;
static uint64_t g_v18_window_us, g_v18_mix_us;
static uint64_t g_v18_dma_cache_us, g_v18_dma_copy_us;

static uint32_t g_dma_ok, g_dma_fail, g_cpu_fallback;
static uint32_t g_dma_max_us;
static uint64_t timestamp_us(void)
{
  struct timeval t;
  gettimeofday(&t, NULL);
  return (uint64_t)t.tv_sec * 1000000ull + (uint64_t)t.tv_usec;
}
void t2gen_render_print_perf(void)
{
  printf("T2GEN V20 STAGES: renders=%lu setup_ms=%llu sprites_ms=%llu "
         "background_ms=%llu window_ms=%llu mix_scale_ms=%llu "
         "dma_cache_ms=%llu dma_copy_ms=%llu\n",
         (unsigned long)g_render_calls,
         (unsigned long long)(g_v18_setup_us/1000ull),
         (unsigned long long)(g_v18_sprite_us/1000ull),
         (unsigned long long)(g_v18_bg_us/1000ull),
         (unsigned long long)(g_v18_window_us/1000ull),
         (unsigned long long)(g_v18_mix_us/1000ull),
         (unsigned long long)(g_v18_dma_cache_us/1000ull),
         (unsigned long long)(g_v18_dma_copy_us/1000ull));
  printf("T2GEN V20 AVG_US: setup=%llu sprites=%llu background=%llu "
         "window=%llu mix_scale=%llu dma_cache=%llu dma_copy=%llu\n",
         (unsigned long long)(g_render_calls ? g_v18_setup_us/g_render_calls : 0),
         (unsigned long long)(g_render_calls ? g_v18_sprite_us/g_render_calls : 0),
         (unsigned long long)(g_render_calls ? g_v18_bg_us/g_render_calls : 0),
         (unsigned long long)(g_render_calls ? g_v18_window_us/g_render_calls : 0),
         (unsigned long long)(g_render_calls ? g_v18_mix_us/g_render_calls : 0),
         (unsigned long long)(g_render_calls ? g_v18_dma_cache_us/g_render_calls : 0),
         (unsigned long long)(g_render_calls ? g_v18_dma_copy_us/g_render_calls : 0));

  printf("T2GEN V9.6 VIDEO PERF: renders=%lu compose_ms=%llu dma_ms=%llu dma_max_us=%lu dma_ok=%lu dma_fail=%lu cpu_fallback=%lu avg_compose_us=%llu avg_dma_us=%llu tile_misses=%lu tile_cache=%u\n",
         (unsigned long)g_render_calls,
         (unsigned long long)(g_compose_us/1000ull),
         (unsigned long long)(g_transfer_us/1000ull),
         (unsigned long)g_dma_max_us,
         (unsigned long)g_dma_ok,(unsigned long)g_dma_fail,
         (unsigned long)g_cpu_fallback,
         (unsigned long long)(g_render_calls ? g_compose_us/g_render_calls : 0),
         (unsigned long long)(g_dma_ok ? g_transfer_us/g_dma_ok : 0),
         (unsigned long)g_tile_misses, (unsigned)g_cache_ready);
}

/* V21: fixed-VDP-state repeat benchmark. The CPU is NOT advanced between
 * repetitions. This is deliberately separate from the gameplay FPS test.
 * Warm-up render is excluded from measurements, and all stage counters are
 * measured by differences to avoid contamination by the prior gameplay run.
 */
int t2gen_render_benchmark(const char *device, unsigned repeats)
{
  if (!device || strcmp(device, "none") == 0)
    {
      printf("T2GEN V21 BENCH: requires a framebuffer device\n");
      return -1;
    }
  if (repeats < 2u || repeats > 1000u)
    {
      printf("T2GEN V21 BENCH: repeats must be 2..1000\n");
      return -1;
    }
  if (t2gen_render_snapshot(device) < 0)
    return -1;
  const uint64_t b_bg = g_v18_bg_us;
  const uint64_t b_mix = g_v18_mix_us;
  const uint64_t b_spr = g_v18_sprite_us;
  const uint64_t b_win = g_v18_window_us;
  const uint64_t b_dma = g_v18_dma_copy_us;
  const uint64_t b_comp = g_compose_us;
  const uint32_t b_miss = g_tile_misses;
  const uint32_t b_fail = g_dma_fail;
  const uint64_t begin = timestamp_us();
  for (unsigned i = 0; i < repeats; ++i)
    if (t2gen_render_snapshot(device) < 0)
      {
        printf("T2GEN V21 BENCH: failed at repeat=%u\n", i);
        return -1;
      }
  const uint64_t wall = timestamp_us() - begin;
  printf("T2GEN V21 FIXED: repeats=%u wall_us=%llu avg_wall_us=%llu "
         "background_us=%llu mix_scale_us=%llu sprites_us=%llu "
         "window_us=%llu dma_copy_us=%llu compose_us=%llu "
         "tile_misses=%lu dma_fail=%lu\n",
         repeats, (unsigned long long)wall,
         (unsigned long long)(wall / repeats),
         (unsigned long long)((g_v18_bg_us - b_bg) / repeats),
         (unsigned long long)((g_v18_mix_us - b_mix) / repeats),
         (unsigned long long)((g_v18_sprite_us - b_spr) / repeats),
         (unsigned long long)((g_v18_window_us - b_win) / repeats),
         (unsigned long long)((g_v18_dma_copy_us - b_dma) / repeats),
         (unsigned long long)((g_compose_us - b_comp) / repeats),
         (unsigned long)(g_tile_misses - b_miss),
         (unsigned long)(g_dma_fail - b_fail));
  return 0;
}

static uint16_t g_last_cram[64];
static bool g_palette_valid;
static uint8_t g_red[64], g_green[64], g_blue[64];

static int framebuffer_init(const char *device)
{
  struct fb_videoinfo_s vi;
  if (g_fd >= 0) return 0;
  g_fd = open(device, O_RDWR);
  if (g_fd < 0) goto fail;
  if (ioctl(g_fd, FBIOGET_VIDEOINFO, (unsigned long)(uintptr_t)&vi) < 0 ||
      ioctl(g_fd, FBIOGET_PLANEINFO, (unsigned long)(uintptr_t)&g_pi) < 0 ||
      vi.xres != OUT_W || vi.yres != OUT_H || g_pi.bpp != 8 ||
      g_pi.stride < OUT_W || g_pi.fblen < g_pi.stride * OUT_H ||
      !g_pi.fbmem) goto fail;
#ifdef CONFIG_STM32_DMA2D
  /* Source must reside in DMA-accessible SRAM/SDRAM, never DTCM. */
  g_dma_lines = (uint8_t *)memalign(32, 640u * SRC_H);
  if (g_dma_lines && (uintptr_t)g_dma_lines >= 0x24000000u &&
      (uintptr_t)g_dma_lines < 0xe0000000u)
    {
      g_dma_enabled = true;
      printf("T2GEN V9.5: DMA2D staging=%p\n", g_dma_lines);
    }
  else
    {
      printf("T2GEN V9.5: no DMA-accessible staging; CPU fallback\n");
      free(g_dma_lines);
      g_dma_lines = NULL;
    }
#endif
  printf("T2GEN V9.8.2: framebuffer ready fd=%d fb=%p stride=%lu DMA=%u\n",
         g_fd, g_pi.fbmem, (unsigned long)g_pi.stride,
#ifdef CONFIG_STM32_DMA2D
         (unsigned)g_dma_enabled
#else
         0u
#endif
         );
  /* Clear only on initial setup; the active rectangle is fully overwritten. */
  for (unsigned y=0; y<OUT_H; ++y)
    memset((uint8_t *)g_pi.fbmem + y*g_pi.stride, 0, OUT_W);
#ifdef CONFIG_ARMV7M_DCACHE
  up_clean_dcache((uintptr_t)g_pi.fbmem,
                  (uintptr_t)g_pi.fbmem + g_pi.stride*OUT_H);
#endif
  return 0;
fail:
  printf("T2GEN V9.1: framebuffer init failed errno=%d\n", errno);
  if (g_fd >= 0) close(g_fd);
  g_fd=-1;
  return -1;
}

/* Build one sprite layer per scanline. The original renderer searched the
 * entire visible sprite list twice for every pixel. Preserve linked-list
 * priority: first nontransparent sprite wins for each priority class. */
/* V16: draw a sprite as decoded 8-pixel tile-row spans.  A sprite's
 * pattern tiles are column-major, and flipping applies to the complete
 * sprite, not separately to each tile.  The first nonzero pixel in each
 * priority plane wins, preserving the previous linked-list behavior. */
static void sprite_scanline(const struct t2gen_vdp_s *v,
                            const struct sprite_s *sprites,
                            const uint8_t *indices, unsigned count,
                            unsigned y, unsigned width,
                            uint8_t low[320], uint8_t high[320])
{
  memset(low, 0, 320);
  memset(high, 0, 320);
  for (unsigned i = 0; i < count; ++i)
    {
      const struct sprite_s *sp = &sprites[indices[i]];
      uint8_t *layer = (sp->attr & 0x8000u) ? high : low;
      int x0 = sp->x > 0 ? sp->x : 0;
      int x1 = sp->x + (int)sp->w;
      if (x1 > (int)width) x1 = (int)width;
      if (x0 >= x1) continue;
      unsigned dy = (unsigned)((int)y - sp->y);
      if (sp->attr & 0x1000u) dy = sp->h - 1u - dy;
      unsigned tiles_y = sp->h >> 3;
      unsigned tile_y = dy >> 3;
      uint8_t palette = (uint8_t)(((sp->attr >> 13) & 3u) << 4);
      bool flip_x = (sp->attr & 0x0800u) != 0u;
      int x = x0;
      while (x < x1)
        {
          unsigned dx = (unsigned)(x - sp->x);
          unsigned sx = flip_x ? sp->w - 1u - dx : dx;
          unsigned tile = ((sp->attr & 0x07ffu) +
                           (sx >> 3) * tiles_y + tile_y) & 0x07ffu;
          unsigned n = flip_x ? (sx & 7u) + 1u : 8u - (sx & 7u);
          if (n > (unsigned)(x1 - x)) n = (unsigned)(x1 - x);
          if (g_cache_ready)
            {
              const uint8_t *row = tile_row_cached(v, (uint16_t)tile, dy);
              unsigned tx = sx & 7u;
              for (unsigned k = 0; k < n; ++k)
                {
                  unsigned px = flip_x ? tx - k : tx + k;
                  uint8_t c = row[px];
                  if (c && !layer[x + (int)k])
                    layer[x + (int)k] = (uint8_t)(palette | c);
                }
            }
          else
            {
              uint16_t entry = (uint16_t)((sp->attr & 0x6000u) | tile);
              for (unsigned k = 0; k < n; ++k)
                {
                  unsigned px = flip_x ? (sx - k) : (sx + k);
                  uint8_t c = tile_pixel(v, entry, px, dy);
                  if (c && !layer[x + (int)k])
                    layer[x + (int)k] = c;
                }
            }
          x += (int)n;
        }
    }
}

int t2gen_render_snapshot(const char *device)
{
  const struct t2gen_vdp_s *v=t2gen_vdp_state();
  ++g_render_attempts;
  if (g_render_attempts <= 1u)
    printf("T2GEN V9.8.2: render enter attempt=%u device=%s\n",
           g_render_attempts, device ? device : "(null)");
  struct sprite_s sprites[80];
  unsigned h40=(v->reg[12]&1u)!=0u;
  unsigned src_w=h40?320u:256u;
  unsigned ox=(OUT_W-src_w*2u)/2u, oy=(OUT_H-SRC_H*2u)/2u;
  unsigned cols=plane_size(v->reg[16]&3u);
  unsigned rows=plane_size((v->reg[16]>>4)&3u);
  unsigned nsp=read_sprites(v,sprites,h40?80u:64u,h40);
  /* Precompute vertical scroll once per screen column, preserving the
   * signed offsets used by the previous per-pixel implementation. */
  int16_t scroll_a[320];
  int16_t scroll_b[320];
  for (unsigned x = 0; x < src_w; ++x)
    {
      scroll_a[x] = vscroll(v, 0u, x);
      scroll_b[x] = vscroll(v, 1u, x);
    }
  unsigned nonzero=0, sprite_pixels=0;
  if (framebuffer_init(device)<0)
    {
      printf("T2GEN V9.8.2: render framebuffer init failed attempt=%u errno=%d\n",
             g_render_attempts, errno);
      return -1;
    }
  uint64_t compose_start = timestamp_us();
  tile_cache_begin();
  if (g_render_attempts <= 1u)
    printf("T2GEN V9.8.2: cache=%p ready=%u epoch=%u\n",
           g_tile_cache, (unsigned)g_cache_ready, (unsigned)g_tile_epoch);
  /* H32/H40 mode transitions leave the former centered rectangle behind. */
  if (g_last_w && g_last_w!=src_w)
    {
      for (unsigned y=oy; y<oy+SRC_H*2u; ++y)
        memset((uint8_t *)g_pi.fbmem+y*g_pi.stride,0,OUT_W);
    }
  g_last_w=src_w;
     if (!g_palette_valid || memcmp(g_last_cram,v->cram,sizeof(g_last_cram)) != 0)
     {
  for (unsigned i=0;i<64u;++i)
      {
        uint16_t c=v->cram[i];
        g_red[i]=(uint8_t)((((c>>1)&7u)*255u)/7u);
        g_green[i]=(uint8_t)((((c>>5)&7u)*255u)/7u);
        g_blue[i]=(uint8_t)((((c>>9)&7u)*255u)/7u);
      }
    struct fb_cmap_s cmap;
    memset(&cmap,0,sizeof(cmap));
    cmap.first=0; cmap.len=64;
    cmap.red=g_red; cmap.green=g_green; cmap.blue=g_blue;
    if (ioctl(g_fd,FBIOPUT_CMAP,(unsigned long)(uintptr_t)&cmap)<0)
      {
        printf("T2GEN V9.1: palette ioctl errno=%d\n",errno);
        return -1;
      }
    
       memcpy(g_last_cram,v->cram,sizeof(g_last_cram));
       g_palette_valid=true;
     }
/* Cache the signed scroll values and screen-space Y for each scanline. */
  for (unsigned y=0;y<SRC_H;++y)
    {
      uint64_t v18_t = timestamp_us();
      uint8_t visible[20];
      unsigned count=0;
      for (unsigned i=0;i<nsp;++i)
        if ((int)y>=sprites[i].y && (int)y<sprites[i].y+(int)sprites[i].h)
          {
            if (count >= (h40?20u:16u)) break;
            visible[count++]=(uint8_t)i;
          }
      uint8_t sprite_lo[320], sprite_hi[320];
      memset(sprite_lo,0,sizeof(sprite_lo));
      memset(sprite_hi,0,sizeof(sprite_hi));
      if (g_view == 0u || g_view == 4u || g_view == 5u)
        sprite_scanline(v, sprites, visible, count, y, src_w,
                        sprite_lo, sprite_hi);
      g_v18_sprite_us += timestamp_us() - v18_t;
      v18_t = timestamp_us();
      int hs_a=hscroll(v,0,y), hs_b=hscroll(v,1,y);
      uint8_t *r0=(uint8_t *)g_pi.fbmem+(oy+2u*y)*g_pi.stride+ox;
      uint8_t *r1=r0+g_pi.stride;
#ifdef CONFIG_STM32_DMA2D
      if (g_dma_enabled) r0 = g_dma_lines + y * 640u;
#endif
      /* V12: compose pre-rasterized plane rows; no VRAM tile lookups in
       * the final per-pixel priority/sprite mixer. */
      uint16_t a_plane[320], b_plane[320];
      background_scanline(v, 0u, y, src_w, cols, rows, hs_a,
                          scroll_a, a_plane);
      background_scanline(v, 1u, y, src_w, cols, rows, hs_b,
                          scroll_b, b_plane);
      g_v18_bg_us += timestamp_us() - v18_t;
      v18_t = timestamp_us();
      /* V15: derive the enabled window region once per scanline, rather
       * than evaluating the register geometry for every source pixel. */
      unsigned hx = (v->reg[17] & 31u) * 16u;
      unsigned vy = (v->reg[18] & 31u) * 8u;
      bool full_window = (v->reg[18] & 0x80u) ? y >= vy : y < vy;
      unsigned wx0 = 0u, wx1 = 0u;
      if (full_window)
        wx1 = src_w;
      else if (v->reg[17] & 0x80u)
        {
          wx0 = hx < src_w ? hx : src_w;
          wx1 = src_w;
        }
      else
        wx1 = hx < src_w ? hx : src_w;
      if (wx1 > wx0)
        {
          window_scanline(v, y, wx0, wx1, h40,
                          a_plane);
        }
      g_v18_window_us += timestamp_us() - v18_t;
      v18_t = timestamp_us();
      /* V17: both the DMA staging buffer and LTDC L8 framebuffer have
       * even-aligned pixel starts. Each source pixel becomes one packed
       * 16-bit store (two identical L8 palette indices). This avoids
       * separate byte stores and repeated 2*x addressing. */
      uint16_t *restrict dst0 = (uint16_t *)(void *)r0;
      uint16_t *restrict dst1 = (uint16_t *)(void *)r1;
      const uint8_t backdrop = v->reg[7] & 0x3fu;
      if (g_view == 0u)
        {
          /* Six presence flags encode the original exact draw order.
           * The final lookup replaces the six overwrite branches. */
          for (unsigned x = 0; x < src_w; ++x)
            {
              uint16_t ap = a_plane[x], bp = b_plane[x];
              uint8_t a = (uint8_t)ap, b = (uint8_t)bp;
              uint8_t slo = sprite_lo[x], shi = sprite_hi[x];
              unsigned pa = ap & 0x100u, pb = bp & 0x100u;
              /* V19: exact Genesis priority order, highest first.
               * Skip constructing six mask bits, a seven-byte array and
               * the dependent selector-table load for every pixel. */
              uint8_t color;
              if (shi) color = shi;
              else if (a && pa) color = a;
              else if (b && pb) color = b;
              else if (slo) color = slo;
              else if (a) color = a;
              else if (b) color = b;
              else color = backdrop;
              nonzero += (color != 0u);
              sprite_pixels += (slo != 0u || shi != 0u);
              uint16_t pair = (uint16_t)color * 0x0101u;
              dst0[x] = pair;
#ifdef CONFIG_STM32_DMA2D
              if (!g_dma_enabled)
#endif
                dst1[x] = pair;
            }
          g_v18_mix_us += timestamp_us() - v18_t;
          continue;
        }
      /* Diagnostic modes retain the original straightforward mixer. */
      for (unsigned x=0; x<src_w; ++x)
        {
          uint16_t ap = a_plane[x], bp = b_plane[x];
          uint8_t a = (uint8_t)ap, b = (uint8_t)bp;
          unsigned pa = ap & 0x100u, pb = bp & 0x100u;
          uint8_t color=backdrop;
          if (g_view==1u) color=a?a:color;
          else if (g_view==2u) color=b?b:color;
          else if (g_view==3u)
            color=a?(pa?0x2fu:0x0fu):b?(pb?0x3fu:0x1fu):0;
          else
            {
              if (g_view==4u) b=0;
              if (g_view==5u) a=0;
              if (b&&!pb) color=b;
              if (a&&!pa) color=a;
              uint8_t slo=sprite_lo[x];
              uint8_t shi=sprite_hi[x];
              if (slo) color=slo;
              if (b&&pb) color=b;
              if (a&&pa) color=a;
              if (shi) color=shi;
              if (slo||shi) ++sprite_pixels;
            }
          if (color) ++nonzero;
          uint16_t pair = (uint16_t)color * 0x0101u;
          dst0[x] = pair;
#ifdef CONFIG_STM32_DMA2D
          if (!g_dma_enabled)
#endif
            dst1[x] = pair;
        }
      g_v18_mix_us += timestamp_us() - v18_t;
    }
#ifdef CONFIG_STM32_DMA2D
  if (g_dma_enabled)
    {
      g_compose_us += timestamp_us() - compose_start;
      uint64_t dma_start = timestamp_us();
#ifdef CONFIG_ARMV7M_DCACHE
      up_clean_dcache((uintptr_t)g_dma_lines,
                      (uintptr_t)g_dma_lines + 640u * SRC_H);
#endif
      g_v18_dma_cache_us += timestamp_us() - dma_start;
      uint64_t v18_copy_start = timestamp_us();
      uint8_t *dest = (uint8_t *)g_pi.fbmem + oy*g_pi.stride + ox;
      /* Copy packed pairs of L8 pixels as raw RGB565 words. The DMA2D
       * memory-to-memory engine does NOT interpret RGB565 color values. */
      int rc0 = stm32_dma2d_t2gen_copy_l8x2(g_dma_lines, dest,
                         640u, g_pi.stride*2u, src_w*2u, SRC_H);
      int rc1 = rc0 == 0 ?
        stm32_dma2d_t2gen_copy_l8x2(g_dma_lines, dest+g_pi.stride,
                         640u, g_pi.stride*2u, src_w*2u, SRC_H) : -1;
      g_v18_dma_copy_us += timestamp_us() - v18_copy_start;
      uint32_t dma_elapsed = (uint32_t)(timestamp_us() - dma_start);
      g_transfer_us += dma_elapsed;
      if (dma_elapsed > g_dma_max_us) g_dma_max_us = dma_elapsed;
      if (rc0 != 0 || rc1 != 0)
        {
          ++g_dma_fail;
          printf("T2GEN V9.5: DMA2D failure (%d,%d), CPU fallback\n", rc0, rc1);
          g_dma_enabled = false;
          /* Retry with CPU composition on the next snapshot. */
          return -1;
        }
      ++g_dma_ok;
    }
  else
    {
      g_compose_us += timestamp_us() - compose_start;
      ++g_cpu_fallback;
    }
#else
  g_compose_us += timestamp_us() - compose_start;
  ++g_cpu_fallback;
#endif
#ifdef CONFIG_ARMV7M_DCACHE
  /* Clean active rows only, including cache-line-aligned surrounding bytes. */
  uintptr_t begin=(uintptr_t)g_pi.fbmem+oy*g_pi.stride+ox;
  uintptr_t end=(uintptr_t)g_pi.fbmem+(oy+SRC_H*2u-1u)*g_pi.stride+ox+src_w*2u;
  /* NuttX cache maintenance accepts an address range; align conservatively. */
#ifdef CONFIG_STM32_DMA2D
  if (!g_dma_enabled)
#endif
    up_clean_dcache(begin & ~(uintptr_t)31u,(end+31u)&~(uintptr_t)31u);
#endif
  ++g_render_calls;
  if (g_render_calls==1u || (g_render_calls%512u)==0u)
    printf("T2GEN V9.1: render=%u mode=%s view=%u sprites=%u "
           "sprite_pixels=%u nonzero=%u plane=%ux%u "
           "A=%04lx B=%04lx SAT=%04lx WIN=%04lx R17=%02x R18=%02x H=%04x V=%04x\n",
           g_render_calls,h40?"H40":"H32",g_view,nsp,sprite_pixels,
           nonzero,cols,rows,
           (unsigned long)(((uint32_t)(v->reg[2]&0x38u)<<10)&65535u),
           (unsigned long)(((uint32_t)(v->reg[4]&7u)<<13)&65535u),
           (unsigned long)(((uint32_t)(v->reg[5]&(h40?0x7eu:0x7fu))<<9)&65535u),
           (unsigned long)(((uint32_t)(v->reg[3] & (h40?0x3cu:0x3eu))<<10)&65535u),
           v->reg[17],v->reg[18],
           (unsigned)vrword(v,((uint32_t)v->reg[13]&0x3fu)<<10),
           v->vsram[0]);
  return 0;
}
