# V0.85 native AOT continuation

Starting from V0.84, adds the observed 0x009A2A ROM entry and offline translation for:
- BTST Dn,(absolute long) with byte bit-index modulo 8, Z-only status update
- MOVE.W (absolute long),Dn
- MOVEA.L An,An
- MOVE.W (An)+,Dn

The generated CFG reaches 0x009A46 on the fall-through path, where opcode B741 is not yet translated. The branch from 0x009A30 to 0x009A7C is also discovered; actual hardware path depends on RAM bit state. This is an incremental, not full graphics-decoder implementation.

Build: python3 tools/generate_cfg_aot.py tools/t2.gen && make -j (from NuttX root).
Hardware not tested here.
