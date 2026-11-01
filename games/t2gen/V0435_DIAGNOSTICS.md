# T2GEN V0.43.5 — application-only BusFault diagnostics

Based on complete V0.43.4 source bundle. No NuttX kernel files changed.

Changes in `src/t2gen_main.c`:
- Removed unsupported Cortex-M7 ACTLR.DISDEFWBUF experiment.
- Removed all console output and DSB operations from within checksum loop.
- Added a DSB immediately after checksum loop.
- Added volatile internal-linked `.bss` phase marker and checksum result.
- Printed checksum only after post-loop DSB and marker updates.

Phase marker `g_t2gen_v0435_phase` values:
- 0x43500001: application entered
- 0x43500010: checksum about to start
- 0x43500020: loop finished, before post-loop DSB
- 0x43500030: DSB finished
- 0x43500040: checksum stored in `g_t2gen_v0435_sum`
- 0x43500050: first checksum diagnostic output finished

These are static symbols, which can be inspected in a debugger using a symbol-aware GDB build; compiler optimizations should retain them because they are volatile. The phase marker is not a persistent crash log and will be reset on reboot.

Run: `t2gen /mnt/t2.gen none`

Note: this archive is not hardware-tested or compile-tested in the user's NuttX tree.
