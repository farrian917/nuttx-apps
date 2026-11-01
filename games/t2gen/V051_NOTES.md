# V0.51 native AOT — Genesis version register and expanded CFG translation

- Genesis hardware version register at 0xA10001 now returns 0x80 (USA NTSC, provisional version 0). This should make ANDI.B #$0F,D0 yield zero and BEQ at 0x224 take branch to 0x22E.
- Offline generator supports MOVE.L #imm,(d16,A1) opcode 237C and MOVE.W (An),Dn opcode family including 3014.
- Big-endian 32-bit writes to Genesis work RAM, rejecting ROM/MMIO writes and odd alignment. ROM signatures checked at runtime.
- No runtime 68000 instruction interpreter; generated C compiled to Thumb-2 in target build.
- The current CFG still stops at the next unsupported opcode. No gameplay, VDP, audio or interrupts yet.
- Generated against ROM CRC32 2F75E896. ROM not included.

Build:
    python3 ../apps/games/t2gen/tools/generate_cfg_aot.py ../apps/games/t2gen/tools/t2.gen
    make -C ../apps/games/t2gen clean
    make -j

Run:
    nsh> t2gen /mnt/t2.gen none

Host GCC -Wall -Wextra -Werror syntax check passed. Target not tested.
