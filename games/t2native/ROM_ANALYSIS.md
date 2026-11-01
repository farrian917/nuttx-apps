# Terminator 2 (Genesis) ROM: verified initial facts

Source ROM SHA-256: `08ac0f65af6e8ef20e7371327f1fbfd5a2e7c359b65e45cd0a3ccc640ccef2ca`
ROM size: 1048576 bytes
Initial 68000 stack pointer: `0x01000000`
Reset PC: `0x00000200`
Header checksum: `0x336F`
Computed checksum: `0x336F`
ROM entry bytes at 0x200: `4a b9 00 a1 00 08 66 06 4a 79 00 a1 00 0c 66 7c 4b fa 00 7c 4c 9d 00 e0 4c dd 1f 00 10 29 ef 01`
ROM bytes at 0x4AB0: `23 fc 00 00 00 00 00 c0 00 00 51 c8 ff f4 4e 75`
ROM bytes at 0xA12E: `b2 79 00 ff 03 b0 67 f8 4e 75 78 1f 7a 1b`

## Known control-flow candidates (not a complete disassembly)
- Reset vector `0x000200` begins with `TST.L ($00A10008).L` (`4A B9 00 A1 00 08`), testing a Mega Drive I/O register.
- `0x004AB0`: `MOVE.L #$00000000,$00C00000` followed by `DBF D0,-12` and `RTS` (verify runtime meaning before translating).
- `0x00A12E`: `CMP.W ($00FF03B0).L,D1` followed by `BEQ.S -8`, `RTS`; observed RAM polling loop.

## Scope
These are ROM-derived observations, **not** a completed native gameplay translation.
Exact behavior requires controlled 68000 traces, RAM-state capture, and routine-by-routine porting.
