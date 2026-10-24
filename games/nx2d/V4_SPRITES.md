# NX2D v4 — SD card enemy sprite sheets

Based on the user-confirmed working NX2D v3 build.

## New functionality
- 3 distinct enemies: soldier, robot, hovering-drone visual (all retain existing ground-based enemy AI and 16x32 hitbox).
- 12 frames each, transparent L8 palette index 0, horizontal flipping.
- Enemy animation: patrol 0-3, firing 4-7, damage 8-9; frames 10-11 reserved for future death state.
- Fallback to v3 procedural enemy rendering if files are missing.
- All physics, weapons, floor collision, camera and framebuffer logic unchanged.

## Copy files to SD card
Copy `assets/enemy0.nx2s`, `enemy1.nx2s`, `enemy2.nx2s` into `/mnt/sdcard/nx2d/` along with `player.nx2s`.

Existing NX2S format: 12-byte header (`NX2S`, LE16 width=16, height=32, frames=12, byte transparency=0, reserved=0), followed by 12 x 16 x 32 bytes of RGB332 palette indices. `nx2d_sprite_load` already supports it.

Build from `apps/games/nx2d` as before. No additional Makefile sources.

Note: drone appearance is visual only; flight AI, death animation and DMA2D acceleration are not part of this patch. The enemy slot determines the appearance (slot modulo 3).
