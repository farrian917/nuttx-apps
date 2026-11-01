# V0.43.6 checksum-bypass diagnostic

Based on V0.43.5. Only `t2gen/src/t2gen_main.c` modified.

- Bypasses Genesis ROM checksum loop and checksum-related printf/fflush.
- Writes phase markers 0x43600010 and 0x43600020 to internal .bss, with DSB.
- Continues to the existing `T2GEN: ROM probe OK` and initialization.
- No changes to NuttX kernel or native engine.
- The checksum bypass is temporary, for diagnosis only.
- Compile/hardware testing not performed.
