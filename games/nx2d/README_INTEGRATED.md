# NX2D integrated tilemap build

This integrates tilemap rendering, camera tracking and AABB collisions into the provided nx2d_new.rar project.

- Keep the existing 1024x600 L8 scaler and Xbox USB input unchanged.
- Map: 80 x 14 tiles (1280 x 224 pixels); floor at y=192, gaps and elevated platforms.
- Player: 16 x 32, 16.16 fixed-point physics, Xbox A jump, left stick / D-pad movement.
- Map draws before player; camera follows player and clamps to level width.
- Makefile now uses `src/nx2d_tilemap.c` and `src/nx2d_level_demo.c` (fixed missing src/ prefix).

Copy `nx2d/` to `~/workspace/nutt_last/apps/games/nx2d/`, rebuild from your NuttX directory, and run:

    nx2d /dev/fb0 /dev/xboxa

Not tested on hardware. Existing Xbox input adapter retains last state on EAGAIN and does not auto-reopen on unplug/replug. No change to the USB driver.
