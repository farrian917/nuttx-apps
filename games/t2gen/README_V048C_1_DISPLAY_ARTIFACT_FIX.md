# T2GEN V0.48c.1 - Safe display artifact fix

This full-source package preserves V0.48c palette LUT optimization, Genesis VDP renderer, and synchronous DMA2D copy, but disables the V0.48a/b LTDC pan path at runtime. This reproduces the user's confirmed clean-image single-buffer test.

NuttX can remain compiled with CONFIG_STM32_LTDC_FB_DOUBLE_BUFFER=y, but this application renders only into the initial LTDC framebuffer. This is NOT a corrected tear-free double-buffer implementation. Double buffering requires auditing stm32_ltdc.c FBIOPAN_DISPLAY / FBIO_WAITFORVSYNC and verifying hardware scanout completion before buffer reuse.

Install by replacing apps/games/t2gen with the t2gen directory in this ZIP, then build NuttX. Expected log: `T2GEN V0.48c.1 SAFE DISPLAY: double=0`.

No blanket DMA2D destination cache invalidation is added because it could discard dirty CPU data.

Archive verified, but compilation and hardware operation not tested here.
