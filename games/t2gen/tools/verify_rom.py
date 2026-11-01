#!/usr/bin/env python3
import sys, zlib, hashlib
from pathlib import Path
p=Path(sys.argv[1]); d=p.read_bytes()
print('size:',len(d),'CRC32:',f'{zlib.crc32(d):08x}','SHA256:',hashlib.sha256(d).hexdigest())
assert len(d)==1048576 and zlib.crc32(d)==0x2f75e896, 'wrong ROM'
assert d[0x200:0x214].hex()=='4ab900a1000866064a7900a1000c667c4bfa007c', 'startup code mismatch'
print('T2GEN V0.48 ROM signature: PASS')
