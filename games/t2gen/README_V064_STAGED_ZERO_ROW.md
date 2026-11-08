# T2GEN V0.64 — staged transparent tile-row check

Based on V0.63. The fused cached full-scroll compositor checks the first
32 bits of each background tile row before checking the second 32 bits.
The backdrop-fill shortcut is taken only when both complete decoded rows
are zero. This preserves flip, priority, sprite and transparency semantics.

Only src/t2gen_render.c differs from V0.63 (plus this README).
The previous V0.62 sprite-plane optimization, 4-pixel unroll, DMA2D,
SRAM2 tile cache and safe display configuration are unchanged.

Benchmark 6000 frames against V0.62 and V0.63. Compare per-window
AVG_US background, sprites, render, and emulated FPS. No target build
or hardware validation has been performed.
