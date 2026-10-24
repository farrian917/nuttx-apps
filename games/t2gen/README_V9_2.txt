T2GEN V9.2 EXPERIMENTAL GAMEPLAY PROGRESSION TEST

Changes:
- Raise bounded execution to 300 million 68000 cycles (~39 s of emulated time).
- Add emulated Genesis port-1 three-button controller data/control registers.
- Auto-pulse Start at emulated frames 480-491 and 900-911.
- Render every 12th VBlank to reduce LCD rendering overhead.
- Batch CPU performance timing every 256 slices.

Usage: t2gen /mnt/t2.gen /dev/fb0 0

WARNING: This is NOT verified gameplay. Start pulses are diagnostic and
not synchronized to title screens. No physical Xbox controls, audio or Z80.
If game still loops at PC A134, inspect game flow and I/O before further
cycle-limit increases. A 300M-cycle run can take several minutes.
