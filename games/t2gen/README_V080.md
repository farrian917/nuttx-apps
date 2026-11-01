# V0.80 — EB4E branch and stack loop AOT

Based on V0.79 and the hardware-observed stop at PC 0x00EB4E.

New offline native translations:
- BCC.S (0x6414 at EB4E), including both branch successors.
- SUBQ.W #1,Dn (0x5340 at EB60), preserving upper Dn word and correct CCR.
- MOVE.W (A7)+,Dn (0x301F at EB62), restoring the stack pointer and CCR.

The 0xEB50 fall-through now translates the timed delay loop; 0xEB64 branch path remains available.
Existing ROM-specific native dispatch, 1,000,000-block budget, TRACE16 and VDP diagnostics retained.

Build: python3 tools/generate_cfg_aot.py tools/t2.gen ; make -j from NuttX root.
Hardware execution not tested. The next untranslated instructions are reported at runtime.
