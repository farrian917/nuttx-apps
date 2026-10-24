# NX2D v7: SDRAM framebuffer copy benchmark

Based on v6 performance profiler. Keeps NuttX .config, FMC timings, LTDC and DMA2D allocation unchanged.

## Install
Copy `nx2d/` over `apps/games/nx2d/`, then rebuild NuttX.

## Run

- `nx2d /dev/fb0 /dev/xboxa` uses libc memcpy scaler and runs both copy benchmarks at startup.
- `nx2d /dev/fb0 /dev/xboxa word32` uses aligned 32-bit scaler stores and runs both benchmarks.

For your Xbox device, substitute the correct controller path if different.

The benchmark overwrites the visible framebuffer temporarily *before* the first gameplay frame. It does not access arbitrary SDRAM or DMA2D overlays. It prints best and average of 4 passes, each writing 614400 bytes. Effective KiB/s is output bytes divided by elapsed time; it includes CPU overhead and LTDC contention. Benchmark the game for at least 120 frames in each mode; compare `NX2D PERF` values.

Expected diagnostic output:
```
NX2D BENCH: framebuffer=... stride=1024 backbuffer=... aligned=1
NX2D BENCH: memcpy 614400B best=... us avg=... us effective=... KiB/s
NX2D BENCH: word32 614400B best=... us avg=... us effective=... KiB/s
NX2D BENCH: game scaler=memcpy
NX2D PERF: compose=... us scale=... us render=... us avg/120
```

## Safety
Do not write to the DMA2D overlay: its configured 2 MiB region overlaps the LTDC framebuffer allocation. The LTDC framebuffer is centered within the reserved region, and its actual address is obtained through FBIOGET_PLANEINFO. Do not change MPU attributes or enable write-back caching without a complete cache coherency plan.

## Limitations
- This is a copy/write benchmark, not a raw SDRAM bandwidth benchmark. No read benchmark is included because benchmarking the live framebuffer as a source would add cache and coherency complications.
- CPU scaling still expands each unique logical source row and copies it to the physical framebuffer. DMA2D cannot perform this nonuniform nearest-neighbor scaling directly.
- No 60 FPS guarantee. Compare measurements on real hardware.
