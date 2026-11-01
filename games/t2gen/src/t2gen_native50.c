/* T2GEN V0.45: ROM-specific, statically compiled native blocks.
 * No runtime 68000 instruction decoding or Musashi dependency.
 * This is a bounded proof of architecture, NOT a playable game.
 */
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "t2gen_native43.h"

struct t2cpu { uint32_t d[8], a[8], pc; uint16_t sr; uint32_t cycles; };
struct t2bus { const uint8_t *rom; size_t len; uint8_t *ram; };

/* Provisional Genesis I/O bus model. No fabricated support outside range. */
static int genesis_io_read8(uint32_t addr, uint8_t *value)
{
  uint32_t off = addr - 0xa10000u;
  if (addr < 0xa10000u || addr > 0xa1001fu) return -1;
  /* The 68000 data registers and direction registers use odd byte lanes.
   * Even lanes are provisionally zero; not verified against hardware.
   */
  if ((off & 1u) == 0u)
    {
      *value = 0u;
      return 0;
    }
  switch (off)
    {
      case 0x03u: case 0x05u: case 0x07u:
        *value = 0x7fu; /* provisional no-buttons controller value */
        return 0;
      case 0x09u: case 0x0bu: case 0x0du:
        *value = 0x00u; /* provisional direction registers */
        return 0;
      default:
        return -1;
    }
}
static int genesis_io_read16(uint32_t addr, uint16_t *value)
{
  uint8_t hi, lo;
  if ((addr & 1u) != 0u || addr < 0xa10000u ||
      addr > 0xa1001eu ||
      genesis_io_read8(addr, &hi) ||
      genesis_io_read8(addr + 1u, &lo))
    return -1;
  *value = (uint16_t)(((uint16_t)hi << 8) | lo);
  return 0;
}
static int genesis_io_read32(uint32_t addr, uint32_t *value)
{
  uint16_t hi, lo;
  if (genesis_io_read16(addr, &hi) ||
      genesis_io_read16(addr + 2u, &lo))
    return -1;
  *value = ((uint32_t)hi << 16) | lo;
  return 0;
}
static int native_bus_read16(const struct t2bus *b, uint32_t addr,
                             uint16_t *value)
{
  addr &= 0xffffffu;
  if (addr & 1u) return -1;
  if (addr < b->len && b->len - addr >= 2u)
    {
      *value = (uint16_t)(((uint16_t)b->rom[addr] << 8) |
                           b->rom[addr + 1u]);
      return 0;
    }
  if (addr >= 0xff0000u && addr <= 0xfffffeu)
    {
      uint32_t off = addr & 0xffffu;
      *value = (uint16_t)(((uint16_t)b->ram[off] << 8) |
                           b->ram[(off + 1u) & 0xffffu]);
      return 0;
    }
  return genesis_io_read16(addr, value);
}
static int rom16(const struct t2bus *b, uint32_t a, uint16_t *v)
{
  if ((a & 1u) || a >= b->len || b->len - a < 2u) return -1;
  *v = ((uint16_t)b->rom[a] << 8) | b->rom[a + 1u];
  return 0;
}
static int rom32(const struct t2bus *b, uint32_t a, uint32_t *v)
{
  uint16_t hi, lo;
  if (rom16(b, a, &hi) || rom16(b, a + 2u, &lo)) return -1;
  *v = ((uint32_t)hi << 16) | lo;
  return 0;
}
static int match16(const struct t2bus *b, uint32_t a, uint16_t expected)
{
  uint16_t actual;
  return rom16(b, a, &actual) == 0 && actual == expected;
}
static int match32(const struct t2bus *b, uint32_t a, uint32_t expected)
{
  uint32_t actual;
  return rom32(b, a, &actual) == 0 && actual == expected;
}
static uint16_t cmp_word(uint16_t dst, uint16_t src, uint16_t sr)
{
  uint16_t r = (uint16_t)(dst - src);
  uint16_t n = (r & 0x8000u) ? 8u : 0u;
  uint16_t z = r == 0u ? 4u : 0u;
  uint16_t v = ((dst ^ src) & (dst ^ r) & 0x8000u) ? 2u : 0u;
  uint16_t c = dst < src ? 1u : 0u;
  return (uint16_t)((sr & 0xfff0u) | n | z | v | c);
}
/* AOT block corresponding to ROM 0xA12E:
 * CMP.W ($00FF03B0).L,D1; BEQ.S -8; RTS.
 * Executed as compiled host operations; no 68000 opcode fetch loop.
 */
