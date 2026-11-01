# T2GEN V0.43.11 — native-engine stack reduction

Based on the uploaded T2GEN V0.43.10 staged-AXI-read source bundle.

## Change in this version

- `t2gen/src/t2gen_native43.c`: moved the 64 KiB emulated 68000 RAM out of
  `struct bus43`'s automatic storage and into a `calloc()` allocation.
- Added `<stdlib.h>` for `calloc()` and `free()`.
- Added allocation-failure handling.
- All normal and early-return paths after successful allocation release the
  emulated RAM through one cleanup path.
- Updated native diagnostic messages to identify V0.43.11.

This reduces the native probe's stack requirement by approximately 64 KiB.
It is particularly important with `CONFIG_GAMES_T2GEN_STACKSIZE=32768`.

## Preserved from the uploaded V0.43.10 bundle

The existing staged AXI-SRAM ROM-read diagnostic, SDRAM diagnostic, Musashi
sources/adapter, native engine, headers, Kconfig, Makefiles, patch material,
and historical notes are retained. No unrelated files were intentionally
removed.

## Important unresolved issue

This change addresses the large automatic stack allocation in the native
probe. It does **not** establish the cause of the earlier imprecise BusFault
reported during the staged SD read, before native execution was entered.
That SDMMC/ROM-read fault remains a separate investigation.

## Integration

Copy the bundled `t2gen` directory into `apps/games/t2gen` in the NuttX apps
tree, replacing the previous T2GEN directory after keeping a backup.

Then rebuild from the NuttX tree:

```sh
make -C ../apps/games/t2gen clean
make -j
```

Flash and test:

```text
nsh> t2gen /mnt/t2.gen none
```

Expected native-probe diagnostics include `T2GEN V0.43.11 NATIVE_ONLY`,
followed by either the isolated block-test messages or
`ROM block signature unavailable`, and finally
`emulated RAM released`.

No target hardware build or runtime validation is claimed by this archive.
