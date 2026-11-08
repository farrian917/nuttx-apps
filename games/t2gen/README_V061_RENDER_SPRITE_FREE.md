# T2GEN V0.61 — sprite-free scanline fast path

Based on V0.53 (four-pixel background compositor), not V0.59 CPU changes.

Changes in src/t2gen_render.c:
- Remove duplicate 320-byte memset of each sprite layer inside sprite_scanline; the caller already clears the active src_w bytes.
- Do not invoke sprite_scanline when no sprite intersects the scanline.
- Pass the existing visible-sprite count into the fused background compositor as a boolean. When zero, skip the per-span sprite-presence scan entirely and use the existing four-pixel sprite-free mixer.
- Sprite-containing scanlines use the exact previous composition path. No palette, priority, DMA2D or framebuffer changes.

Measure emulated FPS, AVG_US background/sprites/render, CACHE_DMA, and visual correctness. First compare against V0.53 on the same 300-frame windows. Target build and hardware run not verified.
