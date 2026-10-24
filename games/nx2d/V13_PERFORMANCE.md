# NX2D v13 — 60 Hz frame pacing and outlier profiling

Based on v12. Default scaler remains `ratio`, default background remains `spans`.

## Changes

- Startup framebuffer benchmark is now optional: add `bench` as a command-line argument.
- Scaler selection works without calling the benchmark (previously the benchmark set the global scaler mode).
- A late frame advances to the next future absolute 60 Hz deadline, avoiding accumulating catch-up iterations.
- New per-120-frame report includes minimum, average and maximum frame work, worst logic/render time, and missed deadline slots.
- Existing `NX2D PERF` reports are retained.

## Usage

```
nx2d /dev/fb0 /dev/xboxa ratio spans
nx2d /dev/fb0 /dev/xboxa ratio spans bench
nx2d /dev/fb0 /dev/xboxa ratio16 spans
```

## Notes

`overruns` counts frames whose measured CPU work exceeded 16,667 us. `skipped` counts absolute 60 Hz deadline slots passed over by the pacing mechanism. These are distinct metrics. A nonzero skipped count can occur because of OS scheduling delays even when average work is below budget.

This package was statically inspected and ZIP-tested, but not compiled or run on STM32H743 hardware.
