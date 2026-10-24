# NX2D v14 — Input / game update / rendering spike isolation

Based on v13. `ratio spans` remains default. No MPU, SDRAM, LTDC or USB driver changes.

## Run

```
nx2d /dev/fb0 /dev/xboxa ratio spans
nx2d /dev/fb0 /dev/xboxa ratio spans detail
nx2d /dev/fb0 /dev/xboxa ratio spans bench
```

Default v14 suppresses the per-120-frame VIDEO profiling prints (the video still measures sections). `detail` enables them. Main timing is split into Xbox read, game update and rendering. Output reports average and maxima, the component times from the *same* worst frame, plus threshold counts and missed 60 Hz slots. `read()` is opened O_NONBLOCK, but elapsed input time still captures unexpected waits/preemption. These measurements are elapsed times, not isolated CPU usage.

Caution: the main-loop report is printed after frame pacing, and USB console output can perturb subsequent frames. Compare several consecutive 120-frame windows; avoid enabling `detail` during initial jitter diagnosis. The maximum component times may occur on different frames. `WORST` is the breakdown from the same maximum-total-work frame.

Archive integrity verified; compilation and hardware validation pending.
