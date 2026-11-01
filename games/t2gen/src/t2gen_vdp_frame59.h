#ifndef T2GEN_VDP_FRAME59_H
#define T2GEN_VDP_FRAME59_H
#include <stdint.h>
struct t2gen_vdp_frame59 { uint8_t vram[65536]; uint8_t cram[128]; uint8_t regs[24]; };
int t2gen_vdp_frame59_render(const char *path, const struct t2gen_vdp_frame59 *v);
#endif
