T2GEN V9.4 - scanline sprite acceleration, NX2D V19 reference

This full project derives from V9.3 and preserves the working Genesis gameplay.

Changes:
- Precompose sprite priority layers once per scanline instead of scanning
  every visible sprite for every output pixel twice.
- Compute window selection once per pixel.
- Keep persistent L8 framebuffer and cached CLUT from V9.3.

IMPORTANT DMA2D STATUS:
The supplied NX2D V19 archive does not establish a callable DMA2D transfer
API for T2GEN. This release does NOT claim DMA2D acceleration; it retains
the safe working framebuffer writer. Integrating actual DMA2D requires the
board's STM32H7 NuttX DMA2D driver API and configuration.

The STM32H743 DMA2D engine supports copies, fills, pixel conversion and
blending, but not 2x image scaling. A future backend can use DMA2D for
framebuffer transfers after CPU horizontal/vertical expansion.

Build: replace apps/games/t2gen with this folder, then rebuild NuttX.
Run: t2gen /mnt/t2.gen /dev/fb0 0
