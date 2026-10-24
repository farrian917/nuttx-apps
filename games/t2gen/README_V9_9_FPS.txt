T2GEN V9.9 - FPS profiling and low-risk renderer optimization

Changes from V9.8.2:
- Replaces power-of-two plane table modulo operations with bit masks.
- Reduces periodic renderer diagnostic logging from 128 to 512 renders.
- Limits startup renderer diagnostics to the first render.
- Reports real emulated and rendered FPS every 300 emulated frames.
- Reports total elapsed wall time and average FPS on exit.
- Preserves DMA2D, framebuffer mapping, tile cache, Xbox input, 3-frame rendering interval, and 16-KiB default stack.

IMPORTANT:
- This is a profiling/low-risk optimization build, NOT a guaranteed major FPS increase.
- Your repeated 'XBOX RAW' / 'XBOX STATE' / 'XBOX KBD' messages originate from the NuttX USB Xbox driver, not t2gen. Disable or rate-limit those driver printf calls separately for an accurate performance benchmark.
- Build with optimization (e.g. -O2 or -Os) and inspect compiler flags.
- No cross-compile or hardware test was performed.

Install: replace apps/games/t2gen with this directory, rebuild NuttX, run:
  t2gen /mnt/t2.gen /dev/fb0 0

Look for:
  T2GEN V9.9 FPS: emu=... render=...
  T2GEN V9.9 TOTAL: wall_ms=... emulated_frames=... rendered=...
  T2GEN V9.6 VIDEO PERF: ... avg_compose_us=... avg_dma_us=...
