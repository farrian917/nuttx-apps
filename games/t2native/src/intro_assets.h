#ifndef T2_INTRO_ASSETS_H
#define T2_INTRO_ASSETS_H
#include <stdint.h>
struct t2_intro_frame_s { uint32_t offset, size; uint16_t sample; uint8_t keyframe; };
extern const uint8_t t2_intro_blob[];
extern const unsigned t2_intro_blob_len;
extern const struct t2_intro_frame_s t2_intro_frames[];
extern const unsigned t2_intro_frame_count;
#endif
