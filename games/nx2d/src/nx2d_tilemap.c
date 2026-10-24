#include "nx2d_tilemap.h"
#include <string.h>

static int clampi(int x, int lo, int hi)
{
  if (hi < lo) hi = lo;
  if (x < lo) return lo;
  if (x > hi) return hi;
  return x;
}

bool nx2d_tilemap_solid(const struct nx2d_tilemap_s *map,
                        int world_x, int world_y)
{
  int tx, ty;
  if (!map || !map->tiles || world_x < 0 || world_y < 0)
    return true;
  tx = world_x / NX2D_TILE_SIZE;
  ty = world_y / NX2D_TILE_SIZE;
  if (tx >= map->width || ty >= map->height) return true;
  return map->tiles[(size_t)ty * map->width + tx] == NX2D_TILE_SOLID;
}

int nx2d_tilemap_camera_x(const struct nx2d_tilemap_s *map,
                          int player_center_x, unsigned view_w)
{
  int max_x;
  if (!map) return 0;
  max_x = (int)map->width * NX2D_TILE_SIZE - (int)view_w;
  return clampi(player_center_x - (int)view_w / 2, 0, max_x);
}

/* Draw only visible solid tile spans; preserve empty background pixels. */
void nx2d_tilemap_draw(const struct nx2d_tilemap_s *map,
                       uint8_t *dst, unsigned pitch,
                       unsigned view_w, unsigned view_h,
                       int camera_x, int camera_y)
{
  if (!map || !map->tiles || !dst || pitch < view_w) return;
  const int ts = NX2D_TILE_SIZE;
  const int first_tx = camera_x >= 0 ? camera_x / ts : (camera_x - ts + 1) / ts;
  const int last_tx = (camera_x + (int)view_w - 1) >= 0 ?
    (camera_x + (int)view_w - 1) / ts :
    (camera_x + (int)view_w - ts) / ts;
  for (unsigned y = 0; y < view_h; ++y)
    {
      const int wy = camera_y + (int)y;
      const int ty = wy >= 0 ? wy / ts : (wy - ts + 1) / ts;
      uint8_t *row = dst + (size_t)y * pitch;
      if (ty < 0 || ty >= (int)map->height) continue;
      const uint8_t color = (uint8_t)(((wy % ts) + ts) % ts < 2 ? 0xe0 : 0x92);
      const uint8_t *tiles = map->tiles + (size_t)ty * map->width;
      for (int tx = first_tx; tx <= last_tx; ++tx)
        {
          if (tx < 0 || tx >= (int)map->width ||
              tiles[tx] != NX2D_TILE_SOLID) continue;
          int left = tx * ts - camera_x;
          int right = left + ts;
          if (left < 0) left = 0;
          if (right > (int)view_w) right = (int)view_w;
          if (right > left) memset(row + left, color, (size_t)(right - left));
        }
    }
}
