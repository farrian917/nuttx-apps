# T2GEN V1.09 — Native LSL.L immediate

Adds native AOT translation of 68000 LSL.L #1..8,Dn, including the ROM opcode E188 at 0x00E05A (LSL.L #8,D0). Preserves X unless carry is set as required for nonzero shift counts; updates X/C together, N/Z and clears V. Adds runtime entry 0xE05A. The following MOVE.B (A0)+,D0 and DBF D1 loop are already translated.

## Display regression

The user's V1.08 UART log shows CRAM nonzero bytes = 0 after 2,588 CRAM writes. The renderer derives pixel colors from CRAM, so previously visible red SEGA can disappear even though VRAM and nontransparent pixel counts are unchanged. This release does NOT force a palette or claim to fix the display. Next debugging step is to inspect CRAM writes and VDP control commands when the palette is cleared, and verify that the game is intentionally blanking during a transition.

## Build

python3 tools/generate_cfg_aot.py tools/t2.gen
python3 tools/check_aot_host.py

Run on STM32H743 using `t2gen /mnt/t2.gen /dev/fb0`.
