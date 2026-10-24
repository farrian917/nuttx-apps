# NX2D v17 — Gameplay telemetry and profiling validation

The `ratio` scaler, `spans` compositor and 60 Hz pacing are unchanged.

Every 120 frames the console reports:
- V17 average, maximum and worst frame times (input/update/render).
- Deadline overruns and skipped pacing slots.
- GAME: tick count, player world position, camera, HP, checkpoint, deaths.
- PROGRESS: score, collected tokens, kills, maximum active enemies/bullets/effects.
- CLOCK: how often input/update timing returned zero.

IMPORTANT: NuttX CLOCK_MONOTONIC may have coarse resolution. A zero stage
duration means the stage is below the timer resolution, NOT zero CPU work.
If precise sub-millisecond timing is needed, a validated Cortex-M7 DWT cycle
counter or board-specific high-resolution timer can be added later.

Run: nx2d /dev/fb0 /dev/xboxa ratio spans
Optional: nx2d /dev/fb0 /dev/xboxa ratio spans detail

The Xbox RAW/STATE/KBD messages are emitted by the USB driver, not NX2D.
No new threads, no extra dependencies. Not hardware tested.
