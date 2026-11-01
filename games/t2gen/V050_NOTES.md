# T2GEN V0.50 — Offline control-flow AOT prototype

Built from the supplied V0.49 source and exact `t2.gen` (CRC32 2F75E896).

## New
- `tools/generate_cfg_aot.py`: offline conservative basic-block analyzer.
- `src/t2gen_aot_cfg.inc`: generated native C code for PC 0x21C.
- `tools/aot_cfg_report.json`: discovered blocks, edges, unsupported opcodes.
- `src/t2gen_native50.c`: integrates generated dispatch and checked byte reads.

The generator currently supports a deliberately narrow instruction subset:
MOVEQ, ANDI.B #imm,Dn, MOVE.B (d16,A1),D0 (matching encoded form),
BRA.S, BEQ.S, BNE.S. No runtime opcode decoding is added.

The exact ROM at 0x21C contains MOVE.B (d16,A1),D0; ANDI.B; BEQ.S.
Both branch targets stop at unsupported MOVE variants (0x226 and 0x22E).
The byte memory access may stop earlier if the calculated address is
outside the modeled ROM, RAM, and provisional controller I/O regions.

## Build
Copy `t2gen/` to `apps/games/t2gen/` and run:

    python3 ../apps/games/t2gen/tools/generate_cfg_aot.py /path/to/t2.gen
    make -C ../apps/games/t2gen clean
    make -j

On target:

    nsh> t2gen /mnt/t2.gen none

## Important limitations
- NOT a playable port, not a full 68000 translator.
- The controller MMIO model is still provisional.
- No sound/video gameplay support added.
- Generated source contains no ROM data and does not redistribute the ROM.
- Host GCC syntax check passed. ARM cross-build and hardware test pending.
- The CFG scan is conservative, follows direct branches only, and may not
  identify reachable code behind indirect jumps, exceptions or tables.
- CPU instruction cycle timings and some bus behaviors still need validation.
