import sys,re,struct,os
from pathlib import Path
import numpy as np
from PIL import Image
import lz4.block
root=Path(__file__).resolve().parents[1]/'src'; host=Path(os.environ.get('T2_VDP_CAPTURE_DIR','/mnt/data/v07host'));sys.path.insert(0,str(host))
from render import render
source=(host/'render.py').read_text();source=source.replace(' # sprite table, Genesis H40: 80 sprites max, 320px offset=128',' # sprite table, Genesis H40: 80 sprites max, 320px offset=128')
start=source.index(' # sprite table, Genesis H40:');end=source.index(' # Genesis CRAM bit positions',start)
source=source[:start]+source[end:]
ns={'__name__':'vdponly'};exec(source,ns)
def rgb332(a):
 a=np.asarray(a,dtype=np.uint16)
 return ((((a[:,:,0]*7+127)//255)<<5)|(((a[:,:,1]*7+127)//255)<<2)|((a[:,:,2]*3+127)//255)).astype(np.uint8)
def vdp(k):
 b=(host/'frames'/f'state_{k:04}.bin').read_bytes();return b[:65536],np.frombuffer(b[65536:65664],dtype='<u2'),b[65744:65768]
def sprites(k):
 v,cram,reg=vdp(k);sat=(reg[5]&127)<<9
 def word(a):return (v[a&65535]<<8)|v[(a+1)&65535]
 idx=0;seen=set();entries=[]
 for _ in range(80):
  if idx in seen:break
  seen.add(idx);o=sat+idx*8;y=(word(o)&1023)-128;x=(word(o+6)&1023)-128;sz=v[(o+2)&65535];link=v[(o+3)&65535]&127;attr=word(o+4)
  if 35<=x<=125 and 125<=y<=215:entries.append((x,y,((sz>>2)&3)+1,(sz&3)+1,attr))
  idx=link
  if idx==0:break
 return v,cram,entries
# Capture T-800 from actual VDP SAT, preserving all per-sprite offsets and tile flip/palette bits.
ids=[700,720,730,740]
frames=[]; x0=48;y0=156;W=56;H=56
for k in ids:
 v,cram,entries=sprites(k)
 rgba=np.zeros((H,W),dtype=np.uint8);mask=np.zeros((H,W),dtype=np.uint8)
 for x,y,tw,th,attr in reversed(entries):
  for ty in range(th):
   for tx in range(tw):
    ti=(attr&2047)+(tw-1-tx if attr&0x0800 else tx)*th+(th-1-ty if attr&0x1000 else ty)
    raw=np.frombuffer(v[ti*32:ti*32+32],dtype=np.uint8).reshape(8,4)
    tile=np.empty((8,8),dtype=np.uint8);tile[:,::2]=raw>>4;tile[:,1::2]=raw&15
    if attr&0x1000:tile=tile[::-1]
    if attr&0x0800:tile=tile[:,::-1]
    for dy in range(8):
     for dx in range(8):
      c=int(tile[dy,dx]);xx=x+tx*8+dx-x0;yy=y+ty*8+dy-y0
      if c and 0<=xx<W and 0<=yy<H:
       rgb=int(cram[((attr>>13)&3)*16+c]);r=((rgb&14)>>1)*255//7;g=((rgb&224)>>5)*255//7;b=((rgb&3584)>>9)*255//7
       rgba[yy,xx]=((r*7+127)//255<<5)|((g*7+127)//255<<2)|((b*3+127)//255);mask[yy,xx]=1
 frames.append((k,rgba,mask))
# use stage plane composition at snapshot 700, HUD from full capture at top.
stage=rgb332(ns['render'](host/'frames/state_0700.bin'))
full=rgb332(render(host/'frames/state_0700.bin'))
stage[:48]=full[:48]
# ensure background not displaying character; VDP plane-only image.
Image.fromarray(stage).resize((640,448),Image.Resampling.NEAREST).save(str(root.parent/'stage_preview.png'))
# Preview sprite frames in grid, nearest neighbour
out=Image.new('RGB',(W*4*3,H*4*3),(20,20,20))
for i,(k,p,m) in enumerate(frames):
 r=((p>>5)&7)*255//7;g=((p>>2)&7)*255//7;b=(p&3)*255//3
 rgb=np.stack((r,g,b),axis=-1).astype(np.uint8);im=Image.fromarray(np.dstack((rgb,m*255)),'RGBA').resize((W*4,H*4),Image.Resampling.NEAREST)
 out.paste(im,((i%3)*W*4,(i//3)*H*4),im)
out.save(str(root.parent/'sprites_preview.png'))
blob=stage.tobytes();comp=lz4.block.compress(blob,store_size=False,mode='high_compression')
raw=b''.join(p.tobytes()+m.tobytes() for _,p,m in frames)
comp_s=lz4.block.compress(raw,store_size=False,mode='high_compression')
def carr(name,data):
 s=f'const uint8_t {name}[] = {{\n';s+=''.join(' '+','.join(f'0x{v:02x}' for v in data[i:i+24])+',\n' for i in range(0,len(data),24));return s+'};\n'
(root/'game_assets.c').write_text('#include <stdint.h>\n#include "game_assets.h"\n'+carr('t2_stage_lz4',comp)+'const unsigned t2_stage_lz4_size=sizeof(t2_stage_lz4);\n'+carr('t2_player_lz4',comp_s)+'const unsigned t2_player_lz4_size=sizeof(t2_player_lz4);\n')
(root/'game_assets.h').write_text(f'''#ifndef T2_GAME_ASSETS_H
#define T2_GAME_ASSETS_H
#include <stdint.h>
#define T2_PLAYER_W {W}
#define T2_PLAYER_H {H}
#define T2_PLAYER_ORIGIN_X {x0+32}
#define T2_PLAYER_ORIGIN_Y {y0}
#define T2_PLAYER_FRAME_COUNT {len(frames)}
#define T2_PLAYER_FRAME_BYTES (T2_PLAYER_W*T2_PLAYER_H*2)
extern const uint8_t t2_stage_lz4[];
extern const unsigned t2_stage_lz4_size;
extern const uint8_t t2_player_lz4[];
extern const unsigned t2_player_lz4_size;
#endif
''')
print('stage compressed',len(comp),'sprite compressed',len(comp_s),'entries',[(k,len(sprites(k)[2])) for k in ids])
