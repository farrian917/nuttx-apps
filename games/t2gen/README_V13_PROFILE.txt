T2GEN V13 — CPU versus video profiling (based on V12)

Video run: t2gen /mnt/t2.gen /dev/fb0 0
CPU-only run: t2gen /mnt/t2.gen none 0

The CPU-only run still emulates the Genesis VDP, timing, controller, and Musashi CPU, but skips the video renderer and framebuffer DMA.
V13 WINDOW reports elapsed wall time, rendering time, and rendering share every 300 emulated frames.
Compare matching frame intervals in the two runs, as the game workload changes over time.

Memory: Musashi opcode dispatch table is 256 KiB on a 32-bit target and cannot be safely moved wholesale into limited STM32H743 internal SRAM without a memory map. The cycle table is also substantial. No unverified memory placement changes are made in V13.

Not hardware tested or cross-compiled.
