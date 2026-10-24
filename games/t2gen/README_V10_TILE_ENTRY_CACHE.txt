T2GEN V10: name-table entry caching (experimental)

Based on V9.9 complete tree. Reuses plane A/B and window name-table
entries for adjacent pixels with identical tile coordinates. Keys include
vertical tile coordinate to preserve per-column V-scroll behavior.

Preserved: Musashi CPU, 128KiB decoded tile cache, DMA2D copy, framebuffer
address obtained from /dev/fb0, existing every-third-frame policy, Xbox.

This change alone is NOT expected to guarantee 60 FPS. Profile CPU and
renderer times after disabling Xbox driver's high-volume serial logs.

To install: replace apps/games/t2gen with this folder; rebuild NuttX.
Run: t2gen /mnt/t2.gen /dev/fb0 0

Uncompiled and untested on target hardware.
