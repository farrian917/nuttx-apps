# T2GEN V0.44.3 — TST.W absolute-long support

Based on the complete V0.44.2 source archive. Preserves all existing files and previous diagnostics.

- Adds 68000 opcode `0x4A79`: `TST.W (xxx).L`.
- Fetches the 32-bit effective address from ROM, applies the 24-bit address bus mask.
- Uses checked big-endian 16-bit reads from ROM, emulated 68000 RAM, or the provisional Genesis I/O model.
- Rejects odd and unmapped addresses; logs operand address and value.
- Updates N and Z and clears V and C while preserving X and upper SR bits.
- Charges 16 nominal 68000 cycles for the instruction.
- Reset trace markers now identify V0.44.3.

**Caveat:** I/O even-byte lanes and default register values remain provisional. This is a bounded diagnostic native interpreter, not a playable emulator. No NuttX kernel changes.

Install `t2gen/` into `apps/games/t2gen/`, build with `make -C ../apps/games/t2gen clean && make -j` from NuttX root, then run `t2gen /mnt/t2.gen none`.

Host syntax checking is not a target cross-compile or hardware test.
