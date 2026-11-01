/* Generated offline for ROM CRC32 2F75E896. Native operations only. */
static int t2gen_aot_0214(struct t2cpu *c, const struct t2bus *b)
{
  uint32_t v;
  uint32_t addr = c->a[5];
  if (!match16(b, 0x214u, 0x4c9du) || !match16(b, 0x216u, 0x00e0u)) return -1;
  { uint16_t w; if (native_bus_read16(b, addr, &w) != 0) return -3; v = (uint32_t)(int32_t)(int16_t)w; }
  c->d[5] = v;
  addr += 2u;
  { uint16_t w; if (native_bus_read16(b, addr, &w) != 0) return -3; v = (uint32_t)(int32_t)(int16_t)w; }
  c->d[6] = v;
  addr += 2u;
  { uint16_t w; if (native_bus_read16(b, addr, &w) != 0) return -3; v = (uint32_t)(int32_t)(int16_t)w; }
  c->d[7] = v;
  addr += 2u;
  c->a[5] = addr;
  c->pc = 0x000218u;
  c->cycles += 24u;
  printf("T2GEN V0.49 AOT_0214: MOVEM.W regs=3 A5=%06lx next=%06lx\n", (unsigned long)c->a[5], (unsigned long)c->pc);
  return 0;
}
static int t2gen_aot_0218(struct t2cpu *c, const struct t2bus *b)
{
  uint32_t v;
  uint32_t addr = c->a[5];
  if (!match16(b, 0x218u, 0x4cddu) || !match16(b, 0x21au, 0x1f00u)) return -1;
  if (native_bus_read32(b, addr, &v) != 0) return -3;
  c->a[0] = v;
  addr += 4u;
  if (native_bus_read32(b, addr, &v) != 0) return -3;
  c->a[1] = v;
  addr += 4u;
  if (native_bus_read32(b, addr, &v) != 0) return -3;
  c->a[2] = v;
  addr += 4u;
  if (native_bus_read32(b, addr, &v) != 0) return -3;
  c->a[3] = v;
  addr += 4u;
  if (native_bus_read32(b, addr, &v) != 0) return -3;
  c->a[4] = v;
  addr += 4u;
  c->a[5] = addr;
  c->pc = 0x00021cu;
  c->cycles += 52u;
  printf("T2GEN V0.49 AOT_0218: MOVEM.L regs=5 A5=%06lx next=%06lx\n", (unsigned long)c->a[5], (unsigned long)c->pc);
  return 0;
}
