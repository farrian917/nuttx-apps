#ifndef NX2D_H
#define NX2D_H
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#define NX2D_W 320
#define NX2D_H 224
#define NX2D_WORLD_W 2400
#define NX2D_BUTTON_LEFT  (1u << 0)
#define NX2D_BUTTON_RIGHT (1u << 1)
#define NX2D_BUTTON_JUMP  (1u << 2)
#define NX2D_BUTTON_QUIT  (1u << 3)
struct nx2d_video_s {
  int fd;
  uint8_t *map;
  size_t maplen;
  uint16_t *pixels;
  unsigned width, height, stride;
};
struct nx2d_game_s {
  int32_t x, y, vx, vy, camera;
  bool grounded;
  uint32_t ticks;
};
int nx2d_video_open(struct nx2d_video_s *v, const char *path);
void nx2d_video_close(struct nx2d_video_s *v);
void nx2d_video_draw(struct nx2d_video_s *v, const struct nx2d_game_s *g);
void nx2d_game_init(struct nx2d_game_s *g);
void nx2d_game_step(struct nx2d_game_s *g, uint32_t buttons);
int nx2d_input_open(const char *path);
uint32_t nx2d_input_read(int fd);
#endif
