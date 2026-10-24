# NX2D v19 — Video DWT breakdown and pacing diagnostics

Run `nx2d /dev/fb0 /dev/xboxa ratio spans`.

New diagnostics every 120 frames:
- `NX2D V19 VIDEO AVG`: DWT cycles per frame for background, tilemap,
  objects/HUD, unique-row expansion, and framebuffer writes.
- `NX2D V19 PACING`: skipped deadline count buckets and wake lateness.
- Existing V18 DWT stage timing and gameplay telemetry retained.

All DWT section counters are 32-bit modulo differences accumulated in 64-bit
variables. Convert cycles to microseconds by dividing by 480 if CPU=480MHz.
Expand/fbwrite counters exclude some loop and clock overhead; do not assume
these five components sum exactly to full render time.

Video profiler no longer prints inside `nx2d_video_draw`; snapshots are printed
by main after the frame wait. `detail` remains accepted but legacy coarse
video printout is disabled to avoid frame-loop console interference.

`late_wakes` uses the existing coarse CLOCK_MONOTONIC clock and may not be
meaningful below its tick resolution. `skipped` is a scheduling/deadline
counter, not direct proof of missed display refresh.

No changes to ratio scaler, spans renderer, or gameplay rules.
Not compiled with the target toolchain or tested on target hardware.
