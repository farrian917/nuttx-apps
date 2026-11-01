# T2GEN V0.75 — batch CLR/TST AOT continuation

ROM-specific offline native AOT. Added CLR.B/W/L absolute-long and Dn, TST.B/W/L absolute-long and Dn. Normal game launch skips repeated SDRAM pattern tests; `t2gen --sdram-test` explicitly runs them. No runtime 68000 interpreter. VBlank, DMA and Z80 execution are not implemented by this patch.

Generate: `python3 tools/generate_cfg_aot.py tools/t2.gen` then build using NuttX `make -j`.
