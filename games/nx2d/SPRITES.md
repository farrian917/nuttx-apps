# NX2D sprite animation

Copy `assets/player.nx2s` to `/mnt/sdcard/nx2d/player.nx2s` on the board (create the directory first). The path is currently hard-coded in `nx2d_video.c`; change it to match your SD mountpoint. If absent, NX2D retains the previous rectangle player.

Format: 12-byte header `NX2S`, little-endian uint16 width=16, height=32, frames=12, uint8 transparent index=0, uint8 reserved=0. Then 12 frames of 16x32 row-major L8 palette indices. The existing RGB332 CLUT is unchanged. Index 0 is transparent, so avoid index 0 for visible sprite pixels.

Frames: 0-1 idle, 2-7 running, 8-9 jumping/falling, 10-11 shooting. Flip horizontally for facing left. X or RB activates firing animation (visual only, no projectile). Animations use game ticks assuming 60 updates/sec.

To use your own art, export 12 frames of 16x32 indexed RGB332 pixels with palette index 0 transparent, preserving the header. The included sprite is a simple procedural test character, not copyrighted game art.

This package preserves the existing framebuffer scaling, tilemap and controller implementation. The sprite is loaded once at framebuffer initialization. No repeated SD reads during frames. Note: the file loader currently requires exactly 16x32x12 frames; general-size sprite sheets can be added later.
