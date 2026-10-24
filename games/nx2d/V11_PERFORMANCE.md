# NX2D v11 — scaler experiments

Based on v10 spans. Default is still `unroll` + `spans`.

Commands:

```
nx2d /dev/fb0 /dev/xboxa unroll spans
nx2d /dev/fb0 /dev/xboxa burst16 spans
nx2d /dev/fb0 /dev/xboxa packed spans
```

`burst16` compares 16 sequential word stores per loop against 8.
`packed` packs four output pixels into each 32-bit word directly from the
320px source row, avoiding the intermediate 1024-byte expansion loop.
Both keep the same 320x224 -> 1024x600 nearest-neighbor mapping.

New `NX2D PERF: expand=... fbwrite=...` measurements separate horizontal
expansion and SDRAM framebuffer writes. Clock sampling inside the row loop
adds overhead, so compare against the `unroll` baseline in this version,
not against v10. The measured components need not add up exactly to `scale`.

No changes to LTDC, DMA2D, MPU, SDRAM or cache settings.
The source has not been compiled or tested on hardware.
