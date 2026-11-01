#!/usr/bin/env python3
"""Conservative ROM-specific 68000 basic-block translator (small subset)."""
import argparse, json, zlib
from pathlib import Path
p=argparse.ArgumentParser()
p.add_argument('rom',type=Path)
p.add_argument('--entry',type=lambda x:int(x,0),default=0x21c)
p.add_argument('--limit',type=int,default=8192)
p.add_argument('--extra-entry',action='append',type=lambda x:int(x,0),default=[0x4a32,0xead4,0xaa0e,0xeb44,0xeb4e,0xeb6c,0xeb20,0xeb36,0xeb84,0x99bc,0x99fa,0x9a2a,0x9a46,0x9a80,0x4d2c,0x4d38,0x9b30,0xe1a0,0xe1f2,0xe1fc,0xe202,0xe22c,0xe05a,0xdf6e],help='Runtime-observed dynamic entry PC (repeatable); 0x4a32 seeded from V0.69 UART')
a=p.parse_args(); b=a.rom.read_bytes(); root=Path(__file__).resolve().parents[1]
def w(pc):
 if pc&1 or pc+2>len(b):raise ValueError('invalid ROM PC')
 return int.from_bytes(b[pc:pc+2],'big')
blocks={}; pending=[a.entry]+a.extra_entry; errors=[]
while pending and len(blocks)<a.limit:
 start=pending.pop(0)
 if start in blocks:continue
 if start&1 or start+2>len(b):errors.append({'pc':hex(start),'reason':'out of ROM'});continue
 pc=start; ops=[]; successors=[]; reason=None
 for _ in range(256):
  if pc+2>len(b):reason='out of ROM';break
  op=w(pc)
  if op==0x6a00: # BPL.W, signed 16-bit PC-relative displacement
   if pc+4>len(b):reason='truncated';break
   ext=w(pc+2);disp=ext-65536 if ext&0x8000 else ext
   target=(pc+2+disp)&0xffffff;nxt=pc+4
   ops.append(('bpl_w',pc,op,target,nxt,ext));successors=[target,nxt];pc=nxt;break
  elif op==0x4ef8: # JMP (xxx).W, sign-extended absolute short
   if pc+4>len(b):reason='truncated';break
   ext=w(pc+2);target=(ext-65536 if ext&0x8000 else ext)&0xffffff
   ops.append(('jmp_absw',pc,op,target,ext));successors=[target];pc+=4;break
  elif (op&0xfff8)==0x4e90: # JSR (An), runtime target must be pretranslated
   ops.append(('jsr_an',pc,op,op&7,pc+2));successors=[pc+2];pc+=2;break
  elif op==0x4eba: # JSR (d16,PC), 68000 PC base is extension word address
   if pc+4>len(b):reason='truncated';break
   ext=w(pc+2);disp=ext-65536 if ext&0x8000 else ext
   target=(pc+2+disp)&0xffffff;nxt=pc+4
   ops.append(('jsr_pcdisp',pc,op,target,nxt,ext));successors=[target,nxt];pc=nxt;break
  elif (op&0xf1ff)==0x41e8: # LEA (d16,An),Am (destination encoded in bits 11..9)
   if pc+4>len(b):reason='truncated';break
   ops.append(('v110_lea_disp_an',pc,op,(op>>9)&7,op&7,w(pc+2)));pc+=4
  elif (op&0xf1f8)==0xe188: # LSL.L #1..8,Dn (68000 immediate count)
   count=((op>>9)&7) or 8
   ops.append(('v109_lsll_imm',pc,op,op&7,count));pc+=2
  elif op==0x4eb9: # JSR absolute long
   if pc+6>len(b):reason='truncated';break
   target=int.from_bytes(b[pc+2:pc+6],'big')&0xffffff
   ops.append(('jsr_absl',pc,op,target,pc+6));successors=[target,pc+6];pc+=6;break
  elif op==0x4eb8: # JSR absolute short (sign-extended)
   if pc+4>len(b):reason='truncated';break
   ext=w(pc+2);target=(ext-65536 if ext&0x8000 else ext)&0xffffff
   ops.append(('jsr_absw',pc,op,target,pc+4,ext));successors=[target,pc+4];pc+=4;break
  elif (op&0xf1ff)==0x10fc: # MOVE.B #imm,(An)+; byte immediate is stored in a word
   if pc+4>len(b):reason='truncated';break
   imm=w(pc+2)
   ops.append(('moveb_imm_postinc',pc,op,(op>>9)&7,imm));pc+=4
  elif (op&0xfff8)==0x2f08: # MOVE.L An,-(A7)
   ops.append(('movel_an_predec_sp',pc,op,op&7));pc+=2
  elif (op&0xf1ff)==0x205f: # MOVEA.L (A7)+,An
   ops.append(('movea_postinc_sp',pc,op,(op>>9)&7));pc+=2
  elif op==0x30bc: # MOVE.W #imm,(An)
   if pc+4>len(b):reason='truncated';break
   ops.append(('movew_imm_ind',pc,op,(op>>9)&7,w(pc+2)));pc+=4
  elif (op&0xfff8)==0x0810: # BTST #imm,(An)
   if pc+4>len(b):reason='truncated';break
   ops.append(('btst_imm_ind',pc,op,op&7,w(pc+2)));pc+=4
  elif (op&0xfff8)==0x4250: # CLR.W (An)
   ops.append(('clrw_ind',pc,op,op&7));pc+=2
  elif op==0x4e73: # RTE, supervisor-only
   ops.append(('rte',pc,op));pc+=2;break
  elif op==0x4e75: # RTS
   ops.append(('rts',pc,op));pc+=2;break
  elif (op&0xff00)==0x6100: # BSR short/word
   ext=op&255
   if ext==255:reason='68020 long BSR unsupported';break
   if ext==0:
    if pc+4>len(b):reason='truncated';break
    disp=w(pc+2);disp=disp-65536 if disp&0x8000 else disp;nxt=pc+4
   else:
    disp=ext-256 if ext&128 else ext;nxt=pc+2
   target=(pc+2+disp)&0xffffff
   ops.append(('bsr',pc,op,target,nxt));successors=[target,nxt];pc=nxt;break
  elif op==0x4ef9: # JMP (xxx).L
   if pc+6>len(b):reason='truncated';break
   target=int.from_bytes(b[pc+2:pc+6],'big') & 0xffffff
   ops.append(('jmp_absl',pc,op,target));successors=[target];pc+=6;break
  elif (op&0xf1ff)==0x203c: # MOVE.L #imm,Dn
   if pc+6>len(b):reason='truncated';break
   imm=int.from_bytes(b[pc+2:pc+6],'big')
   ops.append(('movel_imm_dn',pc,op,(op>>9)&7,imm));pc+=6
  elif (op&0xfff8)==0x33c0: # MOVE.W Dn,(abs.l)
   if pc+6>len(b):reason='truncated';break
   ops.append(('movew_dn_absl',pc,op,op&7,int.from_bytes(b[pc+2:pc+6],'big')));pc+=6
  elif (op&0xf1f8)==0xb040: # CMP.W Dn,Dn
   ops.append(('cmpw_dn_dn',pc,op,(op>>9)&7,op&7));pc+=2
  elif (op&0xff00) in (0x6e00,0x6a00,0x6400,0x6500) and (op&255)==0: # BGT/BPL/BCC/BCS.W
   if pc+4>len(b):reason='truncated';break
   disp=w(pc+2);disp=disp-65536 if disp&0x8000 else disp
   target=(pc+2+disp)&0xffffff;nxt=pc+4
   kind={0x6e00:'bgt',0x6a00:'bpl',0x6400:'bcc',0x6500:'bcs'}[op&0xff00]
   ops.append((kind,pc,op,target,nxt));successors=[target,nxt];pc=nxt;break
  elif op==0x33fc: # MOVE.W #imm,(xxx).L
   if pc+8>len(b):reason='truncated';break
   imm=w(pc+2);addr=int.from_bytes(b[pc+4:pc+8],'big')
   ops.append(('movew_imm_absl',pc,op,imm,addr));pc+=8
  elif (op&0xf1ff)==0x41f8: # LEA (xxx).W,An
   if pc+4>len(b):reason='truncated';break
   ext=w(pc+2);addr=(ext-65536 if ext&0x8000 else ext)&0xffffff
   ops.append(('lea_absw',pc,op,(op>>9)&7,addr,ext));pc+=4
  elif (op&0xfff8)==0x23c8: # MOVE.L An,(xxx).L
   if pc+6>len(b):reason='truncated';break
   addr=int.from_bytes(b[pc+2:pc+6],'big')
   ops.append(('movel_an_absl',pc,op,op&7,addr));pc+=6
  elif op==0x23fc: # MOVE.L #imm,(xxx).L
   if pc+10>len(b):reason='truncated';break
   imm=int.from_bytes(b[pc+2:pc+6],'big');addr=int.from_bytes(b[pc+6:pc+10],'big')
   ops.append(('movel_imm_absl',pc,op,imm,addr));pc+=10
  elif (op&0xf100)==0x7000: # MOVEQ
   reg=(op>>9)&7; imm=op&255; imm=imm-256 if imm&128 else imm
   ops.append(('moveq',pc,op,reg,imm));pc+=2
  elif (op&0xf1c0)==0x0100 and ((op>>3)&7)==2: # BTST Dn,(An), memory byte
   ops.append(('btst_dn_ind',pc,op,(op>>9)&7,op&7));pc+=2
  elif (op&0xfff8)==0x2d00: # MOVE.L Dn,-(A6)
   ops.append(('movel_dn_predec',pc,op,6,op&7));pc+=2
  elif (op&0xf1f8)==0xe008 and (op&0x00c0)==0: # LSR.B #imm,Dn
   count=(op>>9)&7
   if count==0:count=8
   ops.append(('lsrb_imm',pc,op,op&7,count));pc+=2
  elif (op&0xf1ff)==0x41fa: # LEA (d16,PC),An
   if pc+4>len(b):reason='truncated';break
   ext=w(pc+2);disp=ext-65536 if ext&0x8000 else ext
   ops.append(('lea_pc_disp',pc,op,(op>>9)&7,disp,ext));pc+=4
  elif (op&0xf1f8)==0x1030: # MOVE.B (d8,An,Xn),Dn, brief index
   ext=w(pc+2)
   if ext&0x0700:reason=f'68020 indexed extension unsupported {ext:04x}';break
   ops.append(('v90_moveb_index',pc,op,(op>>9)&7,op&7,ext));pc+=4
  elif (op&0xfff8)==0x4a00: # TST.B Dn
   ops.append(('tstb_dn',pc,op,op&7));pc+=2
  elif (op&0xff00) in (0x6000,0x6600,0x6700) and (op&255)==0: # Bcc.W
   if pc+4>len(b):reason='truncated';break
   disp=w(pc+2);disp=disp-65536 if disp&0x8000 else disp
   target=(pc+2+disp)&0xffffff;nxt=pc+4
   kind={0x6000:'bra',0x6600:'bne',0x6700:'beq'}[op&0xff00]
   ops.append((kind,pc,op,target,nxt));successors=[target] if kind=='bra' else [target,nxt];pc=nxt;break
  elif (op&0xf1ff)==0x41f9: # LEA (abs).L,An
   if pc+6>len(b):reason='truncated';break
   addr=int.from_bytes(b[pc+2:pc+6],'big')
   ops.append(('lea_absl',pc,op,(op>>9)&7,addr));pc+=6
  elif (op&0xf1ff)==0x303c: # MOVE.W #imm,Dn
   if pc+4>len(b):reason='truncated';break
   ops.append(('movew_imm_dn',pc,op,(op>>9)&7,w(pc+2)));pc+=4
  elif (op&0xf1f8)==0xb010: # CMP.B (An),Dn
   ops.append(('cmpb_ind_dn',pc,op,(op>>9)&7,op&7));pc+=2
  elif (op&0xf1f8)==0x5048: # ADDQ.W #1..8,An (address register operation, CCR unchanged)
   count=(op>>9)&7
   if count==0:count=8
   ops.append(('addq_w_an',pc,op,op&7,count));pc+=2
  elif (op&0xf1ff)==0x5088: # ADDQ.L #imm,An
   count=(op>>9)&7
   if count==0:count=8
   ops.append(('addq_l_an',pc,op,op&7,count));pc+=2
  elif op==0x4a79: # TST.W absolute long
   if pc+6>len(b):reason='truncated';break
   addr=int.from_bytes(b[pc+2:pc+6],'big')
   ops.append(('tstw_absl',pc,op,addr));pc+=6
  elif op==0x4280: # CLR.L D0
   ops.append(('clrl_d0',pc,op));pc+=2
  elif op==0x1039: # MOVE.B absolute long,D0
   if pc+6>len(b):reason='truncated';break
   addr=int.from_bytes(b[pc+2:pc+6],'big')
   ops.append(('moveb_absl_d0',pc,op,addr));pc+=6
  elif op==0x4cd6: # MOVEM.L (A6),registers, normal mask order
   if pc+4>len(b):reason='truncated';break
   mask=w(pc+2)
   ops.append(('moveml_ind_regs',pc,op,6,mask));pc+=4
  elif op==0x46fc: # MOVE #imm,SR (privileged)
   if pc+4>len(b):reason='truncated';break
   ops.append(('move_imm_sr',pc,op,w(pc+2)));pc+=4
  elif (op&0xf1f8)==0x10d8: # MOVE.B (An)+,(Am)+
   ops.append(('moveb_postinc_postinc',pc,op,(op>>9)&7,op&7));pc+=2
  elif (op&0xf1f8)==0x1158 and ((op>>6)&7)==5 and (op&0x38)==0x18: # MOVE.B (An)+,(d16,Am)
   if pc+4>len(b):reason='truncated';break
   ext=w(pc+2);disp=ext-65536 if ext&0x8000 else ext
   ops.append(('moveb_postinc_disp',pc,op,(op>>9)&7,op&7,disp,ext));pc+=4
  elif (op&0xf1f8)==0x1018: # MOVE.B (An)+,Dn
   ops.append(('moveb_postinc',pc,op,(op>>9)&7,op&7));pc+=2
  elif (op&0xf1f8)==0x2080: # MOVE.L Dn,(Am), e.g. 2680
   ops.append(('movel_dn_ind',pc,op,(op>>9)&7,op&7));pc+=2
  elif (op&0xf1f8)==0x2098: # MOVE.L (An)+,(Am), e.g. 289D
   ops.append(('movel_postinc_ind',pc,op,(op>>9)&7,op&7));pc+=2
  elif (op&0xf1f8)==0x3080: # MOVE.W Dn,(An)
   ops.append(('movew_dn_ind',pc,op,(op>>9)&7,op&7));pc+=2
  elif (op&0xf1f8)==0xd040: # ADD.W Dn,Dn (source Dn, destination Dn)
   ops.append(('addw_dn',pc,op,(op>>9)&7,op&7));pc+=2
  elif (op&0xf0f8)==0x50c8: # DBcc Dn,disp16; initially DBF only
   if (op&0x0f00)!=0x0100:reason=f'unsupported DBcc condition {op:04x}';break
   if pc+4>len(b):reason='truncated';break
   disp=w(pc+2);disp=disp-65536 if disp&0x8000 else disp
   target=(pc+2+disp)&0xffffff;nxt=pc+4
   ops.append(('dbf',pc,op,op&7,target,nxt));successors=[target,nxt];pc=nxt;break
  elif (op&0xffc0)==0x0200 and (op&0x003f)<8: # ANDI.B #imm,Dn
   if pc+4>len(b):reason='truncated';break
   imm=w(pc+2);ops.append(('andi_b',pc,op,op&7,imm));pc+=4
  elif (op&0xf1ff)==0x1029: # MOVE.B (d16,A1),D0 generalized destination
   if pc+4>len(b):reason='truncated';break
   reg=(op>>9)&7;disp=w(pc+2);disp=disp-65536 if disp&0x8000 else disp
   ops.append(('moveb_disp',pc,op,reg,1,disp));pc+=4
  elif (op&0xfff8)==0x2378: # MOVE.L #imm,(d16,A1) special opcode 237C
   if op!=0x237c:reason=f'unsupported MOVE opcode {op:04x}';break
   if pc+8>len(b):reason='truncated';break
   imm=int.from_bytes(b[pc+2:pc+6],'big');disp=w(pc+6);disp=disp-65536 if disp&0x8000 else disp
   ops.append(('movel_imm_disp',pc,op,1,imm,disp));pc+=8
  elif (op&0xf1ff)==0x3014: # MOVE.W (A4),D0 (register fields generalized)
   dreg=(op>>9)&7;areg=op&7
   ops.append(('movew_ind',pc,op,dreg,areg));pc+=2
  elif (op&0xf1f8)==0x2040: # MOVEA.L Dn,An
   ops.append(('movea_l_dn',pc,op,(op>>9)&7,op&7));pc+=2
  elif (op&0xfff8)==0x4e60: # MOVE An,USP (supervisor)
   ops.append(('move_usp',pc,op,op&7));pc+=2
  elif (op&0xff00) in (0x6000,0x6600,0x6700) and (op&255)!=0 and (op&255)!=255:
   disp=op&255;disp=disp-256 if disp&128 else disp
   target=(pc+2+disp)&0xffffff; nxt=pc+2
   kind={0x6000:'bra',0x6600:'bne',0x6700:'beq'}[op&0xff00]
   ops.append((kind,pc,op,target,nxt));successors=[target] if kind=='bra' else [target,nxt];pc=nxt;break
  elif (op&0xf1f8)==0xc0c0: # MULU.W Dn,Dn (unsigned 16x16 -> 32)
   ops.append(('mulu_dn',pc,op,(op>>9)&7,op&7));pc+=2
  elif (op&0xf1f8)==0xc1c0: # MULS.W Dn,Dn (signed 16x16 -> 32)
   ops.append(('muls_dn',pc,op,(op>>9)&7,op&7));pc+=2
  elif (op&0xf1f8)==0x3000: # MOVE.W Dn,Dn
   ops.append(('movew_dn_dn',pc,op,(op>>9)&7,op&7));pc+=2
  elif (op&0xfff8)==0x0240: # ANDI.W #imm,Dn
   if pc+4>len(b):reason='truncated';break
   ops.append(('andi_w_dn',pc,op,op&7,w(pc+2)));pc+=4
  elif (op&0xf1f8)==0x2e40: # MOVEA.L Dn,A7 (also handled by MOVEA generic)
   ops.append(('movea_l_dn',pc,op,(op>>9)&7,op&7));pc+=2
  elif (op&0xf1ff)==0x2079: # MOVEA.L (abs.l),An
   if pc+6>len(b):reason='truncated';break
   ops.append(('movea_absl',pc,op,(op>>9)&7,int.from_bytes(b[pc+2:pc+6],'big')));pc+=6
  elif op==0x4e71: # NOP
   ops.append(('nop',pc,op));pc+=2
  elif (op&0xff00)==0x6b00 and (op&255)!=255: # BMI.S/BMI.W
   ext=op&255
   if ext==0:
    if pc+4>len(b):reason='truncated';break
    d=w(pc+2);disp=d-65536 if d&0x8000 else d;nxt=pc+4
   else:
    disp=ext-256 if ext&128 else ext;nxt=pc+2
   target=(pc+2+disp)&0xffffff
   ops.append(('bmi',pc,op,target,nxt));successors=[target,nxt];pc=nxt;break
  elif op in (0x0800,0x0839,0x08b9): # BTST/BCLR immediate bit
   if pc+4>len(b):reason='truncated';break
   bit=w(pc+2)
   if op==0x0800:
    ops.append(('btst_imm_dn',pc,op,0,bit));pc+=4
   else:
    if pc+8>len(b):reason='truncated';break
    addr=int.from_bytes(b[pc+4:pc+8],'big')
    ops.append(('btst_imm_absl' if op==0x0839 else 'bclr_imm_absl',pc,op,bit,addr));pc+=8
  elif op==0x23d8: # MOVE.L (A0)+,(abs.l)
   if pc+6>len(b):reason='truncated';break
   addr=int.from_bytes(b[pc+2:pc+6],'big')
   ops.append(('movel_postinc_absl',pc,op,0,addr));pc+=6
  elif op==0x2f39: # MOVE.L (abs.l),-(A7)
   if pc+6>len(b):reason='truncated';break
   addr=int.from_bytes(b[pc+2:pc+6],'big')
   ops.append(('movel_absl_predec',pc,op,7,addr));pc+=6
  elif op==0x3039: # MOVE.W (abs.l),D0
   if pc+6>len(b):reason='truncated';break
   addr=int.from_bytes(b[pc+2:pc+6],'big')
   ops.append(('movew_absl_dn',pc,op,0,addr));pc+=6
  elif (op&0xf1ff)==0x1039: # MOVE.B (abs.l),Dn
   if pc+6>len(b):reason='truncated';break
   ops.append(('moveb_absl_dn',pc,op,(op>>9)&7,int.from_bytes(b[pc+2:pc+6],'big')));pc+=6
  elif (op&0xf1f8)==0x1000: # MOVE.B Dn,Dn
   ops.append(('moveb_dn_dn',pc,op,(op>>9)&7,op&7));pc+=2
  elif (op&0xf1f8)==0x2000: # MOVE.L Dn,Dn
   ops.append(('movel_dn_dn',pc,op,(op>>9)&7,op&7));pc+=2
  elif (op&0xfff8)==0x0680: # ADDI.L #imm,Dn
   if pc+6>len(b):reason='truncated';break
   ops.append(('addi_l_dn',pc,op,op&7,int.from_bytes(b[pc+2:pc+6],'big')));pc+=6
  elif (op&0xf1ff)==0x31f3: # MOVE.W (d8,An,Xn), (abs).L
   if pc+8>len(b):reason='truncated';break
   ext=w(pc+2)
   if ext&0x0700:reason=f'68020 indexed extension unsupported {ext:04x}';break
   addr=int.from_bytes(b[pc+4:pc+8],'big')
   ops.append(('v107_movew_index_absl',pc,op,op&7,ext,addr));pc+=8
  elif (op&0xf1f8)==0x1180: # MOVE.B Dn,(d8,An,Xn) 68000 brief index
   if pc+4>len(b):reason='truncated';break
   ext=w(pc+2)
   if ext&0x0700:reason='68020 indexed extension unsupported';break
   ops.append(('v106_moveb_dn_index',pc,op,(op>>9)&7,op&7,ext));pc+=4
  elif (op&0xf1f8)==0x1080: # MOVE.B Dn,(An)
   ops.append(('moveb_dn_ind',pc,op,(op>>9)&7,op&7));pc+=2
  elif (op&0xf1f8)==0x5040: # ADDQ.W #1,Dn
   ops.append(('addq_w_dn',pc,op,op&7));pc+=2
  elif (op&0xfff8)==0x13c0: # MOVE.B Dn,(abs.l)
   if pc+6>len(b):reason='truncated';break
   ops.append(('moveb_dn_absl',pc,op,op&7,int.from_bytes(b[pc+2:pc+6],'big')));pc+=6
  elif (op&0xf1f8)==0x3018: # MOVE.W (An)+,Dn
   ops.append(('movew_postinc_dn',pc,op,(op>>9)&7,op&7));pc+=2
  elif (op&0xf1ff)==0x0139: # BTST Dn,(abs.l): bit number modulo 8
   if pc+6>len(b):reason='truncated';break
   ops.append(('btst_dn_absl',pc,op,(op>>9)&7,int.from_bytes(b[pc+2:pc+6],'big')));pc+=6
  elif (op&0xf1ff)==0x3039: # MOVE.W (abs.l),Dn
   if pc+6>len(b):reason='truncated';break
   ops.append(('movew_absl_dn',pc,op,(op>>9)&7,int.from_bytes(b[pc+2:pc+6],'big')));pc+=6
  elif (op&0xf1f8)==0x2048: # MOVEA.L An,An
   ops.append(('movea_an_an',pc,op,(op>>9)&7,op&7));pc+=2
  elif op==0x56f9: # SNE.B (abs.l), condition flags unchanged
   if pc+6>len(b):reason='truncated';break
   addr=int.from_bytes(b[pc+2:pc+6],'big')
   ops.append(('sne_absl',pc,op,addr));pc+=6
  elif op==0x33f9: # MOVE.W (abs.l),(abs.l)
   if pc+10>len(b):reason='truncated';break
   source=int.from_bytes(b[pc+2:pc+6],'big');dest=int.from_bytes(b[pc+6:pc+10],'big')
   ops.append(('movew_absl_absl',pc,op,source,dest));pc+=10
  elif (op&0xfff8) in (0x4c98,0x4cd8): # MOVEM.W/L (An)+,register list
   if pc+4>len(b):reason='truncated';break
   size=2 if (op&0xfff8)==0x4c98 else 4
   ops.append(('movem_postinc_regs',pc,op,op&7,w(pc+2),size));pc+=4
  elif (op&0xfff8)==0x48e0: # MOVEM.L register list,-(An), reversed predecrement mask
   if pc+4>len(b):reason='truncated';break
   ops.append(('moveml_predec',pc,op,op&7,w(pc+2)));pc+=4
  elif (op&0xf1ff)==0x207c: # MOVEA.L #imm,An
   if pc+6>len(b):reason='truncated';break
   ops.append(('movea_imm',pc,op,(op>>9)&7,int.from_bytes(b[pc+2:pc+6],'big')));pc+=6
  elif (op&0xf1ff)==0x41f9: # LEA (abs.l),An (covered earlier)
   raise AssertionError('unreachable')
  elif op in (0x4239,0x4279,0x42b9): # CLR.B/W/L (abs.l)
   if pc+6>len(b):reason='truncated';break
   addr=int.from_bytes(b[pc+2:pc+6],'big')
   ops.append(('clr_absl',pc,op,{0x4239:1,0x4279:2,0x42b9:4}[op],addr));pc+=6
  elif (op&0xfff8) in (0x4200,0x4240,0x4280): # CLR.B/W/L Dn
   ops.append(('clr_dn',pc,op,{0x4200:1,0x4240:2,0x4280:4}[op&0xfff8],op&7));pc+=2
  elif op in (0x4a39,0x4a79,0x4ab9): # TST.B/W/L (abs.l)
   if pc+6>len(b):reason='truncated';break
   addr=int.from_bytes(b[pc+2:pc+6],'big')
   ops.append(('tst_absl',pc,op,{0x4a39:1,0x4a79:2,0x4ab9:4}[op],addr));pc+=6
  elif (op&0xfff8) in (0x4a00,0x4a40,0x4a80): # TST.B/W/L Dn
   ops.append(('tst_dn',pc,op,{0x4a00:1,0x4a40:2,0x4a80:4}[op&0xfff8],op&7));pc+=2
  elif (op&0xff00)==0x6400 and (op&255) not in (0,255): # BCC.S (carry clear)
   disp=op&255;disp=disp-256 if disp&128 else disp
   target=(pc+2+disp)&0xffffff;nxt=pc+2
   ops.append(('bcc',pc,op,target,nxt));successors=[target,nxt];pc=nxt;break
  elif (op&0xf1f8)==0x5140: # SUBQ.W #1..8,Dn
   count=(op>>9)&7;count=count if count else 8
   ops.append(('v103_subq_w_dn',pc,op,op&7,count));pc+=2
  elif (op&0xfff8)==0x5340: # SUBQ.W #1,Dn
   ops.append(('subq_w_dn',pc,op,op&7));pc+=2
  elif (op&0xf1ff)==0x301f: # MOVE.W (A7)+,Dn
   ops.append(('movew_postinc_a7_dn',pc,op,(op>>9)&7));pc+=2
  elif (op&0xff00)==0x6500 and (op&255) not in (0,255): # BCS.S
   disp=op&255;disp=disp-256 if disp&128 else disp
   target=(pc+2+disp)&0xffffff;nxt=pc+2
   ops.append(('bcs',pc,op,target,nxt));successors=[target,nxt];pc=nxt;break
  elif (op&0xfff8)==0x0c00: # CMPI.B #imm,Dn
   if pc+4>len(b):reason='truncated';break
   imm=w(pc+2);ops.append(('cmpi_b_dn',pc,op,op&7,imm));pc+=4
  elif (op&0xfff8)==0x3f00: # MOVE.W Dn,-(A7)
   ops.append(('movew_dn_predec_a7',pc,op,op&7));pc+=2
  elif (op&0xf1ff) in (0x5079,0x5179): # ADDQ/SUBQ.W abs.l
   if pc+6>len(b):reason='truncated';break
   addr=int.from_bytes(b[pc+2:pc+6],'big');count=(op>>9)&7 or 8
   ops.append(('quick_w_absl',pc,op,bool(op&0x100),count,addr));pc+=6
  elif (op&0xf1f8)==0x5000: # ADDQ.B #1..8,Dn
   count=(op>>9)&7
   if count==0:count=8
   ops.append(('v105_addq_b_dn',pc,op,op&7,count));pc+=2
  elif op==0x5200: # ADDQ.B #1,D0
   ops.append(('addq_b_d0',pc,op));pc+=2
  elif op==0x3abc: # MOVE.W #imm,(d16,PC) is not a valid destination EA on 68000.
   reason='invalid 68000 destination EA for opcode 3abc (inspect ROM path)';break
  elif (op&0xf1f8)==0xb140: # EOR.W Dn,Dn
   ops.append(('eor_w',pc,op,(op>>9)&7,op&7));pc+=2
  elif (op&0xf1f8)==0x8040: # OR.W Dn,Dn
   ops.append(('or_w',pc,op,(op>>9)&7,op&7));pc+=2
  elif (op&0xf1f8)==0xc040: # AND.W Dn,Dn
   ops.append(('and_w',pc,op,(op>>9)&7,op&7));pc+=2
  elif (op&0xf1f8)==0x3040: # MOVEA.W Dn,An (sign extend)
   ops.append(('movea_w_dn',pc,op,(op>>9)&7,op&7));pc+=2
  elif (op&0xf1f8)==0x30c0: # MOVE.W Dn,(An)+
   ops.append(('movew_dn_postinc',pc,op,(op>>9)&7,op&7));pc+=2
  elif (op&0xf1f8)==0x9040: # SUB.W Dn,Dn
   ops.append(('sub_w',pc,op,(op>>9)&7,op&7));pc+=2
  elif (op&0xfff8)==0x0440: # SUBI.W #imm,Dn
   if pc+4>len(b):reason='truncated';break
   ops.append(('subi_w_dn',pc,op,op&7,w(pc+2)));pc+=4
  elif (op&0xf1ff)==0x90fc: # SUBA.W #imm,An
   if pc+4>len(b):reason='truncated';break
   ops.append(('suba_w_imm',pc,op,(op>>9)&7,w(pc+2)));pc+=4
  elif (op&0xf1f8)==0xe048 and ((op>>9)&7)!=0: # LSR.W #count,Dn
   count=(op>>9)&7
   ops.append(('lsr_w',pc,op,op&7,count));pc+=2
  elif (op&0xf1f8)==0xe008 and ((op>>9)&7)!=0: # LSR.B #count,Dn (handled elsewhere)
   count=(op>>9)&7
   ops.append(('lsrb_imm',pc,op,op&7,count));pc+=2
  elif (op&0xfff8) in (0x5200,0x5201,0x5300,0x5301) and (op&0xfff8) in (0x5200,0x5300): # ADDQ/SUBQ.B Dn
   ops.append(('quick_b_dn',pc,op,op&7,1 if op&0x0100 else 0));pc+=2
  elif (op&0xf1f8)==0xd000: # ADD.B Dn,Dn
   ops.append(('add_b_dn',pc,op,(op>>9)&7,op&7));pc+=2
  elif (op&0xfff8)==0x0640: # ADDI.W #imm,Dn
   ops.append(('addi_w_dn',pc,op,op&7,w(pc+2)));pc+=4
  elif op in (0x0679,0x0479,0x0c79,0xb479): # ADDI/SUBI/CMPI/CMP.W absolute long
   if op==0xb479:
    ops.append(('cmpw_absl_dn',pc,op,2,int.from_bytes(b[pc+2:pc+6],'big')));pc+=6
   elif op==0x0c79:
    ops.append(('cmpi_w_absl',pc,op,w(pc+2),int.from_bytes(b[pc+4:pc+8],'big')));pc+=8
   else:
    ops.append(('imm_w_absl',pc,op,op==0x0479,w(pc+2),int.from_bytes(b[pc+4:pc+8],'big')));pc+=8
  elif op==0x23c0: # MOVE.L D0,(abs.l)
   ops.append(('movel_dn_absl',pc,op,0,int.from_bytes(b[pc+2:pc+6],'big')));pc+=6
  elif op==0x23df: # MOVE.L (A7)+,(abs.l)
   ops.append(('movel_postinc_absl',pc,op,7,int.from_bytes(b[pc+2:pc+6],'big')));pc+=6
  elif op==0x2039: # MOVE.L (abs.l),D0
   ops.append(('movel_absl_dn',pc,op,0,int.from_bytes(b[pc+2:pc+6],'big')));pc+=6
  elif op==0x117c: # MOVE.B #imm,(d16,A0)
   ops.append(('moveb_imm_disp',pc,op,0,w(pc+2)&255,w(pc+4)));pc+=6
  elif op==0x1783: # MOVE.B D3,(d16,A3)
   ops.append(('moveb_dn_disp',pc,op,3,3,w(pc+2)));pc+=4
  elif op==0xe349: # LSL.W #1,D1
   ops.append(('lsl_w_1',pc,op,1));pc+=2
  elif op==0xe588: # LSL.L #2,D0
   ops.append(('lsl_l_2',pc,op,0));pc+=2
  elif op==0x08f9: # BSET #imm,(abs.l)
   ops.append(('bset_imm_absl',pc,op,w(pc+2)&7,int.from_bytes(b[pc+4:pc+8],'big')));pc+=8
  elif (op&0xf1ff)==0x103c: # MOVE.B #imm,Dn
   ops.append(('v89_moveb_imm_dn',pc,op,(op>>9)&7,w(pc+2)&255));pc+=4
  elif op==0x13fc: # MOVE.B #imm,(abs.l)
   ops.append(('v89_moveb_imm_absl',pc,op,w(pc+2)&255,int.from_bytes(b[pc+4:pc+8],'big')));pc+=8
  elif (op&0xfff8)==0x0800: # BTST #imm,Dn
   ops.append(('v89_btst_imm_dn',pc,op,op&7,w(pc+2)&31));pc+=4
  elif (op&0xfff8)==0x0280: # ANDI.L #imm,Dn
   ops.append(('v89_andi_l_dn',pc,op,op&7,int.from_bytes(b[pc+2:pc+6],'big')));pc+=6
  elif (op&0xf1ff)==0xd079: # ADD.W (abs.l),Dn
   ops.append(('v89_addw_absl_dn',pc,op,(op>>9)&7,int.from_bytes(b[pc+2:pc+6],'big')));pc+=6
  elif (op&0xf1ff)==0x1030: # MOVE.B (d8,A0,D0.W),Dn already handled above
   reason='indexed addressing requires validated extension';break
  elif (op&0xf1ff)==0x1028: # MOVE.B (d16,A0),Dn
   ops.append(('v89_moveb_disp_dn',pc,op,(op>>9)&7,op&7,w(pc+2)));pc+=4
  elif (op&0xf1ff)==0x123c: # MOVE.B #imm,D1 (general case covered)
   ops.append(('v89_moveb_imm_dn',pc,op,(op>>9)&7,w(pc+2)&255));pc+=4
  elif (op&0xfff8)==0x4440: # NEG.W Dn
   ops.append(('v89_negw_dn',pc,op,op&7));pc+=2
  elif (op&0xf1ff)==0xb079: # CMP.W (abs.l),Dn
   ops.append(('cmpw_absl_dn',pc,op,(op>>9)&7,int.from_bytes(b[pc+2:pc+6],'big')));pc+=6
  elif (op&0xfff8)==0x08c0: # BSET #imm,Dn (32-bit)
   ops.append(('v90_bset_dn',pc,op,op&7,w(pc+2)&31));pc+=4
  elif (op&0xfff8)==0x4640:
   ops.append(('v90_notw',pc,op,op&7));pc+=2
  elif (op&0xf1f8)==0xe140: # ASL.W immediate, count 0 means 8
   ops.append(('v90_aslw',pc,op,op&7,((op>>9)&7) or 8));pc+=2
  elif (op&0xf1f8)==0xe148: # LSL.W register count
   ops.append(('v90_lslw_reg',pc,op,op&7,(op>>9)&7));pc+=2
  elif (op&0xfff8)==0x0040:
   ops.append(('v90_oriw',pc,op,op&7,w(pc+2)));pc+=4
  elif op==0x23f9:
   ops.append(('v90_movel_mem_mem',pc,op,int.from_bytes(b[pc+2:pc+6],'big'),int.from_bytes(b[pc+6:pc+10],'big')));pc+=10
  elif op==0x3f39:
   ops.append(('v90_movew_mem_stack',pc,op,int.from_bytes(b[pc+2:pc+6],'big')));pc+=6
  elif (op&0xf1ff)==0x1030 or (op&0xf1ff)==0x1633:
   ext=w(pc+2)
   if ext&0x0700:reason=f'68020 indexed extension unsupported {ext:04x}';break
   ops.append(('v90_moveb_index',pc,op,(op>>9)&7,op&7,ext));pc+=4
  elif op==0x50f9: # ST (abs.l), always true; flags unaffected
   if pc+6>len(b):reason='truncated';break
   ops.append(('v91_st_absl',pc,op,int.from_bytes(b[pc+2:pc+6],'big')));pc+=6
  elif (op&0xf1f8)==0x8000: # OR.B Dn,Dn
   ops.append(('v91_orb_dn',pc,op,(op>>9)&7,op&7));pc+=2
  elif (op&0xfff8)==0x4840: # SWAP Dn
   ops.append(('v91_swap_dn',pc,op,op&7));pc+=2
  elif (op&0xf1f8)==0x20c0: # MOVE.L Dn,(An)+
   ops.append(('v91_movel_dn_postinc',pc,op,(op>>9)&7,op&7));pc+=2
  elif op==0x06b9: # ADDI.L #imm,(abs.l)
   if pc+10>len(b):reason='truncated';break
   ops.append(('v91_addil_absl',pc,op,int.from_bytes(b[pc+2:pc+6],'big'),int.from_bytes(b[pc+6:pc+10],'big')));pc+=10
  elif op==0x33df: # MOVE.W (A7)+,(abs.l)
   if pc+6>len(b):reason='truncated';break
   ops.append(('v91_movew_sp_absl',pc,op,int.from_bytes(b[pc+2:pc+6],'big')));pc+=6
  elif op==0x0279: # ANDI.W #imm,(abs.l)
   ops.append(('v95_andiw_absl',pc,op,w(pc+2),int.from_bytes(b[pc+4:pc+8],'big')));pc+=8
  elif (op&0xf1f8)==0x2028: # MOVE.L (d16,An),Dn
   ops.append(('v95_movel_disp_dn',pc,op,(op>>9)&7,op&7,w(pc+2)));pc+=4
  elif (op&0xfff8)==0x4a50: # TST.W (An)
   ops.append(('v95_tstw_an',pc,op,op&7));pc+=2
  elif (op&0xfff8)==0x0c40: # CMPI.W #imm,Dn
   ops.append(('v95_cmpi_w_dn',pc,op,op&7,w(pc+2)));pc+=4
  elif (op&0xf1ff)==0xc0f9: # MULU.W (abs.l),Dn
   ops.append(('v95_mulu_absl',pc,op,(op>>9)&7,int.from_bytes(b[pc+2:pc+6],'big')));pc+=6
  elif (op&0xf1ff)==0xc0fc: # MULU.W #imm,Dn
   ops.append(('v95_mulu_imm',pc,op,(op>>9)&7,w(pc+2)));pc+=4
  elif (op&0xf1f8)==0xd0c0: # ADDA.W Dn,An
   ops.append(('v95_addaw_dn',pc,op,(op>>9)&7,op&7));pc+=2
  elif (op&0xfff8)==0x4218: # CLR.B (An)+
   ops.append(('v95_clrb_postinc',pc,op,op&7));pc+=2
  elif (op&0xf1ff)==0xc139: # AND.B Dn,(abs.l)
   ops.append(('v95_andb_dn_absl',pc,op,(op>>9)&7,int.from_bytes(b[pc+2:pc+6],'big')));pc+=6
  elif (op&0xf1f8)==0x2070:
   ops.append(('v97_movea_index',pc,op,(op>>9)&7,op&7,w(pc+2)));pc+=4
  elif op==0x13f9:
   ops.append(('v97_moveb_abs_abs',pc,op,int.from_bytes(b[pc+2:pc+6],'big'),int.from_bytes(b[pc+6:pc+10],'big')));pc+=10
  elif (op&0xfff8)==0x33e8:
   ops.append(('v97_movew_disp_abs',pc,op,op&7,w(pc+2),int.from_bytes(b[pc+4:pc+8],'big')));pc+=8
  elif (op&0xf1ff)==0xd1b9:
   ops.append(('v97_addl_dn_abs',pc,op,(op>>9)&7,int.from_bytes(b[pc+2:pc+6],'big')));pc+=6
  elif (op&0xfff8)==0x23f0 or op==0x23f1:
   ops.append(('v97_movel_index_abs',pc,op,op&7,w(pc+2),int.from_bytes(b[pc+4:pc+8],'big')));pc+=8
  elif (op&0xfff8)==0xe440:
   ops.append(('v97_asrw2',pc,op,op&7));pc+=2
  elif (op&0xf1f8)==0x90c0:
   ops.append(('v97_subaw_dn',pc,op,(op>>9)&7,op&7));pc+=2
  elif (op&0xf1ff)==0xd0fc:
   ops.append(('v97_addaw_imm',pc,op,(op>>9)&7,w(pc+2)));pc+=4
  elif (op&0xfff8)==0x33d8:
   ops.append(('v97_movew_post_abs',pc,op,op&7,int.from_bytes(b[pc+2:pc+6],'big')));pc+=6
  elif (op&0xf1f8)==0x20d8:
   ops.append(('v97_movel_post_post',pc,op,(op>>9)&7,op&7));pc+=2
  elif (op&0xfff8)==0x4fe8:
   ops.append(('v97_lea_disp',pc,op,op&7,w(pc+2)));pc+=4
  elif (op&0xf1ff)==0x30fc:
   ops.append(('v97_movew_imm_post',pc,op,(op>>9)&7,w(pc+2)));pc+=4
  elif (op&0xf1f8)==0x10c0:
   ops.append(('v97_moveb_dn_post',pc,op,(op>>9)&7,op&7));pc+=2
  else:reason=f'unsupported opcode {op:04x}';break
 else:reason='256-instruction block limit'
 blocks[start]={'ops':ops,'stop_pc':pc,'reason':reason,'successors':successors}
 for target in successors:
  if target not in blocks and target not in pending:pending.append(target)
