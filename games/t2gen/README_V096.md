# T2GEN V0.96: Mega Drive controller I/O bus

Based on V0.95. Handle writes to 0xA10003..0xA1001F on the odd byte lane, especially 0xA10009=0x40 (controller port A direction register). State is per-emulation-run and readable. Even-lane writes are ignored. Byte/word reads use current register state; word writes are split into byte lanes. Controller inputs are provisionally unpressed and pulled high; no six-button protocol or physical gamepad. UART logs first 24 IO writes.

This removes the V0.95 bus-write error at 0xA10009 but does not guarantee the next callback/IRQ6 path is fully translated. Offline AOT is unchanged; no interpreter.

Build as before; run `t2gen /mnt/t2.gen /dev/fb0`.
