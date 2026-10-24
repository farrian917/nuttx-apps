# NX2D v6 performance build

Based on confirmed-working NX2D v5. Physics, enemy AI, Xbox and sprites unchanged.

- Horizontal source lookup calculated once at video startup.
- Only 224 logical scanlines are horizontally expanded per frame; repeated destination rows use memcpy.
- Timing (CLOCK_MONOTONIC) reported to NSH every 120 frames: game logic, compose, scale, total work, and over-budget frame count.
- The existing 60 Hz pacing remains unchanged.

**DMA2D note:** STM32H743 DMA2D has no arbitrary nearest-neighbor image scaling mode. No DMA2D acceleration is claimed or enabled in this build. Benchmark CPU scaling first. DMA2D can later be tested for fills and copies via a board-specific integration, but it cannot replace the scaler directly.

**Coherency:** LTDC framebuffer must be mapped non-cacheable or explicitly cache-cleaned using the board's existing memory configuration. This package does not change MPU or double-buffering.

**Run:** `nx2d /dev/fb0 /dev/xboxa`. Copy the existing `.nx2s` assets as before. Send back NX2D PERF log lines for optimization decisions.
