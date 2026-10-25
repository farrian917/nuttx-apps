#ifndef T2GEN_RENDER_H
#define T2GEN_RENDER_H
#include <stdint.h>
void t2gen_render_set_view(unsigned view);
int t2gen_render_snapshot(const char *device);
int t2gen_render_benchmark(const char *device, unsigned repeats);
#endif

/* V9.6: per-stage rendering/DMA2D profiling */
void t2gen_render_print_perf(void);
void t2gen_render_print_window(uint64_t wall_us, uint64_t render_us);
