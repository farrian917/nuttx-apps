# T2GEN V1.01 — FF0230 initialization diagnostics

Based on V1.00. This is a diagnostic build, not a speculative state fix.

Added generated native AOT traces at 0093C6 (MOVE.L (A0)+,FF0230), 0093CC, 0093D6, 0093E0, 0093EA, 0093F2 and 009400. The source pointer and longword at 0093C6 are printed before the instruction. `native_bus_write32` reports writes to FF0230, FF0234 and FF0238.

Regenerate: `python3 ../apps/games/t2gen/tools/generate_cfg_aot.py ../apps/games/t2gen/tools/t2.gen` then `make -j`.

Send all `T2GEN V1.01` lines and the first AOT stop. Host generated-C syntax test passed; embedded compilation and execution have not been verified.
