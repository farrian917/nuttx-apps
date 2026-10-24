T2GEN restored full source tree from supplied t2gen(1).rar, with V6 diagnostic files applied.
Install: extract this ZIP into ~/workspace/nutt_last/apps/games/ (creates t2gen/).
Build: cd ~/workspace/nutt_last/nuttx && make -j
Run: t2gen /mnt/t2.gen /dev/fb0
V6 is a bounded CPU and preliminary VDP DMA diagnostic. No rendering, VDP timing/interrupts, Z80 or audio.
