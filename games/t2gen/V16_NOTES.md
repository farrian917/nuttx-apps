# T2GEN V16 — sprite tile-row span optimization

Based on V15, preserving V14 Musashi bus fast paths, V15 compositor,
DMA2D framebuffer transfer, and CPU-only mode (`none`).

## Change
`src/t2gen_render.c`: sprite scanline rasterizer now decodes or retrieves
a tile row once per contiguous tile span rather than invoking sprite_pixel
for each pixel. Full-sprite horizontal/vertical flips, column-major sprite
tile arrangement, transparent pixels, and first-sprite-wins ordering are
preserved. The uncached fallback uses the original tile_pixel decoder.

## Test
`t2gen /mnt/t2.gen none 0`
`t2gen /mnt/t2.gen /dev/fb0 0`

Compare the FPS, WINDOW, and VIDEO PERF lines against V15. Verify flipped
sprites visually, especially around tile boundaries. Not hardware tested.
