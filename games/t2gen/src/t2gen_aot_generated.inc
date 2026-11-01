/* V0.47: ROM-specific native TST.W at PC 0x208, observed operand A1000C.
 * Instruction bytes are validated against the loaded ROM before execution.
 */
static int t2gen_aot_0208(struct t2cpu *c, const struct t2bus *b)
{
  uint16_t value;
  if (!match16(b, 0x208u, 0x4a79u) ||
      !match32(b, 0x20au, 0x00a1000cu))
    {
      printf("T2GEN V0.47 AOT_0208: ROM signature mismatch\n");
      return -1;
    }
  if (native_bus_read16(b, 0xa1000cu, &value) != 0)
    {
      printf("T2GEN V0.47 AOT_0208: unsupported bus read a1000c\n");
      return -3;
    }
  c->sr = (uint16_t)((c->sr & 0xfff0u) |
                     ((value & 0x8000u) ? 8u : 0u) |
                     ((value == 0u) ? 4u : 0u));
  c->cycles += 16u;
  c->pc = 0x20eu;
  printf("T2GEN V0.47 AOT_0208: TST.W addr=a1000c value=%04x sr=%04x next=%06lx\n",
         value, c->sr, (unsigned long)c->pc);
  return 0;
}

/* ROM-specific AOT: 0x20E BNE.S +0x7C, generated from CRC32 2F75E896. */
static int t2gen_aot_020e(struct t2cpu *c, const struct t2bus *b)
{
  if (!match16(b, 0x20eu, 0x667cu)) return -1;
  if ((c->sr & 4u) == 0u)
    {
      c->pc = 0x28cu;
      c->cycles += 10u;
    }
  else
    {
      c->pc = 0x210u;
      c->cycles += 8u;
    }
  printf("T2GEN V0.48 AOT_020E: BNE -> %06lx sr=%04x\n",
         (unsigned long)c->pc, c->sr);
  return 0;
}
/* ROM-specific AOT: 0x210 LEA (0x007C,PC),A5. PC base is 0x212. */
static int t2gen_aot_0210(struct t2cpu *c, const struct t2bus *b)
{
  if (!match16(b, 0x210u, 0x4bfau) ||
      !match16(b, 0x212u, 0x007cu)) return -1;
  c->a[5] = 0x28eu;
  c->pc = 0x214u;
  c->cycles += 8u;
  printf("T2GEN V0.48 AOT_0210: LEA A5=%06lx next=%06lx\n",
         (unsigned long)c->a[5], (unsigned long)c->pc);
  return 0;
}
