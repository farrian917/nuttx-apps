# NX2D Combat v2 (STM32H743 / NuttX)

Built on the working Combat v1 source tree. All original SD assets remain.

## Controls
- D-pad / left stick: walk
- A: jump
- X or RB: shoot
- Y: cycle pistol -> automatic -> shotgun (edge triggered)

## Features
- Pistol (12 ticks), automatic (5 ticks), shotgun (3 pellets, 22 ticks)
- Enemies fire red projectiles when within 180px and close in height
- Enemy walking animation (procedural), damage flash, expanding explosions
- HUD: health red blocks, kill markers, weapon indicator (cyan/yellow/magenta)
- Per-pixel projectile collision stepping; 16 total bullets shared between sides

## Build
Copy nx2d to apps/games/nx2d and run `make -j` from the NuttX root.
Launch `nx2d /dev/fb0 /dev/xboxa`.
Keep `/mnt/sdcard/nx2d/player.nx2s` on SD for animated player.

## Notes
- Audio is NOT implemented; no assumed audio driver or hardware.
- Enemy art remains procedural (animated leg pose), not loaded sprite sheets.
- Fixed-size arrays, no dynamic allocations per frame.
- Preserves 320x224 L8 software framebuffer and 1024x600 nearest-neighbor scaler.
- Source has not been cross-compiled on the user's NuttX configuration.
