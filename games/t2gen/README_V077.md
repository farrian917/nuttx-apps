# T2GEN V0.77 — ROM-specific native AOT

Hardware-observed continuation PC: 0x00AA0E (V0.76).

Changes:
- Seed 0x00AA0E in offline CFG discovery.
- MULU.W and MULS.W Dn,Dn (68000 16-bit operands, 32-bit result, NZVC update).
- MOVE.W Dn,Dn, ANDI.W #imm,Dn, MOVEA.L (abs.l),An.
- 16-entry native block PC ring printed on untranslated-PC stop.
- Unsupported opcode context (PC, opcode, next 16 ROM bytes) in tools/aot_cfg_report.json.
- Host syntax-check script for generated C (not a functional CPU test).

Build:
  python3 ../apps/games/t2gen/tools/generate_cfg_aot.py ../apps/games/t2gen/tools/t2.gen
  make -j
  nsh> t2gen /mnt/t2.gen /dev/fb0

ROM CRC32: 2f75e896. No runtime 68000 instruction decoder or Musashi.

Not yet implemented: Z80 execution, VDP DMA, accurate VBlank interrupts.
STM32H743 compilation and hardware execution are NOT verified by host syntax check.
