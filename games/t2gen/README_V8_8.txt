T2GEN V8.8 — Genesis sprite/scroll/priority renderer test

Based on V8.7. Added H32/H40 width, per-plane horizontal and vertical scroll, sprite attribute table linked list, sprite flips, column-major pattern layout, low/high sprite priority, and diagnostic sprite pixel counts. Retains 60M-cycle run, VBlank framebuffer updates and previous Musashi/VDP diagnostics.

Known limitations: no window plane, shadow/highlight, pixel-accurate sprite collision/overflow, controller/Z80/audio, or real-time pacing. H-scroll mode 1 approximated. Render order is approximate for some equal-priority sprite/plane overlaps. No target compile verification.

Build as existing NuttX apps/games/t2gen; run: t2gen /mnt/t2.gen /dev/fb0
