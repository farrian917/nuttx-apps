
/* T2GEN V9.5: DMA2D raw L8 framebuffer copy via RGB565 word packing.
 * Add to arch/arm/src/stm32h7/stm32_dma2d.c (inside CONFIG_STM32_DMA2D).
 * Output L8 is unsupported in DMA2D; packing pairs into RGB565 words in
 * memory-to-memory mode preserves both 8-bit palette indices unchanged.
 */
int stm32_dma2d_t2gen_copy_l8x2(const void *src, void *dst,
                                  unsigned src_stride, unsigned dst_stride,
                                  unsigned width_bytes, unsigned height)
{
  int ret;
  if (!g_initialized || !src || !dst || !height || height > 65535u ||
      !width_bytes || (width_bytes & 1u) || width_bytes > 32766u ||
      (src_stride & 1u) || (dst_stride & 1u) ||
      src_stride < width_bytes || dst_stride < width_bytes ||
      (((uintptr_t)src | (uintptr_t)dst) & 1u))
    return -EINVAL;
  ret = nxmutex_lock(&g_lock);
  if (ret < 0) return ret;
  putreg32((uint32_t)(uintptr_t)src, STM32_DMA2D_FGMAR);
  putreg32((uint32_t)(uintptr_t)dst, STM32_DMA2D_OMAR);
  putreg32((src_stride - width_bytes) / 2u, STM32_DMA2D_FGOR);
  putreg32((dst_stride - width_bytes) / 2u, STM32_DMA2D_OOR);
  putreg32(DMA2D_XGPFCCR_CM(DMA2D_PF_RGB565), STM32_DMA2D_FGPFCCR);
  putreg32(DMA2D_OPFCCR_CM(DMA2D_PF_RGB565), STM32_DMA2D_OPFCCR);
  putreg32(DMA2D_NLR_PL(width_bytes / 2u) | DMA2D_NLR_NL(height),
           STM32_DMA2D_NLR);
  stm32_dma2d_control(STM32_DMA2D_CR_MODE_BLIT,
                       STM32_DMA2D_CR_MODE_CLEAR);
  ret = stm32_dma2d_start();
  nxmutex_unlock(&g_lock);
  return ret;
}
