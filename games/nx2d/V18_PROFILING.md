# NX2D v18 — Camera fix and DWT profiling

- Fixes camera telemetry: camera is integer world pixels, not 16.16.
- Fixes literal `\n` in telemetry output.
- Adds ARM Cortex-M7 DWT CYCCNT per-stage CPU-cycle timing (average/max).
- DWT is optional: if unavailable, existing CLOCK_MONOTONIC timing remains.
- Adds `quiet` argument to suppress periodic NX2D profiler logging when
  comparing frame pacing. Startup messages still print. This is useful to
  isolate console logging from skipped frame slots.
- Keeps `ratio`, `spans`, framebuffer layout, and game rules unchanged.

Run:
  nx2d /dev/fb0 /dev/xboxa ratio spans
  nx2d /dev/fb0 /dev/xboxa ratio spans detail
  nx2d /dev/fb0 /dev/xboxa ratio spans quiet

DWT values are CPU cycles, NOT microseconds. Divide by actual CPU clock
in MHz to obtain microseconds (e.g. 480 cycles/us at 480 MHz).
DWT 32-bit subtraction is valid for each stage if its duration is less
than one counter wrap (~8.95 seconds at 480 MHz).
DWT may be unavailable on cores with debug access disabled.
Timing includes preemption. USB driver XBOX RAW/STATE/KBD messages are
not suppressed by the NX2D quiet option.

Not compiled or tested on the target board.
