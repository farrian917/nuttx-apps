# T2GEN V0.63 — zero-tile-row background span experiment

Based on V0.62. In the cached fused full-scroll background compositor,
when a span has no sprite pixels, test both decoded eight-pixel tile rows.
If both are entirely transparent, emit the backdrop palette index using
`memset` and update the nonzero-pixel diagnostic in one operation.

This is deliberately a small, reversible experiment. Tile index zero is
not assumed to be transparent. All 8 pixels of both rows are checked,
regardless of flip or priority. Other paths are unchanged.

This may improve blank-heavy scenes but may regress scenes with complex
backgrounds due to the extra row checks. Benchmark against V0.62 across
6,000 emulated frames; compare AVG_US background, render and emulated FPS.

No hardware compile or runtime validation has been performed.
