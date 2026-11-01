# T2GEN V0.87 — AOT coverage audit + SUBI.W

This is an **incremental** update, **not** a complete MC68000 translator.

- Added correct 16-bit `SUBI.W #imm,Dn` handling, preserving upper Dn word and calculating N/Z/V/C/X.
- Added observed entry `0x009A80` and expanded the reachable path to `0x009A94`.
- Added `tools/aot_coverage.py` to report untranslated reachable opcodes without treating ROM data as executable code.
- Existing ROM-specific native C AOT design is preserved: no Musashi or runtime CPU interpreter.

Generate and audit:

```sh
python3 tools/generate_cfg_aot.py tools/t2.gen > /tmp/t2gen-aot-report.json
python3 tools/aot_coverage.py tools/aot_cfg_report.json --json tools/aot_coverage_summary.json
```

Current ROM CRC32: `2f75e896`. Current generator output: 191 blocks, 649 instructions, 16 distinct unsupported opcode values (17 unsupported sites). This is *not* complete ROM execution coverage. Additional MC68000 families, effective addressing, exception handling and indirect flow resolution remain necessary. Hardware test pending.
