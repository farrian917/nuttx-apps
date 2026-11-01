# T2GEN V0.96.1 — full repaired source

Fixes the invalid pointer shift and wrong `native_bus_write8` calls in `native_bus_read16()` introduced by V0.96. I/O word reads now call `genesis_io_read16()`. Also routes word writes to Genesis I/O registers through two ordered byte writes, so I/O word accesses are supported. Existing offline AOT and IRQ6 code is retained.

Build on target:
`python3 ../apps/games/t2gen/tools/generate_cfg_aot.py ../apps/games/t2gen/tools/t2.gen && make -j`

The generated AOT host syntax check passed. STM32 cross-compilation has not been run here.
