# T2GEN V1.05 — Native ADDQ.B Dn

Adds general ADDQ.B #1..8,Dn AOT decoding and generation, including ROM opcode 0x5401 at 0x00E1F2. Preserves upper 24 bits of Dn; calculates 68000 X/N/Z/V/C flags; adds 0x00E1F2 to dynamic AOT entry points. Regenerates src/t2gen_aot_cfg.inc. No runtime 68k interpreter or Musashi.

Build:

    cd ~/workspace/nutt_last/nuttx
    python3 ../apps/games/t2gen/tools/generate_cfg_aot.py ../apps/games/t2gen/tools/t2.gen
    make -j

Run: t2gen /mnt/t2.gen /dev/fb0

Host AOT syntax check completed; STM32H743 execution remains untested. The next unsupported instruction may stop execution; capture UART AOT_STOP and TRACE16.
