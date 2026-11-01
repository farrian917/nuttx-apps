# T2GEN V0.71 — fix MOVE.B immediate postincrement destination

Hardware V0.70 stopped at block 0x004A28 with `WRITE_STOP addr=000000`. Root cause: for opcode 0x10FC (MOVE.B #$00,(A0)+), the offline generator incorrectly selected the destination register with `op & 7` (source immediate addressing-mode register field = 4), writing through A4 instead of A0.

V0.71 uses `(op >> 9) & 7` (68000 MOVE destination register bits 11:9). Generated block now writes to A0, starting at 0xFF0002, then postincrements A0. It keeps the ROM write guard; it does not permit writes to address zero.

Added `T2GEN V0.71 WRITE_FAULT` with source PC/opcode, effective address, operand size/value and CPU registers for this instruction family. The `AOT_STOP` and `STACK` labels are now V0.71.

Validation: generator completed, generated 0x004A28 block inspected for A0 rather than A4, host GCC syntax check. Real STM32H743 execution pending.

Build: `python3 ../apps/games/t2gen/tools/generate_cfg_aot.py ../apps/games/t2gen/tools/t2.gen` then `make -j`.

No Musashi or runtime opcode interpreter.
