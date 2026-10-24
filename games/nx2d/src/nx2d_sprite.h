#ifndef NX2D_SPRITE_H
#define NX2D_SPRITE_H
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#define NX2D_SPRITE_W 16
#define NX2D_SPRITE_H 32
#define NX2D_SPRITE_FRAMES 12
#define NX2D_SPRITE_TRANSPARENT 0
/* File format: NX2S + LE16 width,height,frames,transparent + frame pixels. */
struct nx2d_sprite_s { uint8_t *pixels; uint16_t width,height,frames; uint8_t transparent; };
int nx2d_sprite_load(struct nx2d_sprite_s *s, const char *path);
void nx2d_sprite_free(struct nx2d_sprite_s *s);
void nx2d_sprite_draw(const struct nx2d_sprite_s *s, uint8_t *dst,
                      unsigned stride,unsigned dw,unsigned dh,
                      int x,int y,unsigned frame,bool flip);
#endif
