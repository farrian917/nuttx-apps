# T2GEN V18 stage profiler

Based on V17; no intended changes to video output or CPU emulation.

Run `t2gen /mnt/t2.gen /dev/fb0 0` and compare final `T2GEN V18 STAGES` and `T2GEN V18 AVG_US` with existing `VIDEO PERF`.

Stage timings are collected per scanline with `timestamp_us()`; their overhead can reduce FPS slightly. `setup` includes palette/initialization work before scanlines; `sprites` includes visible sprite list; `background` includes scroll lookup and both plane scans; `window` includes window scanline; `mix_scale` includes priority selection and 2x pixel stores; `dma_cache` is staging cache clean; `dma_copy` is both DMA2D transfers. Other costs, including timestamp calls, are not fully attributed.

Do not compare V18 FPS as an optimization: this is a diagnostic build. The V17 render behavior is retained.
