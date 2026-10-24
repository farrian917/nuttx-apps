T2GEN V8.4 — extended execution and first-nonzero diagnostics

Full source based on V8.3. No VDP functional changes intended.
- 10,000,000 68000 cycles (~78 NTSC frames at 488 cycles/scanline)
- VDP progress printed every 1000 slices instead of 100
- First nonzero CPU VDP writes to VRAM, CRAM, VSRAM
- Explicit DMA fill arm/execute/completion and fill counters
- Existing V8.3 bus trace, V8.1 memory inspection and snapshot retained

Known limitations: approximate DMA/timing, no sprites/audio/Z80,
static snapshot only. NOT a playable emulator.

Install under apps/games/t2gen and rebuild NuttX.
