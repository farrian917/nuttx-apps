# T2GEN V0.44: sprite-empty span fast path

Based on V0.43.1 native centered L8 renderer. In the fused full-scroll compositor, check each 1..8 pixel tile span for the absence of both sprite priority layers. When no sprites occur, use a two-plane priority-aware fast loop instead of loading and mixing sprite pixels for each output pixel. Preserve exact transparent-index-zero behavior and A/B tile priorities. Sprite-bearing spans continue through the existing four-way priority-specialized compositor. The uncached and window/column-scroll fallbacks are unchanged.

Fix the profiling bug in V0.43.1: background timing was skipped whenever DMA2D was enabled due to a dangling conditional. The fused path is now included in background_ms and should no longer inflate unaccounted_ms.

This is an experimental CPU optimization; faster FPS is not guaranteed. Test with render divider 3 first, then divider 1. No STM32H743 cross-build or board execution performed.
