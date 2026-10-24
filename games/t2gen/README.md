# T2GEN v4 — Musashi integration adapter (source scaffold)

**Not a complete emulator.** The external Musashi CPU core is not bundled.
The default configuration runs the proven v3 startup bus diagnostic.

To enable CPU execution:
1. Obtain upstream Musashi source and generated m68kops.c from its project.
2. Copy required files into src/musashi (see that directory's README).
3. Set CONFIG_GAMES_T2GEN_MUSASHI=y and rebuild NuttX.
4. Run `t2gen /mnt/t2.gen /dev/fb0`.

The adapter maps cartridge ROM, 64 KiB 68000 RAM, basic Genesis I/O and
VDP register access. VDP/Z80 timing, interrupts, graphics and sound are NOT
implemented. VDP write counts are diagnostic, not proof of successful boot.

Known limitations: incomplete Genesis I/O register semantics, simplistic
VDP status, no Z80, no interrupts, no cycle accuracy, no SRAM or mapper.
The Musashi code may require adjusting include paths or configuration
for your specific upstream revision. Do not run unbounded execution.
