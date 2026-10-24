# NX2D v5 Advanced Enemy AI

Based on confirmed-working v4 source and original SD-card sprite sheets.

- Slot 0: soldier patrols platform and fires
- Slot 1: robot pursues player horizontally and fires
- Slot 2: drone flies horizontally and adjusts height toward player; fires when horizontally aligned
- Death: 24 simulation ticks of shrinking flash; dead enemies cannot shoot or damage player
- Enemy simulation skipped outside camera +/- 80 pixels (no re-spawn after death)
- Existing floor/platform physics, Xbox controller, weapons, sprites, parallax and L8 scaling preserved

Note: Drone retains a 16x32 collision box. Drone gunfire still requires approximate player height alignment. FPS instrumentation not yet added.

Copy `nx2d` into `apps/games/`, rebuild NuttX, and launch as before.
