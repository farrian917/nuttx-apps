# NX2D v15 — Collectibles and score

Built on v14 with the measured fast `ratio` scaler and `spans` background unchanged.

## New gameplay
- Ten animated golden pickups placed at safe ground-level positions.
- Each pickup awards 100 points and disappears on contact.
- Collecting five pickups restores one health point (up to 5).
- The HUD shows collected tokens as gold markers.
- No extra assets, threads, framebuffer formats, or NuttX configuration changes.

## Run
`nx2d /dev/fb0 /dev/xboxa ratio spans`

## Notes
- The original v14 performance diagnostics remain enabled.
- The existing game resets score/pickups on death because it calls `nx2d_game_init`.
- Xbox `XBOX RAW/STATE/KBD` messages originate from the USB driver, not NX2D.
- Not compiled or tested on the target STM32H743; verify on hardware.
