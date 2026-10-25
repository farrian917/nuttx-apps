# T2GEN V21: fixed-snapshot benchmark

Based on V20. Adds an optional deterministic renderer benchmark after the existing 300-million-cycle Musashi run.

Run `t2gen /mnt/t2.gen /dev/fb0 0 40` to render the final unchanged VDP state 40 times, after one excluded warm-up render. Look for `T2GEN V21 FIXED:`.

Compare V19/V20 fairly only after applying the same benchmark patch to each source version. This V21 package alone cannot provide an apples-to-apples V19 vs V20 comparison.

The test includes framebuffer writes and DMA2D. It does not advance the emulated CPU or change VRAM between repeats. Cache epochs still advance as in normal rendering. The gameplay run occurs before the fixed test and can affect thermal and clock conditions.

Existing `t2gen /mnt/t2.gen /dev/fb0 0` behavior remains unchanged. No cross-compile or hardware validation was performed.
