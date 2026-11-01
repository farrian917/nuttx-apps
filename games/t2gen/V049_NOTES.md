# T2GEN V0.49 — native ROM-specific MOVEM translation

Built from the user-supplied V0.48 source and T2 ROM (CRC32 2F75E896).

## Added
- Offline Python generator `t2gen/tools/generate_movem_aot.py` translates the two known MOVEM postincrement instructions at 0x214 and 0x218 into native C, with literal ROM signature checks.
- `t2gen/src/t2gen_aot_movem.inc` is already generated for this exact ROM.
- `t2gen/src/t2gen_native49.c` dispatches PC 0x214 and 0x218 to the compiled code, with a checked big-endian 32-bit bus read.
- MOVEM.W values are sign-extended to 32-bit registers; MOVEM.L loads 32-bit values. A5 is post-incremented by the total byte count.
- Expected next untranslated PC: 0x21C, if the existing provisional I/O model leads down the same path.

## Build
Replace apps/games/t2gen with this archive's t2gen directory, then:

    make -C ../apps/games/t2gen clean
    make -j

Run on NuttX:

    nsh> t2gen /mnt/t2.gen none

To regenerate for the same ROM:

    python3 ../apps/games/t2gen/tools/generate_movem_aot.py /path/to/t2.gen

## Scope
This is **not a full native port**. The generator currently supports only the two known MOVEM instructions. It is not a general CFG translator. It contains no ROM and no complete Genesis hardware emulation. Controller I/O values remain provisional. The native path contains no runtime 68000 instruction decoding or Musashi interpreter.

Host GCC syntax validation passed. No ARM cross-build or hardware validation was performed here.
