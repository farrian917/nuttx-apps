# T2GEN V0.91 — Offline AOT instruction-family batch

Based on V0.90, exact ROM CRC32 2f75e896.

Added: ST (abs.l), OR.B Dn,Dn, SWAP Dn, MOVE.L Dn,(An)+,
ADDI.L #imm,(abs.l), MOVE.W (A7)+,(abs.l).

Coverage after regeneration: 308 blocks, 1081 instructions, 8 unsupported sites.
Remaining sites: 0052e8, 008718, 009c8a, 00a31e, 00a51c,
00abbc, 00b892, 00e192. Invalid CFG EA at 000332 persists.

Hardware not tested. No runtime 68000 interpreter.
