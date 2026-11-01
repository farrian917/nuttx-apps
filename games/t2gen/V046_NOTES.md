# T2GEN V0.46 — ROM-specific AOT dispatcher and offline generator

Based on V0.45 and retains the proven SDRAM/SD-read path and heap RAM fix.

## New
- `src/t2gen_native46.c`: native PC-indexed block dispatcher, not a
  68000 opcode interpreter.
- `tools/generate_aot.py`: offline generator for exactly the known
  `TST.W (xxx).L` instruction at ROM address 0x208.
- `src/t2gen_aot_generated.inc`: safe default stub until the generator runs.

## Critical: supply your own ROM to generate the next block
The ROM itself is not included in this archive and was not available during
packaging. On your Linux build machine, BEFORE compiling NuttX, run:

    python3 ../apps/games/t2gen/tools/generate_aot.py /path/to/t2.gen

The generator reads the actual 32-bit address operand from ROM offsets
0x20A..0x20D, validates the opcode and writes the ROM-specific native C
block to `src/t2gen_aot_generated.inc`. Then rebuild:

    make -C ../apps/games/t2gen clean
    make -j

On NuttX:
    nsh> t2gen /mnt/t2.gen none

If you do not run the generator, the application safely stops at PC 0x208.
If the operand points to MMIO, generated code stops with an exact address
diagnostic. Do NOT invent MMIO register values to force progress.

## Scope and limitations
- The generated block is C compiled into ARM Thumb-2, with no runtime opcode
  decoding. It supports ROM and emulated 64 KiB RAM word reads.
- Only ROM PCs 0x200 and 0x208 are currently wired into the dispatcher.
- The 0xA12E AOT block remains a separate self-test.
- Reset MMIO read at 0xA10008 remains provisional, not hardware-accurate.
- This is NOT a playable native port or a general AOT translator.
- No NuttX kernel modifications, no Musashi linked in native-only mode.

Host GCC syntax checks passed for the default stub build.
STM32H743 build and runtime validation have not been performed.
