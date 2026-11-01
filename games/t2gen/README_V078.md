# T2GEN V0.78 — block-budget correction

Based on V0.77, this release increases the native AOT dispatcher budget from 65,536 to 1,000,000 blocks. The ROM-specific `MULS.W D1,D1` / `DBF D0` loop at 0x00AA0E requires 65,536 visits when D0.W initially equals 0xFFFF, in addition to startup blocks. This is a diagnostic budget change, not an instruction-semantic change.

The budget can be overridden with `-DT2GEN_NATIVE_BLOCK_BUDGET=<count>u` in CFLAGS. On exhaustion, the emulator now prints the final PC, D0, D1, SR, A7, cycles and last 16 block PCs. The program still exits after the budget, rather than running indefinitely.

Build normally with `python3 ../apps/games/t2gen/tools/generate_cfg_aot.py ../apps/games/t2gen/tools/t2.gen` then `make -j`. Run `t2gen /mnt/t2.gen /dev/fb0`. STM32 hardware validation is pending.
