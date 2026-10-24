# NX2D v12 — exact-ratio packed scaler

The framebuffer is 1024x600 L8; the source is 320x224 L8.

## New modes

- `ratio` (default): exact 5-input-to-16-output horizontal groups, four 32-bit packed words per group, 8-word unrolled SRAM-to-SDRAM writes.
- `ratio16`: same packing with 16-word unrolled writes.
- `packed`: v11 lookup-based packing for A/B comparison.

Run:

```
nx2d /dev/fb0 /dev/xboxa packed spans
nx2d /dev/fb0 /dev/xboxa ratio spans
nx2d /dev/fb0 /dev/xboxa ratio16 spans
```

## Implementation notes

Horizontal expansion is exact nearest-neighbor: floor(x * 320 / 1024).
Each five input bytes maps to sixteen output bytes with repeat counts 4,3,3,3,3.
Expanded row stays in internal SRAM and is reused for repeated output rows.
No SDRAM framebuffer reads are performed by the new modes.
No MPU, SDRAM, DMA2D, or LTDC configuration changes.
The startup synthetic framebuffer benchmark measures copies only, not expansion.
The full `NX2D PERF` numbers are the meaningful end-to-end comparison.
This version is not tested on target hardware.
