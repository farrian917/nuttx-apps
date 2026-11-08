# T2GEN V0.72: cached tile-row metadata (experimental)

Based on V0.64, not V0.71. Enable `CONFIG_GAMES_T2GEN_V072_ROW_METADATA=y`.

Each decoded tile is classified once per cache refill: eight-bit all-zero and all-opaque row masks, stored in regular RAM. The compositor uses the all-zero masks instead of repeated 32-bit row reads, and counts opaque-front opportunities but deliberately retains V0.64 pixel mixing. Cache invalidation uses the existing `tile_version` / `tile_reset_serial` mechanism. Sprite spans and uncached fallback are unchanged.

Diagnostics every 300 emulated frames: `T2GEN V0.72 ROW_META: frame=... both_zero=... nonzero=... opaque_front=... decodes=...`. Counters refer to processed sprite-free spans; opaque_front counts candidate spans, not executed opaque fast paths.

Test both enabled and disabled with identical paired-sync and other options. Inspect rendering visually. Metadata may regress speed in scenes with many tile updates. No target build or hardware validation performed.
