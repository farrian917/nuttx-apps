# T2GEN V0.46 — demand-driven rear-plane fetch (experimental)

Based on V0.44, not V0.45. In the sprite-empty cached scanline path,
read and map the frontmost background pixel first; read the rear plane
only when the front pixel's decoded 4-bit color is transparent (zero).
No per-span opaque scan or additional tile metadata. Existing sprite,
uncached, and non-full-scroll paths remain unchanged.

This is an experiment: branching may outweigh saved SRAM2 reads depending
on scene opacity and compiler output. Compare with V0.44 using identical
render divider=3 and 300-frame windows. Hardware and cross-compilation
have not been validated here.
