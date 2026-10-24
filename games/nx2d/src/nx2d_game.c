#include "nx2d.h"
#include "nx2d_tilemap.h"
#include "nx2d_level_demo.h"
#include <string.h>

#define FX(n) ((int32_t)(n) * 65536)
#define PLAYER_W 16
#define PLAYER_H 32

static bool blocked(int x, int y)
{
  const struct nx2d_tilemap_s *m = &g_nx2d_demo_level;
  return nx2d_tilemap_solid(m, x, y) ||
         nx2d_tilemap_solid(m, x + PLAYER_W - 1, y) ||
         nx2d_tilemap_solid(m, x, y + PLAYER_H - 1) ||
         nx2d_tilemap_solid(m, x + PLAYER_W - 1, y + PLAYER_H - 1);
}

/* Player-only collision rules: elevated tiles are one-way platforms.
 * The bottom two map rows remain fully solid ground. Enemy collision uses
 * blocked() unchanged, so their platform patrol remains intact. */
static bool player_ground_solid(int px, int py)
{
  const int ground_top = ((int)g_nx2d_demo_level.height - 2) * NX2D_TILE_SIZE;
  return py >= ground_top &&
         nx2d_tilemap_solid(&g_nx2d_demo_level, px, py);
}

static bool player_wall_blocked(int px, int py)
{
  return player_ground_solid(px, py) ||
         player_ground_solid(px + PLAYER_W - 1, py) ||
         player_ground_solid(px, py + PLAYER_H - 1) ||
         player_ground_solid(px + PLAYER_W - 1, py + PLAYER_H - 1);
}

static bool player_landing(int px, int old_y, int new_y)
{
  const int old_foot = old_y + PLAYER_H;
  const int new_foot = new_y + PLAYER_H;
  const int top = ((old_foot + NX2D_TILE_SIZE - 1) /
                   NX2D_TILE_SIZE) * NX2D_TILE_SIZE;

  /* Falling across the top of a tile, including an already aligned foot. */
  if (new_foot < old_foot || old_foot > top || new_foot < top)
    return false;

  return nx2d_tilemap_solid(&g_nx2d_demo_level, px, top) ||
         nx2d_tilemap_solid(&g_nx2d_demo_level,
                            px + PLAYER_W - 1, top);
}

/* Find a legal standing position at a requested X coordinate.  Enemies
 * must never start inside an elevated platform.  Both feet need support. */
static int enemy_spawn_y(int x)
{
  const int bottom = (int)g_nx2d_demo_level.height * NX2D_TILE_SIZE;
  for (int y = bottom - PLAYER_H - 1; y >= 0; --y)
    {
      if (!blocked(x, y) &&
          nx2d_tilemap_solid(&g_nx2d_demo_level, x, y + PLAYER_H) &&
          nx2d_tilemap_solid(&g_nx2d_demo_level,
                            x + PLAYER_W - 1, y + PLAYER_H))
        return y;
    }
  return -1;
}

void nx2d_game_init(struct nx2d_game_s *g)
{
  memset(g, 0, sizeof(*g));
  g->x = FX(40);
  g->y = FX(160);
  g->grounded = true;
  g->hp = 5;
  g->last_shot = 0;
  /* Fixed demonstration spawns, placed on the main ground. */
  static const int16_t spawn_x[] = {230, 400, 570, 760, 960, 1130};
  for (unsigned i = 0; i < sizeof(spawn_x) / sizeof(spawn_x[0]); i++)
    {
      int sx = spawn_x[i];
      int sy = enemy_spawn_y(sx);
      /* In case a spawn X is unusable, try nearby columns. */
      for (int d = 16; sy < 0 && d <= 96; d += 16)
        {
          sx = spawn_x[i] + d;
          sy = enemy_spawn_y(sx);
          if (sy < 0)
            {
              sx = spawn_x[i] - d;
              sy = enemy_spawn_y(sx);
            }
        }
      g->enemies[i].x = (int16_t)sx;
      g->enemies[i].y = (int16_t)(sy < 0 ? 0 : sy);
      g->enemies[i].hp = 3;
      g->enemies[i].active = sy >= 0;
      g->enemies[i].direction = -1;
      g->enemies[i].type = (uint8_t)(i % 3);
      if (g->enemies[i].type == 2 && g->enemies[i].active)
        g->enemies[i].y -= 52;
    }
}

