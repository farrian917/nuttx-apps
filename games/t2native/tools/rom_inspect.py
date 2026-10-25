#!/usr/bin/env python3
"""ROM fingerprint and initial 68000 vector/candidate report; no emulator."""
import argparse
import hashlib
from pathlib import Path

def be16(b, o):
    return int.from_bytes(b[o:o+2], "big")

def be32(b, o):
    return int.from_bytes(b[o:o+4], "big")

def main():
    p = argparse.ArgumentParser()
    p.add_argument("rom", type=Path)
    args = p.parse_args()
    data = args.rom.read_bytes()
    if len(data) < 0x200 or len(data) % 2:
        raise SystemExit("Expected an even-sized raw Mega Drive ROM >= 512 bytes")
    checksum = sum(be16(data, o) for o in range(0x200, len(data), 2)) & 0xffff
    print("size:", len(data))
    print("sha256:", hashlib.sha256(data).hexdigest())
    print("system:", data[0x100:0x110].decode("ascii", "replace").strip())
    print("domestic:", data[0x120:0x150].decode("ascii", "replace").strip())
    print("international:", data[0x150:0x180].decode("ascii", "replace").strip())
    print("serial:", data[0x180:0x18e].decode("ascii", "replace").strip())
    print("SP:", f"{be32(data, 0):08x}", "PC:", f"{be32(data, 4):08x}")
    print("header checksum:", f"{be16(data, 0x18e):04x}",
          "computed:", f"{checksum:04x}",
          "match:", checksum == be16(data, 0x18e))
    for address in (0x200, 0x4ab0, 0xa12e, 0xa0e4):
        print(f"ROM[{address:06x}]:", data[address:address+24].hex(" "))
    print("Vectors (first 64, excluding SP):")
    for i in range(1, 64):
        address = be32(data, 4*i)
        if address:
            valid = address < len(data) and address % 2 == 0
            print(f"  {i:2d} -> {address:08x} {'ROM' if valid else 'outside-ROM'}")

if __name__ == "__main__":
    main()
