# T2GEN V0.60 native AOT continuation

Based on V0.59.1 stack fix and real ROM-driven VDP renderer.

- Offline ROM-specific AOT adds MOVE.L Dn,(An) (opcode 2680 at 0x268 and 0x272), supporting DBF-controlled zero-fill loops.
- No runtime 68000 interpreter, no fabricated SEGA logo.
- Still does not implement VDP DMA or complete ROM startup. Do not expect visible graphics yet.
- Regenerate the CFG using tools/generate_cfg_aot.py and tools/t2.gen; build NuttX and run `t2gen /mnt/t2.gen /dev/fb0`.

Expected next unsupported opcode: 0x175d at PC 0x27a.
