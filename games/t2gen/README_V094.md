# V0.94: IRQ6 AOT entry and indirect callback diagnostic

Added offline AOT roots 0x004D2C (IRQ6 entry) and 0x004D38 (return path), plus
JSR (An) generation. The existing MOVEM.L save/restore and RTE generator paths
now compile for the real handler. At runtime, JSR (A0) pushes its return address
and dispatches to the exact pretranslated address in A0; it never interprets
opcodes. Logs `IRQ6_CALLBACK` and `CALLBACK_WRITE` for RAM pointer FF0138.

**Limitation:** The callback target is stored in RAM and is not statically known
from the IRQ handler. If not among existing AOT roots, the dispatcher will
report untranslated PC. Use the observed target to add a new --extra-entry and
extend coverage; do not bypass the callback or clear FF0218 artificially.

No STM32 hardware build was performed here.
