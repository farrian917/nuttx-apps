# T2GEN V0.99 — indexed pointer trace

Diagnostic-only update from V0.98. The offline AOT generator now emits instruction-boundary traces for indexed MOVE.L at 0x009436, indexed MOVEA.L at 0x009442, and indirect JSR at 0x009446. Traces show base, signed index, displacement, computed EA and loaded/stored result. No RAM execution support or pointer correction is attempted.

Build: python3 ../apps/games/t2gen/tools/generate_cfg_aot.py ../apps/games/t2gen/tools/t2.gen && make -j

Run: t2gen /mnt/t2.gen /dev/fb0

Look for T2GEN V0.99 IDX_MOVE, IDX_MOVE_RESULT, IDX_MOVEA, IDX_MOVEA_RESULT, JSR.

Host generated-C syntax checked; STM32 compilation and hardware execution not verified.
