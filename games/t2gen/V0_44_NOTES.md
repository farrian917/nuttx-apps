# T2GEN V0.44 — bounded native reset-vector trace

Based on verified V0.43.11 bundle. Adds an independent 68000 reset-vector interpreter in `t2gen/src/t2gen_native43.c` while preserving the passing A12E block tests.

Supported subset: NOP, RTS with RAM stack, STOP, MOVE #imm,SR, MOVEQ, BRA and Bcc (68000 8/16-bit displacements), JMP absolute long, LEA absolute long. BSR, writes, MMIO and all other opcodes are intentionally unsupported. Execution is bounded by 256 instructions and 4096 nominal cycles; first 16 instructions print trace. Unsupported instructions stop safely.

**This is not a complete emulator and does not play the game.** There is no full bus implementation, video, audio, or interrupts. The earlier intermittent SD read BusFault has not been conclusively diagnosed. No NuttX kernel files are modified.

Install `t2gen/` into `apps/games/t2gen/`, rebuild and run `t2gen /mnt/t2.gen none`. Look for `T2GEN V0.44 RESET_TRACE` and `RESET_STOP` after the existing V0.43.11 block test output.

Host C syntax check was performed; target compilation and hardware test remain pending.
