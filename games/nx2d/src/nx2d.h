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
#define NX2D_BUTTON_FIRE  (1u << 4)
#define NX2D_BUTTON_WEAPON (1u << 5)
struct nx2d_video_s {
  int fd;
  uint8_t *map;
  size_t maplen;
  uint8_t *pixels;
  uint8_t *backbuffer;
  unsigned width, height, stride;
};
#define NX2D_MAX_BULLETS 16
#define NX2D_MAX_ENEMIES 8
struct nx2d_bullet_s {
  int16_t x, y, vx;
  uint8_t active, enemy;
};
#define NX2D_MAX_EFFECTS 12
struct nx2d_effect_s { int16_t x, y; uint8_t age, active; };
struct nx2d_enemy_s {
  int16_t x, y;
  int8_t direction;
  uint8_t hp, active, flash, cooldown;
  uint8_t type, dying, death_age;
};
struct nx2d_game_s {
  int32_t x, y, vx, vy, camera;
  bool grounded;
  bool facing_left;
  bool firing;
  uint32_t ticks;
  uint32_t last_shot;
  uint16_t invulnerable;
  uint8_t hp, kills, weapon, previous_weapon;
  struct nx2d_effect_s effects[NX2D_MAX_EFFECTS];
  struct nx2d_bullet_s bullets[NX2D_MAX_BULLETS];
  struct nx2d_enemy_s enemies[NX2D_MAX_ENEMIES];
};
int nx2d_video_open(struct nx2d_video_s *v, const char *path);
void nx2d_video_close(struct nx2d_video_s *v);
void nx2d_video_set_scaler(struct nx2d_video_s *v, unsigned mode);
void nx2d_video_benchmark(struct nx2d_video_s *v, unsigned mode);
void nx2d_video_set_background(unsigned mode);
void nx2d_video_draw(struct nx2d_video_s *v, const struct nx2d_game_s *g);
void nx2d_game_init(struct nx2d_game_s *g);
void nx2d_game_step(struct nx2d_game_s *g, uint32_t buttons);
int nx2d_input_open(const char *path);
uint32_t nx2d_input_read(int fd);
#endif
