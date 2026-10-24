# NX2D integrated tilemap build
This is the supplied nx2d_new tree with tilemap drawing and collision integrated.
- Logical screen 320x224; unchanged fullscreen 1024x600 L8 scaling.
- 80x14 tiles of 16x16 pixels; 1280x224 world.
- Ground on bottom two tile rows and five elevated platforms.
- Xbox adapter unchanged, using /dev/xboxa by default.
- Build from ~/workspace/nutt_last/nuttx with make -j.
- Run: nx2d /dev/fb0 /dev/xboxa
- No device hardware or NuttX cross-build was available here for testing.
