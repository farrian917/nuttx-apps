# T2GEN V0.73 — direct opaque-front compositor (experimental)

Based on V0.72, with V0.73 disabled by default. Set
`CONFIG_GAMES_T2GEN_V073_DIRECT_OPAQUE=y` and leave V0.72 disabled.

A cache-refill-generated 8-bit row opacity mask allows the renderer to
select the visually frontmost background plane for sprite-free spans.
When its decoded tile row is fully opaque, write that plane's palette
indices directly and avoid reading rear-plane pixel data. Horizontal
flipping is handled by signed pointer stride. Vertical flipping is
resolved when selecting the row. The existing mixed/sprite and uncached
paths remain unchanged.

Reports `T2GEN V0.73 DIRECT_OPAQUE: frame=... spans=... pixels=...`
and V0.72 row metadata counters every 300 emulated frames.

IMPORTANT: The existing tile-row cache fetches both planes before the
fast-path decision. This version reduces inner pixel mixing, not tile
cache lookup overhead. Benchmark with the flag both on and off, keeping
paired-sync and other settings identical. Visual validation required.

Not cross-compiled or tested on STM32H743.
