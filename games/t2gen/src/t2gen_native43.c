/* V0.43: standalone, Musashi-free ARM Thumb-2 native block executor.
 * Deliberately bounded and fail-closed: NOT a playable full-ROM engine.
 */
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "t2gen_native43.h"

struct cpu43 { uint32_t d[8], a[8], pc; uint16_t sr; uint64_t cycles; };
/* Keep the 64 KiB emulated 68000 RAM off the NuttX task stack. */
struct bus43 { const uint8_t *rom; size_t size; uint8_t *ram; };
static uint16_t rd16(struct bus43 *b,uint32_t addr)
{
  addr &= 0xffffffu;
  if (addr < b->size && b->size-addr >= 2)
    return (uint16_t)((uint16_t)b->rom[addr]<<8 | b->rom[addr+1]);
  if (addr >= 0xff0000u)
    return (uint16_t)((uint16_t)b->ram[addr&65535u]<<8 | b->ram[(addr+1)&65535u]);
  return 0xffffu;
}
static uint32_t rd32(struct bus43 *b,uint32_t a)
{ return ((uint32_t)rd16(b,a)<<16)|rd16(b,a+2); }
/* CCR bits X N Z V C. CMP changes NZVC, preserves X. */
static uint16_t cmp16(uint16_t dst,uint16_t src,uint16_t oldsr)
{
  uint32_t result;
#if defined(__arm__) && defined(__thumb__)
  uint32_t apsr;
  __asm__ volatile("subs %[r], %[d], %[s]\n\tmrs %[f], apsr"
    : [r]"=&r"(result),[f]"=r"(apsr)
    : [d]"r"((uint32_t)dst),[s]"r"((uint32_t)src) : "cc");
  /* Force 16-bit flags, not 32-bit APSR flags. */
  (void)apsr;
#else
  result=(uint32_t)dst-(uint32_t)src;
#endif
  uint16_t r=(uint16_t)result;
  uint16_t c=(dst<src)?1u:0u;
  uint16_t v=(((dst^src)&(dst^r)&0x8000u)!=0u)?2u:0u;
  uint16_t z=(r==0u)?4u:0u;
  uint16_t n=(r&0x8000u)?8u:0u;
  return (uint16_t)((oldsr&0xfff0u)|n|z|v|c);
}
/* One validated native block, with cycle-bounded repeated execution.
 * CMP.W ($00FF03B0).L,D1; BEQ.S -8; RTS.
 * The block is not entered from the reset vector automatically.
 */
static int block_a12e(struct cpu43 *c,struct bus43 *b,uint32_t budget,
                      uint32_t *iterations)
{
  if (rd16(b,0xa12e)!=0xb279u || rd32(b,0xa130)!=0x00ff03b0u ||
      rd16(b,0xa134)!=0x67f8u || rd16(b,0xa136)!=0x4e75u)
    return -2;
  while (budget >= 22u)
    {
      c->sr=cmp16((uint16_t)c->d[1],rd16(b,0xff03b0u),c->sr);
      c->cycles+=14u; budget-=14u;
      (*iterations)++;
      if (c->sr&4u)
        {
          c->cycles+=10u; c->pc=0xa12eu;
          /* Never run indefinitely; caller must service VDP/IRQs. */
          return 1;
        }
      c->cycles+=8u; c->pc=0xa136u;
      return 0;
    }
  return 1;
}

/* V0.44: conservative reset-vector interpreter. No MMIO side effects.
 * Only known instructions are executed; all others fail closed.
 */
#define V044_MAX_STEPS 256u
#define V044_MAX_CYCLES 4096u

static int v044_fetch16(struct bus43 *b, uint32_t addr, uint16_t *value)
{
  if ((addr & 1u) != 0u || addr > 0xfffffeu ||
      addr >= b->size || b->size - addr < 2u)
    return -1;
  *value = rd16(b, addr);
  return 0;
}

static int v044_fetch32(struct bus43 *b, uint32_t addr, uint32_t *value)
{
  uint16_t hi, lo;
  if (v044_fetch16(b, addr, &hi) != 0 ||
      v044_fetch16(b, addr + 2u, &lo) != 0)
    return -1;
  *value = ((uint32_t)hi << 16) | lo;
  return 0;
}

/* V0.44.2: read-only, provisional Genesis I/O model for reset tracing.
 * Odd byte lanes carry the documented I/O registers; even lanes are
 * approximated as zero. This is not cycle-accurate open-bus emulation.
 */
