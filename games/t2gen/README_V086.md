# V0.86 ROM-specific native AOT

Based on V0.85. Extends the 0x009A46 arithmetic path with EOR.W, OR.W, AND.W, SUB.W, LSR.W, MOVEA.W, MOVE.W Dn,(An)+ and SUBA.W immediate. Also fixes an existing ANDI.B decoder mask that incorrectly classified ANDI.W opcode 0x0244 as byte-sized, which would corrupt D4's high byte in the graphics/data-processing loop.

Offline generation: python3 tools/generate_cfg_aot.py tools/t2.gen

No Musashi and no runtime 68000 interpreter. Hardware testing remains necessary. The generated report is tools/aot_cfg_report.json.
