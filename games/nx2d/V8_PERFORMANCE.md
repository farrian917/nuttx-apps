# NX2D v8 — composition optimization

Changes:
- Tilemap draws clipped spans for solid 16x16 tiles rather than calling collision for every pixel.
- Parallax writes rows sequentially instead of vertical strided columns.
- Separate profile: bg, map, objects, compose, scale.
- `word32` scaler now default; optional `memcpy` argument selects baseline.
- Fix v7 startup benchmark so memcpy and word32 actually test different copy functions.

Run:
`nx2d /dev/fb0 /dev/xboxa` (word32)
`nx2d /dev/fb0 /dev/xboxa memcpy` (baseline)

Observe NX2D PERF lines over 120 frames. No FMC/MPU/SDRAM allocation changes.
Performance improvements are unverified until tested on hardware.
