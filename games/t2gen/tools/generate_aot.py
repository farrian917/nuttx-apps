#!/usr/bin/env python3
"""Generate a ROM-specific, statically compiled TST.W block at 0x208.
This is an intentionally narrow AOT generator, not a complete translator.
"""
import argparse
from pathlib import Path

parser = argparse.ArgumentParser()
parser.add_argument("rom", type=Path, help="Exact unmodified Genesis ROM")
parser.add_argument("--output", type=Path, default=Path(__file__).resolve().parents[1] /
                    "src/t2gen_aot_generated.inc")
args = parser.parse_args()
if args.output.exists() and "t2gen_aot_020e" in args.output.read_text():
    parser.error("V0.48 includes multiple generated blocks; this V0.46-era generator would overwrite them. Do not rerun it.")
data = args.rom.read_bytes()
if len(data) < 0x20e:
    parser.error("ROM too short for instruction at 0x208")
if data[0x208:0x20a] != bytes.fromhex("4a79"):
    parser.error(f"expected TST.W abs.l at 0x208, got {data[0x208:0x20a].hex()}")
addr = int.from_bytes(data[0x20a:0x20e], "big")
if addr & 1:
    parser.error(f"odd address 0x{addr:08x} cannot be accessed as 68000 word")
if addr > 0xffffff:
    parser.error(f"out-of-range 68000 address 0x{addr:08x}")
code = r"""/* Generated from ROM: TST.W ($ADDR).L at 0x000208.
 * Generated native code; no runtime opcode dispatch or interpretation.
 */
static int t2gen_aot_0208(struct t2cpu *c, const struct t2bus *b)
{
  const uint32_t addr = 0xADDRu;
  uint16_t value;
  if (!match16(b, 0x208u, 0x4a79u) ||
      !match32(b, 0x20au, 0xADDRu))
    {
      printf("T2GEN V0.47 AOT_0208: ROM signature mismatch\n");
      return -1;
    }
  if (native_bus_read16(b, addr, &value) != 0)
    {
      printf("T2GEN V0.47 AOT_0208: unsupported read addr=%06lx\\n",
             (unsigned long)addr);
      return -3;
    }
  c->sr = (uint16_t)((c->sr & 0xfff0u) |
                     ((value & 0x8000u) ? 8u : 0u) |
                     ((value == 0u) ? 4u : 0u));
  c->cycles += 16u; /* TST.W abs.l on 68000 */
  c->pc = 0x20eu;
  printf("T2GEN V0.47 AOT_0208: TST.W addr=%06lx value=%04x sr=%04x next=%06lx\n",
         (unsigned long)addr, value, c->sr, (unsigned long)c->pc);
  return 0;
}
"""
code = code.replace("ADDR", f"{addr:08x}")
args.output.parent.mkdir(parents=True, exist_ok=True)
args.output.write_text(code)
print(f"Generated {args.output} for TST.W at 0x208, operand 0x{addr:06x}")
