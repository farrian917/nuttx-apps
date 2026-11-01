# T2GEN V0.45 — Native ARM-targeted AOT proof of architecture

This release changes the NuttX native-only build from the V0.44.x runtime
68000 opcode tracer to statically compiled C routines. `arm-none-eabi-gcc`
compiles these routines into native Cortex-M7 Thumb-2 code.

## Implemented
- Signature-guarded native reset block at ROM PC 0x000200:
  TST.L ($00A10008).L; BNE.S +6.
- Signature-guarded native self-test block at 0x00A12E:
  CMP.W ($00FF03B0).L,D1; BEQ.S -8; RTS boundary.
- No runtime 68000 instruction decoder, no Musashi linkage, and no
  modifications to the NuttX kernel.
- Heap-backed 64 KiB Genesis RAM, preserving the previous stack fix.
- The existing SD card ROM loading and SDRAM test in t2gen_main.c remain.

## Limits / accuracy
This is **NOT a playable port of Terminator 2** and is not a complete
static translator. It contains two manually translated ROM-specific
blocks. A complete implementation needs a ROM-aware AOT generator,
indirect-branch resolution, memory/VDP/I/O models, interrupt scheduling,
audio and display integration.

The reset block uses the previous *provisional* 0xA10008 MMIO value of
zero; it is not proven hardware-accurate. It stops at PC 0x000208 rather
than interpreting subsequent ROM opcodes. The 0xA12E block is exercised
only as an isolated self-test and does not emulate the RTS return.

The source checks known instruction signatures before executing native
blocks and fails closed if they differ. A ROM file is not included.

## Installation
Replace apps/games/t2gen with the included t2gen directory, then:
    make -C ../apps/games/t2gen clean
    make -j
Run:
    nsh> t2gen /mnt/t2.gen none

The existing CONFIG_GAMES_T2GEN_V043_NATIVE_ONLY=y selects the
native-only path. The Makefile now compiles src/t2gen_native45.c
instead of src/t2gen_native43.c.

Host GCC syntax check passed. No ARM cross-compiler or STM32 board
was available in the packaging environment; hardware test pending.
