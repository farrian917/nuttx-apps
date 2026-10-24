T2GEN V9.8.2 diagnostic build

Changes:
- Render failure no longer permanently disables future frames.
- First five render attempts print diagnostic information.
- Framebuffer setup reports address, stride, DMA state.
- Sprite scanline buffers explicitly initialized.
- Default T2GEN stack raised to 16384 bytes (existing .config setting overrides default).
- Tile cache, Xbox controller, DMA2D and framebuffer memory layout retained.

IMPORTANT: In existing NuttX .config, explicitly set CONFIG_GAMES_T2GEN_STACKSIZE=16384; Kconfig default does not override existing values.

Replace apps/games/t2gen with the t2gen directory from this archive.
No ARM cross-build was performed here.
