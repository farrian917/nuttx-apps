# T2GEN V0.90 — offline 68000 AOT batch

Based on V0.89. Added BSET immediate to Dn, NOT.W, ASL.W immediate, LSL.W register count, ORI.W, MOVE.L absolute-to-absolute, MOVE.W absolute-to-stack-predecrement, and generalized brief indexed MOVE.B. Preserves native C AOT with no runtime interpreter.

Coverage on t2.gen CRC32 2f75e896: 263 blocks, 893 instructions, 9 unsupported sites. The invalid destination EA at 000332 remains unresolved. This is not full ROM coverage.

Run:
python3 tools/generate_cfg_aot.py tools/t2.gen > /dev/null
python3 tools/aot_coverage.py
python3 tools/check_aot_host.py

Host syntax check passed; STM32 hardware build/execution not tested.
