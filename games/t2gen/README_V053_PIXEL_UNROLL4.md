# T2GEN V0.53: four-pixel unrolled sprite-free span compositor

Base: V0.48c.1 stable single-buffer LTDC release.

Only the cached, sprite-free fused compositor has changed. Two priority
variants (Plane A front, Plane B front) process four consecutive pixels
per loop iteration and handle a 1-3 pixel tail. The original demand-driven
rear-plane read, palette selection, backdrop, pixel accounting and sprite
fallback are preserved. No driver, cache, DMA2D, 68000 or ROM changes.

This is an untested performance experiment. Measure FPS and AVG_US background
against V0.48c.1 and visually verify the display. No performance gain is
claimed until measured on hardware.
