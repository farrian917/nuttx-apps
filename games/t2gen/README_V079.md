# V0.79 ROM-specific native AOT continuation

Based on V0.78. Offline CFG seeds the observed 0x00EB44 entry and translates CMPI.B #imm,Dn, BCS.S, MOVE.W Dn,-(A7), ADDQ/SUBQ.W absolute-long, ADDQ.B #1,D0.

Offline CFG with bundled 1 MiB ROM CRC32 2f75e896: 156 blocks, 461 instructions. First new branch at EB44: CMPI.B #$70,D0; BCS.S $EB64. Remaining unsupported opcode at EB4E is 6414 (BCC.S), and at EB6C is 56F9. No hardware validation has been performed.

Generate: python3 tools/generate_cfg_aot.py tools/t2.gen
Build in NuttX tree: make -j
Run: t2gen /mnt/t2.gen /dev/fb0
