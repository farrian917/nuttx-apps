T2GEN V8.9 diagnostic plane rendering

Build in existing NuttX apps/games directory.

Usage:
  t2gen /mnt/t2.gen /dev/fb0 0  - composite
  t2gen /mnt/t2.gen /dev/fb0 1  - plane A only
  t2gen /mnt/t2.gen /dev/fb0 2  - plane B only
  t2gen /mnt/t2.gen /dev/fb0 3  - priority visualization

V8.9 adds signed scroll decoding, explicit backdrop/plane/sprite ordering,
and plane dimensions/base address diagnostics. It does not claim full VDP
accuracy (window plane, interlace, shadow/highlight, sprite collision absent).
Note: each invocation runs the emulation from reset; no live view switching.
Target build and hardware validation have not been performed.
