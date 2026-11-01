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
  const uint32_t io_value = 0u; /* provisional I/O lane model */
  if (!match16(b, 0x200u, 0x4ab9u) ||
      !match32(b, 0x202u, 0x00a10008u) ||
      !match16(b, 0x206u, 0x6606u))
    return -1;

  c->sr = (uint16_t)((c->sr & 0xfff0u) |
                       ((io_value & 0x80000000u) ? 8u : 0u) |
                       ((io_value == 0u) ? 4u : 0u));
  c->cycles += 20u;
  printf("T2GEN V0.45 AOT: pc=000200 TST.L ($A10008).L value=%08lx sr=%04x\n",
         (unsigned long)io_value, c->sr);

  /* BNE.S +6: branch target 0x20E; fallthrough 0x208. */
  c->pc = (c->sr & 4u) ? 0x208u : 0x20eu;
  c->cycles += (c->sr & 4u) ? 8u : 10u;
  printf("T2GEN V0.45 AOT: pc=000206 BNE.S +6 -> %06lx\n",
         (unsigned long)c->pc);
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
  printf("T2GEN V0.45 NATIVE_AOT: SP=%08lx PC=%06lx (no Musashi, no interpreter)\n",
         (unsigned long)sp, (unsigned long)pc);
  if (pc != 0x200u)
    {
      printf("T2GEN V0.45 STOP: unknown reset PC; no native block\n");
      goto done;
    }
  rc = native_reset_0200(&c, &b);
  if (rc)
    {
      printf("T2GEN V0.45 STOP: ROM reset signature mismatch\n");
      goto done;
    }
  printf("T2GEN V0.45 NATIVE_STOP: pc=%06lx cycles=%lu reason=next block not translated\n",
         (unsigned long)c.pc, (unsigned long)c.cycles);

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
  printf("T2GEN V0.45: native probe returned\n");
}
