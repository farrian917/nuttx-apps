# T2GEN V0.44.2 — provisional Genesis I/O read support

Based on V0.44.1. Adds a read-only byte-lane model for 0xA10000–0xA1001F
and checked big-endian long reads for TST.L at 0xA10008.

The Mega Drive I/O registers are generally on odd byte addresses; even
lanes/open-bus values are approximated as zero for this diagnostic only.
Controller ports default to 0x7F (no buttons pressed), controls to zero.
The version register is provisionally 0xA0. These values are NOT verified
against the target game and must not be treated as accurate hardware emulation.

No writes or side effects are modeled. Unsupported reads still stop safely.
The 256-step/4096-cycle bounds and prior native block tests are retained.

Build from NuttX tree:
```
make -C ../apps/games/t2gen clean
make -j
```
Run `t2gen /mnt/t2.gen none`. Look for `V0.44.2 IO_READ32` and `RESET_STOP`.

This is not a playable emulator. No target hardware validation was performed.