static int v0442_io_read8(uint32_t address, uint8_t *value)
{
  uint32_t a = address & 0xffffffu;
  if (a < 0xa10000u || a > 0xa1001fu)
    return -1;
  if ((a & 1u) == 0u)
    {
      *value = 0u; /* provisional even-lane/open-bus approximation */
      return 0;
    }
  switch (a)
    {
      case 0xa10001u: *value = 0xa0u; return 0; /* provisional version */
      case 0xa10003u: /* port A data: no buttons pressed */
      case 0xa10005u: /* port B data */
      case 0xa10007u: /* expansion data */
        *value = 0x7fu;
        return 0;
      case 0xa10009u: case 0xa1000bu: case 0xa1000du:
        *value = 0x00u; /* control registers, inputs */
        return 0;
      case 0xa1000fu: case 0xa10011u: case 0xa10013u:
      case 0xa10015u: case 0xa10017u: case 0xa10019u:
        *value = 0x00u; /* serial registers: provisional */
        return 0;
      default:
        return -1;
    }
}

static int v0442_read32(struct bus43 *b, uint32_t address, uint32_t *value)
{
  uint32_t a = address & 0xffffffu;
  uint32_t v = 0u;
  unsigned i;
  if ((a & 1u) != 0u || a > 0xfffffcu)
    return -1;
  if ((a < b->size && b->size - a >= 4u) ||
      (a >= 0xff0000u && a <= 0xfffffcu))
    {
      *value = rd32(b, a);
      return 0;
    }
  if (a < 0xa10000u || a > 0xa1001cu)
    return -1;
  for (i = 0; i < 4u; ++i)
    {
      uint8_t byte;
      if (v0442_io_read8(a + i, &byte) != 0)
        return -1;
      v = (v << 8) | byte;
    }
  *value = v;
  printf("T2GEN V0.44.2 IO_READ32: addr=%06lx value=%08lx (provisional lanes)\n",
         (unsigned long)a, (unsigned long)v);
  return 0;
}

/* V0.44.3: checked, big-endian word reads from ROM, RAM and I/O. */
static int v0443_read16(struct bus43 *b, uint32_t address, uint16_t *value)
{
  uint32_t a = address & 0xffffffu;
  uint8_t hi, lo;

  if ((a & 1u) != 0u || a > 0xfffffeu)
    return -1;
  if ((a < b->size && b->size - a >= 2u) ||
      (a >= 0xff0000u && a <= 0xfffffeu))
    {
      *value = rd16(b, a);
      return 0;
    }
  if (a < 0xa10000u || a > 0xa1001eu ||
      v0442_io_read8(a, &hi) != 0 ||
      v0442_io_read8(a + 1u, &lo) != 0)
    return -1;
  *value = (uint16_t)(((uint16_t)hi << 8) | lo);
  printf("T2GEN V0.44.3 IO_READ16: addr=%06lx value=%04x (provisional lanes)\n",
         (unsigned long)a, *value);
  return 0;
}

static int v044_condition(unsigned cc, uint16_t sr)
{
  int n = !!(sr & 8u), z = !!(sr & 4u);
  int v = !!(sr & 2u), c = !!(sr & 1u);
  switch (cc)
    {
      case 0: return 1;               /* BRA */
      case 2: return !c && !z;        /* BHI */
      case 3: return c || z;          /* BLS */
      case 4: return !c;              /* BCC */
      case 5: return c;               /* BCS */
      case 6: return !z;              /* BNE */
      case 7: return z;               /* BEQ */
      case 8: return !v;              /* BVC */
      case 9: return v;               /* BVS */
      case 10: return !n;             /* BPL */
      case 11: return n;              /* BMI */
      case 12: return n == v;         /* BGE */
      case 13: return n != v;         /* BLT */
      case 14: return !z && n == v;   /* BGT */
      case 15: return z || n != v;    /* BLE */
      default: return -1;             /* BSR handled separately */
    }
}

