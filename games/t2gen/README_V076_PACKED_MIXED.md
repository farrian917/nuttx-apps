# T2GEN V0.76 — four-pixel mixed compositor experiment

Full source based on V0.73. V0.74 early-opaque and V0.75 DWT instrumentation are not included.

## A/B build

Baseline: `CONFIG_GAMES_T2GEN_V073_DIRECT_OPAQUE=y`, `CONFIG_GAMES_T2GEN_V076_PACKED_MIXED=n`.

Experimental: `CONFIG_GAMES_T2GEN_V073_DIRECT_OPAQUE=y`, `CONFIG_GAMES_T2GEN_V076_PACKED_MIXED=y`.

V0.72 row metadata should remain disabled; the V0.73 option supplies it internally.

The packed path handles forward-reading, sprite-free, mixed spans of at least four pixels. Horizontal-flipped and shorter spans use the existing scalar compositor. Tile row opacity, sprite priorities, palette banks, backdrop and DMA2D are unchanged.

This is an experiment, not a guaranteed speedup. In particular, 32-bit loads and four palette lookups may cost more than the original demand-driven scalar path on Cortex-M7. Compare the same 3000–6000 emulated frames with the option on and off. Cross-compilation and hardware tests are not available in this environment.
