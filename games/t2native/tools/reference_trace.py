#!/usr/bin/env python3
"""Extract V0.3 frame reference traces from a NuttX serial log."""
import argparse
import csv
import re
from pathlib import Path

PATTERN = re.compile(r"T2GEN V0\\.3 REF: (.+)")
FIELDS = ("frame", "cycles", "PC", "SR", "D0", "D1", "A0", "A7",
          "RAM_FNV", "VDP_WR", "PAD")

def parse(text):
    for line in text.splitlines():
        m = PATTERN.search(line)
        if not m:
            continue
        fields = dict(re.findall(r"([A-Za-z0-9_]+)=([0-9a-fA-F]+)", m.group(1)))
        if all(key in fields for key in FIELDS):
            yield {key: fields[key] for key in FIELDS}

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("serial_log", type=Path)
    ap.add_argument("csv_out", type=Path)
    args = ap.parse_args()
    rows = list(parse(args.serial_log.read_text(errors="replace")))
    with args.csv_out.open("w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=FIELDS)
        writer.writeheader()
        writer.writerows(rows)
    print(f"Extracted {len(rows)} frame snapshots into {args.csv_out}")

if __name__ == "__main__":
    main()