static void v044_reset_probe(struct bus43 *b)
{
  struct cpu43 c;
  uint32_t steps = 0;
  uint32_t start_pc;
  const char *reason = "step limit";
  uint16_t opcode = 0;
  memset(&c, 0, sizeof(c));
  c.a[7] = rd32(b, 0);
  c.pc = rd32(b, 4);
  start_pc = c.pc;
  c.sr = 0x2700u;
  printf("T2GEN V0.44.3 RESET_TRACE: SP=%08lx PC=%06lx max_steps=%u max_cycles=%u\n",
         (unsigned long)c.a[7], (unsigned long)c.pc,
         V044_MAX_STEPS, V044_MAX_CYCLES);
  if ((c.pc & 1u) != 0u || c.pc >= b->size)
    {
      reason = "invalid reset vector";
      goto done;
    }
  while (steps < V044_MAX_STEPS && c.cycles < V044_MAX_CYCLES)
    {
      uint32_t at = c.pc;
      uint32_t next = at + 2u;
      uint16_t ext;
      if (v044_fetch16(b, at, &opcode) != 0)
        {
          reason = "instruction fetch outside ROM or odd address";
          break;
        }
      if (steps < 16u)
        printf("T2GEN V0.44.3 TRACE[%lu]: pc=%06lx op=%04x sr=%04x\n",
               (unsigned long)steps, (unsigned long)at, opcode, c.sr);
      if (opcode == 0x4e71u) /* NOP */
        {
          c.cycles += 4u;
        }
      else if (opcode == 0x4e75u) /* RTS: only stack in emulated RAM */
        {
          uint32_t sp = c.a[7] & 0xffffffu;
          if ((sp & 1u) != 0u || sp < 0xff0000u || sp > 0xfffffcu)
            { reason = "RTS stack outside emulated RAM"; break; }
          next = rd32(b, sp);
          c.a[7] += 4u;
          c.cycles += 16u;
        }
      else if (opcode == 0x4e72u) /* STOP */
        {
          if (v044_fetch16(b, next, &ext) != 0)
            { reason = "truncated STOP"; break; }
          c.sr = ext;
          next += 2u;
          c.cycles += 4u;
          c.pc = next;
          steps++;
          reason = "STOP instruction";
          break;
        }
      else if (opcode == 0x46fcu) /* MOVE #imm,SR */
        {
          if (v044_fetch16(b, next, &ext) != 0)
            { reason = "truncated MOVE immediate to SR"; break; }
          c.sr = ext;
          next += 2u;
          c.cycles += 12u;
        }
      else if ((opcode & 0xf100u) == 0x7000u) /* MOVEQ #imm,Dn */
        {
          unsigned reg = (opcode >> 9) & 7u;
          int32_t val = (int8_t)(opcode & 0xffu);
          c.d[reg] = (uint32_t)val;
          c.sr = (uint16_t)((c.sr & 0xfff0u) |
                 (val < 0 ? 8u : 0u) | (val == 0 ? 4u : 0u));
          c.cycles += 4u;
        }
      else if ((opcode & 0xf000u) == 0x6000u) /* BRA/Bcc, not BSR */
        {
          unsigned cc = (opcode >> 8) & 15u;
          int cond = v044_condition(cc, c.sr);
          int32_t displacement = (int8_t)(opcode & 0xffu);
          if (cond < 0)
            { reason = "BSR requires stack write (unsupported)"; break; }
          if ((opcode & 0xffu) == 0u)
            {
              if (v044_fetch16(b, next, &ext) != 0)
                { reason = "truncated branch displacement"; break; }
              displacement = (int16_t)ext;
              next += 2u;
            }
          else if ((opcode & 0xffu) == 0xffu)
            {
              /* 0xFF is a long displacement on 68020+, but an 8-bit
               * displacement on 68000. This engine targets 68000. */
            }
          if (cond)
            next = (uint32_t)((int32_t)(at + 2u) + displacement);
          c.cycles += cond ? 10u : 8u;
        }
      else if (opcode == 0x4a79u) /* TST.W (xxx).L, 68000 */
        {
          uint32_t addr;
          uint16_t value;
          uint32_t a24;
          if (v044_fetch32(b, next, &addr) != 0)
            { reason = "truncated TST.W absolute address"; break; }
          a24 = addr & 0xffffffu;
          printf("T2GEN V0.44.3 TST.W: pc=%06lx addr=%08lx a24=%06lx\n",
                 (unsigned long)at, (unsigned long)addr,
                 (unsigned long)a24);
          if (v0443_read16(b, a24, &value) != 0)
            {
              reason = "TST.W unmapped or unaligned address";
              break;
            }
          c.sr = (uint16_t)((c.sr & 0xfff0u) |
                 ((value & 0x8000u) ? 8u : 0u) |
                 ((value == 0u) ? 4u : 0u));
          next += 4u;
          c.cycles += 16u; /* 68000 TST.W absolute long */
          printf("T2GEN V0.44.3 TST.W: value=%04x sr=%04x\n",
                 value, c.sr);
        }
      else if (opcode == 0x4ab9u) /* TST.L (xxx).L, 68000 */
        {
          uint32_t addr;
          uint32_t value;
          uint32_t a24;
          if (v044_fetch32(b, next, &addr) != 0)
            { reason = "truncated TST.L absolute address"; break; }
          a24 = addr & 0xffffffu;
          printf("T2GEN V0.44.2 TST.L: pc=%06lx addr=%08lx a24=%06lx\n",
                 (unsigned long)at, (unsigned long)addr,
                 (unsigned long)a24);
          if (v0442_read32(b, a24, &value) != 0)
            {
              reason = "TST.L unmapped or unaligned address";
              break;
            }
          c.sr = (uint16_t)((c.sr & 0xfff0u) |
                 ((value & 0x80000000u) ? 8u : 0u) |
                 ((value == 0u) ? 4u : 0u));
          next += 4u;
          c.cycles += 20u;
          printf("T2GEN V0.44.2 TST.L: value=%08lx sr=%04x\n",
                 (unsigned long)value, c.sr);
        }
      else if (opcode == 0x4ef9u) /* JMP absolute long */
        {
          if (v044_fetch32(b, next, &next) != 0)
            { reason = "truncated JMP absolute long"; break; }
          c.cycles += 10u;
        }
      else if ((opcode & 0xf1ffu) == 0x41f9u) /* LEA abs.l,An */
        {
          uint32_t value;
          if (v044_fetch32(b, next, &value) != 0)
            { reason = "truncated LEA absolute long"; break; }
          c.a[(opcode >> 9) & 7u] = value;
          next += 4u;
          c.cycles += 12u;
        }
      else
        {
          reason = "unsupported opcode (no execution)";
          break;
        }
      c.pc = next;
      steps++;
      if ((c.pc & 1u) != 0u || c.pc >= b->size)
        {
          reason = "next PC outside ROM or odd";
          break;
        }
    }
  if (c.cycles >= V044_MAX_CYCLES)
    reason = "cycle limit";
done:
  printf("T2GEN V0.44.3 RESET_STOP: reason=%s start=%06lx pc=%06lx "
         "opcode=%04x steps=%lu cycles=%lu sr=%04x\n",
         reason, (unsigned long)start_pc, (unsigned long)c.pc, opcode,
         (unsigned long)steps, (unsigned long)c.cycles, c.sr);
}