void nx2d_game_step(struct nx2d_game_s *g, uint32_t buttons)
{
  int32_t target = 0;
  int x, y, desired, step;
  const int map_width = (int)g_nx2d_demo_level.width * NX2D_TILE_SIZE;

  if (buttons & NX2D_BUTTON_LEFT) target -= FX(2);
  if (buttons & NX2D_BUTTON_RIGHT) target += FX(2);
  g->vx = target;
  if (target < 0) g->facing_left = true;
  if (target > 0) g->facing_left = false;
  g->firing = (buttons & NX2D_BUTTON_FIRE) != 0;

  if ((buttons & NX2D_BUTTON_JUMP) && g->grounded)
    {
      g->vy = -FX(7);
      g->grounded = false;
    }

  g->vy += FX(1) / 3;
  if (g->vy > FX(8)) g->vy = FX(8);

  /* Pixel-stepped collision prevents tunneling through 16px tiles. */
  x = g->x >> 16;
  y = g->y >> 16;
  desired = (g->x + g->vx) >> 16;
  while (x != desired)
    {
      step = desired > x ? 1 : -1;
      if (x + step < 0 || x + step + PLAYER_W > map_width ||
          player_wall_blocked(x + step, y)) break;
      x += step;
    }
  g->x = FX(x);

  desired = (g->y + g->vy) >> 16;
  g->grounded = false;
  while (y != desired)
    {
      step = desired > y ? 1 : -1;
      if ((step > 0 && player_landing(x, y, y + step)) ||
          (step < 0 && player_wall_blocked(x, y + step)))
        {
          if (step > 0) g->grounded = true;
          g->vy = 0;
          break;
        }
      y += step;
    }
  g->y = FX(y);
  if (!g->grounded && g->vy >= 0 && player_landing(x, y, y + 1))
    g->grounded = true;

  g->camera = nx2d_tilemap_camera_x(&g_nx2d_demo_level,
                                     x + PLAYER_W / 2, NX2D_W);
  if (g->camera > map_width - NX2D_W)
    g->camera = map_width - NX2D_W;
  /* Edge-triggered weapon switching: pistol -> automatic -> shotgun. */
  if ((buttons & NX2D_BUTTON_WEAPON) && !g->previous_weapon)
    g->weapon = (g->weapon + 1) % 3;
  g->previous_weapon = (buttons & NX2D_BUTTON_WEAPON) != 0;

  const unsigned delay = g->weapon == 1 ? 5 : (g->weapon == 2 ? 22 : 12);
  if (g->firing && (g->ticks - g->last_shot >= delay || g->ticks == 0))
    {
      unsigned count = g->weapon == 2 ? 3 : 1;
      for (unsigned shot = 0; shot < count; shot++)
        {
          for (unsigned i = 0; i < NX2D_MAX_BULLETS; i++)
            {
              struct nx2d_bullet_s *b = &g->bullets[i];
              if (!b->active)
                {
                  b->x = (int16_t)(x + (g->facing_left ? -4 : PLAYER_W));
                  b->y = (int16_t)(y + 11 + (int)shot * 3);
                  b->vx = g->facing_left ? -8 : 8;
                  b->enemy = 0;
                  b->active = 1;
                  break;
                }
            }
        }
      g->last_shot = g->ticks;
    }

  /* Advance all bullets in single-pixel increments to avoid tunnelling. */
  for (unsigned i = 0; i < NX2D_MAX_BULLETS; i++)
    {
      struct nx2d_bullet_s *b = &g->bullets[i];
      if (!b->active) continue;
      int dir = b->vx > 0 ? 1 : -1;
      int distance = b->vx > 0 ? b->vx : -b->vx;
      for (int k = 0; k < distance && b->active; k++)
        {
          b->x += dir;
          if (b->x < 0 || b->x >= map_width ||
              nx2d_tilemap_solid(&g_nx2d_demo_level, b->x, b->y))
            { b->active = 0; break; }
          if (b->enemy)
            {
              if (!g->invulnerable && b->x + 4 > x && b->x < x + PLAYER_W &&
                  b->y + 3 > y && b->y < y + PLAYER_H)
                {
                  b->active = 0;
                  if (g->hp) g->hp--;
                  g->invulnerable = 90;
                  if (!g->hp) { nx2d_game_init(g); return; }
                }
            }
          else
            {
              for (unsigned j = 0; j < NX2D_MAX_ENEMIES; j++)
                {
                  struct nx2d_enemy_s *e = &g->enemies[j];
                  if (e->active && !e->dying && b->x + 4 > e->x && b->x < e->x + 16 &&
                      b->y + 3 > e->y && b->y < e->y + 32)
                    {
                      b->active = 0;
                      e->flash = 6;
                      if (--e->hp == 0)
                        {
                          e->dying = 1;
                          e->death_age = 0;
                          g->kills++;
                          for (unsigned q = 0; q < NX2D_MAX_EFFECTS; q++)
                            if (!g->effects[q].active)
                              {
                                g->effects[q].active = 1;
                                g->effects[q].age = 0;
                                g->effects[q].x = e->x + 8;
                                g->effects[q].y = e->y + 16;
                                break;
                              }
                        }
                      break;
                    }
                }
            }
        }
    }

  for (unsigned i = 0; i < NX2D_MAX_ENEMIES; i++)
    {
      struct nx2d_enemy_s *e = &g->enemies[i];
      if (!e->active) continue;
      if (e->dying)
        {
          if (++e->death_age >= 24) e->active = 0;
          continue;
        }
      /* Skip distant AI work until the camera approaches. */
      if (e->x < g->camera - 80 || e->x > g->camera + NX2D_W + 80)
        continue;
      if (e->flash) e->flash--;
      if (e->cooldown) e->cooldown--;

      /* Chase only when the player is nearby. Stay on solid ground. */
      int dx = x - e->x;
      if (e->type != 0 && dx > -220 && dx < 220)
        e->direction = dx < 0 ? -1 : 1;
      /* Fire only when the player is near and at approximately same height. */
      if (dx > -180 && dx < 180 && y > e->y - 20 && y < e->y + 20 &&
          !e->cooldown)
        {
          for (unsigned q = 0; q < NX2D_MAX_BULLETS; q++)
            if (!g->bullets[q].active)
              {
                g->bullets[q].active = 1;
                g->bullets[q].enemy = 1;
                g->bullets[q].x = e->x + (dx < 0 ? -3 : 16);
                g->bullets[q].y = e->y + 12;
                g->bullets[q].vx = dx < 0 ? -4 : 4;
                e->cooldown = 90 + (uint8_t)(i * 11);
                break;
              }
        }
      if (e->type == 2)
        {
          int ty = y - 56;
          if (ty < 20) ty = 20;
          if (ty > 128) ty = 128;
          if ((g->ticks & 3u) == 0)
            {
              int ny = e->y + (ty > e->y ? 1 : ty < e->y ? -1 : 0);
              if (!blocked(e->x, ny)) e->y = (int16_t)ny;
            }
          if ((g->ticks & 1u) == 0)
            {
              int nx = e->x + e->direction;
              if (nx >= 0 && nx + PLAYER_W < map_width &&
                  !blocked(nx, e->y)) e->x = (int16_t)nx;
              else e->direction = -e->direction;
            }
        }
      else if ((g->ticks + i * 3) % (e->type == 1 ? 2 : 3) == 0)
        {
          int nx = e->x + e->direction;
          if (!blocked(nx, e->y) &&
              nx2d_tilemap_solid(&g_nx2d_demo_level,
                                nx, e->y + PLAYER_H) &&
              nx2d_tilemap_solid(&g_nx2d_demo_level,
                                nx + PLAYER_W - 1, e->y + PLAYER_H))
            e->x = (int16_t)nx;
          else
            e->direction = -e->direction;
        }
      if (!e->dying && g->invulnerable == 0 &&
          x < e->x + 16 && x + PLAYER_W > e->x &&
          y < e->y + 32 && y + PLAYER_H > e->y)
        {
          if (g->hp) g->hp--;
          g->invulnerable = 90;
          if (g->hp == 0)
            {
              /* Restart demonstration after losing all health. */
              nx2d_game_init(g);
              return;
            }
        }
    }
  for (unsigned i = 0; i < NX2D_MAX_EFFECTS; i++)
    if (g->effects[i].active && ++g->effects[i].age >= 18)
      g->effects[i].active = 0;
  if (g->invulnerable) g->invulnerable--;
  g->ticks++;
}
