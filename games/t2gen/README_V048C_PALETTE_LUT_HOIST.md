# T2GEN V0.48c — renderer LUT hoist experiment

Based on V0.48b deferred-VSYNC full source, preserving its double-buffer
synchronization and DMA2D code unchanged.

The fused full-scroll renderer previously constructed a 4 x 16 palette-index
lookup table on the stack for every one of the 224 scanlines. This version
replaces that per-line construction with a file-scope static const table.
Palette nibble 0 remains transparent for all four banks, and the remaining
entries are exactly `(palette_bank << 4) | nibble`.

This is a low-risk optimization experiment, NOT a claim of 35+ FPS. Measure
actual effect against V0.48b; compiler optimization may have already hoisted
some or all of the original initialization.

Build:
  cd ~/workspace/nutt_last/nuttx && make -j$(nproc)
Run:
  nsh> t2gen
Compare 300-frame FPS and AVG_US background/compose; validate visuals.

NOTE: the V0.48b deferred-VSYNC design is inherited unchanged. Its wait ioctl
is not a hardware-level guarantee of a completed prior pan without further
LTDC driver inspection; confirm tear-free behavior on the display.
