# NX2D v20 — framebuffer writer A/B experiment

The existing `ratio` implementation is preserved as baseline.
The new `ratio64` scaler uses the same exact 320->1024 pixel expansion,
but attempts aligned 64-bit stores to the L8 framebuffer, falling back
to the existing 32-bit burst writer if the destination is unaligned.

Run both at the same scene position and without Xbox debug console traffic:

    nx2d /dev/fb0 /dev/xboxa ratio spans
    nx2d /dev/fb0 /dev/xboxa ratio64 spans

Compare `NX2D V20 VIDEO AVG ... fbwrite=...` and `DWT AVG ... render=...`.
Divide DWT cycles by 480 for microseconds at 480 MHz.

WARNING: 64-bit ARM stores are not guaranteed to outperform 32-bit stores
on the STM32H743's external FMC SDRAM, and C compiler codegen may differ.
This test does not alter MPU/cache attributes and cannot validate whether
LTDC-visible memory is cache coherent. Do not change cache attributes
without a separate coherency plan. `ratio64` is experimental; if display
artifacts appear, return to `ratio` immediately.

The target firmware has not been cross-compiled or hardware-tested here.
