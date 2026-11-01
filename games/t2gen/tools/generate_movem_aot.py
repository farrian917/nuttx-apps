#!/usr/bin/env python3
"""ROM-specific AOT for consecutive MOVEM (An)+ -> registers. No runtime decode."""
from pathlib import Path
import argparse, zlib
p=argparse.ArgumentParser()
p.add_argument('rom',type=Path)
p.add_argument('--output',type=Path,default=Path(__file__).resolve().parents[1]/'src/t2gen_aot_movem.inc')
a=p.parse_args()
b=a.rom.read_bytes()
if len(b)<0x21c: p.error('ROM too short')
if zlib.crc32(b)!=0x2f75e896:p.error('expected exact T2 ROM CRC32 2f75e896')
code=['/* Generated offline for ROM CRC32 2F75E896. Native operations only. */']
for pc in (0x214,0x218):
    op=int.from_bytes(b[pc:pc+2],'big'); mask=int.from_bytes(b[pc+2:pc+4],'big')
    if op&0xfbff != 0x4898: # MOVEM reg-to-memory? use explicit expected below
        pass
    expected={0x214:(0x4c9d,0x00e0),0x218:(0x4cdd,0x1f00)}[pc]
    if (op,mask)!=expected:p.error(f'ROM opcode mismatch at {pc:06x}: {op:04x} {mask:04x}')
    size=4 if op&0x40 else 2
    reglist=[r for r in range(16) if mask&(1<<r)]
    lines=[f'static int t2gen_aot_{pc:04x}(struct t2cpu *c, const struct t2bus *b)', '{', '  uint32_t v;',f'  uint32_t addr = c->a[5];',f'  if (!match16(b, 0x{pc:x}u, 0x{op:04x}u) || !match16(b, 0x{pc+2:x}u, 0x{mask:04x}u)) return -1;']
    # MOVEM postincrement: source address register updated after all loads
    for r in reglist:
        lines.append(f'  if (native_bus_read{size*8}(b, addr, &v) != 0) return -3;') if size==4 else lines.append('  { uint16_t w; if (native_bus_read16(b, addr, &w) != 0) return -3; v = (uint32_t)(int32_t)(int16_t)w; }')
        lines.append(f'  c->{"d" if r<8 else "a"}[{r if r<8 else r-8}] = v;')
        lines.append(f'  addr += {size}u;')
    lines += ['  c->a[5] = addr;',f'  c->pc = 0x{pc+4:06x}u;',f'  c->cycles += {12+4*len(reglist) if size==2 else 12+8*len(reglist)}u;',f'  printf("T2GEN V0.49 AOT_{pc:04X}: MOVEM.{"L" if size==4 else "W"} regs={len(reglist)} A5=%06lx next=%06lx\\n", (unsigned long)c->a[5], (unsigned long)c->pc);','  return 0;','}']
    code.extend(lines)
a.output.write_text('\n'.join(code)+'\n')
print(f'Generated {a.output}; {len(code)} lines; ROM CRC32={zlib.crc32(b):08x}')
