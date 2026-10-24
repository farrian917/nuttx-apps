T2GEN V9.6 DMA2D PROFILING / QUIET BUILD

Full source tree, based on V9.5.

IMPORTANT: The STM32H7 NuttX kernel still requires the V9.5
stm32_dma2d_t2gen_copy_l8x2 helper installed in stm32_dma2d.c.
The original helper is included in patches/. Do not install twice.

Changes:
* Removes per-write RAM-watch instrumentation in the hot 68000 bus path.
* Disables repeated WAIT and initial bus trace printing.
* Prints VDP render diagnostics once per 128 rendered frames.
* Adds cumulative composition time and DMA2D transfer time, success/fail counters.
* Corrects CPU time measurement to avoid sharing a timestamp with the renderer.
* Keeps DMA2D enabled, same framebuffer, gameplay and frame cadence.

Run: t2gen /mnt/t2.gen /dev/fb0 0
Capture final 'T2GEN V9.6 VIDEO PERF' and 'T2GEN V9.6 PERF'.
NOTE: the CPU time measures m68k_execute only (in 256-slice batches);
not all emulation overhead. DMA transfer time includes cache clean and driver wait.
This project has not been tested on the target board.