void t2gen_native43_probe(const uint8_t *rom, size_t len)
{
  struct bus43 b;
  struct cpu43 c;
  uint32_t iters = 0;
  int rc;

  memset(&b, 0, sizeof(b));
  memset(&c, 0, sizeof(c));

  /* The former uint8_t ram[65536] member consumed 64 KiB of task stack.
   * Allocate emulated RAM separately instead.
   */

  b.ram = calloc(1, 65536u);
  if (b.ram == NULL)
    {
      printf("T2GEN V0.43.11: emulated RAM allocation failed\n");
      return;
    }

  b.rom = rom;
  b.size = len;

  c.a[7] = rd32(&b, 0);
  c.pc = rd32(&b, 4);
  c.sr = 0x2700u;

  printf("T2GEN V0.43.11 NATIVE_ONLY: reset PC=%06lx SP=%08lx, "
         "Musashi not linked\n",
         (unsigned long)c.pc, (unsigned long)c.a[7]);

  /* Explicit isolated block test: this is not full ROM execution. */

  if (len < 0xa138u || rd16(&b, 0xa12e) != 0xb279u)
    {
      printf("T2GEN V0.43.11: ROM block signature unavailable\n");
      goto cleanup;
    }

  c.pc = 0xa12eu;
  c.d[1] = 0x56u;
  b.ram[0x03b0] = 0;
  b.ram[0x03b1] = 0x56u;

  rc = block_a12e(&c, &b, 64u, &iters);
  printf("T2GEN V0.43.11 BLOCK_TEST: rc=%d pc=%06lx sr=%04x "
         "cycles=%lu iterations=%lu expected_rc=1\n",
         rc, (unsigned long)c.pc, c.sr,
         (unsigned long)c.cycles, (unsigned long)iters);

  b.ram[0x03b1] = 0x57u;
  rc = block_a12e(&c, &b, 64u, &iters);
  printf("T2GEN V0.43.11 BLOCK_EXIT: rc=%d pc=%06lx sr=%04x "
         "cycles=%lu iterations=%lu expected_pc=00a136\n",
         rc, (unsigned long)c.pc, c.sr,
         (unsigned long)c.cycles, (unsigned long)iters);

  printf("T2GEN V0.43.11 STOP: full-ROM execution unsupported; "
         "no Musashi fallback\n");

cleanup:
  /* Independent, bounded reset-vector trace; no ROM/MMIO writes. */
  v044_reset_probe(&b);
  free(b.ram);
  printf("T2GEN V0.43.11: emulated RAM released\n");
}
