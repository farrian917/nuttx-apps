# T2GEN V0.76 — MOVEM register restore, native AOT

Based on V0.75. The ROM-specific offline CFG translator now supports
`MOVEM.W (An)+,<register list>` and `MOVEM.L (An)+,<register list>`.

At the hardware-observed 0x00EB1A, opcode 4CDF 0F85 restores seven
32-bit registers from (A7)+ in D0-D7/A0-A7 mask order. The generated
native C uses bus reads, advances the source address for each selected
register, and applies the final postincrement after loading the registers.
The subsequent RTS at 0x00EB1E is already translated.

This release does not implement VBlank, DMA or a Z80 interpreter.
The runtime destination after RTS depends on the stack and has not been
verified on hardware. Further untranslated blocks may still stop execution.

Build:
  python3 ../apps/games/t2gen/tools/generate_cfg_aot.py ../apps/games/t2gen/tools/t2.gen
  make -j
Run:
  t2gen /mnt/t2.gen /dev/fb0

Offline checks: generated CFG and host GCC -std=c11 -fsyntax-only
for src/t2gen_native59.c. No STM32 hardware execution verified.
