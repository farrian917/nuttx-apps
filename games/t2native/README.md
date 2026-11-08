# T2NATIVE V1.5 — Verified VDP tile and sprite extraction

Based on V1.3, not V1.4. Original intro and H32 centering unchanged.

* Original first-level background reconstructed from Plane A/B of captured VDP state 700, with the original HUD preserved.
* Original player sprite reconstructed from VDP sprite attribute table (SAT), VRAM tiles, and CRAM palette at snapshots 700, 720, 730 and 740. No screen-difference cropping.
* Default pose uses snapshot 700. The three alternate upper-body poses are used during firing. **No invented walk cycle.**
* No fake scrolling or repeated background. Gameplay uses a fixed 320x224 view until a genuine level map is reconstructed.
* Original intro at 25% speed; no runtime 68000/Musashi.

## Build

Extract `t2native/` to `apps/games/t2native`, enable `CONFIG_GAMES_T2NATIVE=y`, rebuild NuttX.

Run `nsh> t2native`. At title type `s` (and Enter if terminal is canonical). In gameplay `a/d` move, `w` jump, `f` shoot, `q` quit.

## Asset provenance

Input ROM `t2(2).gen`, 1,048,576 bytes, CRC32 `2F75E896`.
Source VDP states `state_0700.bin`, `state_0720.bin`, `state_0730.bin`, `state_0740.bin` from previous offline Musashi capture. These captures are **not** the complete level map and do not establish correct walk animation timing. Assets are embedded; no ROM file is needed on target.

`tools/make_v15.py` regenerates `game_assets.c` and `game_assets.h` from the existing offline captures. It requires the capture files, numpy, Pillow and lz4 on the host. Set `T2_VDP_CAPTURE_DIR` to the directory containing `render.py` and `frames/state_*.bin`. This is optional for the target build.
