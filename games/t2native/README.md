# T2NATIVE V0.2 — exact-port reverse-engineering baseline

This release is a **ROM-verified native graphics prototype**, not a playable port.
It executes no Motorola 68000 code. The original Terminator 2 game logic is **not** translated yet.
It retains V0.1's synthetic tilemap and moving marker, which are not original game assets.

## Host analysis
Run `python3 tools/rom_inspect.py '/path/to/T2 - Terminator 2 - Judgment Day (USA, Europe).gen'`.
See `ROM_ANALYSIS.md` for verified values from the provided ROM.

## NuttX
Install `t2native` under `apps/games/`, register its Kconfig, and enable `CONFIG_GAMES_T2NATIVE=y`.
Run `t2native /mnt/t2.gen /dev/fb0 60`.
V0.2 checks the 1 MiB reference ROM, reset vector, and Genesis header checksum
before starting the native graphics prototype. It deliberately does not emulate or
translate the game.

## Exact port next steps
1. Instrument T2GEN to export per-frame CPU PC, RAM checksums, controller inputs,
   VDP writes, and selected state variables.
2. Reconstruct reset and initialization routines from 68000 instructions.
3. Translate routines into C, validating output state against recorded traces.
4. Add native input/logic/frame scheduling and later original graphics/audio.

No gameplay fidelity or performance improvement is claimed for V0.2.
