T2GEN V9.7 — Xbox gamepad from NX2D V19
========================================
Based on V9.6 with DMA2D driver helper preserved. No changes to framebuffer reservation.

Uses <nuttx/input/xbox-controller.h>, reads struct xbox_controller_buttonstate_s
from /dev/xboxa nonblocking once per emulated frame. EAGAIN retains prior state.

Xbox D-pad/left stick => Genesis directions
Xbox A => Genesis A, Xbox B => Genesis B, Xbox X => Genesis C
Xbox Start => Genesis START

Genesis port1 active-low TH multiplexing is implemented in t2gen_musashi.c.
Automatic START pulses from V9.2 are removed. The Xbox keyboard device
/dev/xboxkbda is not used by the emulator.

IMPORTANT: The NX2D V19 source confirms pad.a/pad.b/pad.x, dpad and stick
fields, but does not use pad.start or stick_left_y. Verify those names and
vertical-axis sign in your own xbox-controller.h. If your header uses another
name for Start, change 'pad.start' accordingly. No hardware build was run.

Install into apps/games/t2gen, keep the V9.5 DMA2D driver helper, rebuild.
Run: t2gen /mnt/t2.gen /dev/fb0 0
