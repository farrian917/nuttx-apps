# NX2D v9 — Scaler experiments

v8 already caches each expanded 1024-byte source row. v9 does **not** claim to add that feature again. It compares four output paths on the same 1024x600 L8 framebuffer:

- `memcpy`: copy cached expanded row to each display row
- `word32`: existing 256 x 32-bit stores
- `unroll`: eight 32-bit stores per loop iteration (default)
- `rowcopy`: for repeated source rows, copy from the previous SDRAM framebuffer row; otherwise unrolled stores. This may be slower because it reads SDRAM as well as writes it.

Run `nx2d /dev/fb0 /dev/xboxa [memcpy|word32|unroll|rowcopy]` and compare `NX2D PERF` and `NX2D BENCH` output. The startup BENCH writes test patterns to the framebuffer temporarily. No MPU/FMC/LTDC/DMA2D configuration is changed. Word32 modes require 4-byte alignment; benchmark falls back to memcpy if unaligned.

This is a measurement-focused optimization experiment, not a guaranteed 60 FPS improvement.
