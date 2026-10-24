T2GEN V8.7 - 60 million 68000 cycles, render every emulated VBlank.
Retains existing tile renderer, DMA fill and Musashi bus.
No wall-clock pacing, scrolling, sprites, Z80 or audio.
On STM32H743, full framebuffer updates each frame can be expensive.
Run: t2gen /mnt/t2.gen /dev/fb0
Observe LCD and share console log.
