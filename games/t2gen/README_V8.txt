T2GEN V8 - STATIC PLANE SNAPSHOT (EXPERIMENTAL)

Based on the V7 complete project. Preserves V7 bounded 68000 execution
and the existing approximate DMA and scanline model.

After the CPU run, t2gen /mnt/t2.gen /dev/fb0 writes a 640x448 centered
2x-scale static diagnostic snapshot to a 1024x600 8-bit LTDC framebuffer.
It programs palette indices 0..63 with FBIOPUT_CMAP using Genesis CRAM.

Known limitations:
- Snapshot only, no real-time emulation, no sprites, no window, no scroll,
  no per-pixel priority, no 256-pixel mode, no PAL resolution.
- DMA and VDP status handling are preliminary. The output may be garbled.
- This modifies the framebuffer and LTDC CLUT. Reboot or reinitialize the
  display driver to restore any previous display palette.
- The LTDC driver must support FBIOPUT_CMAP for L8; failure is reported.
- STM32 cache clean uses up_clean_dcache if CONFIG_ARMV7M_DCACHE is enabled.
- This archive was not compiled against the user's NuttX checkout.

Install:
  cd ~/workspace/nutt_last/apps/games
  mv t2gen t2gen_v7_backup
  unzip ~/Downloads/t2gen_v8_full_project.zip
  cd ~/workspace/nutt_last/nuttx
  make -j

Run:
  nsh> t2gen /mnt/t2.gen /dev/fb0
