# T2GEN V0.95: IRQ6 callback native AOT expansion

Adds 0x009B30 to the offline CFG roots, retaining 0x004D2C and 0x004D38.
Adds ANDI.W #imm,(abs.l), MOVE.L (d16,An),Dn, TST.W (An), CMPI.W #imm,Dn,
MULU.W #imm,Dn, ADDA.W Dn,An, CLR.B (An)+ and AND.B Dn,(abs.l).

ROM CRC32 2f75e896. Reachable coverage: 353 blocks, 1259 instructions,
14 unsupported sites. These include newly discovered paths from the IRQ6 callback.
This does NOT claim complete IRQ6 callback execution or a working framebuffer.

Run generator, coverage, build, hardware UART test. No runtime opcode interpreter.