static int native_a12e(struct t2cpu *c, struct t2bus *b)
{
  uint16_t src;
  if (!match16(b, 0xa12eu, 0xb279u) ||
      !match32(b, 0xa130u, 0x00ff03b0u) ||
      !match16(b, 0xa134u, 0x67f8u) ||
      !match16(b, 0xa136u, 0x4e75u))
    return -1;
  src = (uint16_t)(((uint16_t)b->ram[0x03b0u] << 8) |
                    b->ram[0x03b1u]);
  c->sr = cmp_word((uint16_t)c->d[1], src, c->sr);
  c->cycles += 14u;
  if (c->sr & 4u)
    {
      c->cycles += 10u;
      c->pc = 0xa12eu;
      return 1;
    }
  c->cycles += 8u;
  c->pc = 0xa136u;
  return 0; /* STOP at RTS; stack return semantics not implemented */
}
/* AOT reset block: TST.L ($A10008).L; BNE.S +6.
 * The I/O model is deliberately provisional (zero) as in V0.44.2.
 * We do not claim to implement the following TST.W at 0x208.
 */
static int native_reset_0200(struct t2cpu *c, const struct t2bus *b)
{
  uint32_t io_value;
  if (!match16(b, 0x200u, 0x4ab9u) ||
      !match32(b, 0x202u, 0x00a10008u) ||
      !match16(b, 0x206u, 0x6606u))
    return -1;

  if (genesis_io_read32(0xa10008u, &io_value) != 0) return -3;
  c->sr = (uint16_t)((c->sr & 0xfff0u) |
                       ((io_value & 0x80000000u) ? 8u : 0u) |
                       ((io_value == 0u) ? 4u : 0u));
  c->cycles += 20u;
  printf("T2GEN V0.50 AOT: pc=000200 TST.L ($A10008).L value=%08lx sr=%04x\n",
         (unsigned long)io_value, c->sr);

  /* BNE.S +6: branch target 0x20E; fallthrough 0x208. */
  c->pc = (c->sr & 4u) ? 0x208u : 0x20eu;
  c->cycles += (c->sr & 4u) ? 8u : 10u;
  printf("T2GEN V0.50 AOT: pc=000206 BNE.S +6 -> %06lx\n",
         (unsigned long)c->pc);
  return 0;
}

static int native_bus_read8(const struct t2bus *b, uint32_t addr,
                            uint8_t *value)
{
  addr &= 0xffffffu;
  if (addr < b->len)
    {
      *value = b->rom[addr];
      return 0;
    }
  if (addr >= 0xff0000u)
    {
      *value = b->ram[addr & 0xffffu];
      return 0;
    }
  return genesis_io_read8(addr, value);
}
static int native_bus_read32(const struct t2bus *b, uint32_t addr, uint32_t *value)
{
  uint16_t hi, lo;
  if (native_bus_read16(b, addr, &hi) ||
      native_bus_read16(b, addr + 2u, &lo)) return -1;
  *value = ((uint32_t)hi << 16) | lo;
  return 0;
}
/* Offline-generated ROM-specific blocks, no runtime opcode decoding. */
#include "t2gen_aot_generated.inc"
#include "t2gen_aot_movem.inc"
#include "t2gen_aot_cfg.inc"

