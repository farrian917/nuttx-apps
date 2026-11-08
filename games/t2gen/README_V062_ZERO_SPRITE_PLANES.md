# T2GEN V0.62 — Zero-sprite-plane renderer experiment

Based on V0.61. In `src/t2gen_render.c`, sprite-free scanlines use one
immutable 320-byte zero row for both sprite planes, avoiding two per-line
`memset` operations. Writable arrays are zeroed only when the sprite
rasterizer will actually run. Fused background composition, priority,
window/debug paths, SRAM2 tile cache, and DMA2D are unchanged.

This is a conservative optimization, not a claimed speedup. Compare
300-frame FPS and `T2GEN V0.31 AVG_US` fields with V0.61 across the
same first six windows. Test sprites, no-sprites, and diagnostic views.

Build: install the t2gen directory in apps/games and rebuild NuttX.
Target compilation and hardware execution have not been verified.
