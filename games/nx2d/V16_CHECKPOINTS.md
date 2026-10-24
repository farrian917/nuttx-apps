# NX2D v16 — Checkpoints and enemy score

- World-space checkpoints at x=600 and x=1200, with colored flags.
- Crossing a checkpoint activates it. Active flags change color.
- Death respawns the player at the last checkpoint with 5 HP and 120 ticks
  of invulnerability; pickups, score and defeated enemies are preserved.
- Before reaching any checkpoint, death restarts the demonstration.
- Each enemy kill now awards 250 points (saturates safely at uint16 limit).
- V15 tokens and all v14 performance instrumentation are retained.
- No new threads or framebuffer changes.

Test: `nx2d /dev/fb0 /dev/xboxa ratio spans`

This release was not built with the target NuttX toolchain or hardware-tested.
