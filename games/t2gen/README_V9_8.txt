T2GEN V9.8 - LAZY TILE CACHE + PRECOMPUTED VSCROLL

Based on V9.7. Retains /dev/xboxa gamepad, 3-button Genesis IO,
DMA2D transfers and profiling. No NuttX driver modifications beyond
those already required for V9.5.

Changes:
- Allocate 128 KiB decoded tile cache on NuttX heap.
- Decode a Genesis 8x8 tile once per rendered snapshot on first use.
- Preserve per-tile flip, palette and sprite layout.
- Precompute vertical scroll per X column once per snapshot.
- Keep fallback path if tile cache allocation fails.
- Report tile_misses and tile_cache in VIDEO PERF.

Important: caching is per snapshot, NOT persistent across emulated frames,
because VRAM may be modified by the game between frames. This avoids
stale graphics without adding VRAM dirty tracking.

Run: t2gen /mnt/t2.gen /dev/fb0 0
Compare VIDEO PERF compose_ms, dma_ms, and CPU PERF to V9.7.

Experimental: not cross-compiled or hardware-tested.
