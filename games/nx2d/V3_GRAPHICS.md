# NX2D v3: Parallax + enemy walking animation

Based on the confirmed-working Combat v2 **floor collision fix** archive.

- 2 integer-only parallax mountain layers (1/4 and 1/2 camera speed)
- Sky color gradient in RGB332 L8
- Transparent empty map cells; solid tile colors unchanged
- Four-phase procedural enemy walking animation, with direction and damage flash
- No changes to player physics, platform collision, Xbox controls, weapons, framebuffer scaler or NuttX build config
- No new assets needed

Build from apps/games/nx2d as before and run `nx2d /dev/fb0 /dev/xboxa`.

This version does not yet load enemy sprite sheets from SD. That is a separate next feature.
