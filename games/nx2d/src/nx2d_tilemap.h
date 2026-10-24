#ifndef NX2D_TILEMAP_H
#define NX2D_TILEMAP_H
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#define NX2D_TILE_SIZE 16
#define NX2D_TILE_EMPTY 0
#define NX2D_TILE_SOLID 1
struct nx2d_tilemap_s {
  const uint8_t *tiles;
  uint16_t width;
  uint16_t height;
};
/* All positions in logical 320x224 pixels; dst is L8, pitch bytes/row. */
void nx2d_tilemap_draw(const struct nx2d_tilemap_s *map,
                       uint8_t *dst, unsigned pitch,
                       unsigned view_w, unsigned view_h,
                       int camera_x, int camera_y);
bool nx2d_tilemap_solid(const struct nx2d_tilemap_s *map,
                        int world_x, int world_y);
int nx2d_tilemap_camera_x(const struct nx2d_tilemap_s *map,
                          int player_center_x, unsigned view_w);
#endif
