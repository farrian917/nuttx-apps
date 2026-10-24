#ifndef T2GEN_RENDER_H
#define T2GEN_RENDER_H
void t2gen_render_set_view(unsigned view);
int t2gen_render_snapshot(const char *device);
#endif

/* V9.6: per-stage rendering/DMA2D profiling */
void t2gen_render_print_perf(void);
