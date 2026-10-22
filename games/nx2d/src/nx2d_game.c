#include "nx2d.h"
#include <string.h>
/* Physics use 16.16 fixed point. World ground at y=192. */
#define FX(x) ((int32_t)(x) << 16)
void nx2d_game_init(struct nx2d_game_s *g)
{
  memset(g, 0, sizeof(*g));
  g->x = FX(40);
  g->y = FX(160);
}
void nx2d_game_step(struct nx2d_game_s *g, uint32_t buttons)
{
  int32_t target = 0;
  if (buttons & NX2D_BUTTON_LEFT) target -= FX(2);
  if (buttons & NX2D_BUTTON_RIGHT) target += FX(2);
  g->vx = target;
  if ((buttons & NX2D_BUTTON_JUMP) && g->grounded)
    {
      g->vy = -FX(7);
      g->grounded = false;
    }
  g->vy += FX(1) / 3;
  if (g->vy > FX(8)) g->vy = FX(8);
  g->x += g->vx;
  g->y += g->vy;
  if (g->x < 0) g->x = 0;
  if (g->x > FX(NX2D_WORLD_W - 16)) g->x = FX(NX2D_WORLD_W - 16);
  if (g->y >= FX(160))
    {
      g->y = FX(160);
      g->vy = 0;
      g->grounded = true;
    }
  int32_t camera = (g->x >> 16) - 110;
  if (camera < 0) camera = 0;
  if (camera > NX2D_WORLD_W - NX2D_W) camera = NX2D_WORLD_W - NX2D_W;
  g->camera = camera;
  g->ticks++;
}
