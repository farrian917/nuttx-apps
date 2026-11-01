# T2GEN V0.47 — Shared Genesis I/O reads for native AOT blocks

Based on V0.46. This release adds a shared read-only Genesis I/O bus
for ROM-specific compiled blocks, and supplies the observed 0x208 block.

- `src/t2gen_native47.c`: 8/16/32-bit big-endian Genesis I/O reads,
  checked ROM/RAM word reads, PC-indexed native block dispatcher.
- `src/t2gen_aot_generated.inc`: pre-generated block for
  `TST.W ($00A1000C).L` at 0x208, signature-checked against the ROM.
- `tools/generate_aot.py`: updated to generate blocks using the shared bus.
- No NuttX kernel modifications and no Musashi in the selected native path.

**Hardware accuracy warning**: The controller and even-byte-lane values are
PROVISIONAL. The initial value at 0xA10008 and 0xA1000C remains zero.
The resulting branch path may differ from a real Mega Drive. Only the
observed ROM signature at 0x208 is supported by the bundled block.

Build:
    make -C ../apps/games/t2gen clean
    make -j
Run:
    nsh> t2gen /mnt/t2.gen none

Expected diagnostics:
    T2GEN V0.47 AOT_0208: TST.W addr=a1000c value=0000 ...
    T2GEN V0.47 DISPATCH_STOP: untranslated pc=00020e

The generator can be rerun with your exact ROM:
    python3 ../apps/games/t2gen/tools/generate_aot.py /path/to/t2.gen

Host GCC syntax checks passed; target hardware execution is untested.
This is not a playable native Terminator 2 port.
