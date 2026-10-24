T2GEN V9.0 - STM32H743 NuttX framebuffer optimization

Changes:
- Persistent /dev/fb0 handle and cached framebuffer information
- No full framebuffer clear each frame; clear once and on H32/H40 transitions
- Per-scanline horizontal scroll lookup
- Visible-sprite list built once per scanline
- Reduced framebuffer cache clean region
- Live render every 4th emulated VBlank, final snapshot preserved
- Additional views 4=A plus sprites, 5=B plus sprites to isolate duplicates

Usage:
 t2gen /mnt/t2.gen /dev/fb0 0    composite
 t2gen /mnt/t2.gen /dev/fb0 1    A only
 t2gen /mnt/t2.gen /dev/fb0 2    B only
 t2gen /mnt/t2.gen /dev/fb0 4    A + sprites
 t2gen /mnt/t2.gen /dev/fb0 5    B + sprites

Note: extra logos are not yet proven to be a priority bug. Background
plane content and masking can be inspected with views 1/2/4/5.
No audio, Z80 or real-time frame pacing. Not compiled on target.
