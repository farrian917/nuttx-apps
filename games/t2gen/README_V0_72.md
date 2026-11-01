# T2GEN V0.72 — batched offline AOT extension

Starting point: V0.71 hardware log stops at 0x004AA0.

## New decoded instruction families
- MOVE.L #imm,Dn (0x203C family), including N/Z and clearing V/C.
- MOVE.W #imm,(abs.l) (0x33FC), including VDP-mapped writes.
- LEA (abs.w),An (0x41F8 family), with 24-bit sign extension.
- MOVE.L An,(abs.l) (0x23C8 family).

The generator now allows 256 instructions per discovered block and up to 8192 blocks. The report includes aggregate coverage and unsupported-opcode histogram. No runtime opcode decoding or Musashi is added.

## Limitations
This is not a complete 68000 decoder or verified full-game translation. The ROM may still stop at unsupported instructions, bus faults, or unsupported dynamic targets. VDP still does not implement all hardware behavior. Hardware testing is pending.

## Generate
python3 tools/generate_cfg_aot.py tools/t2.gen

## Hardware
Build the normal NuttX application and run: t2gen /mnt/t2.gen /dev/fb0

Inspect tools/aot_cfg_report.json for coverage and unsupported instructions.