lines=['/* Generated from the exact ROM; no runtime 68000 opcode decoding. */',
       'static uint16_t t2gen_v100_read16(const struct t2bus *b,uint32_t a){uint16_t v=0;native_bus_read16(b,a,&v);return v;}',
       'static uint32_t t2gen_v100_read32(const struct t2bus *b,uint32_t a){uint32_t v=0;native_bus_read32(b,a,&v);return v;}',
       'static int t2gen_aot_cfg_dispatch(struct t2cpu *c, const struct t2bus *b)',
       '{','  uint8_t byte_value;','  switch (c->pc)','    {']
for start,block in sorted(blocks.items()):
 if not block["ops"]: continue
 lines.extend([f'      case 0x{start:06x}u:', '        {'])
 for op in block['ops']:
  kind,pc,raw,*args=op
  if pc in (0x93f2,0x93f8,0x9400,0x9406,0x9408,0x9420,0x9430):
   lines.append(f'          printf("T2GEN V1.00 STEP: pc={pc:06x} kind={kind} D0=%08lx A0=%06lx A1=%06lx FF0230=%08lx FF0238=%08lx FF023C=%08lx\\n",(unsigned long)c->d[0],(unsigned long)(c->a[0]&0xffffffu),(unsigned long)(c->a[1]&0xffffffu),(unsigned long)t2gen_v100_read32(b,0xff0230u),(unsigned long)t2gen_v100_read32(b,0xff0238u),(unsigned long)t2gen_v100_read32(b,0xff023cu));')
  if pc in (0x93f8,0x9406):
   lines.append(f'          printf("T2GEN V1.00 WORD: pc={pc:06x} A0=%06lx value=%04lx\\n",(unsigned long)(c->a[0]&0xffffffu),(unsigned long)t2gen_v100_read16(b,c->a[0]));')
  if pc==0x9406:
   lines.append('          {unsigned k;printf("T2GEN V1.00 RAM_DUMP: FF0230=");for(k=0;k<48;k++){uint8_t x=0;native_bus_read8(b,0xff0230u+k,&x);printf("%02x",x);}printf("\\n");}')
   lines.append('          {unsigned k;printf("T2GEN V1.00 RAM_DUMP: FF0410=");for(k=0;k<48;k++){uint8_t x=0;native_bus_read8(b,0xff0410u+k,&x);printf("%02x",x);}printf("\\n");}')
  if pc in (0x93b6,0x93c6,0x93cc,0x93d6,0x93e0,0x93ea,0x93f2,0x9400):
   lines.append(f'          printf("T2GEN V1.01 INIT_STEP: pc={pc:06x} kind={kind} A0=%06lx D0=%08lx FF0230=%08lx FF0234=%08lx FF0238=%08lx\\n",(unsigned long)(c->a[0]&0xffffffu),(unsigned long)c->d[0],(unsigned long)t2gen_v100_read32(b,0xff0230u),(unsigned long)t2gen_v100_read32(b,0xff0234u),(unsigned long)t2gen_v100_read32(b,0xff0238u));')
  if pc==0x93c6:
   lines.append('          {uint32_t v=0;int rc=native_bus_read32(b,c->a[0],&v);printf("T2GEN V1.01 INIT_SOURCE: A0=%06lx read_rc=%d long=%08lx\\n",(unsigned long)(c->a[0]&0xffffffu),rc,(unsigned long)v);}')
  if pc in (0x93c6,0x93cc,0x93d6,0x93e0):
   lines.append(f'          printf("T2GEN V1.01 INIT_BEFORE: pc={pc:06x} FF0230=%08lx FF0234=%08lx FF0238=%08lx\\n",(unsigned long)t2gen_v100_read32(b,0xff0230u),(unsigned long)t2gen_v100_read32(b,0xff0234u),(unsigned long)t2gen_v100_read32(b,0xff0238u));')
  lines.append(f'          if (!match16(b, 0x{pc:x}u, 0x{raw:04x}u)) return -1;')
  if kind in ('eor_w','or_w','and_w','sub_w'):
   src,dst=args
   expr={'eor_w':'x ^ y','or_w':'x | y','and_w':'x & y','sub_w':'x - y'}[kind]
   lines += [f'          {{ uint16_t x=(uint16_t)c->d[{dst}], y=(uint16_t)c->d[{src}],r=(uint16_t)({expr});',f'            c->d[{dst}]=(c->d[{dst}]&0xffff0000u)|r;']
   if kind=='sub_w':
    lines += ['            uint16_t carry=(x<y)?1u:0u;', '            uint16_t ov=((x^y)&(x^r)&0x8000u)?2u:0u;', '            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u)|ov|carry|(carry?16u:0u));']
   else:lines += ['            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u));']
   lines += ['          }','          c->cycles+=4u;']
  elif kind=='v110_lea_disp_an':
   dst,base,disp=args
   lines += [f'          if(!match16(b,0x{pc+2:x}u,0x{disp:04x}u))return -1;',
             f'          c->a[{dst}]=(c->a[{base}]+(int16_t)0x{disp:04x}u)&0xffffffu;',
             '          c->cycles+=8u;']
  elif kind=='v109_lsll_imm':
   reg,count=args
   lines += [f'          {{ uint32_t x=c->d[{reg}],r=x<<{count};',
             f'            uint16_t carry=(uint16_t)((x>>{32-count})&1u);',
             f'            c->d[{reg}]=r;',
             '            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x80000000u)?8u:0u)|(r==0u?4u:0u)|(carry?17u:0u));',
             '          }',f'          c->cycles+={8+2*count}u;']
  elif kind=='lsr_w':
   reg,count=args
   lines += [f'          {{ uint16_t old=(uint16_t)c->d[{reg}],r=(uint16_t)(old>>{count});',f'            uint16_t carry=(old>>{count-1})&1u;',f'            c->d[{reg}]=(c->d[{reg}]&0xffff0000u)|r;', '            c->sr=(uint16_t)((c->sr&0xffe0u)|(r==0u?4u:0u)|(carry?17u:0u));',f'            c->cycles+={6+2*count}u;','          }']
  elif kind=='movea_w_dn':
   dst,src=args
   lines += [f'          c->a[{dst}]=(uint32_t)(int32_t)(int16_t)c->d[{src}]&0xffffffu;', '          c->cycles+=4u;']
  elif kind=='movew_dn_postinc':
   dst,src=args
   lines += [f'          {{ uint16_t v=(uint16_t)c->d[{src}];',f'            if(native_bus_write16((struct t2bus *)b,c->a[{dst}],v)!=0)return -3;',f'            c->a[{dst}]=(c->a[{dst}]+2u)&0xffffffu;', '            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u));','          }','          c->cycles+=8u;']
  elif kind=='subi_w_dn':
   dst,imm=args
   lines += [f'          if(!match16(b,0x{pc+2:x}u,0x{imm:04x}u))return -1;',
             f'          {{ uint32_t x=c->d[{dst}]&65535u,y=0x{imm:04x}u,r=(x-y)&65535u;',
             f'            c->d[{dst}]=(c->d[{dst}]&0xffff0000u)|r;',
             '            uint16_t carry=(x<y)?1u:0u;',
             '            uint16_t overflow=((x^y)&(x^r)&0x8000u)?2u:0u;',
             '            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u)|overflow|carry|(carry?16u:0u));',
             '          }','          c->cycles+=8u;']
  elif kind=='suba_w_imm':
   dst,imm=args
   lines += [f'          if(!match16(b,0x{pc+2:x}u,0x{imm:04x}u))return -1;',f'          c->a[{dst}]=(c->a[{dst}]-(uint32_t)(int32_t)(int16_t)0x{imm:04x}u)&0xffffffu;', '          c->cycles+=8u;']
  elif kind in ('quick_b_dn','add_b_dn','addi_w_dn','lsl_w_1','lsl_l_2'):
   if kind=='quick_b_dn':
    reg,sub=args;expr='x-1u' if sub else 'x+1u';size=8
    lines += [f'          {{ uint32_t x=c->d[{reg}]&255u,r=({expr})&255u;',f'            c->d[{reg}]=(c->d[{reg}]&0xffffff00u)|r;',f'            uint16_t carry={"x==0u" if sub else "x==255u"};',f'            uint16_t ov={"x==128u" if sub else "x==127u"};', '            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&128u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?17u:0u));','          }','          c->cycles+=4u;']
   elif kind=='add_b_dn':
    dst,src=args;lines += [f'          {{ uint32_t x=c->d[{dst}]&255u,y=c->d[{src}]&255u,r=(x+y)&255u;',f'            c->d[{dst}]=(c->d[{dst}]&0xffffff00u)|r;', '            uint16_t carry=(x+y)>255u,ov=((~(x^y))&(x^r)&128u)!=0u;', '            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&128u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?17u:0u));','          }','          c->cycles+=4u;']
   elif kind=='addi_w_dn':
    reg,imm=args;lines += [f'          {{ uint32_t x=c->d[{reg}]&65535u,y=0x{imm:04x}u,r=(x+y)&65535u;',f'            c->d[{reg}]=(c->d[{reg}]&0xffff0000u)|r;', '            uint16_t carry=(x+y)>65535u,ov=((~(x^y))&(x^r)&32768u)!=0u;', '            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?17u:0u));','          }','          c->cycles+=8u;']
   else:
    reg=args[0];bits=16 if kind=='lsl_w_1' else 32;count=1 if bits==16 else 2;mask='65535u' if bits==16 else '0xffffffffu';sign='32768u' if bits==16 else '0x80000000u';preserve=f'(c->d[{reg}]&0xffff0000u)|r' if bits==16 else 'r'
    lines += [f'          {{ uint32_t x=c->d[{reg}]&{mask},r=(x<<{count})&{mask};',f'            uint16_t carry=(x>>{bits-count})&1u;',f'            c->d[{reg}]={preserve};',f'            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&{sign})?8u:0u)|(r==0u?4u:0u)|(carry?17u:0u));','          }',f'          c->cycles+={6+2*count}u;']
  elif kind in ('movel_dn_absl','movel_postinc_absl','movel_absl_dn','moveb_imm_disp','moveb_dn_disp','bset_imm_absl','cmpw_absl_dn','cmpi_w_absl','imm_w_absl'):
   if kind=='movel_dn_absl':
    reg,addr=args;lines += [f'          {{ uint32_t v=c->d[{reg}]; if(native_bus_write32((struct t2bus *)b,0x{addr:08x}u,v)!=0)return -3;', '            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }','          c->cycles+=20u;']
   elif kind=='movel_postinc_absl':
    reg,addr=args;lines += [f'          {{ uint32_t v; if(native_bus_read32(b,c->a[{reg}],&v)!=0)return -3;',f'            c->a[{reg}]=(c->a[{reg}]+4u)&0xffffffu;',f'            if(native_bus_write32((struct t2bus *)b,0x{addr:08x}u,v)!=0)return -3;', '            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }','          c->cycles+=28u;']
   elif kind=='movel_absl_dn':
    reg,addr=args;lines += [f'          {{ uint32_t v; if(native_bus_read32(b,0x{addr:08x}u,&v)!=0)return -3;',f'            c->d[{reg}]=v;', '            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }','          c->cycles+=16u;']
   elif kind in ('moveb_imm_disp','moveb_dn_disp'):
    if kind=='moveb_imm_disp': reg,imm,disp=args;val=f'0x{imm:02x}u'
    else:reg,src,disp=args;val=f'(c->d[{src}]&255u)'
    lines += [f'          {{ uint32_t v={val}; uint32_t addr=(c->a[{reg}]+(int16_t)0x{disp:04x}u)&0xffffffu;', '            if(native_bus_write8((struct t2bus *)b,addr,(uint8_t)v)!=0)return -3;', '            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&128u)?8u:0u)|(v==0u?4u:0u)); }','          c->cycles+=16u;']
   elif kind=='bset_imm_absl':
    bit,addr=args;lines += [f'          {{ uint8_t v; if(native_bus_read8(b,0x{addr:08x}u,&v)!=0)return -3;',f'            c->sr=(uint16_t)((c->sr&~4u)|((v&(1u<<{bit}))?0u:4u));',f'            if(native_bus_write8((struct t2bus *)b,0x{addr:08x}u,(uint8_t)(v|(1u<<{bit})))!=0)return -3; }}','          c->cycles+=20u;']
   else:
    if kind=='cmpw_absl_dn': reg,addr=args;imm=None
    elif kind=='cmpi_w_absl': imm,addr=args;reg=None
    else: sub,imm,addr=args;reg=None
    lines += [f'          {{ uint16_t v; if(native_bus_read16(b,0x{addr:08x}u,&v)!=0)return -3;']
    if kind=='imm_w_absl':
     expr='v-(uint16_t)0x%04xu'%imm if sub else 'v+(uint16_t)0x%04xu'%imm
     lines += [f'            uint32_t x=v,y=0x{imm:04x}u,r=({expr})&65535u;',f'            if(native_bus_write16((struct t2bus *)b,0x{addr:08x}u,(uint16_t)r)!=0)return -3;']
    else:
     lines += [f'            uint32_t x={"(c->d[%d]&65535u)"%reg if reg is not None else "v"},y={"v" if reg is not None else "0x%04xu"%imm},r=(x-y)&65535u;']
    is_sub=kind!='imm_w_absl' or sub
    lines += [f'            uint16_t carry={"x<y" if is_sub else "(x+y)>65535u"};',f'            uint16_t ov={"((x^y)&(x^r)&32768u)!=0u" if is_sub else "((~(x^y))&(x^r)&32768u)!=0u"};',f'            c->sr=(uint16_t)((c->sr&{"0xfff0u" if kind in ("cmpw_absl_dn","cmpi_w_absl") else "0xffe0u"})|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?1u:0u){"" if kind in ("cmpw_absl_dn","cmpi_w_absl") else "|(carry?16u:0u)"});','          }','          c->cycles+=16u;']
  if kind.startswith('v89_'):
   if kind=='v89_moveb_imm_dn':
    reg,v=args;lines += [f'          byte_value=0x{v:02x}u;',f'          c->d[{reg}]=(c->d[{reg}]&0xffffff00u)|byte_value;', '          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&128u)?8u:0u)|(byte_value==0u?4u:0u));','          c->cycles+=8u;']
   elif kind=='v89_moveb_imm_absl':
    v,addr=args;lines += [f'          byte_value=0x{v:02x}u;',f'          if(native_bus_write8((struct t2bus *)b,0x{addr:08x}u,byte_value)!=0)return -3;', '          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&128u)?8u:0u)|(byte_value==0u?4u:0u));','          c->cycles+=20u;']
   elif kind=='v89_btst_imm_dn':
    reg,bit=args;lines += [f'          c->sr=(uint16_t)((c->sr&~4u)|((c->d[{reg}]&(1u<<{bit}))?0u:4u));','          c->cycles+=10u;']
   elif kind=='v89_andi_l_dn':
    reg,imm=args;lines += [f'          c->d[{reg}] &= 0x{imm:08x}u;',f'          c->sr=(uint16_t)((c->sr&0xfff0u)|((c->d[{reg}]&0x80000000u)?8u:0u)|(c->d[{reg}]==0u?4u:0u));','          c->cycles+=16u;']
   elif kind=='v89_addw_absl_dn':
    reg,addr=args;lines += [f'          {{ uint16_t v; if(native_bus_read16(b,0x{addr:08x}u,&v)!=0)return -3;',f'            uint32_t x=c->d[{reg}]&65535u,y=v,r=(x+y)&65535u;',f'            c->d[{reg}]=(c->d[{reg}]&0xffff0000u)|r;', '            uint16_t carry=((x+y)>65535u)?1u:0u,ov=((~(x^y))&(x^r)&32768u)?2u:0u;', '            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|ov|carry|(carry?16u:0u)); }','          c->cycles+=12u;']
   elif kind=='v89_moveb_disp_dn':
    dst,areg,disp=args;lines += [f'          if(native_bus_read8(b,(c->a[{areg}]+(int16_t)0x{disp:04x}u)&0xffffffu,&byte_value)!=0)return -3;',f'          c->d[{dst}]=(c->d[{dst}]&0xffffff00u)|byte_value;', '          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&128u)?8u:0u)|(byte_value==0u?4u:0u));','          c->cycles+=12u;']
   elif kind=='v89_negw_dn':
    reg=args[0];lines += [f'          {{ uint32_t x=c->d[{reg}]&65535u,r=(-x)&65535u;',f'            c->d[{reg}]=(c->d[{reg}]&0xffff0000u)|r;', '            uint16_t carry=x!=0u?1u:0u;', '            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(x==32768u?2u:0u)|carry|(carry?16u:0u)); }','          c->cycles+=4u;']
  if kind=='movel_an_predec_sp':
   reg=args[0]
   lines += ['          c->a[7]=(c->a[7]-4u)&0xffffffu;',f'          if (native_bus_write32((struct t2bus *)b,c->a[7],c->a[{reg}])!=0) return -3;', '          c->cycles += 12u;']
  elif kind=='movea_postinc_sp':
   reg=args[0]
   lines += ['          { uint32_t value; if (native_bus_read32(b,c->a[7],&value)!=0) return -3;',f'            c->a[{reg}]=value&0xffffffu; c->a[7]=(c->a[7]+4u)&0xffffffu;', '          }','          c->cycles += 12u;']
  elif kind=='movew_imm_ind':
   reg,imm=args
   lines += [f'          if (!match16(b,0x{pc+2:x}u,0x{imm:04x}u)) return -1;',f'          if (native_bus_write16((struct t2bus *)b,c->a[{reg}],0x{imm:04x}u)!=0) return -3;',f'          c->sr=(uint16_t)((c->sr&0xfff0u)|{8 if imm&0x8000 else 0}u|{4 if imm==0 else 0}u);','          c->cycles += 12u;']
  elif kind=='btst_imm_ind':
   reg,imm=args
   lines += [f'          if (!match16(b,0x{pc+2:x}u,0x{imm:04x}u)) return -1;',f'          if (native_bus_read8(b,c->a[{reg}],&byte_value)!=0) return -3;',f'          c->sr=(uint16_t)((c->sr&~4u)|((byte_value&(1u<<{imm%8}))?0u:4u));','          c->cycles += 12u;']
  elif kind=='clrw_ind':
   reg=args[0]
   lines += [f'          if (native_bus_write16((struct t2bus *)b,c->a[{reg}],0u)!=0) return -3;', '          c->sr=(uint16_t)((c->sr&0xfff0u)|4u);','          c->cycles += 12u;']
  if kind=='moveb_absl_dn':
   reg,addr=args
   lines += [f'          if (!match32(b,0x{pc+2:x}u,0x{addr:08x}u)) return -1;',f'          if (native_bus_read8(b,0x{addr:08x}u,&byte_value)!=0) return -3;',f'          c->d[{reg}]=(c->d[{reg}]&0xffffff00u)|byte_value;', '          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));','          c->cycles+=16u;']
  elif kind=='moveb_dn_dn':
   dst,src=args
   lines += [f'          byte_value=(uint8_t)c->d[{src}];',f'          c->d[{dst}]=(c->d[{dst}]&0xffffff00u)|byte_value;', '          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));','          c->cycles+=4u;']
  elif kind=='movel_dn_dn':
   dst,src=args
   lines += [f'          c->d[{dst}]=c->d[{src}];',f'          c->sr=(uint16_t)((c->sr&0xfff0u)|((c->d[{dst}]&0x80000000u)?8u:0u)|(c->d[{dst}]==0u?4u:0u));','          c->cycles+=4u;']
  elif kind=='addi_l_dn':
   reg,imm=args
   lines += [f'          if (!match32(b,0x{pc+2:x}u,0x{imm:08x}u)) return -1;',f'          {{ uint32_t dst=c->d[{reg}],src=0x{imm:08x}u,r=dst+src;',f'            c->d[{reg}]=r;', '            uint16_t carry=(r<dst)?1u:0u;', '            uint16_t ov=((~(dst^src)&(dst^r)&0x80000000u)!=0u)?2u:0u;', '            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x80000000u)?8u:0u)|(r==0u?4u:0u)|ov|carry|(carry?16u:0u));','          }','          c->cycles+=16u;']
  elif kind=='v107_movew_index_absl':
   areg,ext,addr=args
   ixreg=(ext>>12)&7;ixaddr=bool(ext&0x8000);ixlong=bool(ext&0x0800);disp=ext&255
   if disp>=128:disp-=256
   idx=f'c->{"a" if ixaddr else "d"}[{ixreg}]'
   idxexpr=f'(int32_t){idx}' if ixlong else f'(int32_t)(int16_t)({idx}&0xffffu)'
   lines += [f'          if (!match16(b,0x{pc+2:x}u,0x{ext:04x}u)||!match32(b,0x{pc+4:x}u,0x{addr:08x}u)) return -1;',
             f'          {{ uint32_t ea=(c->a[{areg}]+({idxexpr})+({disp}))&0xffffffu; uint16_t val;',
             '            if (native_bus_read16(b,ea,&val)!=0) return -3;',
             f'            if (native_bus_write16((struct t2bus *)b,0x{addr:08x}u,val)!=0) return -3;',
             '            c->sr=(uint16_t)((c->sr&0xfff0u)|((val&0x8000u)?8u:0u)|(val==0u?4u:0u));',
             '          }', '          c->cycles+=26u;']
  elif kind=='v106_moveb_dn_index':
   areg,dreg,ext=args
   ixreg=(ext>>12)&7;ixaddr=bool(ext&0x8000);ixlong=bool(ext&0x0800);disp=ext&255
   if disp>=128:disp-=256
   idx=f'c->a[{ixreg}]' if ixaddr else f'c->d[{ixreg}]'
   idxexpr=f'(int32_t){idx}' if ixlong else f'(int32_t)(int16_t)({idx}&0xffffu)'
   lines += [f'          if (!match16(b,0x{pc+2:x}u,0x{ext:04x}u)) return -1;',f'          {{ uint32_t ea=(uint32_t)(c->a[{areg}]+({idxexpr})+({disp}));',f'            byte_value=(uint8_t)c->d[{dreg}];', '            if (native_bus_write8((struct t2bus *)b,ea&0xffffffu,byte_value)!=0) return -3;', '            c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));', '          }', '          c->cycles+=18u;']
  elif kind=='moveb_dn_ind':
   areg,dreg=args
   lines += [f'          byte_value=(uint8_t)c->d[{dreg}];',f'          if (native_bus_write8((struct t2bus *)b,c->a[{areg}],byte_value)!=0) return -3;', '          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));','          c->cycles+=8u;']
  elif kind=='addq_w_dn':
   reg=args[0]
   lines += [f'          {{ uint16_t dst=(uint16_t)c->d[{reg}],r=(uint16_t)(dst+1u);',f'            c->d[{reg}]=(c->d[{reg}]&0xffff0000u)|r;', '            uint16_t carry=(dst==0xffffu)?1u:0u;', '            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u)|(dst==0x7fffu?2u:0u)|carry|(carry?16u:0u));','          }','          c->cycles+=4u;']
  elif kind=='moveb_dn_absl':
   reg,addr=args
   lines += [f'          if (!match32(b,0x{pc+2:x}u,0x{addr:08x}u)) return -1;',f'          byte_value=(uint8_t)c->d[{reg}];',f'          if (native_bus_write8((struct t2bus *)b,0x{addr:08x}u,byte_value)!=0) return -3;', '          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));','          c->cycles+=16u;']
  if kind=='movew_postinc_dn':
   dst,src=args
   lines += [f'          {{ uint16_t v; if(native_bus_read16(b,c->a[{src}],&v)!=0) return -3;',f'            c->a[{src}]=(c->a[{src}]+2u)&0xffffffu;',f'            c->d[{dst}]=(c->d[{dst}]&0xffff0000u)|v;', '            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }','          c->cycles+=8u;']
  if kind=='btst_dn_absl':
   reg,addr=args
   lines += [f'          if (!match32(b,0x{pc+2:x}u,0x{addr:08x}u)) return -1;',f'          if (native_bus_read8(b,0x{addr:08x}u,&byte_value)!=0) return -3;',f'          c->sr=(uint16_t)((c->sr&~4u)|((byte_value&(1u<<(c->d[{reg}]&7u)))?0u:4u));','          c->cycles+=12u;']
  elif kind=='movea_an_an':
   dst,src=args
   lines += [f'          c->a[{dst}]=c->a[{src}];','          c->cycles+=4u;']
  if kind=='cmpi_b_dn':
   reg,imm=args
   lines += [f'          if (!match16(b, 0x{pc+2:x}u, 0x{imm:04x}u)) return -1;',f'          {{ uint8_t dst=(uint8_t)c->d[{reg}], src=0x{imm&255:02x}u, result=(uint8_t)(dst-src);', '            uint16_t n=(result&0x80u)?8u:0u, z=(result==0u)?4u:0u;', '            uint16_t v=((dst^src)&(dst^result)&0x80u)?2u:0u;', '            uint16_t carry=(dst<src)?1u:0u;', '            c->sr=(uint16_t)((c->sr&0xfff0u)|n|z|v|carry);', '          }','          c->cycles += 8u;']
  elif kind=='v103_subq_w_dn':
   reg,count=args
   lines += [f'          {{uint32_t dst=c->d[{reg}]&65535u,src={count}u,r=(dst-src)&65535u;',f'           c->d[{reg}]=(c->d[{reg}]&0xffff0000u)|r;', '           uint16_t cy=(dst<src),ov=((dst^src)&(dst^r)&32768u)!=0u;', '           c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(cy?17u:0u));}', '          c->cycles+=4u;']
  elif kind=='subq_w_dn':
   reg=args[0]
   lines += [f'          {{ uint16_t dst=(uint16_t)c->d[{reg}],result=(uint16_t)(dst-1u);',f'            c->d[{reg}]=(c->d[{reg}]&0xffff0000u)|result;', '            uint16_t carry=(dst==0u)?1u:0u;', '            c->sr=(uint16_t)((c->sr&0xffe0u)|((result&0x8000u)?8u:0u)|(result==0u?4u:0u)|(dst==0x8000u?2u:0u)|carry|(carry?16u:0u));', '          }','          c->cycles += 4u;']
  elif kind=='movew_postinc_a7_dn':
   reg=args[0]
   lines += [f'          {{ uint16_t v; if (native_bus_read16(b,c->a[7],&v)!=0) return -3;', '            c->a[7]=(c->a[7]+2u)&0xffffffu;',f'            c->d[{reg}]=(c->d[{reg}]&0xffff0000u)|v;', '            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u));', '          }','          c->cycles += 8u;']
  elif kind=='movew_dn_predec_a7':
   reg=args[0]
   lines += ['          c->a[7]=(c->a[7]-2u)&0xffffffu;',f'          if (native_bus_write16((struct t2bus *)b,c->a[7],(uint16_t)c->d[{reg}]) != 0) return -3;',f'          {{ uint16_t v=(uint16_t)c->d[{reg}]; c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }}','          c->cycles += 8u;']
  elif kind=='quick_w_absl':
   sub,count,addr=args
   lines += [f'          if (!match32(b,0x{pc+2:x}u,0x{addr:08x}u)) return -1;',f'          {{ uint16_t dst,src={count}u,result; if (native_bus_read16(b,0x{addr:08x}u,&dst)!=0) return -3;',f'            result=(uint16_t)(dst {"-" if sub else "+"} src);',f'            if (native_bus_write16((struct t2bus *)b,0x{addr:08x}u,result)!=0) return -3;',f'            uint16_t carry={"dst<src" if sub else "(uint32_t)dst+src>0xffffu"}?1u:0u;',f'            uint16_t overflow={"((dst^src)&(dst^result)&0x8000u)" if sub else "((~(dst^src))&(dst^result)&0x8000u)"}?2u:0u;', '            c->sr=(uint16_t)((c->sr&0xffe0u)|((result&0x8000u)?8u:0u)|(result==0u?4u:0u)|overflow|carry|(carry?16u:0u));','          }','          c->cycles += 20u;']
  elif kind=='v105_addq_b_dn':
   reg,count=args
   lines += [f'          {{ uint32_t dst=c->d[{reg}]&255u,src={count}u,r=(dst+src)&255u;',f'            c->d[{reg}]=(c->d[{reg}]&0xffffff00u)|r;', '            uint16_t cy=((dst+src)>255u)?1u:0u;', '            uint16_t ov=((~(dst^src)&(dst^r)&128u)!=0u)?2u:0u;', '            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&128u)?8u:0u)|(r==0u?4u:0u)|ov|cy|(cy?16u:0u));', '          }','          c->cycles+=4u;']
  elif kind=='addq_b_d0':
   lines += ['          { uint8_t dst=(uint8_t)c->d[0],result=(uint8_t)(dst+1u);', '            c->d[0]=(c->d[0]&0xffffff00u)|result;', '            uint16_t carry=(dst==0xffu)?1u:0u;', '            c->sr=(uint16_t)((c->sr&0xffe0u)|((result&0x80u)?8u:0u)|(result==0u?4u:0u)|(dst==0x7fu?2u:0u)|carry|(carry?16u:0u));','          }','          c->cycles += 4u;']
  if kind=='jsr_an':
   areg,nxt=args
   if pc==0x9446: lines.append('          printf("T2GEN V0.99 JSR: pc=009446 target=%06lx FF0238/FF023C follow\\n",(unsigned long)(c->a[1]&0xffffffu));')
   lines += [f'          {{ uint32_t target=c->a[{areg}] & 0xffffffu;',
             f'            uint32_t sp=(c->a[7]-4u)&0xffffffu;',
             f'            if(native_bus_write32((struct t2bus *)b,sp,0x{nxt:06x}u)!=0)return -3;',
             f'            c->a[7]=sp; c->pc=target; c->cycles+=16u;',
             f'            printf("T2GEN V0.94 IRQ6_CALLBACK: pointer_addr=FF0138 target=%06lx return={nxt:06x}\\n",(unsigned long)target);',
             '          }','          return 0;']
  elif kind in ('jsr_absl','jsr_absw','jsr_pcdisp','bsr'):
   target,nxt=args[:2]
   if kind=='jsr_absl':lines.append(f'          if (!match32(b, 0x{pc+2:x}u, 0x{target:08x}u)) return -1;')
   if kind=='jsr_pcdisp':lines.append(f'          if (!match16(b, 0x{pc+2:x}u, 0x{args[2]:04x}u)) return -1;')
   if kind=='jsr_absw':lines.append(f'          if (!match16(b, 0x{pc+2:x}u, 0x{args[2]:04x}u)) return -1;')
   if kind=='bsr' and (raw&255)==0:lines.append(f'          if (!match16(b, 0x{pc+2:x}u, 0x{w(pc+2):04x}u)) return -1;')
   lines += [f'          {{ uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;',
             f'            if (native_bus_write32((struct t2bus *)b, new_sp, 0x{nxt:06x}u) != 0) return -3;',
             f'            c->a[7] = new_sp; c->pc = 0x{target:06x}u;',
             f'            c->cycles += {18 if kind=="jsr_absl" else 18 if kind=="jsr_absw" else 18}u;',
             '          }', '          return 0;']
  elif kind=='moveml_predec':
   areg,mask=args
   lines.append(f'          if (!match16(b, 0x{pc+2:x}u, 0x{mask:04x}u)) return -1;')
   # MOVEM predecrement bit 0 corresponds to A7, bit 15 to D0.
   for bit in range(16):
    if mask&(1<<bit):
     typ='a' if bit<8 else 'd';reg=7-bit if bit<8 else 15-bit
     lines += [f'          c->a[{areg}] = (c->a[{areg}] - 4u) & 0xffffffu;',f'          if (native_bus_write32((struct t2bus *)b, c->a[{areg}], c->{typ}[{reg}]) != 0) return -3;']
   lines.append(f'          c->cycles += {8+8*mask.bit_count()}u;')
  elif kind=='movea_imm':
   reg,imm=args
   lines += [f'          if (!match32(b, 0x{pc+2:x}u, 0x{imm:08x}u)) return -1;',f'          c->a[{reg}] = 0x{imm:08x}u;', '          c->cycles += 12u;']
  elif kind=='clr_absl':
   size,addr=args
   fn={1:'native_bus_write8',2:'native_bus_write16',4:'native_bus_write32'}[size]
   lines += [f'          if (!match32(b, 0x{pc+2:x}u, 0x{addr:08x}u)) return -1;',f'          if ({fn}((struct t2bus *)b, 0x{addr:08x}u, 0u) != 0) return -3;', '          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);',f'          c->cycles += {16 if size==4 else 12}u;']
  elif kind=='clr_dn':
   size,reg=args
   mask={1:0xffffff00,2:0xffff0000,4:0}[size]
   lines += [f'          c->d[{reg}] &= 0x{mask:08x}u;', '          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);', f'          c->cycles += {6 if size==4 else 4}u;']
  elif kind=='tst_absl':
   size,addr=args
   fn={1:'native_bus_read8',2:'native_bus_read16',4:'native_bus_read32'}[size]
   typ={1:'uint8_t',2:'uint16_t',4:'uint32_t'}[size]
   sign={1:0x80,2:0x8000,4:0x80000000}[size]
   lines += [f'          if (!match32(b, 0x{pc+2:x}u, 0x{addr:08x}u)) return -1;',f'          {{ {typ} value;',f'            if ({fn}(b, 0x{addr:08x}u, &value) != 0) return -3;',f'            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((value & 0x{sign:x}u) ? 8u : 0u) | (value == 0u ? 4u : 0u));','          }',f'          c->cycles += {16 if size==4 else 12}u;']
  elif kind=='tst_dn':
   size,reg=args
   mask={1:0xff,2:0xffff,4:0xffffffff}[size];sign={1:0x80,2:0x8000,4:0x80000000}[size]
   lines += [f'          {{ uint32_t value = c->d[{reg}] & 0x{mask:08x}u;',f'            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((value & 0x{sign:x}u) ? 8u : 0u) | (value == 0u ? 4u : 0u));','          }','          c->cycles += 4u;']
  elif kind=='nop':
   lines.append('          c->cycles += 4u;')
  elif kind=='bmi':
   target,nxt=args
   if (raw&255)==0:lines.append(f'          if (!match16(b, 0x{pc+2:x}u, 0x{w(pc+2):04x}u)) return -1;')
   lines += [f'          c->pc = (c->sr & 8u) ? 0x{target:06x}u : 0x{nxt:06x}u;', '          c->cycles += (c->sr & 8u) ? 10u : 8u;', '          return 0;']
  elif kind=='btst_imm_dn':
   reg,bit=args
   lines += [f'          if (!match16(b, 0x{pc+2:x}u, 0x{bit:04x}u)) return -1;',f'          c->sr = (uint16_t)((c->sr & ~4u) | ((c->d[{reg}] & (1u << {bit%32})) ? 0u : 4u));','          c->cycles += 10u;']
  elif kind in ('btst_imm_absl','bclr_imm_absl'):
   bit,addr=args
   lines += [f'          if (!match16(b, 0x{pc+2:x}u, 0x{bit:04x}u) || !match32(b, 0x{pc+4:x}u, 0x{addr:08x}u)) return -1;',f'          if (native_bus_read8(b, 0x{addr:08x}u, &byte_value) != 0) return -3;',f'          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << {bit%8})) ? 0u : 4u));']
   if kind=='bclr_imm_absl':lines.append(f'          if (native_bus_write8((struct t2bus *)b, 0x{addr:08x}u, (uint8_t)(byte_value & ~(1u << {bit%8}))) != 0) return -3;')
   lines.append('          c->cycles += 16u;')
  elif kind=='movel_absl_predec':
   reg,addr=args
   lines += [f'          if (!match32(b, 0x{pc+2:x}u, 0x{addr:08x}u)) return -1;',f'          {{ uint32_t val; if (native_bus_read32(b, 0x{addr:08x}u, &val) != 0) return -3;',f'            c->a[{reg}] = (c->a[{reg}] - 4u) & 0xffffffu;',f'            if (native_bus_write32((struct t2bus *)b, c->a[{reg}], val) != 0) return -3;', '            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x80000000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));','          }','          c->cycles += 24u;']
  elif kind=='movew_dn_absl':
   reg,addr=args
   lines += [f'          if (!match32(b, 0x{pc+2:x}u, 0x{addr:08x}u)) return -1;',f'          {{ uint16_t v=(uint16_t)c->d[{reg}];',f'            if (native_bus_write16((struct t2bus *)b,0x{addr:08x}u,v)!=0) return -3;', '            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));','          }','          c->cycles += 16u;']
  elif kind=='cmpw_dn_dn':
   dst,src=args
   lines += [f'          {{ uint32_t x=c->d[{src}]&0xffffu,y=c->d[{dst}]&0xffffu,r=(y-x)&0xffffu;', '            uint16_t f=(uint16_t)(((r&0x8000u)?8u:0u)|((r==0u)?4u:0u)|(((y^x)&(y^r)&0x8000u)?2u:0u)|((x>y)?1u:0u));', '            c->sr=(uint16_t)((c->sr&0xfff0u)|f);','          }','          c->cycles += 4u;']
  elif kind in ('bgt','bpl'):
   target,nxt=args
   if (raw&255)==0:lines.append(f'          if (!match16(b,0x{pc+2:x}u,0x{w(pc+2):04x}u)) return -1;')
   expr='(!(c->sr & 4u) && (!!(c->sr & 8u)==!!(c->sr & 2u)))' if kind=='bgt' else '!(c->sr & 8u)'
   lines += [f'          c->pc=({expr})?0x{target:06x}u:0x{nxt:06x}u;',f'          c->cycles+=({expr})?10u:8u;','          return 0;']
  elif kind=='movew_absl_dn':
   reg,addr=args
   lines += [f'          if (!match32(b, 0x{pc+2:x}u, 0x{addr:08x}u)) return -1;',f'          {{ uint16_t val; if (native_bus_read16(b, 0x{addr:08x}u, &val) != 0) return -3;',f'            c->d[{reg}] = (c->d[{reg}] & 0xffff0000u) | val;', '            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));','          }','          c->cycles += 16u;']
  elif kind=='movew_absl_absl':
   source,dest=args
   lines += [f'          if (!match32(b, 0x{pc+2:x}u, 0x{source:08x}u) || !match32(b, 0x{pc+6:x}u, 0x{dest:08x}u)) return -1;',f'          {{ uint16_t val; if (native_bus_read16(b, 0x{source:08x}u, &val) != 0) return -3;',f'            if (native_bus_write16((struct t2bus *)b, 0x{dest:08x}u, val) != 0) return -3;', '            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));','          }','          c->cycles += 28u;']
  elif kind=='sne_absl':
   addr,=args
   lines += [f'          if (!match32(b, 0x{pc+2:x}u, 0x{addr:08x}u)) return -1;',
             f'          if (native_bus_write8((struct t2bus *)b, 0x{addr:08x}u, (c->sr & 4u) ? 0u : 0xffu) != 0) return -3;',
             '          c->cycles += 16u;']
  elif kind=='movel_imm_dn':
   reg,imm=args
   lines += [f'          if (!match32(b, 0x{pc+2:x}u, 0x{imm:08x}u)) return -1;',f'          c->d[{reg}] = 0x{imm:08x}u;',f'          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x{imm:08x}u & 0x80000000u) ? 8u : 0u) | (0x{imm:08x}u == 0u ? 4u : 0u));','          c->cycles += 12u;']
  elif kind=='movew_imm_absl':
   imm,addr=args
   lines += [f'          if (!match16(b, 0x{pc+2:x}u, 0x{imm:04x}u) || !match32(b, 0x{pc+4:x}u, 0x{addr:08x}u)) return -1;',f'          if (native_bus_write16((struct t2bus *)b, 0x{addr:08x}u, 0x{imm:04x}u) != 0) return -3;',f'          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x{imm:04x}u & 0x8000u) ? 8u : 0u) | (0x{imm:04x}u == 0u ? 4u : 0u));','          c->cycles += 20u;']
  elif kind=='lea_absw':
   reg,addr,ext=args
   lines += [f'          if (!match16(b, 0x{pc+2:x}u, 0x{ext:04x}u)) return -1;',f'          c->a[{reg}] = 0x{addr:06x}u;','          c->cycles += 8u;']
  elif kind=='movel_an_absl':
   reg,addr=args
   lines += [f'          if (!match32(b, 0x{pc+2:x}u, 0x{addr:08x}u)) return -1;',f'          if (native_bus_write32((struct t2bus *)b, 0x{addr:08x}u, c->a[{reg}]) != 0) return -3;',f'          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->a[{reg}] & 0x80000000u) ? 8u : 0u) | (c->a[{reg}] == 0u ? 4u : 0u));','          c->cycles += 20u;']
  elif kind=='moveb_imm_postinc':
   areg,imm=args
   lines += [f'          if (!match16(b, 0x{pc+2:x}u, 0x{imm:04x}u)) return -1;',
             f'          if (native_bus_write8((struct t2bus *)b, c->a[{areg}] & 0xffffffu, 0x{imm&255:02x}u) != 0)',
             f'            {{ printf("T2GEN V0.71 WRITE_FAULT: PC={pc:06x} opcode={raw:04x} EA=A{areg} addr=%06lx size=B value={imm&255:02x} D0=%08lx A0=%08lx A4=%08lx A7=%06lx SR=%04x\\n", (unsigned long)(c->a[{areg}] & 0xffffffu), (unsigned long)c->d[0], (unsigned long)c->a[0], (unsigned long)c->a[4], (unsigned long)c->a[7], (unsigned)c->sr); return -3; }}',
             f'          c->a[{areg}] = (c->a[{areg}] + {2 if areg==7 else 1}u) & 0xffffffu;',
             f'          c->sr = (uint16_t)((c->sr & 0xfff0u) | {(8 if imm&128 else 0) | (4 if (imm&255)==0 else 0)}u);',
             '          c->cycles += 12u;']
  elif kind=='rte':
   lines += ['          { uint16_t old_sr; uint32_t old_pc;',
             '            if (!(c->sr & 0x2000u)) return -3;',
             '            if (native_bus_read16(b, c->a[7], &old_sr) || native_bus_read32(b, c->a[7]+2u, &old_pc)) return -3;',
             '            c->a[7] = (c->a[7] + 6u) & 0xffffffu;',
             '            if (!(old_sr & 0x2000u)) { uint32_t ssp=c->a[7]; c->a[7]=c->usp; c->usp=ssp; }',
             '            c->sr = old_sr; c->pc = old_pc & 0xffffffu; c->cycles += 20u;',
             '            printf("T2GEN V0.93 RTE: pc=%06lx SR=%04x\\n", (unsigned long)c->pc, (unsigned)c->sr);',
             '          }', '          return 0;']
  elif kind=='rts':
   lines += ['          { uint32_t return_pc;',
             '            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;',
             '            c->a[7] = (c->a[7] + 4u) & 0xffffffu;',
             '            c->pc = return_pc & 0xffffffu;',
             '            c->cycles += 16u;', '          }', '          return 0;']
  elif kind=='bpl_w':
   target,nxt,ext=args
   lines += [f'          if (!match16(b, 0x{pc+2:x}u, 0x{ext:04x}u)) return -1;',
             f'          c->pc = (c->sr & 8u) ? 0x{nxt:06x}u : 0x{target:06x}u;',
             '          c->cycles += 10u;', '          return 0;']
  elif kind=='jmp_absw':
   target,ext=args
   lines += [f'          if (!match16(b, 0x{pc+2:x}u, 0x{ext:04x}u)) return -1;',
             f'          c->pc = 0x{target:06x}u;', '          c->cycles += 10u;', '          return 0;']
  elif kind=='jmp_absl':
   target,=args
   lines += [f'          if (!match32(b, 0x{pc+2:x}u, 0x{target:08x}u)) return -1;',
             f'          c->pc = 0x{target:06x}u;', '          c->cycles += 12u;', '          return 0;']
  elif kind=='movel_imm_absl':
   imm,addr=args
   lines += [f'          if (!match32(b, 0x{pc+2:x}u, 0x{imm:08x}u) || !match32(b, 0x{pc+6:x}u, 0x{addr:08x}u)) return -1;',
             f'          if (native_bus_write32((struct t2bus *)b, 0x{addr:08x}u, 0x{imm:08x}u) != 0)',
             f'            {{ printf("T2GEN V0.67 WRITE32_STOP: pc={pc:06x} addr={addr:08x} value={imm:08x}\\n"); return -3; }}',
             f'          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x{imm:08x}u & 0x80000000u) ? 8u : 0u) | (0x{imm:08x}u == 0u ? 4u : 0u));',
             '          c->cycles += 28u;']
  elif kind in ('mulu_dn','muls_dn'):
   dst,src=args
   if kind=='mulu_dn':
    lines += [f'          c->d[{dst}] = (uint32_t)((c->d[{dst}] & 0xffffu) * (c->d[{src}] & 0xffffu));']
   else:
    lines += [f'          c->d[{dst}] = (uint32_t)((int32_t)(int16_t)c->d[{dst}] * (int32_t)(int16_t)c->d[{src}]);']
   lines += [f'          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[{dst}] & 0x80000000u) ? 8u : 0u) | (c->d[{dst}] == 0u ? 4u : 0u));','          c->cycles += 70u;']
  elif kind=='movew_dn_dn':
   dst,src=args
   lines += [f'          {{ uint16_t v=(uint16_t)c->d[{src}]; c->d[{dst}]=(c->d[{dst}] & 0xffff0000u) | v;', '            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }','          c->cycles += 4u;']
  elif kind=='andi_w_dn':
   reg,imm=args
   lines += [f'          if (!match16(b, 0x{pc+2:x}u, 0x{imm:04x}u)) return -1;',f'          {{ uint16_t v=(uint16_t)c->d[{reg}] & 0x{imm:04x}u; c->d[{reg}]=(c->d[{reg}] & 0xffff0000u) | v;', '            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }','          c->cycles += 8u;']
  elif kind=='movea_absl':
   reg,addr=args
   lines += [f'          if (!match32(b, 0x{pc+2:x}u, 0x{addr:08x}u)) return -1;',f'          if (native_bus_read32(b, 0x{addr:08x}u, &c->a[{reg}]) != 0) return -3;','          c->cycles += 20u;']
  elif kind=='moveq':
   reg,imm=args;lines += [f'          c->d[{reg}] = (uint32_t)(int32_t)({imm});',f'          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[{reg}] & 0x80000000u) ? 8u : 0u) | (c->d[{reg}] == 0u ? 4u : 0u));','          c->cycles += 4u;']
  elif kind=='btst_dn_ind':
   dreg,areg=args
   lines += [f'          if (native_bus_read8(b, c->a[{areg}], &byte_value) != 0) {{ printf("T2GEN V0.57 BTST_READ_STOP: pc={pc:06x} addr=%06lx\\n", (unsigned long)c->a[{areg}]); return -3; }}',
             f'          {{ uint8_t bit = (uint8_t)(c->d[{dreg}] & 7u);',
             '            c->sr = (uint16_t)((c->sr & (uint16_t)~4u) | ((byte_value & (1u << bit)) ? 0u : 4u));',
             f'            if (c->a[{areg}] == 0xa11100u) printf("T2GEN V0.57 BUSREQ_POLL: pc={pc:06x} value=%02x bit=%u z=%u\\n", (unsigned)byte_value, (unsigned)bit, (unsigned)((c->sr & 4u) != 0u));',
             '          }', '          c->cycles += 8u;']
  elif kind=='lsrb_imm':
   reg,count=args
   lines += [f'          {{ uint32_t old = c->d[{reg}] & 255u;',
             f'            uint32_t carry = (old >> {count-1}) & 1u;',
             f'            uint32_t result = old >> {count};',
             f'            c->d[{reg}] = (c->d[{reg}] & 0xffffff00u) | result;',
             '            c->sr = (uint16_t)((c->sr & 0xffe0u) | (carry ? 0x11u : 0u) | (result == 0u ? 4u : 0u) | (result & 0x80u ? 8u : 0u));',
             '            c->cycles += 6u + 2u * '+str(count)+'u;', '          }']
  elif kind=='lea_pc_disp':
   reg,disp,ext=args
   lines += [f'          if (!match16(b, 0x{pc+2:x}u, 0x{ext:04x}u)) return -1;',
             f'          c->a[{reg}] = 0x{(pc+2+disp)&0xffffff:06x}u;', '          c->cycles += 8u;']
  elif kind=='moveb_a0_d0_index':
   reg,disp,ext=args
   lines += [f'          if (!match16(b, 0x{pc+2:x}u, 0x{ext:04x}u)) return -1;',
             f'          {{ uint32_t addr = (c->a[0] + (uint32_t)(int32_t)(int16_t)c->d[0] + (uint32_t)({disp})) & 0xffffffu;',
             f'            if (native_bus_read8(b, addr, &byte_value) != 0) {{ printf("T2GEN V0.65 INDEX_READ_STOP: pc={pc:06x} addr=%06lx\\n", (unsigned long)addr); return -3; }}',
             f'            c->d[{reg}] = (c->d[{reg}] & 0xffffff00u) | byte_value;',
             '            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 128u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));',
             '            c->cycles += 14u;', '          }']
  elif kind=='tstb_dn':
   reg,=args
   lines += [f'          {{ uint8_t v = (uint8_t)c->d[{reg}];',
             '            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 128u) ? 8u : 0u) | (v == 0u ? 4u : 0u));',
             '            c->cycles += 4u;', '          }']
  elif kind=='lea_absl':
   reg,addr=args
   lines += [f'          if (!match32(b, 0x{pc+2:x}u, 0x{addr:08x}u)) return -1;',
             f'          c->a[{reg}] = 0x{addr:08x}u;', '          c->cycles += 12u;']
  elif kind=='movew_imm_dn':
   reg,imm=args
   lines += [f'          if (!match16(b, 0x{pc+2:x}u, 0x{imm:04x}u)) return -1;',
             f'          c->d[{reg}] = (c->d[{reg}] & 0xffff0000u) | 0x{imm:04x}u;',
             f'          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x{imm:04x}u & 0x8000u) ? 8u : 0u) | (0x{imm:04x}u == 0u ? 4u : 0u));',
             '          c->cycles += 8u;']
  elif kind=='cmpb_ind_dn':
   reg,areg=args
   lines += [f'          if (native_bus_read8(b, c->a[{areg}], &byte_value) != 0) return -3;',
             f'          {{ uint32_t x = c->d[{reg}] & 255u, y = byte_value, r = (x-y) & 255u;',
             '            uint16_t flags = (uint16_t)((r & 128u ? 8u : 0u) | (r == 0u ? 4u : 0u) | (((x ^ y) & (r ^ x) & 128u) ? 2u : 0u) | (y > x ? 1u : 0u));',
             '            c->sr = (uint16_t)((c->sr & 0xfff0u) | flags);',
             '          }', '          c->cycles += 8u;']
  elif kind=='addq_w_an':
   reg,count=args
   lines += [f'          c->a[{reg}] += {count}u;', '          c->cycles += 8u;']
  elif kind=='addq_l_an':
   reg,count=args
   lines += [f'          c->a[{reg}] = (c->a[{reg}] + {count}u) & 0xffffffu;', '          c->cycles += 8u;']
  elif kind=='tstw_absl':
   addr,=args
   lines += [f'          if (!match32(b, 0x{pc+2:x}u, 0x{addr:08x}u)) return -1;',
             '          { uint16_t v;',
             f'            if (native_bus_read16(b, 0x{addr:08x}u, &v) != 0) return -3;',
             '            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));',
             '            c->cycles += 16u;', '          }']
  elif kind=='clrl_d0':
   lines += ['          c->d[0] = 0u;', '          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);', '          c->cycles += 6u;']
  elif kind=='moveb_absl_d0':
   addr,=args
   lines += [f'          if (!match32(b, 0x{pc+2:x}u, 0x{addr:08x}u)) return -1;',
             f'          if (native_bus_read8(b, 0x{addr:08x}u, &byte_value) != 0) return -3;',
             '          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;',
             '          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 0x80u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));',
             '          c->cycles += 16u;']
  elif kind=='movem_postinc_regs':
   areg,mask,size=args
   lines += [f'          if (!match16(b, 0x{pc+2:x}u, 0x{mask:04x}u)) return -1;',
             f'          {{ uint32_t addr = c->a[{areg}]; uint32_t val; uint16_t word; unsigned idx;',
             '            for (idx = 0; idx < 16u; ++idx)',
             '              {',
             f'                if (!(0x{mask:04x}u & (1u << idx))) continue;']
   if size==4:
    lines += ['                if (native_bus_read32(b, addr, &val) != 0) return -3;']
   else:
    lines += ['                if (native_bus_read16(b, addr, &word) != 0) return -3;',
              '                val = (uint32_t)(int32_t)(int16_t)word;']
   lines += ['                if (idx < 8u) c->d[idx] = val;',
             '                else c->a[idx - 8u] = val;',
             f'                addr = (addr + {size}u) & 0xffffffu;',
             '              }',
             f'            c->a[{areg}] = addr; /* postincrement wins if base An is in mask */',
             '          }',
             f'          c->cycles += {8+4*mask.bit_count() if size==2 else 8+8*mask.bit_count()}u;']
  elif kind=='moveml_ind_regs':
   areg,mask=args
   lines += [f'          if (!match16(b, 0x{pc+2:x}u, 0x{mask:04x}u)) return -1;',
             f'          {{ uint32_t base = c->a[{areg}], val; unsigned idx;',
             '            for (idx = 0; idx < 16u; ++idx)',
             '              {',
             f'                if ((0x{mask:04x}u & (1u << idx)) == 0u) continue;',
             '                if (native_bus_read32(b, base, &val) != 0)',
             f'                  {{ printf("T2GEN V0.63 MOVEM_READ_STOP: pc={pc:06x} addr=%06lx\\n", (unsigned long)base); return -3; }}',
             '                if (idx < 8u) c->d[idx] = val;',
             '                else c->a[idx - 8u] = val;',
             '                base = (base + 4u) & 0xffffffu;',
             '              }',
             '          }',
             f'          c->cycles += 12u + 8u * {mask.bit_count()}u;']
  elif kind=='move_imm_sr':
   imm,=args
   lines += [f'          if (!match16(b, 0x{pc+2:x}u, 0x{imm:04x}u)) return -1;',
             '          if (!(c->sr & 0x2000u)) return -3;',
             f'          c->sr = 0x{imm:04x}u;',
             '          c->cycles += 12u;']
  elif kind=='movel_dn_predec':
   areg,dreg=args
   lines += [f'          {{ uint32_t dest = (c->a[{areg}] - 4u) & 0xffffffu;',f'            c->a[{areg}] = dest;',f'            if (native_bus_write32((struct t2bus *)b, dest, c->d[{dreg}]) != 0) {{ printf("T2GEN V0.58 WRITE32_STOP: pc={pc:06x} addr=%06lx\\n", (unsigned long)dest); return -3; }}', '            c->cycles += 12u;', '          }']
  elif kind=='moveb_postinc_postinc':
   dstreg,srcreg=args
   lines += [f'          {{ uint32_t source = c->a[{srcreg}], dest = c->a[{dstreg}];',
             f'            if (native_bus_read8(b, source, &byte_value) != 0) {{ printf("T2GEN V0.57 COPY_READ_STOP: pc={pc:06x} addr=%06lx\\n", (unsigned long)source); return -3; }}',
             f'            if (native_bus_write8((struct t2bus *)b, dest, byte_value) != 0) {{ printf("T2GEN V0.57 COPY_WRITE_STOP: pc={pc:06x} addr=%06lx\\n", (unsigned long)dest); return -3; }}',
             f'            c->a[{srcreg}] = (source + {2 if srcreg==7 else 1}u) & 0xffffffu;',
             f'            c->a[{dstreg}] = (dest + {2 if dstreg==7 else 1}u) & 0xffffffu;',
             '            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 128u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));',
             '          }', '          c->cycles += 12u;']
  elif kind=='moveb_postinc_disp':
   dstreg,srcreg,disp,ext=args
   lines += [f'          if (!match16(b, 0x{pc+2:x}u, 0x{ext:04x}u)) return -1;',
             f'          if (native_bus_read8(b, c->a[{srcreg}], &byte_value) != 0) return -3;',
             f'          if (native_bus_write8((struct t2bus *)b, (c->a[{dstreg}] + (uint32_t)({disp})) & 0xffffffu, byte_value) != 0) return -3;',
             f'          c->a[{srcreg}] = (c->a[{srcreg}] + {2 if srcreg==7 else 1}u) & 0xffffffu;',
             '          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 128u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));',
             '          c->cycles += 16u;']
  elif kind=='moveb_postinc':
   dreg,areg=args
   lines += [f'          if (native_bus_read8(b, c->a[{areg}], &byte_value) != 0) return -3;',f'          c->a[{areg}] = (c->a[{areg}] + {2 if areg==7 else 1}u) & 0xffffffu;',f'          c->d[{dreg}] = (c->d[{dreg}] & 0xffffff00u) | byte_value;',f'          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 128u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));','          c->cycles += 8u;']
  elif kind=='movel_dn_ind':
   areg,dreg=args
   lines += [f'          if (native_bus_write32((struct t2bus *)b, c->a[{areg}], c->d[{dreg}]) != 0) {{ printf("T2GEN V0.60 WRITE32_STOP: pc={pc:06x} addr=%06lx\\n", (unsigned long)c->a[{areg}]); return -3; }}', '          c->cycles += 12u;']
  elif kind=='movel_postinc_ind':
   areg,sreg=args
   lines += [f'          {{ uint32_t long_value; uint32_t source = c->a[{sreg}];',f'            if (native_bus_read32(b, source, &long_value) != 0) {{ printf("T2GEN V0.57 READ32_STOP: pc={pc:06x} addr=%06lx\\n", (unsigned long)source); return -3; }}',f'            if (native_bus_write32((struct t2bus *)b, c->a[{areg}], long_value) != 0) {{ printf("T2GEN V0.57 WRITE32_STOP: pc={pc:06x} addr=%06lx value=%08lx\\n", (unsigned long)c->a[{areg}], (unsigned long)long_value); return -3; }}',f'            c->a[{sreg}] = (source + 4u) & 0xffffffu;',f'            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));', '          }','          c->cycles += 20u;']
  elif kind=='movew_dn_ind':
   areg,dreg=args
   lines += [f'          if (native_bus_write16((struct t2bus *)b, c->a[{areg}], (uint16_t)c->d[{dreg}]) != 0) {{ printf("T2GEN V0.57 WRITE16_STOP: pc={pc:06x} addr=%06lx\\n", (unsigned long)c->a[{areg}]); return -3; }}','          c->cycles += 8u;']
  elif kind=='addw_dn':
   dreg,sreg=args
   lines += [f'          {{ uint32_t x = c->d[{sreg}] & 65535u, y = c->d[{dreg}] & 65535u, r = (x+y) & 65535u;',f'            uint16_t flags = (uint16_t)(((r & 0x8000u) ? 8u : 0u) | ((r == 0u) ? 4u : 0u) | (((~(x ^ y) & (r ^ y)) & 0x8000u) ? 2u : 0u) | ((x+y > 65535u) ? 17u : 0u));',f'            c->d[{dreg}] = (c->d[{dreg}] & 0xffff0000u) | r;', '            c->sr = (uint16_t)((c->sr & 0xffe0u) | flags);', '          }','          c->cycles += 4u;']
  elif kind=='dbf':
   reg,target,nxt=args
   lines += [f'          {{ uint16_t count = (uint16_t)(c->d[{reg}] - 1u);',f'            c->d[{reg}] = (c->d[{reg}] & 0xffff0000u) | count;',f'            c->pc = (count != 0xffffu) ? 0x{target:06x}u : 0x{nxt:06x}u;', '            c->cycles += (count != 0xffffu) ? 10u : 14u;', '          }','          return 0;']
  elif kind=='andi_b':
   reg,imm=args;lines += [f'          if (!match16(b, 0x{pc+2:x}u, 0x{imm:04x}u)) return -1;',f'          c->d[{reg}] = (c->d[{reg}] & 0xffffff00u) | ((c->d[{reg}] & 255u) & 0x{imm&255:02x}u);',f'          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[{reg}] & 0x80u) ? 8u : 0u) | ((c->d[{reg}] & 255u) == 0u ? 4u : 0u));','          c->cycles += 8u;']
  elif kind=='moveb_disp':
   reg,areg,disp=args; ext=w(pc+2)
   lines += [f'          if (!match16(b, 0x{pc+2:x}u, 0x{ext:04x}u)) return -1;',f'          if (native_bus_read8(b, (c->a[{areg}] + (uint32_t)({disp})) & 0xffffffu, &byte_value) != 0)', '            {',f'              printf("T2GEN V0.57 BUS_STOP: pc={pc:06x} addr=%06lx\\n", (unsigned long)((c->a[{areg}] + (uint32_t)({disp})) & 0xffffffu));','              return -3;','            }',f'          c->d[{reg}] = (c->d[{reg}] & 0xffffff00u) | byte_value;',f'          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 0x80u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));','          c->cycles += 12u;']
  elif kind=='movel_imm_disp':
   areg,imm,disp=args
   lines += [f'          if (!match32(b, 0x{pc+2:x}u, 0x{imm:08x}u) || !match16(b, 0x{pc+6:x}u, 0x{w(pc+6):04x}u)) return -1;',f'          if (native_bus_write32((struct t2bus *)b, (c->a[{areg}] + (uint32_t)({disp})) & 0xffffffu, 0x{imm:08x}u) != 0) return -3;',f'          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x{imm:08x}u & 0x80000000u) ? 8u : 0u) | (0x{imm:08x}u == 0u ? 4u : 0u));','          c->cycles += 28u;']
  elif kind=='movew_ind':
   dreg,areg=args
   lines += [f'          {{ uint16_t v; if (native_bus_read16(b, c->a[{areg}], &v) != 0) {{ printf("T2GEN V0.57 READ16_STOP: pc={pc:06x} addr=%06lx\\n", (unsigned long)c->a[{areg}]); return -3; }}',f'            c->d[{dreg}] = (c->d[{dreg}] & 0xffff0000u) | v;',f'            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));','          }','          c->cycles += 8u;']
  elif kind=='movea_l_dn':
   areg,dreg=args;lines += [f'          c->a[{areg}] = c->d[{dreg}];','          c->cycles += 4u;']
  elif kind=='v90_bset_dn':
   reg,bit=args;lines += [f'          if(!match16(b,0x{pc+2:x}u,0x{w(pc+2):04x}u))return -1;',f'          c->sr=(uint16_t)((c->sr&~4u)|((c->d[{reg}]&(1u<<{bit}))?0u:4u));',f'          c->d[{reg}]|=(1u<<{bit});','          c->cycles+=12u;']
  elif kind=='v90_notw':
   reg,=args;lines += [f'          {{ uint16_t v=(uint16_t)~c->d[{reg}];',f'            c->d[{reg}]=(c->d[{reg}]&0xffff0000u)|v;', '            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }','          c->cycles+=4u;']
  elif kind=='v90_aslw':
   reg,count=args;lines += [f'          {{ uint32_t v=c->d[{reg}]&65535u; uint16_t carry=0,overflow=0; unsigned i;',f'            for(i=0;i<{count}u;i++){{uint32_t n=(v<<1)&65535u;carry=(v>>15)&1u;if((v^n)&0x8000u)overflow=2u;v=n;}}',f'            c->d[{reg}]=(c->d[{reg}]&0xffff0000u)|v;', '            c->sr=(uint16_t)((c->sr&0xffe0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)|overflow|(carry?17u:0u)); }',f'          c->cycles+={6+2*count}u;']
  elif kind=='v90_lslw_reg':
   reg,creg=args;lines += [f'          {{ unsigned count=c->d[{creg}]&63u,i;uint32_t v=c->d[{reg}]&65535u;uint16_t carry=0;', '            for(i=0;i<count;i++){carry=(v>>15)&1u;v=(v<<1)&65535u;}',f'            c->d[{reg}]=(c->d[{reg}]&0xffff0000u)|v;', '            c->sr=(uint16_t)((c->sr&(count?0xffe0u:0xfff0u))|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)|(count&&carry?17u:0u)); c->cycles+=6u+2u*count; }']
  elif kind=='v90_oriw':
   reg,imm=args;lines += [f'          if(!match16(b,0x{pc+2:x}u,0x{imm:04x}u))return -1;',f'          {{uint16_t v=(uint16_t)(c->d[{reg}]|0x{imm:04x}u);',f'           c->d[{reg}]=(c->d[{reg}]&0xffff0000u)|v;', '           c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }','          c->cycles+=8u;']
  elif kind=='v90_movel_mem_mem':
   src,dst=args;lines += [f'          if(!match32(b,0x{pc+2:x}u,0x{src:08x}u)||!match32(b,0x{pc+6:x}u,0x{dst:08x}u))return -1;',f'          {{uint32_t v;if(native_bus_read32(b,0x{src:08x}u,&v)!=0)return -3;',f'           if(native_bus_write32((struct t2bus *)b,0x{dst:08x}u,v)!=0)return -3;', '           c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }','          c->cycles+=36u;']
  elif kind=='v90_movew_mem_stack':
   addr,=args;lines += [f'          if(!match32(b,0x{pc+2:x}u,0x{addr:08x}u))return -1;',f'          {{uint16_t v;if(native_bus_read16(b,0x{addr:08x}u,&v)!=0)return -3;', '           c->a[7]=(c->a[7]-2u)&0xffffffu;', '           if(native_bus_write16((struct t2bus *)b,c->a[7],v)!=0)return -3;', '           c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }','          c->cycles+=20u;']
  elif kind=='v90_moveb_index':
   dst,areg,ext=args;idx=(ext>>12)&7;is_a=(ext>>15)&1;is_long=(ext>>11)&1;disp=(ext&255)-256 if ext&128 else ext&255
   source=f'c->a[{idx}]' if is_a else f'c->d[{idx}]'
   index=source if is_long else f'(uint32_t)(int32_t)(int16_t){source}'
   lines += [f'          if(!match16(b,0x{pc+2:x}u,0x{ext:04x}u))return -1;',f'          if(native_bus_read8(b,(c->a[{areg}]+({index})+(uint32_t)({disp}))&0xffffffu,&byte_value)!=0)return -3;',f'          c->d[{dst}]=(c->d[{dst}]&0xffffff00u)|byte_value;', '          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&128u)?8u:0u)|(byte_value==0u?4u:0u));','          c->cycles+=14u;']
  elif kind=='v91_st_absl':
   addr,=args
   lines += [f'          if (!match32(b,0x{pc+2:x}u,0x{addr:08x}u)) return -1;',f'          if (native_bus_write8((struct t2bus *)b,0x{addr:08x}u,0xffu)!=0) return -3;', '          c->cycles+=12u;']
  elif kind=='v91_orb_dn':
   dst,src=args
   lines += [f'          {{ uint8_t v=(uint8_t)(c->d[{dst}] | c->d[{src}]);',f'            c->d[{dst}]=(c->d[{dst}]&0xffffff00u)|v;', '            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80u)?8u:0u)|(v==0u?4u:0u)); }','          c->cycles+=4u;']
  elif kind=='v91_swap_dn':
   reg,=args
   lines += [f'          c->d[{reg}]=(c->d[{reg}]<<16)|(c->d[{reg}]>>16);',f'          c->sr=(uint16_t)((c->sr&0xfff0u)|((c->d[{reg}]&0x80000000u)?8u:0u)|(c->d[{reg}]==0u?4u:0u));','          c->cycles+=4u;']
  elif kind=='v91_movel_dn_postinc':
   areg,dreg=args
   lines += [f'          {{uint32_t v=c->d[{dreg}];',f'           if(native_bus_write32((struct t2bus *)b,c->a[{areg}],v)!=0)return -3;',f'           c->a[{areg}]=(c->a[{areg}]+4u)&0xffffffu;', '           c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }','          c->cycles+=12u;']
  elif kind=='v91_addil_absl':
   imm,addr=args
   lines += [f'          if(!match32(b,0x{pc+2:x}u,0x{imm:08x}u)||!match32(b,0x{pc+6:x}u,0x{addr:08x}u))return -1;',f'          {{uint32_t old,r;uint64_t wide;',f'           if(native_bus_read32(b,0x{addr:08x}u,&old)!=0)return -3;',f'           wide=(uint64_t)old+0x{imm:08x}u;r=(uint32_t)wide;',f'           if(native_bus_write32((struct t2bus *)b,0x{addr:08x}u,r)!=0)return -3;',f'           c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x80000000u)?8u:0u)|(r==0u?4u:0u)|((~(old^0x{imm:08x}u)&(r^old)&0x80000000u)?2u:0u)|((wide>>32)?17u:0u)); }}','          c->cycles+=28u;']
  elif kind=='v91_movew_sp_absl':
   addr,=args
   lines += [f'          if(!match32(b,0x{pc+2:x}u,0x{addr:08x}u))return -1;', '          {uint16_t v;', '           if(native_bus_read16(b,c->a[7],&v)!=0)return -3;', '           c->a[7]=(c->a[7]+2u)&0xffffffu;',f'           if(native_bus_write16((struct t2bus *)b,0x{addr:08x}u,v)!=0)return -3;', '           c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }','          c->cycles+=20u;']
  elif kind=='v95_andiw_absl':
   imm,addr=args
   lines += [f'          if (!match16(b,0x{pc+2:x}u,0x{imm:04x}u)||!match32(b,0x{pc+4:x}u,0x{addr:08x}u))return -1;',f'          {{uint16_t v,r; if(native_bus_read16(b,0x{addr:08x}u,&v))return -3; r=v&0x{imm:04x}u; if(native_bus_write16((struct t2bus *)b,0x{addr:08x}u,r))return -3; c->sr=(c->sr&0xfff0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u);}}','          c->cycles+=20u;']
  elif kind=='v95_movel_disp_dn':
   dn,an,disp=args
   lines += [f'          if(!match16(b,0x{pc+2:x}u,0x{disp:04x}u))return -1;',f'          {{uint32_t v,addr=(c->a[{an}]+(int16_t)0x{disp:04x}u)&0xffffffu; if(native_bus_read32(b,addr,&v))return -3; c->d[{dn}]=v; c->sr=(c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u);}}','          c->cycles+=16u;']
  elif kind=='v95_tstw_an':
   an,=args
   lines += [f'          {{uint16_t v; if(native_bus_read16(b,c->a[{an}],&v))return -3; c->sr=(c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u);}}','          c->cycles+=8u;']
  elif kind=='v95_cmpi_w_dn':
   dn,imm=args
   lines += [f'          if(!match16(b,0x{pc+2:x}u,0x{imm:04x}u))return -1;',f'          {{uint32_t x=c->d[{dn}]&65535u,y=0x{imm:04x}u,r=(x-y)&65535u; c->sr=(c->sr&0xfff0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u)|(((x^y)&(x^r)&0x8000u)?2u:0u)|(x<y?1u:0u);}}','          c->cycles+=8u;']
  elif kind=='v95_mulu_imm':
   dn,imm=args
   lines += [f'          if(!match16(b,0x{pc+2:x}u,0x{imm:04x}u))return -1;',f'          {{uint32_t r=(c->d[{dn}]&65535u)*0x{imm:04x}u; c->d[{dn}]=r; c->sr=(c->sr&0xfff0u)|((r&0x80000000u)?8u:0u)|(r==0u?4u:0u);}}','          c->cycles+=70u;']
  elif kind=='v95_addaw_dn':
   an,dn=args
   lines += [f'          c->a[{an}]=(c->a[{an}]+(int16_t)(c->d[{dn}]&65535u))&0xffffffu;','          c->cycles+=8u;']
  elif kind=='v95_clrb_postinc':
   an,=args
   lines += [f'          if(native_bus_write8((struct t2bus *)b,c->a[{an}],0u))return -3;',f'          c->a[{an}]=(c->a[{an}]+{2 if an==7 else 1}u)&0xffffffu;','          c->sr=(c->sr&0xfff0u)|4u; c->cycles+=12u;']
  elif kind=='v95_andb_dn_absl':
   dn,addr=args
   lines += [f'          if(!match32(b,0x{pc+2:x}u,0x{addr:08x}u))return -1;',f'          {{uint8_t v,r; if(native_bus_read8(b,0x{addr:08x}u,&v))return -3; r=v&(uint8_t)c->d[{dn}]; if(native_bus_write8((struct t2bus *)b,0x{addr:08x}u,r))return -3; c->sr=(c->sr&0xfff0u)|((r&128u)?8u:0u)|(r==0u?4u:0u);}}','          c->cycles+=20u;']
  elif kind.startswith('v97_'):
   def add(*x): lines.extend(x)
   if kind=='v97_movea_index':
    dst,an,ext=args;ix=(ext>>12)&7;is_a=bool(ext&0x8000);is_l=bool(ext&0x0800);disp=ext&255
    val=f'c->{"a" if is_a else "d"}[{ix}]';idx=val if is_l else f'(int32_t)(int16_t)({val}&65535u)'
    if pc==0x9442:
     add(f'          printf("T2GEN V0.99 IDX_MOVEA: pc=009442 base=%06lx index=%08lx disp=%d ea=%06lx\\n",(unsigned long)c->a[{an}],(unsigned long)({idx}),(int)(int8_t)0x{disp:02x}u,(unsigned long)((c->a[{an}]+({idx})+(int8_t)0x{disp:02x}u)&0xffffffu));')
    add(f'          {{uint32_t ea=(c->a[{an}]+({idx})+(int8_t)0x{disp:02x}u)&0xffffffu,v;if(native_bus_read32(b,ea,&v))return -3;c->a[{dst}]=v&0xffffffu;}}','          c->cycles+=18u;')
    if pc==0x9442:
     add('          printf("T2GEN V0.99 IDX_MOVEA_RESULT: A1=%06lx\\n",(unsigned long)c->a[1]);')
   elif kind=='v97_moveb_abs_abs':
    src,dst=args;add(f'          {{uint8_t v;if(native_bus_read8(b,0x{src:x}u,&v)||native_bus_write8((struct t2bus *)b,0x{dst:x}u,v))return -3;c->sr=(c->sr&0xfff0u)|((v&128u)?8u:0u)|(v==0u?4u:0u);}}','          c->cycles+=28u;')
   elif kind=='v97_movew_disp_abs':
    an,disp,dst=args;add(f'          {{uint16_t v;uint32_t a=(c->a[{an}]+(int16_t)0x{disp:04x}u)&0xffffffu;if(native_bus_read16(b,a,&v)||native_bus_write16((struct t2bus *)b,0x{dst:x}u,v))return -3;c->sr=(c->sr&0xfff0u)|((v&32768u)?8u:0u)|(v==0u?4u:0u);}}','          c->cycles+=24u;')
   elif kind=='v97_addl_dn_abs':
    dn,dst=args;add(f'          {{uint32_t x,y=c->d[{dn}],r;uint64_t wide;if(native_bus_read32(b,0x{dst:x}u,&x))return -3;wide=(uint64_t)x+y;r=(uint32_t)wide;if(native_bus_write32((struct t2bus *)b,0x{dst:x}u,r))return -3;c->sr=(c->sr&0xffe0u)|((r&0x80000000u)?8u:0u)|(r==0u?4u:0u)|((~(x^y)&(x^r)&0x80000000u)?2u:0u)|((wide>>32)?17u:0u);}}','          c->cycles+=24u;')
   elif kind=='v97_movel_index_abs':
    an,ext,dst=args
    ix=(ext>>12)&7;is_a=bool(ext&0x8000);is_l=bool(ext&0x0800);disp=ext&255
    val=f'c->{"a" if is_a else "d"}[{ix}]';idx=val if is_l else f'(int32_t)(int16_t)({val}&65535u)'
    if pc==0x9436:
     add(f'          printf("T2GEN V0.99 IDX_MOVE: pc=009436 base=%06lx index=%08lx disp=%d ea=%06lx\\n",(unsigned long)c->a[{an}],(unsigned long)({idx}),(int)(int8_t)0x{disp:02x}u,(unsigned long)((c->a[{an}]+({idx})+(int8_t)0x{disp:02x}u)&0xffffffu));')
    add(f'          {{uint32_t ea=(c->a[{an}]+({idx})+(int8_t)0x{disp:02x}u)&0xffffffu,v;if(native_bus_read32(b,ea,&v)||native_bus_write32((struct t2bus *)b,0x{dst:x}u,v))return -3;c->sr=(c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u);}}','          c->cycles+=28u;')
    if pc==0x9436:
     add('          {uint32_t v=0;native_bus_read32(b,0xff023cu,&v);printf("T2GEN V0.99 IDX_MOVE_RESULT: FF023C=%08lx\\n",(unsigned long)v);}')
   elif kind=='v97_asrw2':
    dn,=args;add(f'          {{uint16_t x=(uint16_t)c->d[{dn}],r=(uint16_t)((int16_t)x>>2),carry=(x>>1)&1u;c->d[{dn}]=(c->d[{dn}]&0xffff0000u)|r;c->sr=(c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(carry?17u:0u);}}','          c->cycles+=10u;')
   elif kind=='v97_subaw_dn':
    an,dn=args;add(f'          c->a[{an}]=(c->a[{an}]-(int32_t)(int16_t)c->d[{dn}])&0xffffffu;','          c->cycles+=8u;')
   elif kind=='v97_addaw_imm':
    an,imm=args;add(f'          c->a[{an}]=(c->a[{an}]+(int16_t)0x{imm:04x}u)&0xffffffu;','          c->cycles+=8u;')
   elif kind=='v97_movew_post_abs':
    an,dst=args;add(f'          {{uint16_t v;if(native_bus_read16(b,c->a[{an}],&v))return -3;c->a[{an}]=(c->a[{an}]+2u)&0xffffffu;if(native_bus_write16((struct t2bus *)b,0x{dst:x}u,v))return -3;c->sr=(c->sr&0xfff0u)|((v&32768u)?8u:0u)|(v==0u?4u:0u);}}','          c->cycles+=20u;')
   elif kind=='v97_movel_post_post':
    dst,src=args;add(f'          {{uint32_t v;if(native_bus_read32(b,c->a[{src}],&v))return -3;c->a[{src}]=(c->a[{src}]+4u)&0xffffffu;if(native_bus_write32((struct t2bus *)b,c->a[{dst}],v))return -3;c->a[{dst}]=(c->a[{dst}]+4u)&0xffffffu;c->sr=(c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u);}}','          c->cycles+=20u;')
   elif kind=='v97_lea_disp':
    an,disp=args;add(f'          c->a[7]=(c->a[{an}]+(int16_t)0x{disp:04x}u)&0xffffffu;','          c->cycles+=8u;')
   elif kind=='v97_movew_imm_post':
    an,imm=args;add(f'          if(native_bus_write16((struct t2bus *)b,c->a[{an}],0x{imm:04x}u))return -3;',f'          c->a[{an}]=(c->a[{an}]+2u)&0xffffffu;',f'          c->sr=(c->sr&0xfff0u)|{8 if imm&32768 else 0}u|{4 if imm==0 else 0}u;','          c->cycles+=12u;')
   elif kind=='v97_moveb_dn_post':
    dst,dn=args;add(f'          {{uint8_t v=(uint8_t)c->d[{dn}];if(native_bus_write8((struct t2bus *)b,c->a[{dst}],v))return -3;c->a[{dst}]=(c->a[{dst}]+{2 if dst==7 else 1}u)&0xffffffu;c->sr=(c->sr&0xfff0u)|((v&128u)?8u:0u)|(v==0u?4u:0u);}}','          c->cycles+=8u;')
  elif kind=='move_usp':
   areg,=args;lines += ['          if (!(c->sr & 0x2000u)) return -3;',f'          /* USP is separately modeled; no A7 swap until supervisor transitions. */',f'          c->usp = c->a[{areg}];','          c->cycles += 4u;']
  elif kind in ('bra','beq','bne','bcs','bcc'):
   target,nxt=args
   if (raw&255)==0: lines.append(f'          if (!match16(b, 0x{pc+2:x}u, 0x{w(pc+2):04x}u)) return -1;')
   expr='1' if kind=='bra' else '(c->sr & 4u)' if kind=='beq' else '(c->sr & 1u)' if kind=='bcs' else '!(c->sr & 1u)' if kind=='bcc' else '!(c->sr & 4u)'
   lines += [f'          c->pc = ({expr}) ? 0x{target:06x}u : 0x{nxt:06x}u;',f'          c->cycles += ({expr}) ? 10u : 8u;','          return 0;']
 if not block['ops'] or block['ops'][-1][0] not in ('bra','beq','bne','bcs','bcc','dbf','jmp_absl','bpl_w','jmp_absw','jsr_absl','jsr_absw','jsr_pcdisp','jsr_an','bsr','rts','bmi','bgt','bpl'):
  lines += [f'          c->pc = 0x{block["stop_pc"]:06x}u;', '          return 0;']
 lines += ['        }']
