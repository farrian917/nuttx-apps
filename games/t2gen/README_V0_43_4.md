# T2GEN V0.43.4 — application-only BusFault diagnostics

Based on V0.43.3 complete bundle. Only `t2gen/src/t2gen_main.c` is changed.
No NuttX kernel files are included or modified.

- In native-only mode, attempt to set Cortex-M7 ACTLR.DISDEFWBUF at startup and print readback.
- Add a DSB plus progress print every 64 KiB during ROM checksum scanning.
- Preserve V0.43.3 diagnostics and native-only engine.
- Intended for privileged flat NuttX build; do not use the ACTLR write in an unprivileged/protected application.
- This is a diagnostic build, not a fix. Write buffering changes may reduce performance and may not make every fault precise.

**Important:** Revert any temporary changes to NuttX `arm_busfault.c` if its added `_alert` register dump interferes with panic reporting. This archive does not revert those kernel changes.

Build and run as before: `t2gen /mnt/t2.gen none`.

Not compiled or tested on physical STM32H743 hardware in this environment.
