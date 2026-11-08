# T2GEN V0.77 — Integrated packed mixed compositor

The V0.76 forward-only four-pixel packed mixed-background compositor is now integrated directly into the renderer, with no experimental Kconfig switch.

Enable CONFIG_GAMES_T2GEN_V073_DIRECT_OPAQUE=y (required for the V0.73 baseline renderer and row metadata). Disable V0.74 early opaque and V0.75 DWT profiling.

The packed path applies only to sprite-free mixed spans with both decoded rows advancing forward and span length >=4. Flipped spans, short tails, opaque-front rows, zero rows, and sprite spans retain the established paths.

This is a source integration, not a measured speedup. Validate image correctness and benchmark on the STM32H743.
