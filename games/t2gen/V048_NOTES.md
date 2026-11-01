# V0.48 — Actual ROM-based native startup extension

Source ROM SHA256: 08ac0f65af6e8ef20e7371327f1fbfd5a2e7c359b65e45cd0a3ccc640ccef2ca
CRC32: 2f75e896, size 1 MiB. ROM itself is NOT included.

Compiled ROM-specific blocks: 0x200, 0x208, 0x20E (BNE.S +0x7C), 0x210 (LEA 0x007C(PC),A5).
0xA12E remains a separate native block self-test.

Expected path with current PROVISIONAL controller I/O model:
  0x200 -> 0x208 -> 0x20E -> 0x210 -> 0x214 (untranslated stop)
At 0x210, A5 becomes 0x28E.

Build from NuttX root:
  python3 ../apps/games/t2gen/tools/verify_rom.py /path/to/t2.gen
  make -C ../apps/games/t2gen clean
  make -j
Run on board:
  t2gen /mnt/t2.gen none

Limitations: This is NOT a complete native game port. The controller I/O
values are provisional, so the game may actually follow another path.
The native dispatcher deliberately stops at untranslated PC 0x214.
A complete port still needs complete reachable code translation, indirect
control flow, VDP, audio, input and accurate Genesis timing.
Host GCC syntax tested; target testing pending.
