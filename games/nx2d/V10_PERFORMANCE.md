# NX2D v10: parallax background A/B benchmark

The 320x224 parallax background is now selectable: `spans` (default) draws the exact same triangular far and near terrain with contiguous horizontal `memset` spans, and `classic` uses the original per-pixel conditions. Both preserve the same sky and terrain palette indices. No changes to SDRAM timings, MPU or framebuffer allocation.

Run:

```
nx2d /dev/fb0 /dev/xboxa unroll spans
nx2d /dev/fb0 /dev/xboxa unroll classic
```

Compare `NX2D PERF: bg=... compose=... scale=... total_work=...`. Because the background occupies only the lower part of the logical image, the span renderer skips all terrain tests above y=132. Performance is hardware-dependent; classic remains available for regression checks.

Known limitation: the scaler still costs ~12.5 ms in v9; this release isolates background optimization rather than changing cache or SDRAM policies.
