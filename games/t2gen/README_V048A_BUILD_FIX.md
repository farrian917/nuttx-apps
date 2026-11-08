# V0.48a build fix

Replaced incorrect `FBIO_WAITFORSYNC` with NuttX ioctl `FBIO_WAITFORVSYNC` in `src/t2gen_render.c`. No rendering algorithm changes. Hardware build and runtime not verified.
