T2GEN V15: video compositor experiment, based on V14.

Changes:
- Main view uses a 64-entry priority-selection table preserving the original
  B-low, A-low, sprite-low, B-high, A-high, sprite-high draw order.
- Window active region is computed once per scanline, and unused window rows
  are not rasterized.
- Diagnostic views 1-5 retain the V14 priority implementation.
- V14 Musashi bus fast paths, CPU-only mode, DMA2D and Xbox preserved.

Benchmark both:
 t2gen /mnt/t2.gen none 0
 t2gen /mnt/t2.gen /dev/fb0 0

Experimental; not built or hardware tested. Compare final VIDEO PERF and FPS.