static int native_dispatch(struct t2cpu *c, struct t2bus *b)
{
  unsigned steps;
  for (steps = 0; steps < 128u; steps++)
    {
      uint32_t previous = c->pc;
      int rc;
      switch (c->pc)
        {
          case 0x000200u:
            rc = native_reset_0200(c, b);
            break;
          case 0x000208u:
            rc = t2gen_aot_0208(c, b);
            break;
          case 0x00020eu:
            rc = t2gen_aot_020e(c, b);
            break;
          case 0x000210u:
            rc = t2gen_aot_0210(c, b);
            break;
          case 0x000214u:
            rc = t2gen_aot_0214(c, b);
            break;
          case 0x000218u:
            rc = t2gen_aot_0218(c, b);
            break;
          default:
            rc = t2gen_aot_cfg_dispatch(c, b);
            if (rc == -2)
              {
                printf("T2GEN V0.50 DISPATCH_STOP: untranslated pc=%06lx\n",
                       (unsigned long)c->pc);
                return 0;
              }
            break;
        }
      if (rc != 0)
        {
          printf("T2GEN V0.50 DISPATCH_STOP: block failure pc=%06lx rc=%d\n",
                 (unsigned long)previous, rc);
          return rc;
        }
      if (c->pc == previous)
        {
          printf("T2GEN V0.50 DISPATCH_STOP: no progress pc=%06lx\n",
                 (unsigned long)c->pc);
          return -1;
        }
    }
  printf("T2GEN V0.50 DISPATCH_STOP: block budget exhausted\n");
  return 0;
}

void t2gen_native43_probe(const uint8_t *rom, size_t len)
{
  struct t2bus b;
  struct t2cpu c;
  uint32_t sp, pc;
  int rc;

  memset(&b, 0, sizeof(b));
  memset(&c, 0, sizeof(c));
  b.rom = rom;
  b.len = len;
  b.ram = (uint8_t *)calloc(65536u, 1u);
  if (!b.ram)
    {
      printf("T2GEN V0.45 ERROR: RAM allocation failed\n");
      return;
    }
  if (rom32(&b, 0u, &sp) || rom32(&b, 4u, &pc))
    {
      printf("T2GEN V0.45 ERROR: missing reset vectors\n");
      goto done;
    }
  c.a[7] = sp;
  c.pc = pc;
  c.sr = 0x2700u;
  printf("T2GEN V0.50 NATIVE_AOT: SP=%08lx PC=%06lx (no Musashi, no interpreter)\n",
         (unsigned long)sp, (unsigned long)pc);
  if (pc != 0x200u)
    {
      printf("T2GEN V0.50 STOP: unknown reset PC; no native block\n");
      goto done;
    }
  rc = native_dispatch(&c, &b);
  printf("T2GEN V0.50 NATIVE_STOP: pc=%06lx cycles=%lu rc=%d\n",
         (unsigned long)c.pc, (unsigned long)c.cycles, rc);

  /* Independent AOT block self-test; not part of the game's control flow. */
  memset(&c, 0, sizeof(c));
  c.pc = 0xa12eu;
  c.sr = 0x2700u;
  c.d[1] = 0x56u;
  b.ram[0x03b1u] = 0x56u;
  rc = native_a12e(&c, &b);
  printf("T2GEN V0.45 AOT_BLOCK_A12E: case=equal rc=%d pc=%06lx sr=%04x cycles=%lu\n",
         rc, (unsigned long)c.pc, c.sr, (unsigned long)c.cycles);
  b.ram[0x03b1u] = 0x57u;
  rc = native_a12e(&c, &b);
  printf("T2GEN V0.45 AOT_BLOCK_A12E: case=unequal rc=%d pc=%06lx sr=%04x cycles=%lu\n",
         rc, (unsigned long)c.pc, c.sr, (unsigned long)c.cycles);
done:
  free(b.ram);
  printf("T2GEN V0.50: native probe returned\n");
}
