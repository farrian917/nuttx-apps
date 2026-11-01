# V0.88 offline AOT instruction-family expansion

Based on V0.87. Adds native translations for previously reported 68000 opcode sites: MOVE.L absolute, MOVE.B displacement, ADD.B, ADDQ/SUBQ.B, ADDI.W, ADDI/SUBI.W absolute, CMP/CMPI.W absolute, LSL.W/L, BSET immediate absolute.

Coverage on bundled ROM CRC32 2f75e896: 224 blocks, 760 instructions, 16 unsupported sites (14 unique reasons), plus unresolved invalid opcode 3abc at 000332. The newly exposed sites require further decoder work. No claim of full 68000 support or STM32 target build.

Run: python3 tools/generate_cfg_aot.py tools/t2.gen && python3 tools/aot_coverage.py
