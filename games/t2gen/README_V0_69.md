# T2GEN V0.69 — batched native AOT control flow

Based on V0.68. Adds offline-generated JSR absolute long/short, BSR short/word, and RTS, with real big-endian 68000 stack push/pop through the existing Genesis bus. Expands offline CFG discovery to 2048 blocks. Call targets and fall-through addresses are discovered statically; indirect targets remain unsupported and fail closed.

No runtime opcode interpreter or Musashi. The AOT generator still supports a limited instruction subset; this is not a complete 68000 translator. No claim of playable graphics.

Generate: `python3 tools/generate_cfg_aot.py tools/t2.gen`

Expected first new stopping point: consult `tools/aot_cfg_report.json`, then validate on STM32 hardware. Stack starts at 0x01000000 and first JSR wraps to 0xFFFFFC (Genesis work RAM).
