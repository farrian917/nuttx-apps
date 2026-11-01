# T2GEN V0.92 — RAM wait-loop diagnostics

Built on V0.91. At PC 0x00A0DA, log FF0218, FF0222, SR, VDP register 1,
interrupt vector 4 and 6 addresses and cycle count. Stop after 4096 consecutive
iterations when FF0218 remains nonzero, instead of burning the 1,000,000-block
budget. Log writes to FF0218/FF0219 via byte and word bus operations.
No fake interrupts, RAM changes, Musashi, or runtime opcode decoding.
This is diagnostic, NOT yet a VBlank interrupt implementation.
