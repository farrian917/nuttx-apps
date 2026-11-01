# T2GEN V0.98 — indexed indirect JSR / RAM target diagnostic

Based on V0.97. Adds read-only tracing at native dispatcher PC 0x009420,
0x009448 and any RAM execution target 0xFF0000-0xFFFFFF. Logs D0/A0/A1,
ROM pointer-table entries at 0x9166+D0.W and 0x913A+D0.W, RAM pointers
at FF0238 and FF023C, and 32 bytes at the RAM execution target plus
48 bytes around FF0620. No RAM code execution, synthetic pointer rewriting,
or runtime 68000 instruction decoding is introduced.

Build: regenerate tools/generate_cfg_aot.py tools/t2.gen then make -j.
Run: t2gen /mnt/t2.gen /dev/fb0. Share INDEX_TRACE and RAM_TARGET lines.
