#!/usr/bin/env python3
"""Syntax-check generated AOT C without NuttX headers; does not execute ROM."""
from pathlib import Path
import subprocess,tempfile
root=Path(__file__).resolve().parents[1]
source='''#include <stdint.h>\n#include <stdio.h>\nstruct t2cpu { uint32_t d[8],a[8],pc,usp; uint16_t sr; uint32_t cycles; };\nstruct t2bus {int dummy;};\nstatic int match16(const struct t2bus *b,uint32_t a,uint16_t v);\nstatic int match32(const struct t2bus *b,uint32_t a,uint32_t v);\nstatic int native_bus_read8(const struct t2bus *b,uint32_t a,uint8_t *v);\nstatic int native_bus_read16(const struct t2bus *b,uint32_t a,uint16_t *v);\nstatic int native_bus_read32(const struct t2bus *b,uint32_t a,uint32_t *v);\nstatic int native_bus_write8(struct t2bus *b,uint32_t a,uint8_t v);\nstatic int native_bus_write16(struct t2bus *b,uint32_t a,uint16_t v);\nstatic int native_bus_write32(struct t2bus *b,uint32_t a,uint32_t v);\n'''+(root/'src/t2gen_aot_cfg.inc').read_text()
with tempfile.TemporaryDirectory() as d:
 p=Path(d)/'check.c';p.write_text(source)
 r=subprocess.run(['gcc','-std=c11','-fsyntax-only','-Wno-unused-function',str(p)],capture_output=True,text=True)
 print(r.stdout+r.stderr)
 raise SystemExit(r.returncode)
