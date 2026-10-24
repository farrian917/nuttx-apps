# T2GEN V20: Packed Plane Rasterizer

Based on V19. Plane A and B pixel and priority are now represented in one
16-bit value per source pixel: bits 0..7 = palette index (0 transparent),
bit 8 = original name-table priority flag. The compositor reads the two
packed values and preserves V19 layer order. The window plane uses the same
representation and directly overwrites plane A in its active region.

Expected improvement: fewer per-pixel plane writes and reads. Actual FPS
and correctness require testing on STM32H743. Retains V18/V19 profiler.

Build: replace apps/games/t2gen, clean the app, then rebuild NuttX.
