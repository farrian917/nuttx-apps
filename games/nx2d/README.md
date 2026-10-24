# NX2D baseline for NuttX STM32H743

This is a first-stage *software-rendered* game engine skeleton, not yet a DMA2D backend or working Xbox USB host integration. It compiles against NuttX versions exposing the framebuffer ioctls, mmap, and POSIX clock_nanosleep; exact NuttX revision and board configuration may require adjustments.

## Installation
Copy this directory to `apps/games/nx2d`. Add `source "$(APPDIR)/games/nx2d/Kconfig"` to `apps/games/Kconfig` and `include $(APPDIR)/games/nx2d/Make.defs` to `apps/games/Make.defs` (or the corresponding existing conventions in your tree). Enable CONFIG_GAMES_NX2D=y, CONFIG_VIDEO_FB=y, CONFIG_FS_MMAP=y if required by your NuttX version, and ensure framebuffer mmap is implemented.

## Run
`nsh> nx2d /dev/fb0 /dev/xboxbuttons`

The input adapter expects an existing device that returns a **4-byte bitmask** in the order left/right/jump/quit; this is *not* a standard NuttX Xbox interface. Replace `nx2d_input.c` with an adapter to your USB host controller's real API. With no input argument, the demo draws but player stays still.

## Important limitations
- Framebuffer must be RGB565 with at least 320x224 pixels.
- mmap support varies by NuttX framebuffer driver. Adapt to board-specific framebuffer access if absent.
- LTDC framebuffer needs coherent cache policy (MPU noncacheable or explicit clean).
- DMA2D acceleration and off-screen double buffering are intentionally not yet implemented. A DMA2D backend needs verified STM32H7 DMA2D API and SDRAM address/cache configuration.
- No tile collision, sprites, audio, or assets yet.
- The sample uses `clock_nanosleep`; replace with a relative sleep if your NuttX configuration does not provide it.

## STM32H743 LTDC L8 variant
Requires CONFIG_STM32_LTDC_L1_L8=y and CONFIG_FB_CMAP=y.
The framebuffer is written as palette indices, and FBIOPUT_CMAP installs an RGB332-derived 256-color CLUT.
Run: nx2d /dev/fb0
The engine still renders a centered 320x224 viewport without scaling, and has no DMA2D acceleration yet.
IMPORTANT: Ensure LTDC framebuffer SDRAM is noncacheable or cleaned after CPU writes.
The game palette is not restored on exit.

## Flicker correction
The game now composes each 320x224 frame offscreen, clips all sprites to the viewport, then copies complete scanlines to the LTDC framebuffer. This is not true hardware double buffering; LTDC tearing and Cortex-M7 D-cache coherency still require board-specific work.
