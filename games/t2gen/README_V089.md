# V0.89 offline AOT instruction expansion

Based on V0.88. Added native translations for MOVE.B immediate to Dn and absolute-long memory, BTST immediate to Dn, ANDI.L immediate to Dn, ADD.W absolute-long to Dn, MOVE.B displacement(An) to Dn, NEG.W Dn, and generalized CMP.W absolute-long to Dn. Re-generated t2gen_aot_cfg.inc for bundled exact ROM CRC32 2f75e896.

Coverage: 251 translated blocks, 833 translated instructions, 14 reported unsupported sites (some duplicates). Unresolved 0x000332 invalid destination EA remains. This is NOT complete MC68000 coverage; STM32H743 build and hardware execution not verified. Do not assume all ROM code is reachable/discovered.

Build: python3 ../apps/games/t2gen/tools/generate_cfg_aot.py ../apps/games/t2gen/tools/t2.gen; python3 ../apps/games/t2gen/tools/aot_coverage.py; make -j
