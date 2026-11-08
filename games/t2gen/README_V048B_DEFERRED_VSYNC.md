# T2GEN V0.48b — deferred VSYNC experiment

Based on V0.48a.1 and V0.46 demand-driven rear-plane renderer.

The frame presentation ioctl (FBIOPAN_DISPLAY) now runs at the end of the render,
while FBIO_WAITFORVSYNC is deferred until the beginning of the next render.
This permits emulation to proceed between pan submission and synchronization.
The previous front buffer is never reused before a successful wait.

**Caution:** In the supplied STM32H7 LTDC driver, FBIO_WAITFORVSYNC calls
stm32_ltdc_reload(LTDC_SRCR_VBR, true), so it triggers another VBlank reload.
The experiment may not reduce the total VSYNC waiting time. New diagnostic
`T2GEN V0.48b VSYNC` lines report average pan/wait time and maximum wait.

No asynchronous DMA2D strip pipeline is included yet. No kernel driver
changes are required for this experiment. This has not been built against
or tested on the target board.

Required configuration:
CONFIG_STM32_DMA2D_FB_BASE=0xc1a00000
CONFIG_STM32_DMA2D_FB_SIZE=2097152
CONFIG_STM32_LTDC_FB_BASE=0xc1c00000
CONFIG_STM32_LTDC_FB_SIZE=2097152
CONFIG_STM32_LTDC_FB_DOUBLE_BUFFER=y
CONFIG_FB_SYNC=y