lines += ['      default: return -2;','    }','}']
# ensure not silently advancing past unsupported instructions: dispatcher will stop at next PC
out=root/'src/t2gen_aot_cfg.inc';out.write_text('\n'.join(lines)+'\n')
report={'rom_crc32':f'{zlib.crc32(b):08x}','entry':f'{a.entry:06x}','blocks':{f'{k:06x}':{'instructions':len(v['ops']),'stop_pc':f'{v["stop_pc"]:06x}','stop_reason':v['reason'],'successors':[f'{x:06x}' for x in v['successors']]} for k,v in sorted(blocks.items())},'errors':errors}
report['unsupported_context']=[{'pc':f'{v["stop_pc"]:06x}', 'opcode':f'{w(v["stop_pc"]):04x}', 'rom_bytes':b[v['stop_pc']:v['stop_pc']+16].hex()} for v in blocks.values() if v['reason'] and v['reason'].startswith('unsupported') and v['stop_pc']+2<=len(b)]
report['summary']={'blocks':len(blocks),'instructions':sum(len(v['ops']) for v in blocks.values()),'unsupported_opcodes':dict(sorted(__import__('collections').Counter(v['reason'] for v in blocks.values() if v['reason'] and v['reason'].startswith('unsupported')).items()))}
(root/'tools/aot_cfg_report.json').write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps(report,indent=2))
