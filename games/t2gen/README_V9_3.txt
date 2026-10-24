T2GEN V9.3 PERFORMANCE TEST (experimental)
Based on V9.2.
- Removes VDP debug UART output and full 64 KiB VRAM scans on each DMA.
- Removes repeated-PC and wait-loop console spam.
- Reduces progress messages 10x.
- Renders every 3rd emulated frame instead of every 12th (max 20 displayed FPS at real-time emulation).
- Avoids unnecessary palette ioctl when CRAM unchanged.
- Early sprite X rejection and one window-region test per pixel.

Note: More frequent rendering can REDUCE total emulation speed if renderer remains CPU-bound.
Compare measured CPU and renderer times from V9.2 and V9.3.
No hardware target build performed.
