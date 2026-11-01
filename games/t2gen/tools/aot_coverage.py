#!/usr/bin/env python3
"""Audit the ROM-specific native AOT CFG report; no runtime interpretation."""
import argparse, collections, json
from pathlib import Path

p=argparse.ArgumentParser()
p.add_argument('report',type=Path,nargs='?',default=Path(__file__).with_name('aot_cfg_report.json'))
p.add_argument('--json',type=Path,help='write compact machine-readable summary')
a=p.parse_args()
r=json.loads(a.report.read_text())
blocks=r['blocks']
unsupported=r.get('unsupported_context',[])
by_opcode=collections.Counter(x['opcode'] for x in unsupported)
other=[(pc,b['stop_reason']) for pc,b in blocks.items() if b['stop_reason'] and not b['stop_reason'].startswith('unsupported')]
indirect=[(pc,b['stop_reason']) for pc,b in blocks.items() if b['stop_reason'] and ('indirect' in b['stop_reason'].lower() or 'dynamic' in b['stop_reason'].lower())]
summary={'rom_crc32':r['rom_crc32'],'translated_blocks':len(blocks),'translated_instructions':sum(b['instructions'] for b in blocks.values()),'unsupported_sites':len(unsupported),'unsupported_opcode_values':dict(sorted(by_opcode.items())),'other_stop_reasons':other,'unresolved_indirect':indirect,'rom_coverage_complete':False}
print('T2GEN OFFLINE AOT COVERAGE (reachable CFG only)')
for k in ('rom_crc32','translated_blocks','translated_instructions','unsupported_sites'):
 print(f'{k:27s} {summary[k]}')
print('Unsupported opcode sites:')
for x in sorted(unsupported,key=lambda x:int(x['pc'],16)):
 print(f"  {x['pc']}  {x['opcode']}  {x['rom_bytes'][:16]}")
if other:
 print('Other CFG stops:')
 for pc,why in other:print(' ',pc,why)
print('WARNING: indirect control flow and data/code ambiguity prevent proof of full ROM coverage.')
if a.json:a.json.write_text(json.dumps(summary,indent=2)+'\n')
