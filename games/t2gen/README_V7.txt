T2GEN V7 experimental full project for STM32H743 / NuttX 13.0.1-RC1

Based on the recovered V6 project. Adds a coarse 262-line NTSC scanline clock, VBlank status bit 3, and level-6 IRQ request when VDP register 1 bit 5 enables V interrupt. Runs a bounded ~1.2 million CPU cycles, prints CPU and VDP counters, and records repeated PCs.

LIMITATIONS: scanline clock is approximate and applied at CPU slice boundaries; interrupt line is deasserted after one simulated scanline rather than on real interrupt acknowledgement. No HBlank, H interrupts, accurate DMA stalls, Z80, PSG, YM2612 or video rendering. VDP 8-bit port semantics and VDP mirrors remain incomplete. For diagnosis only.

Install: extract t2gen/ into ~/workspace/nutt_last/apps/games/t2gen/ and build NuttX.
