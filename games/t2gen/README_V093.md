# V0.93: IRQ6 framework and native RTE

Nominal NTSC VBlank timing, IRQ6 entry using 68000 six-byte stack frame,
SR interrupt masking, IRQ6 vector lookup, and generated native RTE.

LIMITATIONS: the ROM IRQ6 handler at 0x004D2C begins with MOVEM.L and
JSR (A0); coverage of this handler and dynamic calls is NOT complete.
The emulator will stop at untranslated handler code instead of faking a
VBlank completion. This is an incremental implementation, not playable.
