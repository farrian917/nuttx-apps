#ifndef T2_GAME_ASSETS_H
#define T2_GAME_ASSETS_H
#include <stdint.h>
#define T2_PLAYER_W 56
#define T2_PLAYER_H 56
#define T2_PLAYER_ORIGIN_X 80
#define T2_PLAYER_ORIGIN_Y 156
#define T2_PLAYER_FRAME_COUNT 4
#define T2_PLAYER_FRAME_BYTES (T2_PLAYER_W*T2_PLAYER_H*2)
extern const uint8_t t2_stage_lz4[];
extern const unsigned t2_stage_lz4_size;
extern const uint8_t t2_player_lz4[];
extern const unsigned t2_player_lz4_size;
#endif
