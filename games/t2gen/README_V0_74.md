# T2GEN V0.74 — observed 0xEAD4 AOT continuation

Native offline ROM-specific AOT; no runtime opcode interpreter. Added MOVEM.L register-list,-(An) and MOVEA.L #imm,An and seeded hardware-observed 0x00EAD4 entry. Generator report includes remaining unsupported opcodes. No VBlank IRQ implementation yet; the prior status-read-based VDP model is unchanged. No on-target test claimed.

Build: python3 tools/generate_cfg_aot.py tools/t2.gen ; make -j
