# T2GEN V0.48a: LTDC double-buffer integration (stage 1)

Based on benchmarked V0.46 demand-driven rear plane. This is **not** the full
asynchronous SRAM strip ping-pong implementation. It preserves the existing
synchronous DMA2D 320x224 staging path and adds back-buffer presentation.
No hardware build or hardware test was performed by the author.

## NuttX configuration (make menuconfig)

    CONFIG_STM32_DMA2D_FB_BASE=0xc1a00000
    CONFIG_STM32_DMA2D_FB_SIZE=2097152
    CONFIG_STM32_LTDC_FB_BASE=0xc1c00000
    CONFIG_STM32_LTDC_FB_SIZE=2097152
    CONFIG_STM32_LTDC_FB_DOUBLE_BUFFER=y
    CONFIG_FB_SYNC=y

The board.h code reserves 26 MiB SDRAM heap, leaving 0xc1a00000..0xc1ffffff
outside the heap. This layout assumes no other custom fixed allocation there.

## Implementation

On init, FBIOGET_PLANEINFO provides the first framebuffer pointer and total
framebuffer length. If two 1024x600 L8 buffers are present, T2GEN clears both,
then renders to the inactive buffer. Existing synchronous DMA2D helper copies
320x224 into the selected buffer. FBIOPAN_DISPLAY requests VBlank swap, and
FBIO_WAITFORVSYNC waits before the previous front buffer is reused.

The current LTDC driver uses an unvalidated FBIOPAN_DISPLAY address. T2GEN
passes only the two buffers returned from the driver's framebuffer region.

## Installation

    cd ~/workspace/nutt_last/apps/games
    mv t2gen t2gen_before_v048a
    unzip /path/to/T2GEN_V048A_LTDC_DOUBLEBUFFER_FULL_SOURCE.zip
    cd ~/workspace/nutt_last/nuttx
    make menuconfig
    make -j$(nproc)

Before flashing, verify the active .config contains the six settings above.
The previous stm32_dma2d_t2gen_copy_l8x2 helper must remain installed in the
NuttX driver. Do not apply the included helper patch a second time.

## Caveats

- This is a preliminary, untested double-buffer release, not final V0.48.
- FBIO_WAITFORVSYNC can cap presentation at display refresh and affect FPS.
- No async DMA2D API, SRAM ping-pong, or strip pipeline is implemented yet.
- If FBIOPAN_DISPLAY or FBIO_WAITFORVSYNC fails, rendering returns an error.
- A live palette change still updates the shared LTDC CLUT, not per-buffer CLUT.
- Existing full-frame staging memory remains allocated.
