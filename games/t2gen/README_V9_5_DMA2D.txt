T2GEN V9.5 experimental real DMA2D integration

1. Append patches/stm32_dma2d_t2gen_function.c.inc to the end of
   nuttx/arch/arm/src/stm32h7/stm32_dma2d.c, BEFORE any final outer #endif.
   The helper needs existing private g_lock, g_initialized and stm32_dma2d_start.
2. Ensure CONFIG_STM32_DMA2D=y and DMA2D driver is initialized by board.
3. Rebuild NuttX and apps together.
4. Run t2gen /mnt/t2.gen /dev/fb0 0

The helper uses DMA2D memory-to-memory RGB565 transfers to copy pairs of
L8 indices as raw 16-bit words. It copies a 640-byte expanded scanline to
alternate display lines using TWO DMA2D transfers per emulated image.
The DMA2D hardware cannot scale pixels; horizontal expansion remains CPU.

WARNING: This is an experimental uncompiled integration. Source staging
must be in DMA-accessible memory; verify its address. The CPU renderer is
still likely the dominant bottleneck. DMA2D must be initialized.
