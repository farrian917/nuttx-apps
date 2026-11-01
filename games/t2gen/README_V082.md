# T2GEN V0.82 — Z80 bus-request native AOT

From V0.81, seed observed PC 0x00EB20 and companion release routine 0x00EB36. Offline generator handles MOVE.L An,-(A7), MOVEA.L (A7)+,An, MOVE.W #imm,(An), BTST #imm,(An), CLR.W (An). Existing bus model is reused. No Musashi or runtime 68000 interpreter.

Run: `python3 tools/generate_cfg_aot.py tools/t2.gen` then build NuttX. Hardware test pending. Inspect TRACE16 and Z80 BUSREQ on hardware.
