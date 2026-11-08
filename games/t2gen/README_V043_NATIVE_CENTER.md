# T2GEN V0.43: native-resolution centered renderer experiment

Based on V0.41 (not V0.42). Output is 256/320 x 224 centered in 1024 x 600 L8 framebuffer. No CPU horizontal/vertical pixel doubling; one DMA2D transfer per rendered frame. Preserve existing 8-bit palette and Genesis priority. The remainder of the framebuffer is not cleared on every frame; stale pixels outside the centered area may remain from prior applications.

Build using the existing NuttX project. Set CONFIG_GAMES_T2GEN_V040_RENDER_DIVIDER=1 for the 30 displayed FPS test.

Experimental and NOT cross-compiled on target. The framebuffer must be L8 and DMA2D helper must support even byte strides/widths. Compare FPS and V0.31 AVG_US against V0.41.
