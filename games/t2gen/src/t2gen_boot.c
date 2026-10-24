/* Bounded Genesis reset-flow diagnostic. NOT a complete M68000 emulator. */
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "t2gen_boot.h"
struct bus_s {const uint8_t *rom; size_t size; uint8_t ram[65536]; uint32_t reads, writes, io_reads, vdp_writes, unmapped;};
static uint16_t rd16(struct bus_s *b, uint32_t a)
{
  a &= 0xffffffu; b->reads++;
  if (a < b->size - (b->size != 0) && a+1 < b->size) return (uint16_t)(b->rom[a]<<8|b->rom[a+1]);
  if (a >= 0xff0000u) {uint32_t i=a&65535u; return (uint16_t)(b->ram[i]<<8|b->ram[(i+1)&65535u]);}
  if (a >= 0xa10000u && a <= 0xa1001fu) {b->io_reads++; if (a==0xa10000u) return 0xa0u; return 0;}
  if (a >= 0xc00000u && a <= 0xc0001fu) return 0x3400u; /* illustrative VDP status; not cycle accurate */
  b->unmapped++; return 0xffffu;
}
static uint32_t rd32(struct bus_s *b, uint32_t a) {return ((uint32_t)rd16(b,a)<<16)|rd16(b,a+2);}
static void wr16(struct bus_s *b,uint32_t a,uint16_t v)
{
 a&=0xffffffu; b->writes++;
 if(a>=0xff0000u){uint32_t i=a&65535u;b->ram[i]=(uint8_t)(v>>8);b->ram[(i+1)&65535u]=(uint8_t)v;return;}
 if(a>=0xc00000u&&a<=0xc0001fu){b->vdp_writes++;return;}
 b->unmapped++;
}
void t2gen_boot_probe(const uint8_t *rom, size_t size)
{
 struct bus_s *bp = calloc(1, sizeof(struct bus_s));
 if (bp == NULL) { printf("T2GEN V3: bus allocation failed\n"); return; }
 #define b (*bp)
 b.rom=rom;b.size=size;
 uint32_t sp=rd32(&b,0),pc=rd32(&b,4); bool z=false;
 printf("T2GEN V3: reset SP=%08lx PC=%06lx\n",(unsigned long)sp,(unsigned long)pc);
 printf("T2GEN V3: initial SP is outside Genesis work RAM; stack access not attempted\n");
 for(unsigned step=0;step<64;step++)
 {
  if((pc&1u)||pc+1>=size){printf("T2GEN V3 STOP: invalid instruction PC=%06lx\n",(unsigned long)pc);break;}
  uint32_t at=pc; uint16_t op=rd16(&b,pc);pc+=2;
  if(op==0x4e71){printf("T2GEN STEP %02u: %06lx NOP\n",step,(unsigned long)at);continue;}
  if(op==0x4ab9 || op==0x4a79) {
   uint32_t addr=rd32(&b,pc);pc+=4;
   uint32_t val=op==0x4ab9?rd32(&b,addr):rd16(&b,addr);
   z=op==0x4ab9?(val==0):((uint16_t)val==0);
   printf("T2GEN STEP %02u: %06lx TST.%c $%06lx -> %08lx Z=%u\n",step,(unsigned long)at,op==0x4ab9?'L':'W',(unsigned long)addr,(unsigned long)val,(unsigned)z);
   continue;
  }
  if((op&0xff00u)==0x6600u || (op&0xff00u)==0x6700u || (op&0xff00u)==0x6000u){
   int32_t disp=(int8_t)(op&255u);if((op&255u)==0){disp=(int16_t)rd16(&b,pc);pc+=2;}
   bool take=(op&0xff00u)==0x6000u||((op&0xff00u)==0x6600u?!z:z);
   uint32_t target=(uint32_t)((int32_t)pc+disp);
   printf("T2GEN STEP %02u: %06lx %s target=%06lx taken=%u\n",step,(unsigned long)at,(op&0xff00u)==0x6600u?"BNE":(op&0xff00u)==0x6700u?"BEQ":"BRA",(unsigned long)target,(unsigned)take);
   if(take)pc=target;
   continue;
  }
  printf("T2GEN V3 STOP: unsupported opcode %04x at %06lx (no guessed execution)\n",op,(unsigned long)at);
  break;
 }
 /* Exercise the mapped RAM/VDP writes separately, not as emulated ROM activity. */
 wr16(&b,0xff0000u,0x1234u);
 printf("T2GEN V3 BUS SELFTEST: RAM[FF0000]=%04x expected=1234\n",rd16(&b,0xff0000u));
 printf("T2GEN V3 BUS: reads=%lu writes=%lu io_reads=%lu vdp_writes=%lu unmapped=%lu\n",(unsigned long)b.reads,(unsigned long)b.writes,(unsigned long)b.io_reads,(unsigned long)b.vdp_writes,(unsigned long)b.unmapped);
 printf("T2GEN V3: diagnostic interpreter only; real 68000 core and VDP still required\n");
 free(bp);
 #undef b
}
