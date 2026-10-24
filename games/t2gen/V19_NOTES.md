# T2GEN V19 - lower-overhead plane and priority composition

Based on V18 linkfix, retaining its stage profiler and all other functionality.

Changes:
- Replace six-flag priority-mask/LUT and temporary 7-element layer array per pixel with explicit priority-order selection (high sprite, high A, high B, low sprite, low A, low B, backdrop).
- Hoist plane name-table base out of background tile span loop; use direct name-table indexing.
- Render only the active window x interval, directly into plane A buffers, eliminating full-line temporary window buffers and copies.
- Retain V18 profiling as V19 STAGES and V19 AVG_US.

This is an experimental optimization, not yet cross-compiled or hardware validated. Compare V18 and V19 stage timings. If performance regresses, revert to V18.
