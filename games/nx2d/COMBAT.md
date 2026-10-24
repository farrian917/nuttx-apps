# NX2D Combat v1 — STM32H743 / NuttX

Based on the working Animated Sprites v1 archive. Keeps Xbox input, L8 CLUT, 320x224 tilemap, and 1024x600 scaling unchanged.

- X or RB: hold to fire; one bullet per 10 simulation ticks (~6/s at 60Hz).
- Up to 16 projectiles and 8 enemies (6 demo spawns).
- Enemies have 3 HP, move toward nearby player, reverse at walls/ledges.
- Bullets stop on solid tiles, damage enemies, and increment kill counter.
- Player has 5 HP, 90-tick hit invulnerability, and respawns when HP reaches zero.
- HUD: red bars = HP, yellow marks = kills.
- Enemy graphics are generated with L8 rectangles, so no new sprite assets are required.
- Existing player.nx2s still loads from /mnt/sdcard/nx2d/player.nx2s.

Install: replace apps/games/nx2d with the nx2d directory in this archive. Build NuttX normally, then run `nx2d /dev/fb0 /dev/xboxa`.

Notes: This is a gameplay prototype. Enemies are ground-based, not animated sprites yet. No audio, enemy projectiles, or save state. Source package has not been cross-compiled or tested on target hardware.
