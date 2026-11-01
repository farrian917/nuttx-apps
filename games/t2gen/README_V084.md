# T2GEN V0.84 native AOT batch

Based on V0.83. Hardware-observed entry 0x0099BC seeded, plus 0x0099FA.
Added MOVE.W Dn,(abs.l), CMP.W Dn,Dn, BGT.W and additional conditional branch decoding.
Generated ROM-specific CFG: see tools/aot_cfg_report.json. No runtime 68000 interpreter.
This is a conservative partial batch: the newly discovered routine at 0x009A04 stops on unsupported opcode 0x5379 in existing generator handling; the complete graphics path is NOT implemented.
Rebuild using python3 tools/generate_cfg_aot.py tools/t2.gen and NuttX make -j.
STM32H743 hardware testing pending.
