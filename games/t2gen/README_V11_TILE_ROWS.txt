T2GEN V11: decoded tile-row pointer reuse

Based on V10. Keeps 128 KiB tile cache and DMA2D transfer.
For each scanline, cache a pointer to the decoded row when a background
name-table entry changes. The hot per-pixel loop now indexes the row
directly, rather than calling tile_pixel() for both backgrounds.
Fallback remains if cache allocation fails.

Benchmark: disable XBOX RAW/STATE/KBD logging, run
  t2gen /mnt/t2.gen /dev/fb0 0
Compare TOTAL, VIDEO PERF and FPS against V10.

This build is not cross-compiled or hardware validated.
