# T2GEN V0.73 — Batched CPU and VDP diagnostics

- Native AOT: BMI short/word, NOP, BTST immediate D0 / absolute-long, BCLR immediate absolute-long, MOVE.L (A0)+ to absolute-long, MOVE.L absolute-long to -(A7), MOVE.W absolute-long to D0, MOVE.W absolute-long to absolute-long.
- No runtime opcode interpreter or Musashi.
- VDP write classification: VRAM, CRAM, VSRAM, and nonzero word writes. DMA register shown for diagnostic context only; DMA emulation is not implemented.
- Unsupported opcode 3ABC is deliberately rejected because it encodes an invalid PC-relative destination effective address for MOVE.W on a 68000; inspect the corresponding path rather than silently generating incorrect code.
- Hardware execution remains unverified.
