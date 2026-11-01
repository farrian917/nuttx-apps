# T2GEN V0.70 — ROM-specific native AOT continuation

V0.69 hardware stopped at PC=0x004A32, D0=0x00000139, A0=0x00FF0002, A7=0xFFFFF8.

At 0x004A32 the exact ROM bytes are `10 FC 00 00 51 C8 FF FA 4E 75`:

- `MOVE.B #$00,(A0)+` — generated native write to emulated Genesis RAM, with A0 increment and MOVE condition flags.
- `DBF D0,-6` — existing native AOT loop, branching back to 0x004A32.
- `RTS` at 0x004A3A — existing native AOT stack return.

This should clear 314 bytes beginning at 0xFF0002 when D0.W starts at 0x0139. This is an expectation derived from the supplied register log, not yet validated on STM32.

The generator now accepts `--extra-entry 0xHEX` (repeatable) to seed ROM blocks reached dynamically at runtime. It seeds 0x004A32 by default based on the V0.69 UART trace; a static JSR/RTS control-flow graph alone cannot always discover a dynamically returned-to address.

Generator: `python3 tools/generate_cfg_aot.py tools/t2.gen`

Validation: offline generation and GCC host syntax check pass. Hardware pending.

No Musashi and no runtime 68000 opcode interpreter. The existing VDP is incomplete and graphics are not yet expected.
