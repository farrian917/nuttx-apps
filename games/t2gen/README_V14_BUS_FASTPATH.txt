T2GEN V14: Musashi ROM/RAM bus fast paths

Based on V13 CPU/video profiling version.

Changes:
- Direct big-endian ROM word/long reads when fully within ROM.
- Direct 64-KiB RAM word/long reads and writes, with 16-bit wrapping.
- Preserve generic fallback for IO, VDP, and ROM-boundary crossings.
- Preserve V13 CPU-only benchmark (none), rendering, DMA2D, Xbox, and diagnostics.
- No change to Musashi table allocation or MPU configuration; SRAM relocation is intentionally deferred.

Benchmark:
  t2gen /mnt/t2.gen none 0
  t2gen /mnt/t2.gen /dev/fb0 0

Compare V13 vs V14 on the same game and build settings.
This version has not been compiled or tested on the target.
