/* Generated from the exact ROM; no runtime 68000 opcode decoding. */
static uint16_t t2gen_v100_read16(const struct t2bus *b,uint32_t a){uint16_t v=0;native_bus_read16(b,a,&v);return v;}
static uint32_t t2gen_v100_read32(const struct t2bus *b,uint32_t a){uint32_t v=0;native_bus_read32(b,a,&v);return v;}
static int t2gen_aot_cfg_dispatch(struct t2cpu *c, const struct t2bus *b)
{
  uint8_t byte_value;
  switch (c->pc)
    {
      case 0x000200u:
        {
          if (!match16(b, 0x200u, 0x4ab9u)) return -1;
          if (!match32(b, 0x202u, 0x00a10008u)) return -1;
          { uint32_t value;
            if (native_bus_read32(b, 0x00a10008u, &value) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((value & 0x80000000u) ? 8u : 0u) | (value == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x206u, 0x6606u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x00020eu : 0x000208u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x000208u:
        {
          if (!match16(b, 0x208u, 0x4a79u)) return -1;
          if (!match32(b, 0x20au, 0x00a1000cu)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00a1000cu, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x20eu, 0x667cu)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x00028cu : 0x000210u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00020eu:
        {
          if (!match16(b, 0x20eu, 0x667cu)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x00028cu : 0x000210u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x000210u:
        {
          if (!match16(b, 0x210u, 0x4bfau)) return -1;
          if (!match16(b, 0x212u, 0x007cu)) return -1;
          c->a[5] = 0x00028eu;
          c->cycles += 8u;
          if (!match16(b, 0x214u, 0x4c9du)) return -1;
          if (!match16(b, 0x216u, 0x00e0u)) return -1;
          { uint32_t addr = c->a[5]; uint32_t val; uint16_t word; unsigned idx;
            for (idx = 0; idx < 16u; ++idx)
              {
                if (!(0x00e0u & (1u << idx))) continue;
                if (native_bus_read16(b, addr, &word) != 0) return -3;
                val = (uint32_t)(int32_t)(int16_t)word;
                if (idx < 8u) c->d[idx] = val;
                else c->a[idx - 8u] = val;
                addr = (addr + 2u) & 0xffffffu;
              }
            c->a[5] = addr; /* postincrement wins if base An is in mask */
          }
          c->cycles += 20u;
          if (!match16(b, 0x218u, 0x4cddu)) return -1;
          if (!match16(b, 0x21au, 0x1f00u)) return -1;
          { uint32_t addr = c->a[5]; uint32_t val; uint16_t word; unsigned idx;
            for (idx = 0; idx < 16u; ++idx)
              {
                if (!(0x1f00u & (1u << idx))) continue;
                if (native_bus_read32(b, addr, &val) != 0) return -3;
                if (idx < 8u) c->d[idx] = val;
                else c->a[idx - 8u] = val;
                addr = (addr + 4u) & 0xffffffu;
              }
            c->a[5] = addr; /* postincrement wins if base An is in mask */
          }
          c->cycles += 48u;
          if (!match16(b, 0x21cu, 0x1029u)) return -1;
          if (!match16(b, 0x21eu, 0xef01u)) return -1;
          if (native_bus_read8(b, (c->a[1] + (uint32_t)(-4351)) & 0xffffffu, &byte_value) != 0)
            {
              printf("T2GEN V0.57 BUS_STOP: pc=00021c addr=%06lx\n", (unsigned long)((c->a[1] + (uint32_t)(-4351)) & 0xffffffu));
              return -3;
            }
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 0x80u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 12u;
          if (!match16(b, 0x220u, 0x0200u)) return -1;
          if (!match16(b, 0x222u, 0x000fu)) return -1;
          c->d[0] = (c->d[0] & 0xffffff00u) | ((c->d[0] & 255u) & 0x0fu);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80u) ? 8u : 0u) | ((c->d[0] & 255u) == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x224u, 0x6708u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x00022eu : 0x000226u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00021cu:
        {
          if (!match16(b, 0x21cu, 0x1029u)) return -1;
          if (!match16(b, 0x21eu, 0xef01u)) return -1;
          if (native_bus_read8(b, (c->a[1] + (uint32_t)(-4351)) & 0xffffffu, &byte_value) != 0)
            {
              printf("T2GEN V0.57 BUS_STOP: pc=00021c addr=%06lx\n", (unsigned long)((c->a[1] + (uint32_t)(-4351)) & 0xffffffu));
              return -3;
            }
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 0x80u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 12u;
          if (!match16(b, 0x220u, 0x0200u)) return -1;
          if (!match16(b, 0x222u, 0x000fu)) return -1;
          c->d[0] = (c->d[0] & 0xffffff00u) | ((c->d[0] & 255u) & 0x0fu);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80u) ? 8u : 0u) | ((c->d[0] & 255u) == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x224u, 0x6708u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x00022eu : 0x000226u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x000226u:
        {
          if (!match16(b, 0x226u, 0x237cu)) return -1;
          if (!match32(b, 0x228u, 0x53454741u) || !match16(b, 0x22cu, 0x2f00u)) return -1;
          if (native_bus_write32((struct t2bus *)b, (c->a[1] + (uint32_t)(12032)) & 0xffffffu, 0x53454741u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x53454741u & 0x80000000u) ? 8u : 0u) | (0x53454741u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x22eu, 0x3014u)) return -1;
          { uint16_t v; if (native_bus_read16(b, c->a[4], &v) != 0) { printf("T2GEN V0.57 READ16_STOP: pc=00022e addr=%06lx\n", (unsigned long)c->a[4]); return -3; }
            c->d[0] = (c->d[0] & 0xffff0000u) | v;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
          }
          c->cycles += 8u;
          if (!match16(b, 0x230u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x232u, 0x2c40u)) return -1;
          c->a[6] = c->d[0];
          c->cycles += 4u;
          if (!match16(b, 0x234u, 0x4e66u)) return -1;
          if (!(c->sr & 0x2000u)) return -3;
          /* USP is separately modeled; no A7 swap until supervisor transitions. */
          c->usp = c->a[6];
          c->cycles += 4u;
          if (!match16(b, 0x236u, 0x7217u)) return -1;
          c->d[1] = (uint32_t)(int32_t)(23);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x238u, 0x1a1du)) return -1;
          if (native_bus_read8(b, c->a[5], &byte_value) != 0) return -3;
          c->a[5] = (c->a[5] + 1u) & 0xffffffu;
          c->d[5] = (c->d[5] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 128u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x23au, 0x3885u)) return -1;
          if (native_bus_write16((struct t2bus *)b, c->a[4], (uint16_t)c->d[5]) != 0) { printf("T2GEN V0.57 WRITE16_STOP: pc=00023a addr=%06lx\n", (unsigned long)c->a[4]); return -3; }
          c->cycles += 8u;
          if (!match16(b, 0x23cu, 0xda47u)) return -1;
          { uint32_t x = c->d[7] & 65535u, y = c->d[5] & 65535u, r = (x+y) & 65535u;
            uint16_t flags = (uint16_t)(((r & 0x8000u) ? 8u : 0u) | ((r == 0u) ? 4u : 0u) | (((~(x ^ y) & (r ^ y)) & 0x8000u) ? 2u : 0u) | ((x+y > 65535u) ? 17u : 0u));
            c->d[5] = (c->d[5] & 0xffff0000u) | r;
            c->sr = (uint16_t)((c->sr & 0xffe0u) | flags);
          }
          c->cycles += 4u;
          if (!match16(b, 0x23eu, 0x51c9u)) return -1;
          { uint16_t count = (uint16_t)(c->d[1] - 1u);
            c->d[1] = (c->d[1] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x000238u : 0x000242u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00022eu:
        {
          if (!match16(b, 0x22eu, 0x3014u)) return -1;
          { uint16_t v; if (native_bus_read16(b, c->a[4], &v) != 0) { printf("T2GEN V0.57 READ16_STOP: pc=00022e addr=%06lx\n", (unsigned long)c->a[4]); return -3; }
            c->d[0] = (c->d[0] & 0xffff0000u) | v;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
          }
          c->cycles += 8u;
          if (!match16(b, 0x230u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x232u, 0x2c40u)) return -1;
          c->a[6] = c->d[0];
          c->cycles += 4u;
          if (!match16(b, 0x234u, 0x4e66u)) return -1;
          if (!(c->sr & 0x2000u)) return -3;
          /* USP is separately modeled; no A7 swap until supervisor transitions. */
          c->usp = c->a[6];
          c->cycles += 4u;
          if (!match16(b, 0x236u, 0x7217u)) return -1;
          c->d[1] = (uint32_t)(int32_t)(23);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x238u, 0x1a1du)) return -1;
          if (native_bus_read8(b, c->a[5], &byte_value) != 0) return -3;
          c->a[5] = (c->a[5] + 1u) & 0xffffffu;
          c->d[5] = (c->d[5] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 128u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x23au, 0x3885u)) return -1;
          if (native_bus_write16((struct t2bus *)b, c->a[4], (uint16_t)c->d[5]) != 0) { printf("T2GEN V0.57 WRITE16_STOP: pc=00023a addr=%06lx\n", (unsigned long)c->a[4]); return -3; }
          c->cycles += 8u;
          if (!match16(b, 0x23cu, 0xda47u)) return -1;
          { uint32_t x = c->d[7] & 65535u, y = c->d[5] & 65535u, r = (x+y) & 65535u;
            uint16_t flags = (uint16_t)(((r & 0x8000u) ? 8u : 0u) | ((r == 0u) ? 4u : 0u) | (((~(x ^ y) & (r ^ y)) & 0x8000u) ? 2u : 0u) | ((x+y > 65535u) ? 17u : 0u));
            c->d[5] = (c->d[5] & 0xffff0000u) | r;
            c->sr = (uint16_t)((c->sr & 0xffe0u) | flags);
          }
          c->cycles += 4u;
          if (!match16(b, 0x23eu, 0x51c9u)) return -1;
          { uint16_t count = (uint16_t)(c->d[1] - 1u);
            c->d[1] = (c->d[1] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x000238u : 0x000242u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x000238u:
        {
          if (!match16(b, 0x238u, 0x1a1du)) return -1;
          if (native_bus_read8(b, c->a[5], &byte_value) != 0) return -3;
          c->a[5] = (c->a[5] + 1u) & 0xffffffu;
          c->d[5] = (c->d[5] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 128u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x23au, 0x3885u)) return -1;
          if (native_bus_write16((struct t2bus *)b, c->a[4], (uint16_t)c->d[5]) != 0) { printf("T2GEN V0.57 WRITE16_STOP: pc=00023a addr=%06lx\n", (unsigned long)c->a[4]); return -3; }
          c->cycles += 8u;
          if (!match16(b, 0x23cu, 0xda47u)) return -1;
          { uint32_t x = c->d[7] & 65535u, y = c->d[5] & 65535u, r = (x+y) & 65535u;
            uint16_t flags = (uint16_t)(((r & 0x8000u) ? 8u : 0u) | ((r == 0u) ? 4u : 0u) | (((~(x ^ y) & (r ^ y)) & 0x8000u) ? 2u : 0u) | ((x+y > 65535u) ? 17u : 0u));
            c->d[5] = (c->d[5] & 0xffff0000u) | r;
            c->sr = (uint16_t)((c->sr & 0xffe0u) | flags);
          }
          c->cycles += 4u;
          if (!match16(b, 0x23eu, 0x51c9u)) return -1;
          { uint16_t count = (uint16_t)(c->d[1] - 1u);
            c->d[1] = (c->d[1] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x000238u : 0x000242u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x000242u:
        {
          if (!match16(b, 0x242u, 0x289du)) return -1;
          { uint32_t long_value; uint32_t source = c->a[5];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=000242 addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[4], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=000242 addr=%06lx value=%08lx\n", (unsigned long)c->a[4], (unsigned long)long_value); return -3; }
            c->a[5] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x244u, 0x3680u)) return -1;
          if (native_bus_write16((struct t2bus *)b, c->a[3], (uint16_t)c->d[0]) != 0) { printf("T2GEN V0.57 WRITE16_STOP: pc=000244 addr=%06lx\n", (unsigned long)c->a[3]); return -3; }
          c->cycles += 8u;
          if (!match16(b, 0x246u, 0x3287u)) return -1;
          if (native_bus_write16((struct t2bus *)b, c->a[1], (uint16_t)c->d[7]) != 0) { printf("T2GEN V0.57 WRITE16_STOP: pc=000246 addr=%06lx\n", (unsigned long)c->a[1]); return -3; }
          c->cycles += 8u;
          if (!match16(b, 0x248u, 0x3487u)) return -1;
          if (native_bus_write16((struct t2bus *)b, c->a[2], (uint16_t)c->d[7]) != 0) { printf("T2GEN V0.57 WRITE16_STOP: pc=000248 addr=%06lx\n", (unsigned long)c->a[2]); return -3; }
          c->cycles += 8u;
          if (!match16(b, 0x24au, 0x0111u)) return -1;
          if (native_bus_read8(b, c->a[1], &byte_value) != 0) { printf("T2GEN V0.57 BTST_READ_STOP: pc=00024a addr=%06lx\n", (unsigned long)c->a[1]); return -3; }
          { uint8_t bit = (uint8_t)(c->d[0] & 7u);
            c->sr = (uint16_t)((c->sr & (uint16_t)~4u) | ((byte_value & (1u << bit)) ? 0u : 4u));
            if (c->a[1] == 0xa11100u) printf("T2GEN V0.57 BUSREQ_POLL: pc=00024a value=%02x bit=%u z=%u\n", (unsigned)byte_value, (unsigned)bit, (unsigned)((c->sr & 4u) != 0u));
          }
          c->cycles += 8u;
          if (!match16(b, 0x24cu, 0x66fcu)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x00024au : 0x00024eu;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00024au:
        {
          if (!match16(b, 0x24au, 0x0111u)) return -1;
          if (native_bus_read8(b, c->a[1], &byte_value) != 0) { printf("T2GEN V0.57 BTST_READ_STOP: pc=00024a addr=%06lx\n", (unsigned long)c->a[1]); return -3; }
          { uint8_t bit = (uint8_t)(c->d[0] & 7u);
            c->sr = (uint16_t)((c->sr & (uint16_t)~4u) | ((byte_value & (1u << bit)) ? 0u : 4u));
            if (c->a[1] == 0xa11100u) printf("T2GEN V0.57 BUSREQ_POLL: pc=00024a value=%02x bit=%u z=%u\n", (unsigned)byte_value, (unsigned)bit, (unsigned)((c->sr & 4u) != 0u));
          }
          c->cycles += 8u;
          if (!match16(b, 0x24cu, 0x66fcu)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x00024au : 0x00024eu;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00024eu:
        {
          if (!match16(b, 0x24eu, 0x7425u)) return -1;
          c->d[2] = (uint32_t)(int32_t)(37);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[2] & 0x80000000u) ? 8u : 0u) | (c->d[2] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x250u, 0x10ddu)) return -1;
          { uint32_t source = c->a[5], dest = c->a[0];
            if (native_bus_read8(b, source, &byte_value) != 0) { printf("T2GEN V0.57 COPY_READ_STOP: pc=000250 addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write8((struct t2bus *)b, dest, byte_value) != 0) { printf("T2GEN V0.57 COPY_WRITE_STOP: pc=000250 addr=%06lx\n", (unsigned long)dest); return -3; }
            c->a[5] = (source + 1u) & 0xffffffu;
            c->a[0] = (dest + 1u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 128u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          }
          c->cycles += 12u;
          if (!match16(b, 0x252u, 0x51cau)) return -1;
          { uint16_t count = (uint16_t)(c->d[2] - 1u);
            c->d[2] = (c->d[2] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x000250u : 0x000256u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x000250u:
        {
          if (!match16(b, 0x250u, 0x10ddu)) return -1;
          { uint32_t source = c->a[5], dest = c->a[0];
            if (native_bus_read8(b, source, &byte_value) != 0) { printf("T2GEN V0.57 COPY_READ_STOP: pc=000250 addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write8((struct t2bus *)b, dest, byte_value) != 0) { printf("T2GEN V0.57 COPY_WRITE_STOP: pc=000250 addr=%06lx\n", (unsigned long)dest); return -3; }
            c->a[5] = (source + 1u) & 0xffffffu;
            c->a[0] = (dest + 1u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 128u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          }
          c->cycles += 12u;
          if (!match16(b, 0x252u, 0x51cau)) return -1;
          { uint16_t count = (uint16_t)(c->d[2] - 1u);
            c->d[2] = (c->d[2] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x000250u : 0x000256u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x000256u:
        {
          if (!match16(b, 0x256u, 0x3480u)) return -1;
          if (native_bus_write16((struct t2bus *)b, c->a[2], (uint16_t)c->d[0]) != 0) { printf("T2GEN V0.57 WRITE16_STOP: pc=000256 addr=%06lx\n", (unsigned long)c->a[2]); return -3; }
          c->cycles += 8u;
          if (!match16(b, 0x258u, 0x3280u)) return -1;
          if (native_bus_write16((struct t2bus *)b, c->a[1], (uint16_t)c->d[0]) != 0) { printf("T2GEN V0.57 WRITE16_STOP: pc=000258 addr=%06lx\n", (unsigned long)c->a[1]); return -3; }
          c->cycles += 8u;
          if (!match16(b, 0x25au, 0x3487u)) return -1;
          if (native_bus_write16((struct t2bus *)b, c->a[2], (uint16_t)c->d[7]) != 0) { printf("T2GEN V0.57 WRITE16_STOP: pc=00025a addr=%06lx\n", (unsigned long)c->a[2]); return -3; }
          c->cycles += 8u;
          if (!match16(b, 0x25cu, 0x2d00u)) return -1;
          { uint32_t dest = (c->a[6] - 4u) & 0xffffffu;
            c->a[6] = dest;
            if (native_bus_write32((struct t2bus *)b, dest, c->d[0]) != 0) { printf("T2GEN V0.58 WRITE32_STOP: pc=00025c addr=%06lx\n", (unsigned long)dest); return -3; }
            c->cycles += 12u;
          }
          if (!match16(b, 0x25eu, 0x51ceu)) return -1;
          { uint16_t count = (uint16_t)(c->d[6] - 1u);
            c->d[6] = (c->d[6] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00025cu : 0x000262u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00025cu:
        {
          if (!match16(b, 0x25cu, 0x2d00u)) return -1;
          { uint32_t dest = (c->a[6] - 4u) & 0xffffffu;
            c->a[6] = dest;
            if (native_bus_write32((struct t2bus *)b, dest, c->d[0]) != 0) { printf("T2GEN V0.58 WRITE32_STOP: pc=00025c addr=%06lx\n", (unsigned long)dest); return -3; }
            c->cycles += 12u;
          }
          if (!match16(b, 0x25eu, 0x51ceu)) return -1;
          { uint16_t count = (uint16_t)(c->d[6] - 1u);
            c->d[6] = (c->d[6] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00025cu : 0x000262u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x000262u:
        {
          if (!match16(b, 0x262u, 0x289du)) return -1;
          { uint32_t long_value; uint32_t source = c->a[5];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=000262 addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[4], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=000262 addr=%06lx value=%08lx\n", (unsigned long)c->a[4], (unsigned long)long_value); return -3; }
            c->a[5] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x264u, 0x289du)) return -1;
          { uint32_t long_value; uint32_t source = c->a[5];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=000264 addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[4], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=000264 addr=%06lx value=%08lx\n", (unsigned long)c->a[4], (unsigned long)long_value); return -3; }
            c->a[5] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x266u, 0x761fu)) return -1;
          c->d[3] = (uint32_t)(int32_t)(31);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[3] & 0x80000000u) ? 8u : 0u) | (c->d[3] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x268u, 0x2680u)) return -1;
          if (native_bus_write32((struct t2bus *)b, c->a[3], c->d[0]) != 0) { printf("T2GEN V0.60 WRITE32_STOP: pc=000268 addr=%06lx\n", (unsigned long)c->a[3]); return -3; }
          c->cycles += 12u;
          if (!match16(b, 0x26au, 0x51cbu)) return -1;
          { uint16_t count = (uint16_t)(c->d[3] - 1u);
            c->d[3] = (c->d[3] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x000268u : 0x00026eu;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x000268u:
        {
          if (!match16(b, 0x268u, 0x2680u)) return -1;
          if (native_bus_write32((struct t2bus *)b, c->a[3], c->d[0]) != 0) { printf("T2GEN V0.60 WRITE32_STOP: pc=000268 addr=%06lx\n", (unsigned long)c->a[3]); return -3; }
          c->cycles += 12u;
          if (!match16(b, 0x26au, 0x51cbu)) return -1;
          { uint16_t count = (uint16_t)(c->d[3] - 1u);
            c->d[3] = (c->d[3] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x000268u : 0x00026eu;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00026eu:
        {
          if (!match16(b, 0x26eu, 0x289du)) return -1;
          { uint32_t long_value; uint32_t source = c->a[5];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=00026e addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[4], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=00026e addr=%06lx value=%08lx\n", (unsigned long)c->a[4], (unsigned long)long_value); return -3; }
            c->a[5] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x270u, 0x7813u)) return -1;
          c->d[4] = (uint32_t)(int32_t)(19);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[4] & 0x80000000u) ? 8u : 0u) | (c->d[4] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x272u, 0x2680u)) return -1;
          if (native_bus_write32((struct t2bus *)b, c->a[3], c->d[0]) != 0) { printf("T2GEN V0.60 WRITE32_STOP: pc=000272 addr=%06lx\n", (unsigned long)c->a[3]); return -3; }
          c->cycles += 12u;
          if (!match16(b, 0x274u, 0x51ccu)) return -1;
          { uint16_t count = (uint16_t)(c->d[4] - 1u);
            c->d[4] = (c->d[4] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x000272u : 0x000278u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x000272u:
        {
          if (!match16(b, 0x272u, 0x2680u)) return -1;
          if (native_bus_write32((struct t2bus *)b, c->a[3], c->d[0]) != 0) { printf("T2GEN V0.60 WRITE32_STOP: pc=000272 addr=%06lx\n", (unsigned long)c->a[3]); return -3; }
          c->cycles += 12u;
          if (!match16(b, 0x274u, 0x51ccu)) return -1;
          { uint16_t count = (uint16_t)(c->d[4] - 1u);
            c->d[4] = (c->d[4] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x000272u : 0x000278u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x000278u:
        {
          if (!match16(b, 0x278u, 0x7a03u)) return -1;
          c->d[5] = (uint32_t)(int32_t)(3);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[5] & 0x80000000u) ? 8u : 0u) | (c->d[5] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x27au, 0x175du)) return -1;
          if (!match16(b, 0x27cu, 0x0011u)) return -1;
          if (native_bus_read8(b, c->a[5], &byte_value) != 0) return -3;
          if (native_bus_write8((struct t2bus *)b, (c->a[3] + (uint32_t)(17)) & 0xffffffu, byte_value) != 0) return -3;
          c->a[5] = (c->a[5] + 1u) & 0xffffffu;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 128u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 16u;
          if (!match16(b, 0x27eu, 0x51cdu)) return -1;
          { uint16_t count = (uint16_t)(c->d[5] - 1u);
            c->d[5] = (c->d[5] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00027au : 0x000282u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00027au:
        {
          if (!match16(b, 0x27au, 0x175du)) return -1;
          if (!match16(b, 0x27cu, 0x0011u)) return -1;
          if (native_bus_read8(b, c->a[5], &byte_value) != 0) return -3;
          if (native_bus_write8((struct t2bus *)b, (c->a[3] + (uint32_t)(17)) & 0xffffffu, byte_value) != 0) return -3;
          c->a[5] = (c->a[5] + 1u) & 0xffffffu;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 128u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 16u;
          if (!match16(b, 0x27eu, 0x51cdu)) return -1;
          { uint16_t count = (uint16_t)(c->d[5] - 1u);
            c->d[5] = (c->d[5] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00027au : 0x000282u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x000282u:
        {
          if (!match16(b, 0x282u, 0x3480u)) return -1;
          if (native_bus_write16((struct t2bus *)b, c->a[2], (uint16_t)c->d[0]) != 0) { printf("T2GEN V0.57 WRITE16_STOP: pc=000282 addr=%06lx\n", (unsigned long)c->a[2]); return -3; }
          c->cycles += 8u;
          if (!match16(b, 0x284u, 0x4cd6u)) return -1;
          if (!match16(b, 0x286u, 0x7fffu)) return -1;
          { uint32_t base = c->a[6], val; unsigned idx;
            for (idx = 0; idx < 16u; ++idx)
              {
                if ((0x7fffu & (1u << idx)) == 0u) continue;
                if (native_bus_read32(b, base, &val) != 0)
                  { printf("T2GEN V0.63 MOVEM_READ_STOP: pc=000284 addr=%06lx\n", (unsigned long)base); return -3; }
                if (idx < 8u) c->d[idx] = val;
                else c->a[idx - 8u] = val;
                base = (base + 4u) & 0xffffffu;
              }
          }
          c->cycles += 12u + 8u * 15u;
          if (!match16(b, 0x288u, 0x46fcu)) return -1;
          if (!match16(b, 0x28au, 0x2700u)) return -1;
          if (!(c->sr & 0x2000u)) return -3;
          c->sr = 0x2700u;
          c->cycles += 12u;
          if (!match16(b, 0x28cu, 0x606cu)) return -1;
          c->pc = (1) ? 0x0002fau : 0x00028eu;
          c->cycles += (1) ? 10u : 8u;
          return 0;
        }
      case 0x00028cu:
        {
          if (!match16(b, 0x28cu, 0x606cu)) return -1;
          c->pc = (1) ? 0x0002fau : 0x00028eu;
          c->cycles += (1) ? 10u : 8u;
          return 0;
        }
      case 0x0002fau:
        {
          if (!match16(b, 0x2fau, 0x4a79u)) return -1;
          if (!match32(b, 0x2fcu, 0x00c00004u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00c00004u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x300u, 0x4280u)) return -1;
          c->d[0] = 0u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 6u;
          if (!match16(b, 0x302u, 0x1039u)) return -1;
          if (!match32(b, 0x304u, 0x00a10001u)) return -1;
          if (native_bus_read8(b, 0x00a10001u, &byte_value) != 0) return -3;
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 0x80u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 16u;
          if (!match16(b, 0x308u, 0xec08u)) return -1;
          { uint32_t old = c->d[0] & 255u;
            uint32_t carry = (old >> 5) & 1u;
            uint32_t result = old >> 6;
            c->d[0] = (c->d[0] & 0xffffff00u) | result;
            c->sr = (uint16_t)((c->sr & 0xffe0u) | (carry ? 0x11u : 0u) | (result == 0u ? 4u : 0u) | (result & 0x80u ? 8u : 0u));
            c->cycles += 6u + 2u * 6u;
          }
          if (!match16(b, 0x30au, 0x0200u)) return -1;
          if (!match16(b, 0x30cu, 0x0003u)) return -1;
          c->d[0] = (c->d[0] & 0xffffff00u) | ((c->d[0] & 255u) & 0x03u);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80u) ? 8u : 0u) | ((c->d[0] & 255u) == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x30eu, 0x41fau)) return -1;
          if (!match16(b, 0x310u, 0x0126u)) return -1;
          c->a[0] = 0x000436u;
          c->cycles += 8u;
          if (!match16(b, 0x312u, 0x1030u)) return -1;
          if(!match16(b,0x314u,0x0000u))return -1;
          if(native_bus_read8(b,(c->a[0]+((uint32_t)(int32_t)(int16_t)c->d[0])+(uint32_t)(0))&0xffffffu,&byte_value)!=0)return -3;
          c->d[0]=(c->d[0]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&128u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=14u;
          if (!match16(b, 0x316u, 0x4a00u)) return -1;
          { uint8_t v = (uint8_t)c->d[0];
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 128u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 4u;
          }
          if (!match16(b, 0x318u, 0x6700u)) return -1;
          if (!match16(b, 0x31au, 0x00e4u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x0003feu : 0x00031cu;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00031cu:
        {
          if (!match16(b, 0x31cu, 0x41f9u)) return -1;
          if (!match32(b, 0x31eu, 0x000001f0u)) return -1;
          c->a[0] = 0x000001f0u;
          c->cycles += 12u;
          if (!match16(b, 0x322u, 0x323cu)) return -1;
          if (!match16(b, 0x324u, 0x000fu)) return -1;
          c->d[1] = (c->d[1] & 0xffff0000u) | 0x000fu;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x000fu & 0x8000u) ? 8u : 0u) | (0x000fu == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x326u, 0xb010u)) return -1;
          if (native_bus_read8(b, c->a[0], &byte_value) != 0) return -3;
          { uint32_t x = c->d[0] & 255u, y = byte_value, r = (x-y) & 255u;
            uint16_t flags = (uint16_t)((r & 128u ? 8u : 0u) | (r == 0u ? 4u : 0u) | (((x ^ y) & (r ^ x) & 128u) ? 2u : 0u) | (y > x ? 1u : 0u));
            c->sr = (uint16_t)((c->sr & 0xfff0u) | flags);
          }
          c->cycles += 8u;
          if (!match16(b, 0x328u, 0x6700u)) return -1;
          if (!match16(b, 0x32au, 0x0366u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x000690u : 0x00032cu;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x000326u:
        {
          if (!match16(b, 0x326u, 0xb010u)) return -1;
          if (native_bus_read8(b, c->a[0], &byte_value) != 0) return -3;
          { uint32_t x = c->d[0] & 255u, y = byte_value, r = (x-y) & 255u;
            uint16_t flags = (uint16_t)((r & 128u ? 8u : 0u) | (r == 0u ? 4u : 0u) | (((x ^ y) & (r ^ x) & 128u) ? 2u : 0u) | (y > x ? 1u : 0u));
            c->sr = (uint16_t)((c->sr & 0xfff0u) | flags);
          }
          c->cycles += 8u;
          if (!match16(b, 0x328u, 0x6700u)) return -1;
          if (!match16(b, 0x32au, 0x0366u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x000690u : 0x00032cu;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00032cu:
        {
          if (!match16(b, 0x32cu, 0x5288u)) return -1;
          c->a[0] = (c->a[0] + 1u) & 0xffffffu;
          c->cycles += 8u;
          if (!match16(b, 0x32eu, 0x51c9u)) return -1;
          { uint16_t count = (uint16_t)(c->d[1] - 1u);
            c->d[1] = (c->d[1] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x000326u : 0x000332u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x000332u:
        {
          if (!match16(b, 0x332u, 0x49f9u)) return -1;
          if (!match32(b, 0x334u, 0x00c00000u)) return -1;
          c->a[4] = 0x00c00000u;
          c->cycles += 12u;
          if (!match16(b, 0x338u, 0x4bf9u)) return -1;
          if (!match32(b, 0x33au, 0x00c00004u)) return -1;
          c->a[5] = 0x00c00004u;
          c->cycles += 12u;
          c->pc = 0x00033eu;
          return 0;
        }
      case 0x0003feu:
        {
          if (!match16(b, 0x3feu, 0x60feu)) return -1;
          c->pc = (1) ? 0x0003feu : 0x000400u;
          c->cycles += (1) ? 10u : 8u;
          return 0;
        }
      case 0x000690u:
        {
          if (!match16(b, 0x690u, 0x4ef9u)) return -1;
          if (!match32(b, 0x692u, 0x000ffe6eu)) return -1;
          c->pc = 0x0ffe6eu;
          c->cycles += 12u;
          return 0;
        }
      case 0x004a00u:
        {
          if (!match16(b, 0x4a00u, 0x23d8u)) return -1;
          { uint32_t v; if(native_bus_read32(b,c->a[0],&v)!=0)return -3;
            c->a[0]=(c->a[0]+4u)&0xffffffu;
            if(native_bus_write32((struct t2bus *)b,0x00c00000u,v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=28u;
          if (!match16(b, 0x4a06u, 0x51c8u)) return -1;
          { uint16_t count = (uint16_t)(c->d[0] - 1u);
            c->d[0] = (c->d[0] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x004a00u : 0x004a0au;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x004a0au:
        {
          if (!match16(b, 0x4a0au, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x004a28u:
        {
          if (!match16(b, 0x4a28u, 0x41f9u)) return -1;
          if (!match32(b, 0x4a2au, 0x00ff0002u)) return -1;
          c->a[0] = 0x00ff0002u;
          c->cycles += 12u;
          if (!match16(b, 0x4a2eu, 0x303cu)) return -1;
          if (!match16(b, 0x4a30u, 0x0139u)) return -1;
          c->d[0] = (c->d[0] & 0xffff0000u) | 0x0139u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0139u & 0x8000u) ? 8u : 0u) | (0x0139u == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x4a32u, 0x10fcu)) return -1;
          if (!match16(b, 0x4a34u, 0x0000u)) return -1;
          if (native_bus_write8((struct t2bus *)b, c->a[0] & 0xffffffu, 0x00u) != 0)
            { printf("T2GEN V0.71 WRITE_FAULT: PC=004a32 opcode=10fc EA=A0 addr=%06lx size=B value=00 D0=%08lx A0=%08lx A4=%08lx A7=%06lx SR=%04x\n", (unsigned long)(c->a[0] & 0xffffffu), (unsigned long)c->d[0], (unsigned long)c->a[0], (unsigned long)c->a[4], (unsigned long)c->a[7], (unsigned)c->sr); return -3; }
          c->a[0] = (c->a[0] + 1u) & 0xffffffu;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x4a36u, 0x51c8u)) return -1;
          { uint16_t count = (uint16_t)(c->d[0] - 1u);
            c->d[0] = (c->d[0] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x004a32u : 0x004a3au;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x004a32u:
        {
          if (!match16(b, 0x4a32u, 0x10fcu)) return -1;
          if (!match16(b, 0x4a34u, 0x0000u)) return -1;
          if (native_bus_write8((struct t2bus *)b, c->a[0] & 0xffffffu, 0x00u) != 0)
            { printf("T2GEN V0.71 WRITE_FAULT: PC=004a32 opcode=10fc EA=A0 addr=%06lx size=B value=00 D0=%08lx A0=%08lx A4=%08lx A7=%06lx SR=%04x\n", (unsigned long)(c->a[0] & 0xffffffu), (unsigned long)c->d[0], (unsigned long)c->a[0], (unsigned long)c->a[4], (unsigned long)c->a[7], (unsigned)c->sr); return -3; }
          c->a[0] = (c->a[0] + 1u) & 0xffffffu;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x4a36u, 0x51c8u)) return -1;
          { uint16_t count = (uint16_t)(c->d[0] - 1u);
            c->d[0] = (c->d[0] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x004a32u : 0x004a3au;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x004a3au:
        {
          if (!match16(b, 0x4a3au, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x004a3cu:
        {
          if (!match16(b, 0x4a3cu, 0x41f9u)) return -1;
          if (!match32(b, 0x4a3eu, 0x00ff014au)) return -1;
          c->a[0] = 0x00ff014au;
          c->cycles += 12u;
          if (!match16(b, 0x4a42u, 0x303cu)) return -1;
          if (!match16(b, 0x4a44u, 0x0a95u)) return -1;
          c->d[0] = (c->d[0] & 0xffff0000u) | 0x0a95u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0a95u & 0x8000u) ? 8u : 0u) | (0x0a95u == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x4a46u, 0x10fcu)) return -1;
          if (!match16(b, 0x4a48u, 0x0000u)) return -1;
          if (native_bus_write8((struct t2bus *)b, c->a[0] & 0xffffffu, 0x00u) != 0)
            { printf("T2GEN V0.71 WRITE_FAULT: PC=004a46 opcode=10fc EA=A0 addr=%06lx size=B value=00 D0=%08lx A0=%08lx A4=%08lx A7=%06lx SR=%04x\n", (unsigned long)(c->a[0] & 0xffffffu), (unsigned long)c->d[0], (unsigned long)c->a[0], (unsigned long)c->a[4], (unsigned long)c->a[7], (unsigned)c->sr); return -3; }
          c->a[0] = (c->a[0] + 1u) & 0xffffffu;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x4a4au, 0x51c8u)) return -1;
          { uint16_t count = (uint16_t)(c->d[0] - 1u);
            c->d[0] = (c->d[0] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x004a46u : 0x004a4eu;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x004a46u:
        {
          if (!match16(b, 0x4a46u, 0x10fcu)) return -1;
          if (!match16(b, 0x4a48u, 0x0000u)) return -1;
          if (native_bus_write8((struct t2bus *)b, c->a[0] & 0xffffffu, 0x00u) != 0)
            { printf("T2GEN V0.71 WRITE_FAULT: PC=004a46 opcode=10fc EA=A0 addr=%06lx size=B value=00 D0=%08lx A0=%08lx A4=%08lx A7=%06lx SR=%04x\n", (unsigned long)(c->a[0] & 0xffffffu), (unsigned long)c->d[0], (unsigned long)c->a[0], (unsigned long)c->a[4], (unsigned long)c->a[7], (unsigned)c->sr); return -3; }
          c->a[0] = (c->a[0] + 1u) & 0xffffffu;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x4a4au, 0x51c8u)) return -1;
          { uint16_t count = (uint16_t)(c->d[0] - 1u);
            c->d[0] = (c->d[0] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x004a46u : 0x004a4eu;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x004a4eu:
        {
          if (!match16(b, 0x4a4eu, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x004a50u:
        {
          if (!match16(b, 0x4a50u, 0x223cu)) return -1;
          if (!match32(b, 0x4a52u, 0x000003ffu)) return -1;
          c->d[1] = 0x000003ffu;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x000003ffu & 0x80000000u) ? 8u : 0u) | (0x000003ffu == 0u ? 4u : 0u));
          c->cycles += 12u;
          if (!match16(b, 0x4a56u, 0x23fcu)) return -1;
          if (!match32(b, 0x4a58u, 0x60000003u) || !match32(b, 0x4a5cu, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0x60000003u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=004a56 addr=00c00004 value=60000003\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x60000003u & 0x80000000u) ? 8u : 0u) | (0x60000003u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x4a60u, 0x23c0u)) return -1;
          { uint32_t v=c->d[0]; if(native_bus_write32((struct t2bus *)b,0x00c00000u,v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=20u;
          if (!match16(b, 0x4a66u, 0x51c9u)) return -1;
          { uint16_t count = (uint16_t)(c->d[1] - 1u);
            c->d[1] = (c->d[1] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x004a60u : 0x004a6au;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x004a60u:
        {
          if (!match16(b, 0x4a60u, 0x23c0u)) return -1;
          { uint32_t v=c->d[0]; if(native_bus_write32((struct t2bus *)b,0x00c00000u,v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=20u;
          if (!match16(b, 0x4a66u, 0x51c9u)) return -1;
          { uint16_t count = (uint16_t)(c->d[1] - 1u);
            c->d[1] = (c->d[1] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x004a60u : 0x004a6au;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x004a6au:
        {
          if (!match16(b, 0x4a6au, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x004a6cu:
        {
          if (!match16(b, 0x4a6cu, 0x223cu)) return -1;
          if (!match32(b, 0x4a6eu, 0x000003ffu)) return -1;
          c->d[1] = 0x000003ffu;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x000003ffu & 0x80000000u) ? 8u : 0u) | (0x000003ffu == 0u ? 4u : 0u));
          c->cycles += 12u;
          if (!match16(b, 0x4a72u, 0x23fcu)) return -1;
          if (!match32(b, 0x4a74u, 0x40000003u) || !match32(b, 0x4a78u, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0x40000003u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=004a72 addr=00c00004 value=40000003\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x40000003u & 0x80000000u) ? 8u : 0u) | (0x40000003u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x4a7cu, 0x23c0u)) return -1;
          { uint32_t v=c->d[0]; if(native_bus_write32((struct t2bus *)b,0x00c00000u,v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=20u;
          if (!match16(b, 0x4a82u, 0x51c9u)) return -1;
          { uint16_t count = (uint16_t)(c->d[1] - 1u);
            c->d[1] = (c->d[1] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x004a7cu : 0x004a86u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x004a7cu:
        {
          if (!match16(b, 0x4a7cu, 0x23c0u)) return -1;
          { uint32_t v=c->d[0]; if(native_bus_write32((struct t2bus *)b,0x00c00000u,v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=20u;
          if (!match16(b, 0x4a82u, 0x51c9u)) return -1;
          { uint16_t count = (uint16_t)(c->d[1] - 1u);
            c->d[1] = (c->d[1] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x004a7cu : 0x004a86u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x004a86u:
        {
          if (!match16(b, 0x4a86u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x004a88u:
        {
          if (!match16(b, 0x4a88u, 0x700fu)) return -1;
          c->d[0] = (uint32_t)(int32_t)(15);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x4a8au, 0x23fcu)) return -1;
          if (!match32(b, 0x4a8cu, 0xc0000000u) || !match32(b, 0x4a90u, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0xc0000000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=004a8a addr=00c00004 value=c0000000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xc0000000u & 0x80000000u) ? 8u : 0u) | (0xc0000000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x4a94u, 0x23d8u)) return -1;
          { uint32_t v; if(native_bus_read32(b,c->a[0],&v)!=0)return -3;
            c->a[0]=(c->a[0]+4u)&0xffffffu;
            if(native_bus_write32((struct t2bus *)b,0x00c00000u,v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=28u;
          if (!match16(b, 0x4a9au, 0x51c8u)) return -1;
          { uint16_t count = (uint16_t)(c->d[0] - 1u);
            c->d[0] = (c->d[0] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x004a94u : 0x004a9eu;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x004a94u:
        {
          if (!match16(b, 0x4a94u, 0x23d8u)) return -1;
          { uint32_t v; if(native_bus_read32(b,c->a[0],&v)!=0)return -3;
            c->a[0]=(c->a[0]+4u)&0xffffffu;
            if(native_bus_write32((struct t2bus *)b,0x00c00000u,v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=28u;
          if (!match16(b, 0x4a9au, 0x51c8u)) return -1;
          { uint16_t count = (uint16_t)(c->d[0] - 1u);
            c->d[0] = (c->d[0] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x004a94u : 0x004a9eu;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x004a9eu:
        {
          if (!match16(b, 0x4a9eu, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x004aa0u:
        {
          if (!match16(b, 0x4aa0u, 0x203cu)) return -1;
          if (!match32(b, 0x4aa2u, 0x00003fffu)) return -1;
          c->d[0] = 0x00003fffu;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00003fffu & 0x80000000u) ? 8u : 0u) | (0x00003fffu == 0u ? 4u : 0u));
          c->cycles += 12u;
          if (!match16(b, 0x4aa6u, 0x23fcu)) return -1;
          if (!match32(b, 0x4aa8u, 0x40000000u) || !match32(b, 0x4aacu, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0x40000000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=004aa6 addr=00c00004 value=40000000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x40000000u & 0x80000000u) ? 8u : 0u) | (0x40000000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x4ab0u, 0x23fcu)) return -1;
          if (!match32(b, 0x4ab2u, 0x00000000u) || !match32(b, 0x4ab6u, 0x00c00000u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00000u, 0x00000000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=004ab0 addr=00c00000 value=00000000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00000000u & 0x80000000u) ? 8u : 0u) | (0x00000000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x4abau, 0x51c8u)) return -1;
          { uint16_t count = (uint16_t)(c->d[0] - 1u);
            c->d[0] = (c->d[0] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x004ab0u : 0x004abeu;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x004ab0u:
        {
          if (!match16(b, 0x4ab0u, 0x23fcu)) return -1;
          if (!match32(b, 0x4ab2u, 0x00000000u) || !match32(b, 0x4ab6u, 0x00c00000u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00000u, 0x00000000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=004ab0 addr=00c00000 value=00000000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00000000u & 0x80000000u) ? 8u : 0u) | (0x00000000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x4abau, 0x51c8u)) return -1;
          { uint16_t count = (uint16_t)(c->d[0] - 1u);
            c->d[0] = (c->d[0] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x004ab0u : 0x004abeu;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x004abeu:
        {
          if (!match16(b, 0x4abeu, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x004ac0u:
        {
          if (!match16(b, 0x4ac0u, 0x41f9u)) return -1;
          if (!match32(b, 0x4ac2u, 0x00a10000u)) return -1;
          c->a[0] = 0x00a10000u;
          c->cycles += 12u;
          if (!match16(b, 0x4ac6u, 0x33fcu)) return -1;
          if (!match16(b, 0x4ac8u, 0x0100u) || !match32(b, 0x4acau, 0x00a11100u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00a11100u, 0x0100u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0100u & 0x8000u) ? 8u : 0u) | (0x0100u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x4aceu, 0x0839u)) return -1;
          if (!match16(b, 0x4ad0u, 0x0000u) || !match32(b, 0x4ad2u, 0x00a11100u)) return -1;
          if (native_bus_read8(b, 0x00a11100u, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 0)) ? 0u : 4u));
          c->cycles += 16u;
          if (!match16(b, 0x4ad6u, 0x66f6u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x004aceu : 0x004ad8u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x004aceu:
        {
          if (!match16(b, 0x4aceu, 0x0839u)) return -1;
          if (!match16(b, 0x4ad0u, 0x0000u) || !match32(b, 0x4ad2u, 0x00a11100u)) return -1;
          if (native_bus_read8(b, 0x00a11100u, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 0)) ? 0u : 4u));
          c->cycles += 16u;
          if (!match16(b, 0x4ad6u, 0x66f6u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x004aceu : 0x004ad8u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x004ad8u:
        {
          if (!match16(b, 0x4ad8u, 0x4eb9u)) return -1;
          if (!match32(b, 0x4adau, 0x00004af6u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x004adeu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004af6u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x004adeu:
        {
          if (!match16(b, 0x4adeu, 0x13c2u)) return -1;
          if (!match32(b,0x4ae0u,0x00ff0006u)) return -1;
          byte_value=(uint8_t)c->d[2];
          if (native_bus_write8((struct t2bus *)b,0x00ff0006u,byte_value)!=0) return -3;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0x4ae4u, 0x5488u)) return -1;
          c->a[0] = (c->a[0] + 2u) & 0xffffffu;
          c->cycles += 8u;
          if (!match16(b, 0x4ae6u, 0x4eb9u)) return -1;
          if (!match32(b, 0x4ae8u, 0x00004af6u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x004aecu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004af6u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x004aecu:
        {
          if (!match16(b, 0x4aecu, 0x33fcu)) return -1;
          if (!match16(b, 0x4aeeu, 0x0000u) || !match32(b, 0x4af0u, 0x00a11100u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00a11100u, 0x0000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x4af4u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x004af6u:
        {
          if (!match16(b, 0x4af6u, 0x4202u)) return -1;
          c->d[2] &= 0xffffff00u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 4u;
          if (!match16(b, 0x4af8u, 0x117cu)) return -1;
          { uint32_t v=0x40u; uint32_t addr=(c->a[0]+(int16_t)0x0009u)&0xffffffu;
            if(native_bus_write8((struct t2bus *)b,addr,(uint8_t)v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&128u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=16u;
          if (!match16(b, 0x4afeu, 0x117cu)) return -1;
          { uint32_t v=0x40u; uint32_t addr=(c->a[0]+(int16_t)0x0003u)&0xffffffu;
            if(native_bus_write8((struct t2bus *)b,addr,(uint8_t)v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&128u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=16u;
          if (!match16(b, 0x4b04u, 0x4e71u)) return -1;
          c->cycles += 4u;
          if (!match16(b, 0x4b06u, 0x4e71u)) return -1;
          c->cycles += 4u;
          if (!match16(b, 0x4b08u, 0x1028u)) return -1;
          if(native_bus_read8(b,(c->a[0]+(int16_t)0x0003u)&0xffffffu,&byte_value)!=0)return -3;
          c->d[0]=(c->d[0]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&128u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=12u;
          if (!match16(b, 0x4b0cu, 0x117cu)) return -1;
          { uint32_t v=0x00u; uint32_t addr=(c->a[0]+(int16_t)0x0003u)&0xffffffu;
            if(native_bus_write8((struct t2bus *)b,addr,(uint8_t)v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&128u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=16u;
          if (!match16(b, 0x4b12u, 0x4e71u)) return -1;
          c->cycles += 4u;
          if (!match16(b, 0x4b14u, 0x4e71u)) return -1;
          c->cycles += 4u;
          if (!match16(b, 0x4b16u, 0x1228u)) return -1;
          if(native_bus_read8(b,(c->a[0]+(int16_t)0x0003u)&0xffffffu,&byte_value)!=0)return -3;
          c->d[1]=(c->d[1]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&128u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=12u;
          if (!match16(b, 0x4b1au, 0x0801u)) return -1;
          c->sr=(uint16_t)((c->sr&~4u)|((c->d[1]&(1u<<4))?0u:4u));
          c->cycles+=10u;
          if (!match16(b, 0x4b1eu, 0x660au)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x004b2au : 0x004b20u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x004b20u:
        {
          if (!match16(b, 0x4b20u, 0x08c2u)) return -1;
          if(!match16(b,0x4b22u,0x0004u))return -1;
          c->sr=(uint16_t)((c->sr&~4u)|((c->d[2]&(1u<<4))?0u:4u));
          c->d[2]|=(1u<<4);
          c->cycles+=12u;
          if (!match16(b, 0x4b24u, 0x50f9u)) return -1;
          if (!match32(b,0x4b26u,0x00ff0002u)) return -1;
          if (native_bus_write8((struct t2bus *)b,0x00ff0002u,0xffu)!=0) return -3;
          c->cycles+=12u;
          if (!match16(b, 0x4b2au, 0x0800u)) return -1;
          if (!match16(b, 0x4b2cu, 0x0004u)) return -1;
          c->sr = (uint16_t)((c->sr & ~4u) | ((c->d[0] & (1u << 4)) ? 0u : 4u));
          c->cycles += 10u;
          if (!match16(b, 0x4b2eu, 0x660au)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x004b3au : 0x004b30u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x004b2au:
        {
          if (!match16(b, 0x4b2au, 0x0800u)) return -1;
          if (!match16(b, 0x4b2cu, 0x0004u)) return -1;
          c->sr = (uint16_t)((c->sr & ~4u) | ((c->d[0] & (1u << 4)) ? 0u : 4u));
          c->cycles += 10u;
          if (!match16(b, 0x4b2eu, 0x660au)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x004b3au : 0x004b30u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x004b30u:
        {
          if (!match16(b, 0x4b30u, 0x08c2u)) return -1;
          if(!match16(b,0x4b32u,0x0005u))return -1;
          c->sr=(uint16_t)((c->sr&~4u)|((c->d[2]&(1u<<5))?0u:4u));
          c->d[2]|=(1u<<5);
          c->cycles+=12u;
          if (!match16(b, 0x4b34u, 0x50f9u)) return -1;
          if (!match32(b,0x4b36u,0x00ff0003u)) return -1;
          if (native_bus_write8((struct t2bus *)b,0x00ff0003u,0xffu)!=0) return -3;
          c->cycles+=12u;
          if (!match16(b, 0x4b3au, 0x0800u)) return -1;
          if (!match16(b, 0x4b3cu, 0x0005u)) return -1;
          c->sr = (uint16_t)((c->sr & ~4u) | ((c->d[0] & (1u << 5)) ? 0u : 4u));
          c->cycles += 10u;
          if (!match16(b, 0x4b3eu, 0x660au)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x004b4au : 0x004b40u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x004b3au:
        {
          if (!match16(b, 0x4b3au, 0x0800u)) return -1;
          if (!match16(b, 0x4b3cu, 0x0005u)) return -1;
          c->sr = (uint16_t)((c->sr & ~4u) | ((c->d[0] & (1u << 5)) ? 0u : 4u));
          c->cycles += 10u;
          if (!match16(b, 0x4b3eu, 0x660au)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x004b4au : 0x004b40u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x004b40u:
        {
          if (!match16(b, 0x4b40u, 0x08c2u)) return -1;
          if(!match16(b,0x4b42u,0x0006u))return -1;
          c->sr=(uint16_t)((c->sr&~4u)|((c->d[2]&(1u<<6))?0u:4u));
          c->d[2]|=(1u<<6);
          c->cycles+=12u;
          if (!match16(b, 0x4b44u, 0x50f9u)) return -1;
          if (!match32(b,0x4b46u,0x00ff0004u)) return -1;
          if (native_bus_write8((struct t2bus *)b,0x00ff0004u,0xffu)!=0) return -3;
          c->cycles+=12u;
          if (!match16(b, 0x4b4au, 0x0801u)) return -1;
          c->sr=(uint16_t)((c->sr&~4u)|((c->d[1]&(1u<<5))?0u:4u));
          c->cycles+=10u;
          if (!match16(b, 0x4b4eu, 0x660au)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x004b5au : 0x004b50u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x004b4au:
        {
          if (!match16(b, 0x4b4au, 0x0801u)) return -1;
          c->sr=(uint16_t)((c->sr&~4u)|((c->d[1]&(1u<<5))?0u:4u));
          c->cycles+=10u;
          if (!match16(b, 0x4b4eu, 0x660au)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x004b5au : 0x004b50u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x004b50u:
        {
          if (!match16(b, 0x4b50u, 0x08c2u)) return -1;
          if(!match16(b,0x4b52u,0x0007u))return -1;
          c->sr=(uint16_t)((c->sr&~4u)|((c->d[2]&(1u<<7))?0u:4u));
          c->d[2]|=(1u<<7);
          c->cycles+=12u;
          if (!match16(b, 0x4b54u, 0x50f9u)) return -1;
          if (!match32(b,0x4b56u,0x00ff0005u)) return -1;
          if (native_bus_write8((struct t2bus *)b,0x00ff0005u,0xffu)!=0) return -3;
          c->cycles+=12u;
          if (!match16(b, 0x4b5au, 0x4640u)) return -1;
          { uint16_t v=(uint16_t)~c->d[0];
            c->d[0]=(c->d[0]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=4u;
          if (!match16(b, 0x4b5cu, 0x0200u)) return -1;
          if (!match16(b, 0x4b5eu, 0x000fu)) return -1;
          c->d[0] = (c->d[0] & 0xffffff00u) | ((c->d[0] & 255u) & 0x0fu);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80u) ? 8u : 0u) | ((c->d[0] & 255u) == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x4b60u, 0x8400u)) return -1;
          { uint8_t v=(uint8_t)(c->d[2] | c->d[0]);
            c->d[2]=(c->d[2]&0xffffff00u)|v;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=4u;
          if (!match16(b, 0x4b62u, 0x13c2u)) return -1;
          if (!match32(b,0x4b64u,0x00ff0007u)) return -1;
          byte_value=(uint8_t)c->d[2];
          if (native_bus_write8((struct t2bus *)b,0x00ff0007u,byte_value)!=0) return -3;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0x4b68u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x004b5au:
        {
          if (!match16(b, 0x4b5au, 0x4640u)) return -1;
          { uint16_t v=(uint16_t)~c->d[0];
            c->d[0]=(c->d[0]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=4u;
          if (!match16(b, 0x4b5cu, 0x0200u)) return -1;
          if (!match16(b, 0x4b5eu, 0x000fu)) return -1;
          c->d[0] = (c->d[0] & 0xffffff00u) | ((c->d[0] & 255u) & 0x0fu);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80u) ? 8u : 0u) | ((c->d[0] & 255u) == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x4b60u, 0x8400u)) return -1;
          { uint8_t v=(uint8_t)(c->d[2] | c->d[0]);
            c->d[2]=(c->d[2]&0xffffff00u)|v;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=4u;
          if (!match16(b, 0x4b62u, 0x13c2u)) return -1;
          if (!match32(b,0x4b64u,0x00ff0007u)) return -1;
          byte_value=(uint8_t)c->d[2];
          if (native_bus_write8((struct t2bus *)b,0x00ff0007u,byte_value)!=0) return -3;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0x4b68u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x004b6au:
        {
          if (!match16(b, 0x4b6au, 0x33fcu)) return -1;
          if (!match16(b, 0x4b6cu, 0x8004u) || !match32(b, 0x4b6eu, 0x00ff010au)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff010au, 0x8004u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x8004u & 0x8000u) ? 8u : 0u) | (0x8004u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x4b72u, 0x33f9u)) return -1;
          if (!match32(b, 0x4b74u, 0x00ff010au) || !match32(b, 0x4b78u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010au, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x4b7cu, 0x33fcu)) return -1;
          if (!match16(b, 0x4b7eu, 0x8144u) || !match32(b, 0x4b80u, 0x00ff010cu)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff010cu, 0x8144u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x8144u & 0x8000u) ? 8u : 0u) | (0x8144u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x4b84u, 0x33f9u)) return -1;
          if (!match32(b, 0x4b86u, 0x00ff010cu) || !match32(b, 0x4b8au, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x4b8eu, 0x33fcu)) return -1;
          if (!match16(b, 0x4b90u, 0x8238u) || !match32(b, 0x4b92u, 0x00ff010eu)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff010eu, 0x8238u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x8238u & 0x8000u) ? 8u : 0u) | (0x8238u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x4b96u, 0x33f9u)) return -1;
          if (!match32(b, 0x4b98u, 0x00ff010eu) || !match32(b, 0x4b9cu, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010eu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x4ba0u, 0x33fcu)) return -1;
          if (!match16(b, 0x4ba2u, 0x8300u) || !match32(b, 0x4ba4u, 0x00ff0110u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0110u, 0x8300u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x8300u & 0x8000u) ? 8u : 0u) | (0x8300u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x4ba8u, 0x33f9u)) return -1;
          if (!match32(b, 0x4baau, 0x00ff0110u) || !match32(b, 0x4baeu, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0110u, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x4bb2u, 0x33fcu)) return -1;
          if (!match16(b, 0x4bb4u, 0x8406u) || !match32(b, 0x4bb6u, 0x00ff0112u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0112u, 0x8406u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x8406u & 0x8000u) ? 8u : 0u) | (0x8406u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x4bbau, 0x33f9u)) return -1;
          if (!match32(b, 0x4bbcu, 0x00ff0112u) || !match32(b, 0x4bc0u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0112u, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x4bc4u, 0x33fcu)) return -1;
          if (!match16(b, 0x4bc6u, 0x8568u) || !match32(b, 0x4bc8u, 0x00ff0114u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0114u, 0x8568u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x8568u & 0x8000u) ? 8u : 0u) | (0x8568u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x4bccu, 0x33f9u)) return -1;
          if (!match32(b, 0x4bceu, 0x00ff0114u) || !match32(b, 0x4bd2u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0114u, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x4bd6u, 0x33fcu)) return -1;
          if (!match16(b, 0x4bd8u, 0x8600u) || !match32(b, 0x4bdau, 0x00ff0116u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0116u, 0x8600u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x8600u & 0x8000u) ? 8u : 0u) | (0x8600u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x4bdeu, 0x33f9u)) return -1;
          if (!match32(b, 0x4be0u, 0x00ff0116u) || !match32(b, 0x4be4u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0116u, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x4be8u, 0x33fcu)) return -1;
          if (!match16(b, 0x4beau, 0x8700u) || !match32(b, 0x4becu, 0x00ff0118u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0118u, 0x8700u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x8700u & 0x8000u) ? 8u : 0u) | (0x8700u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x4bf0u, 0x33f9u)) return -1;
          if (!match32(b, 0x4bf2u, 0x00ff0118u) || !match32(b, 0x4bf6u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0118u, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x4bfau, 0x33fcu)) return -1;
          if (!match16(b, 0x4bfcu, 0x8800u) || !match32(b, 0x4bfeu, 0x00ff011au)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff011au, 0x8800u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x8800u & 0x8000u) ? 8u : 0u) | (0x8800u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x4c02u, 0x33f9u)) return -1;
          if (!match32(b, 0x4c04u, 0x00ff011au) || !match32(b, 0x4c08u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff011au, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x4c0cu, 0x33fcu)) return -1;
          if (!match16(b, 0x4c0eu, 0x8900u) || !match32(b, 0x4c10u, 0x00ff011cu)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff011cu, 0x8900u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x8900u & 0x8000u) ? 8u : 0u) | (0x8900u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x4c14u, 0x33f9u)) return -1;
          if (!match32(b, 0x4c16u, 0x00ff011cu) || !match32(b, 0x4c1au, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff011cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x4c1eu, 0x33fcu)) return -1;
          if (!match16(b, 0x4c20u, 0x8a00u) || !match32(b, 0x4c22u, 0x00ff011eu)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff011eu, 0x8a00u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x8a00u & 0x8000u) ? 8u : 0u) | (0x8a00u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x4c26u, 0x33f9u)) return -1;
          if (!match32(b, 0x4c28u, 0x00ff011eu) || !match32(b, 0x4c2cu, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff011eu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x4c30u, 0x33fcu)) return -1;
          if (!match16(b, 0x4c32u, 0x8b00u) || !match32(b, 0x4c34u, 0x00ff0120u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0120u, 0x8b00u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x8b00u & 0x8000u) ? 8u : 0u) | (0x8b00u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x4c38u, 0x33f9u)) return -1;
          if (!match32(b, 0x4c3au, 0x00ff0120u) || !match32(b, 0x4c3eu, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0120u, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x4c42u, 0x33fcu)) return -1;
          if (!match16(b, 0x4c44u, 0x8c00u) || !match32(b, 0x4c46u, 0x00ff0122u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0122u, 0x8c00u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x8c00u & 0x8000u) ? 8u : 0u) | (0x8c00u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x4c4au, 0x33f9u)) return -1;
          if (!match32(b, 0x4c4cu, 0x00ff0122u) || !match32(b, 0x4c50u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0122u, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x4c54u, 0x33fcu)) return -1;
          if (!match16(b, 0x4c56u, 0x8d3cu) || !match32(b, 0x4c58u, 0x00ff0124u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0124u, 0x8d3cu) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x8d3cu & 0x8000u) ? 8u : 0u) | (0x8d3cu == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x4c5cu, 0x33f9u)) return -1;
          if (!match32(b, 0x4c5eu, 0x00ff0124u) || !match32(b, 0x4c62u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0124u, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x4c66u, 0x33fcu)) return -1;
          if (!match16(b, 0x4c68u, 0x8e00u) || !match32(b, 0x4c6au, 0x00ff0126u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0126u, 0x8e00u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x8e00u & 0x8000u) ? 8u : 0u) | (0x8e00u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x4c6eu, 0x33f9u)) return -1;
          if (!match32(b, 0x4c70u, 0x00ff0126u) || !match32(b, 0x4c74u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0126u, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x4c78u, 0x33fcu)) return -1;
          if (!match16(b, 0x4c7au, 0x8f02u) || !match32(b, 0x4c7cu, 0x00ff0128u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0128u, 0x8f02u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x8f02u & 0x8000u) ? 8u : 0u) | (0x8f02u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x4c80u, 0x33f9u)) return -1;
          if (!match32(b, 0x4c82u, 0x00ff0128u) || !match32(b, 0x4c86u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0128u, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x4c8au, 0x33fcu)) return -1;
          if (!match16(b, 0x4c8cu, 0x9001u) || !match32(b, 0x4c8eu, 0x00ff012au)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff012au, 0x9001u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x9001u & 0x8000u) ? 8u : 0u) | (0x9001u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x4c92u, 0x33f9u)) return -1;
          if (!match32(b, 0x4c94u, 0x00ff012au) || !match32(b, 0x4c98u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff012au, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x4c9cu, 0x33fcu)) return -1;
          if (!match16(b, 0x4c9eu, 0x9100u) || !match32(b, 0x4ca0u, 0x00ff012cu)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff012cu, 0x9100u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x9100u & 0x8000u) ? 8u : 0u) | (0x9100u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x4ca4u, 0x33f9u)) return -1;
          if (!match32(b, 0x4ca6u, 0x00ff012cu) || !match32(b, 0x4caau, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff012cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x4caeu, 0x33fcu)) return -1;
          if (!match16(b, 0x4cb0u, 0x9200u) || !match32(b, 0x4cb2u, 0x00ff012eu)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff012eu, 0x9200u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x9200u & 0x8000u) ? 8u : 0u) | (0x9200u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x4cb6u, 0x33f9u)) return -1;
          if (!match32(b, 0x4cb8u, 0x00ff012eu) || !match32(b, 0x4cbcu, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff012eu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x4cc0u, 0x33fcu)) return -1;
          if (!match16(b, 0x4cc2u, 0x93ffu) || !match32(b, 0x4cc4u, 0x00ff0130u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0130u, 0x93ffu) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x93ffu & 0x8000u) ? 8u : 0u) | (0x93ffu == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x4cc8u, 0x33f9u)) return -1;
          if (!match32(b, 0x4ccau, 0x00ff0130u) || !match32(b, 0x4cceu, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0130u, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x4cd2u, 0x33fcu)) return -1;
          if (!match16(b, 0x4cd4u, 0x94ffu) || !match32(b, 0x4cd6u, 0x00ff0132u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0132u, 0x94ffu) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x94ffu & 0x8000u) ? 8u : 0u) | (0x94ffu == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x4cdau, 0x33f9u)) return -1;
          if (!match32(b, 0x4cdcu, 0x00ff0132u) || !match32(b, 0x4ce0u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0132u, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x4ce4u, 0x33fcu)) return -1;
          if (!match16(b, 0x4ce6u, 0x9500u) || !match32(b, 0x4ce8u, 0x00ff0134u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0134u, 0x9500u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x9500u & 0x8000u) ? 8u : 0u) | (0x9500u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x4cecu, 0x33f9u)) return -1;
          if (!match32(b, 0x4ceeu, 0x00ff0134u) || !match32(b, 0x4cf2u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0134u, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x4cf6u, 0x33fcu)) return -1;
          if (!match16(b, 0x4cf8u, 0x9600u) || !match32(b, 0x4cfau, 0x00ff0136u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0136u, 0x9600u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x9600u & 0x8000u) ? 8u : 0u) | (0x9600u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x4cfeu, 0x33f9u)) return -1;
          if (!match32(b, 0x4d00u, 0x00ff0136u) || !match32(b, 0x4d04u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0136u, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x4d08u, 0x33fcu)) return -1;
          if (!match16(b, 0x4d0au, 0x9780u) || !match32(b, 0x4d0cu, 0x00ff0138u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0138u, 0x9780u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x9780u & 0x8000u) ? 8u : 0u) | (0x9780u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x4d10u, 0x33f9u)) return -1;
          if (!match32(b, 0x4d12u, 0x00ff0138u) || !match32(b, 0x4d16u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0138u, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x4d1au, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x004d1cu:
        {
          if (!match16(b, 0x4d1cu, 0x23fcu)) return -1;
          if (!match32(b, 0x4d1eu, 0x000ffe6au) || !match32(b, 0x4d22u, 0x00ff0138u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff0138u, 0x000ffe6au) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=004d1c addr=00ff0138 value=000ffe6a\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x000ffe6au & 0x80000000u) ? 8u : 0u) | (0x000ffe6au == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x4d26u, 0x46fcu)) return -1;
          if (!match16(b, 0x4d28u, 0x2000u)) return -1;
          if (!(c->sr & 0x2000u)) return -3;
          c->sr = 0x2000u;
          c->cycles += 12u;
          if (!match16(b, 0x4d2au, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x004d2cu:
        {
          if (!match16(b, 0x4d2cu, 0x48e7u)) return -1;
          if (!match16(b, 0x4d2eu, 0xfffeu)) return -1;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->a[6]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->a[5]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->a[4]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->a[3]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->a[2]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->a[1]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->a[0]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[7]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[6]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[5]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[4]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[3]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[2]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[1]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[0]) != 0) return -3;
          c->cycles += 128u;
          if (!match16(b, 0x4d30u, 0x2079u)) return -1;
          if (!match32(b, 0x4d32u, 0x00ff0138u)) return -1;
          if (native_bus_read32(b, 0x00ff0138u, &c->a[0]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0x4d36u, 0x4e90u)) return -1;
          { uint32_t target=c->a[0] & 0xffffffu;
            uint32_t sp=(c->a[7]-4u)&0xffffffu;
            if(native_bus_write32((struct t2bus *)b,sp,0x004d38u)!=0)return -3;
            c->a[7]=sp; c->pc=target; c->cycles+=16u;
            printf("T2GEN V0.94 IRQ6_CALLBACK: pointer_addr=FF0138 target=%06lx return=004d38\n",(unsigned long)target);
          }
          return 0;
        }
      case 0x004d38u:
        {
          if (!match16(b, 0x4d38u, 0x4cdfu)) return -1;
          if (!match16(b, 0x4d3au, 0x7fffu)) return -1;
          { uint32_t addr = c->a[7]; uint32_t val; uint16_t word; unsigned idx;
            for (idx = 0; idx < 16u; ++idx)
              {
                if (!(0x7fffu & (1u << idx))) continue;
                if (native_bus_read32(b, addr, &val) != 0) return -3;
                if (idx < 8u) c->d[idx] = val;
                else c->a[idx - 8u] = val;
                addr = (addr + 4u) & 0xffffffu;
              }
            c->a[7] = addr; /* postincrement wins if base An is in mask */
          }
          c->cycles += 128u;
          if (!match16(b, 0x4d3cu, 0x4e73u)) return -1;
          { uint16_t old_sr; uint32_t old_pc;
            if (!(c->sr & 0x2000u)) return -3;
            if (native_bus_read16(b, c->a[7], &old_sr) || native_bus_read32(b, c->a[7]+2u, &old_pc)) return -3;
            c->a[7] = (c->a[7] + 6u) & 0xffffffu;
            if (!(old_sr & 0x2000u)) { uint32_t ssp=c->a[7]; c->a[7]=c->usp; c->usp=ssp; }
            c->sr = old_sr; c->pc = old_pc & 0xffffffu; c->cycles += 20u;
            printf("T2GEN V0.93 RTE: pc=%06lx SR=%04x\n", (unsigned long)c->pc, (unsigned)c->sr);
          }
          return 0;
          c->pc = 0x004d3eu;
          return 0;
        }
      case 0x004d3eu:
        {
          if (!match16(b, 0x4d3eu, 0x6100u)) return -1;
          if (!match16(b, 0x4d40u, 0xfe2au)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x004d42u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004b6au;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x004d42u:
        {
          if (!match16(b, 0x4d42u, 0x61d8u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x004d44u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004d1cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x004d44u:
        {
          if (!match16(b, 0x4d44u, 0x41f9u)) return -1;
          if (!match32(b, 0x4d46u, 0x00004e04u)) return -1;
          c->a[0] = 0x00004e04u;
          c->cycles += 12u;
          if (!match16(b, 0x4d4au, 0x23fcu)) return -1;
          if (!match32(b, 0x4d4cu, 0x40000010u) || !match32(b, 0x4d50u, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0x40000010u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=004d4a addr=00c00004 value=40000010\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x40000010u & 0x80000000u) ? 8u : 0u) | (0x40000010u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x4d54u, 0x33fcu)) return -1;
          if (!match16(b, 0x4d56u, 0x0000u) || !match32(b, 0x4d58u, 0x00c00000u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00c00000u, 0x0000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x4d5cu, 0x33fcu)) return -1;
          if (!match16(b, 0x4d5eu, 0x0000u) || !match32(b, 0x4d60u, 0x00c00000u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00c00000u, 0x0000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x4d64u, 0x23fcu)) return -1;
          if (!match32(b, 0x4d66u, 0x70000003u) || !match32(b, 0x4d6au, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0x70000003u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=004d64 addr=00c00004 value=70000003\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x70000003u & 0x80000000u) ? 8u : 0u) | (0x70000003u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x4d6eu, 0x33fcu)) return -1;
          if (!match16(b, 0x4d70u, 0x0000u) || !match32(b, 0x4d72u, 0x00c00000u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00c00000u, 0x0000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x4d76u, 0x33fcu)) return -1;
          if (!match16(b, 0x4d78u, 0x0000u) || !match32(b, 0x4d7au, 0x00c00000u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00c00000u, 0x0000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x4d7eu, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x004d9au:
        {
          if (!match16(b, 0x4d9au, 0x47f9u)) return -1;
          if (!match32(b, 0x4d9cu, 0x00ff0009u)) return -1;
          c->a[3] = 0x00ff0009u;
          c->cycles += 12u;
          if (!match16(b, 0x4da0u, 0x43f9u)) return -1;
          if (!match32(b, 0x4da2u, 0x00c00000u)) return -1;
          c->a[1] = 0x00c00000u;
          c->cycles += 12u;
          if (!match16(b, 0x4da6u, 0x7200u)) return -1;
          c->d[1] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x4da8u, 0x1018u)) return -1;
          if (native_bus_read8(b, c->a[0], &byte_value) != 0) return -3;
          c->a[0] = (c->a[0] + 1u) & 0xffffffu;
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 128u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x4daau, 0x6b1eu)) return -1;
          c->pc = (c->sr & 8u) ? 0x004dcau : 0x004dacu;
          c->cycles += (c->sr & 8u) ? 10u : 8u;
          return 0;
        }
      case 0x004da8u:
        {
          if (!match16(b, 0x4da8u, 0x1018u)) return -1;
          if (native_bus_read8(b, c->a[0], &byte_value) != 0) return -3;
          c->a[0] = (c->a[0] + 1u) & 0xffffffu;
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 128u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x4daau, 0x6b1eu)) return -1;
          c->pc = (c->sr & 8u) ? 0x004dcau : 0x004dacu;
          c->cycles += (c->sr & 8u) ? 10u : 8u;
          return 0;
        }
      case 0x004dacu:
        {
          if (!match16(b, 0x4dacu, 0x0240u)) return -1;
          if (!match16(b, 0x4daeu, 0x00ffu)) return -1;
          { uint16_t v=(uint16_t)c->d[0] & 0x00ffu; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x4db0u, 0x1618u)) return -1;
          if (native_bus_read8(b, c->a[0], &byte_value) != 0) return -3;
          c->a[0] = (c->a[0] + 1u) & 0xffffffu;
          c->d[3] = (c->d[3] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 128u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x4db2u, 0x1783u)) return -1;
          if (!match16(b,0x4db4u,0x1000u)) return -1;
          { uint32_t ea=(uint32_t)(c->a[3]+((int32_t)(int16_t)(c->d[1]&0xffffu))+(0));
            byte_value=(uint8_t)c->d[3];
            if (native_bus_write8((struct t2bus *)b,ea&0xffffffu,byte_value)!=0) return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          }
          c->cycles+=18u;
          if (!match16(b, 0x4db6u, 0x5201u)) return -1;
          { uint32_t dst=c->d[1]&255u,src=1u,r=(dst+src)&255u;
            c->d[1]=(c->d[1]&0xffffff00u)|r;
            uint16_t cy=((dst+src)>255u)?1u:0u;
            uint16_t ov=((~(dst^src)&(dst^r)&128u)!=0u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&128u)?8u:0u)|(r==0u?4u:0u)|ov|cy|(cy?16u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0x4db8u, 0x0801u)) return -1;
          c->sr=(uint16_t)((c->sr&~4u)|((c->d[1]&(1u<<0))?0u:4u));
          c->cycles+=10u;
          if (!match16(b, 0x4dbcu, 0x6600u)) return -1;
          if (!match16(b, 0x4dbeu, 0x0004u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x004dc2u : 0x004dc0u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x004db0u:
        {
          if (!match16(b, 0x4db0u, 0x1618u)) return -1;
          if (native_bus_read8(b, c->a[0], &byte_value) != 0) return -3;
          c->a[0] = (c->a[0] + 1u) & 0xffffffu;
          c->d[3] = (c->d[3] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 128u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x4db2u, 0x1783u)) return -1;
          if (!match16(b,0x4db4u,0x1000u)) return -1;
          { uint32_t ea=(uint32_t)(c->a[3]+((int32_t)(int16_t)(c->d[1]&0xffffu))+(0));
            byte_value=(uint8_t)c->d[3];
            if (native_bus_write8((struct t2bus *)b,ea&0xffffffu,byte_value)!=0) return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          }
          c->cycles+=18u;
          if (!match16(b, 0x4db6u, 0x5201u)) return -1;
          { uint32_t dst=c->d[1]&255u,src=1u,r=(dst+src)&255u;
            c->d[1]=(c->d[1]&0xffffff00u)|r;
            uint16_t cy=((dst+src)>255u)?1u:0u;
            uint16_t ov=((~(dst^src)&(dst^r)&128u)!=0u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&128u)?8u:0u)|(r==0u?4u:0u)|ov|cy|(cy?16u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0x4db8u, 0x0801u)) return -1;
          c->sr=(uint16_t)((c->sr&~4u)|((c->d[1]&(1u<<0))?0u:4u));
          c->cycles+=10u;
          if (!match16(b, 0x4dbcu, 0x6600u)) return -1;
          if (!match16(b, 0x4dbeu, 0x0004u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x004dc2u : 0x004dc0u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x004dc0u:
        {
          if (!match16(b, 0x4dc0u, 0x3283u)) return -1;
          if (native_bus_write16((struct t2bus *)b, c->a[1], (uint16_t)c->d[3]) != 0) { printf("T2GEN V0.57 WRITE16_STOP: pc=004dc0 addr=%06lx\n", (unsigned long)c->a[1]); return -3; }
          c->cycles += 8u;
          if (!match16(b, 0x4dc2u, 0xe143u)) return -1;
          { uint32_t v=c->d[3]&65535u; uint16_t carry=0,overflow=0; unsigned i;
            for(i=0;i<8u;i++){uint32_t n=(v<<1)&65535u;carry=(v>>15)&1u;if((v^n)&0x8000u)overflow=2u;v=n;}
            c->d[3]=(c->d[3]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)|overflow|(carry?17u:0u)); }
          c->cycles+=22u;
          if (!match16(b, 0x4dc4u, 0x51c8u)) return -1;
          { uint16_t count = (uint16_t)(c->d[0] - 1u);
            c->d[0] = (c->d[0] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x004db0u : 0x004dc8u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x004dc2u:
        {
          if (!match16(b, 0x4dc2u, 0xe143u)) return -1;
          { uint32_t v=c->d[3]&65535u; uint16_t carry=0,overflow=0; unsigned i;
            for(i=0;i<8u;i++){uint32_t n=(v<<1)&65535u;carry=(v>>15)&1u;if((v^n)&0x8000u)overflow=2u;v=n;}
            c->d[3]=(c->d[3]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)|overflow|(carry?17u:0u)); }
          c->cycles+=22u;
          if (!match16(b, 0x4dc4u, 0x51c8u)) return -1;
          { uint16_t count = (uint16_t)(c->d[0] - 1u);
            c->d[0] = (c->d[0] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x004db0u : 0x004dc8u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x004dc8u:
        {
          if (!match16(b, 0x4dc8u, 0x60deu)) return -1;
          c->pc = (1) ? 0x004da8u : 0x004dcau;
          c->cycles += (1) ? 10u : 8u;
          return 0;
        }
      case 0x004dcau:
        {
          if (!match16(b, 0x4dcau, 0x0240u)) return -1;
          if (!match16(b, 0x4dccu, 0x00ffu)) return -1;
          { uint16_t v=(uint16_t)c->d[0] & 0x00ffu; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x4dceu, 0x7400u)) return -1;
          c->d[2] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[2] & 0x80000000u) ? 8u : 0u) | (c->d[2] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x4dd0u, 0x1401u)) return -1;
          byte_value=(uint8_t)c->d[1];
          c->d[2]=(c->d[2]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=4u;
          if (!match16(b, 0x4dd2u, 0xd400u)) return -1;
          { uint32_t x=c->d[2]&255u,y=c->d[0]&255u,r=(x+y)&255u;
            c->d[2]=(c->d[2]&0xffffff00u)|r;
            uint16_t carry=(x+y)>255u,ov=((~(x^y))&(x^r)&128u)!=0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&128u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?17u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0x4dd4u, 0x1018u)) return -1;
          if (native_bus_read8(b, c->a[0], &byte_value) != 0) return -3;
          c->a[0] = (c->a[0] + 1u) & 0xffffffu;
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 128u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x4dd6u, 0x6724u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x004dfcu : 0x004dd8u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x004dd8u:
        {
          if (!match16(b, 0x4dd8u, 0x0240u)) return -1;
          if (!match16(b, 0x4ddau, 0x00ffu)) return -1;
          { uint16_t v=(uint16_t)c->d[0] & 0x00ffu; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x4ddcu, 0x5340u)) return -1;
          {uint32_t dst=c->d[0]&65535u,src=1u,r=(dst-src)&65535u;
           c->d[0]=(c->d[0]&0xffff0000u)|r;
           uint16_t cy=(dst<src),ov=((dst^src)&(dst^r)&32768u)!=0u;
           c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(cy?17u:0u));}
          c->cycles+=4u;
          if (!match16(b, 0x4ddeu, 0x1633u)) return -1;
          if(!match16(b,0x4de0u,0x2000u))return -1;
          if(native_bus_read8(b,(c->a[3]+((uint32_t)(int32_t)(int16_t)c->d[2])+(uint32_t)(0))&0xffffffu,&byte_value)!=0)return -3;
          c->d[3]=(c->d[3]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&128u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=14u;
          if (!match16(b, 0x4de2u, 0x1783u)) return -1;
          if (!match16(b,0x4de4u,0x1000u)) return -1;
          { uint32_t ea=(uint32_t)(c->a[3]+((int32_t)(int16_t)(c->d[1]&0xffffu))+(0));
            byte_value=(uint8_t)c->d[3];
            if (native_bus_write8((struct t2bus *)b,ea&0xffffffu,byte_value)!=0) return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          }
          c->cycles+=18u;
          if (!match16(b, 0x4de6u, 0x5202u)) return -1;
          { uint32_t dst=c->d[2]&255u,src=1u,r=(dst+src)&255u;
            c->d[2]=(c->d[2]&0xffffff00u)|r;
            uint16_t cy=((dst+src)>255u)?1u:0u;
            uint16_t ov=((~(dst^src)&(dst^r)&128u)!=0u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&128u)?8u:0u)|(r==0u?4u:0u)|ov|cy|(cy?16u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0x4de8u, 0x5201u)) return -1;
          { uint32_t dst=c->d[1]&255u,src=1u,r=(dst+src)&255u;
            c->d[1]=(c->d[1]&0xffffff00u)|r;
            uint16_t cy=((dst+src)>255u)?1u:0u;
            uint16_t ov=((~(dst^src)&(dst^r)&128u)!=0u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&128u)?8u:0u)|(r==0u?4u:0u)|ov|cy|(cy?16u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0x4deau, 0x0801u)) return -1;
          c->sr=(uint16_t)((c->sr&~4u)|((c->d[1]&(1u<<0))?0u:4u));
          c->cycles+=10u;
          if (!match16(b, 0x4deeu, 0x6600u)) return -1;
          if (!match16(b, 0x4df0u, 0x0004u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x004df4u : 0x004df2u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x004ddeu:
        {
          if (!match16(b, 0x4ddeu, 0x1633u)) return -1;
          if(!match16(b,0x4de0u,0x2000u))return -1;
          if(native_bus_read8(b,(c->a[3]+((uint32_t)(int32_t)(int16_t)c->d[2])+(uint32_t)(0))&0xffffffu,&byte_value)!=0)return -3;
          c->d[3]=(c->d[3]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&128u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=14u;
          if (!match16(b, 0x4de2u, 0x1783u)) return -1;
          if (!match16(b,0x4de4u,0x1000u)) return -1;
          { uint32_t ea=(uint32_t)(c->a[3]+((int32_t)(int16_t)(c->d[1]&0xffffu))+(0));
            byte_value=(uint8_t)c->d[3];
            if (native_bus_write8((struct t2bus *)b,ea&0xffffffu,byte_value)!=0) return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          }
          c->cycles+=18u;
          if (!match16(b, 0x4de6u, 0x5202u)) return -1;
          { uint32_t dst=c->d[2]&255u,src=1u,r=(dst+src)&255u;
            c->d[2]=(c->d[2]&0xffffff00u)|r;
            uint16_t cy=((dst+src)>255u)?1u:0u;
            uint16_t ov=((~(dst^src)&(dst^r)&128u)!=0u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&128u)?8u:0u)|(r==0u?4u:0u)|ov|cy|(cy?16u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0x4de8u, 0x5201u)) return -1;
          { uint32_t dst=c->d[1]&255u,src=1u,r=(dst+src)&255u;
            c->d[1]=(c->d[1]&0xffffff00u)|r;
            uint16_t cy=((dst+src)>255u)?1u:0u;
            uint16_t ov=((~(dst^src)&(dst^r)&128u)!=0u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&128u)?8u:0u)|(r==0u?4u:0u)|ov|cy|(cy?16u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0x4deau, 0x0801u)) return -1;
          c->sr=(uint16_t)((c->sr&~4u)|((c->d[1]&(1u<<0))?0u:4u));
          c->cycles+=10u;
          if (!match16(b, 0x4deeu, 0x6600u)) return -1;
          if (!match16(b, 0x4df0u, 0x0004u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x004df4u : 0x004df2u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x004df2u:
        {
          if (!match16(b, 0x4df2u, 0x3283u)) return -1;
          if (native_bus_write16((struct t2bus *)b, c->a[1], (uint16_t)c->d[3]) != 0) { printf("T2GEN V0.57 WRITE16_STOP: pc=004df2 addr=%06lx\n", (unsigned long)c->a[1]); return -3; }
          c->cycles += 8u;
          if (!match16(b, 0x4df4u, 0xe143u)) return -1;
          { uint32_t v=c->d[3]&65535u; uint16_t carry=0,overflow=0; unsigned i;
            for(i=0;i<8u;i++){uint32_t n=(v<<1)&65535u;carry=(v>>15)&1u;if((v^n)&0x8000u)overflow=2u;v=n;}
            c->d[3]=(c->d[3]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)|overflow|(carry?17u:0u)); }
          c->cycles+=22u;
          if (!match16(b, 0x4df6u, 0x51c8u)) return -1;
          { uint16_t count = (uint16_t)(c->d[0] - 1u);
            c->d[0] = (c->d[0] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x004ddeu : 0x004dfau;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x004df4u:
        {
          if (!match16(b, 0x4df4u, 0xe143u)) return -1;
          { uint32_t v=c->d[3]&65535u; uint16_t carry=0,overflow=0; unsigned i;
            for(i=0;i<8u;i++){uint32_t n=(v<<1)&65535u;carry=(v>>15)&1u;if((v^n)&0x8000u)overflow=2u;v=n;}
            c->d[3]=(c->d[3]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)|overflow|(carry?17u:0u)); }
          c->cycles+=22u;
          if (!match16(b, 0x4df6u, 0x51c8u)) return -1;
          { uint16_t count = (uint16_t)(c->d[0] - 1u);
            c->d[0] = (c->d[0] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x004ddeu : 0x004dfau;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x004dfau:
        {
          if (!match16(b, 0x4dfau, 0x60acu)) return -1;
          c->pc = (1) ? 0x004da8u : 0x004dfcu;
          c->cycles += (1) ? 10u : 8u;
          return 0;
        }
      case 0x004dfcu:
        {
          if (!match16(b, 0x4dfcu, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x004f48u:
        {
          if (!match16(b, 0x4f48u, 0x6100u)) return -1;
          if (!match16(b, 0x4f4au, 0xfdf4u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x004f4cu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004d3eu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x004f4cu:
        {
          if (!match16(b, 0x4f4cu, 0x41f8u)) return -1;
          if (!match16(b, 0x4f4eu, 0x0696u)) return -1;
          c->a[0] = 0x000696u;
          c->cycles += 8u;
          if (!match16(b, 0x4f50u, 0x23fcu)) return -1;
          if (!match32(b, 0x4f52u, 0x40200000u) || !match32(b, 0x4f56u, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0x40200000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=004f50 addr=00c00004 value=40200000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x40200000u & 0x80000000u) ? 8u : 0u) | (0x40200000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x4f5au, 0x6100u)) return -1;
          if (!match16(b, 0x4f5cu, 0xfe3eu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x004f5eu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004d9au;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x004f5eu:
        {
          if (!match16(b, 0x4f5eu, 0x41f8u)) return -1;
          if (!match16(b, 0x4f60u, 0x4e84u)) return -1;
          c->a[0] = 0x004e84u;
          c->cycles += 8u;
          if (!match16(b, 0x4f62u, 0x6100u)) return -1;
          if (!match16(b, 0x4f64u, 0x01f8u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x004f66u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00515cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x004f66u:
        {
          if (!match16(b, 0x4f66u, 0x6100u)) return -1;
          if (!match16(b, 0x4f68u, 0x0026u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x004f6au) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004f8eu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x004f6au:
        {
          if (!match16(b, 0x4f6au, 0x6100u)) return -1;
          if (!match16(b, 0x4f6cu, 0x00feu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x004f6eu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00506au;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x004f6eu:
        {
          if (!match16(b, 0x4f6eu, 0x6100u)) return -1;
          if (!match16(b, 0x4f70u, 0xfb50u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x004f72u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004ac0u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x004f72u:
        {
          if (!match16(b, 0x4f72u, 0x1039u)) return -1;
          if (!match32(b, 0x4f74u, 0x00ff0006u)) return -1;
          if (native_bus_read8(b, 0x00ff0006u, &byte_value) != 0) return -3;
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 0x80u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 16u;
          if (!match16(b, 0x4f78u, 0x0800u)) return -1;
          if (!match16(b, 0x4f7au, 0x0002u)) return -1;
          c->sr = (uint16_t)((c->sr & ~4u) | ((c->d[0] & (1u << 2)) ? 0u : 4u));
          c->cycles += 10u;
          if (!match16(b, 0x4f7cu, 0x6700u)) return -1;
          if (!match16(b, 0x4f7eu, 0x000eu)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x004f8cu : 0x004f80u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x004f80u:
        {
          if (!match16(b, 0x4f80u, 0x33fcu)) return -1;
          if (!match16(b, 0x4f82u, 0x0000u) || !match32(b, 0x4f84u, 0x00ff0000u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0000u, 0x0000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x4f88u, 0x6000u)) return -1;
          if (!match16(b, 0x4f8au, 0xb276u)) return -1;
          c->pc = (1) ? 0x000200u : 0x004f8cu;
          c->cycles += (1) ? 10u : 8u;
          return 0;
        }
      case 0x004f8cu:
        {
          if (!match16(b, 0x4f8cu, 0x60d8u)) return -1;
          c->pc = (1) ? 0x004f66u : 0x004f8eu;
          c->cycles += (1) ? 10u : 8u;
          return 0;
        }
      case 0x004f8eu:
        {
          if (!match16(b, 0x4f8eu, 0x1039u)) return -1;
          if (!match32(b, 0x4f90u, 0x00ff0006u)) return -1;
          if (native_bus_read8(b, 0x00ff0006u, &byte_value) != 0) return -3;
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 0x80u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 16u;
          if (!match16(b, 0x4f94u, 0x0800u)) return -1;
          if (!match16(b, 0x4f96u, 0x0000u)) return -1;
          c->sr = (uint16_t)((c->sr & ~4u) | ((c->d[0] & (1u << 0)) ? 0u : 4u));
          c->cycles += 10u;
          if (!match16(b, 0x4f98u, 0x6700u)) return -1;
          if (!match16(b, 0x4f9au, 0x0008u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x004fa2u : 0x004f9cu;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x004f9cu:
        {
          if (!match16(b, 0x4f9cu, 0x5079u)) return -1;
          if (!match32(b,0x4f9eu,0x00ff0140u)) return -1;
          { uint16_t dst,src=8u,result; if (native_bus_read16(b,0x00ff0140u,&dst)!=0) return -3;
            result=(uint16_t)(dst + src);
            if (native_bus_write16((struct t2bus *)b,0x00ff0140u,result)!=0) return -3;
            uint16_t carry=(uint32_t)dst+src>0xffffu?1u:0u;
            uint16_t overflow=((~(dst^src))&(dst^result)&0x8000u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((result&0x8000u)?8u:0u)|(result==0u?4u:0u)|overflow|carry|(carry?16u:0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x4fa2u, 0x0800u)) return -1;
          if (!match16(b, 0x4fa4u, 0x0001u)) return -1;
          c->sr = (uint16_t)((c->sr & ~4u) | ((c->d[0] & (1u << 1)) ? 0u : 4u));
          c->cycles += 10u;
          if (!match16(b, 0x4fa6u, 0x6700u)) return -1;
          if (!match16(b, 0x4fa8u, 0x0008u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x004fb0u : 0x004faau;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x004fa2u:
        {
          if (!match16(b, 0x4fa2u, 0x0800u)) return -1;
          if (!match16(b, 0x4fa4u, 0x0001u)) return -1;
          c->sr = (uint16_t)((c->sr & ~4u) | ((c->d[0] & (1u << 1)) ? 0u : 4u));
          c->cycles += 10u;
          if (!match16(b, 0x4fa6u, 0x6700u)) return -1;
          if (!match16(b, 0x4fa8u, 0x0008u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x004fb0u : 0x004faau;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x004faau:
        {
          if (!match16(b, 0x4faau, 0x5179u)) return -1;
          if (!match32(b,0x4facu,0x00ff0140u)) return -1;
          { uint16_t dst,src=8u,result; if (native_bus_read16(b,0x00ff0140u,&dst)!=0) return -3;
            result=(uint16_t)(dst - src);
            if (native_bus_write16((struct t2bus *)b,0x00ff0140u,result)!=0) return -3;
            uint16_t carry=dst<src?1u:0u;
            uint16_t overflow=((dst^src)&(dst^result)&0x8000u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((result&0x8000u)?8u:0u)|(result==0u?4u:0u)|overflow|carry|(carry?16u:0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x4fb0u, 0x0800u)) return -1;
          if (!match16(b, 0x4fb2u, 0x0002u)) return -1;
          c->sr = (uint16_t)((c->sr & ~4u) | ((c->d[0] & (1u << 2)) ? 0u : 4u));
          c->cycles += 10u;
          if (!match16(b, 0x4fb4u, 0x6700u)) return -1;
          if (!match16(b, 0x4fb6u, 0x0008u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x004fbeu : 0x004fb8u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x004fb0u:
        {
          if (!match16(b, 0x4fb0u, 0x0800u)) return -1;
          if (!match16(b, 0x4fb2u, 0x0002u)) return -1;
          c->sr = (uint16_t)((c->sr & ~4u) | ((c->d[0] & (1u << 2)) ? 0u : 4u));
          c->cycles += 10u;
          if (!match16(b, 0x4fb4u, 0x6700u)) return -1;
          if (!match16(b, 0x4fb6u, 0x0008u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x004fbeu : 0x004fb8u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x004fb8u:
        {
          if (!match16(b, 0x4fb8u, 0x5479u)) return -1;
          if (!match32(b,0x4fbau,0x00ff0140u)) return -1;
          { uint16_t dst,src=2u,result; if (native_bus_read16(b,0x00ff0140u,&dst)!=0) return -3;
            result=(uint16_t)(dst + src);
            if (native_bus_write16((struct t2bus *)b,0x00ff0140u,result)!=0) return -3;
            uint16_t carry=(uint32_t)dst+src>0xffffu?1u:0u;
            uint16_t overflow=((~(dst^src))&(dst^result)&0x8000u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((result&0x8000u)?8u:0u)|(result==0u?4u:0u)|overflow|carry|(carry?16u:0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x4fbeu, 0x0800u)) return -1;
          if (!match16(b, 0x4fc0u, 0x0003u)) return -1;
          c->sr = (uint16_t)((c->sr & ~4u) | ((c->d[0] & (1u << 3)) ? 0u : 4u));
          c->cycles += 10u;
          if (!match16(b, 0x4fc2u, 0x6700u)) return -1;
          if (!match16(b, 0x4fc4u, 0x0008u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x004fccu : 0x004fc6u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x004fbeu:
        {
          if (!match16(b, 0x4fbeu, 0x0800u)) return -1;
          if (!match16(b, 0x4fc0u, 0x0003u)) return -1;
          c->sr = (uint16_t)((c->sr & ~4u) | ((c->d[0] & (1u << 3)) ? 0u : 4u));
          c->cycles += 10u;
          if (!match16(b, 0x4fc2u, 0x6700u)) return -1;
          if (!match16(b, 0x4fc4u, 0x0008u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x004fccu : 0x004fc6u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x004fc6u:
        {
          if (!match16(b, 0x4fc6u, 0x5579u)) return -1;
          if (!match32(b,0x4fc8u,0x00ff0140u)) return -1;
          { uint16_t dst,src=2u,result; if (native_bus_read16(b,0x00ff0140u,&dst)!=0) return -3;
            result=(uint16_t)(dst - src);
            if (native_bus_write16((struct t2bus *)b,0x00ff0140u,result)!=0) return -3;
            uint16_t carry=dst<src?1u:0u;
            uint16_t overflow=((dst^src)&(dst^result)&0x8000u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((result&0x8000u)?8u:0u)|(result==0u?4u:0u)|overflow|carry|(carry?16u:0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x4fccu, 0x0800u)) return -1;
          if (!match16(b, 0x4fceu, 0x0005u)) return -1;
          c->sr = (uint16_t)((c->sr & ~4u) | ((c->d[0] & (1u << 5)) ? 0u : 4u));
          c->cycles += 10u;
          if (!match16(b, 0x4fd0u, 0x6600u)) return -1;
          if (!match16(b, 0x4fd2u, 0x0016u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x004fe8u : 0x004fd4u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x004fccu:
        {
          if (!match16(b, 0x4fccu, 0x0800u)) return -1;
          if (!match16(b, 0x4fceu, 0x0005u)) return -1;
          c->sr = (uint16_t)((c->sr & ~4u) | ((c->d[0] & (1u << 5)) ? 0u : 4u));
          c->cycles += 10u;
          if (!match16(b, 0x4fd0u, 0x6600u)) return -1;
          if (!match16(b, 0x4fd2u, 0x0016u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x004fe8u : 0x004fd4u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x004fd4u:
        {
          if (!match16(b, 0x4fd4u, 0x0800u)) return -1;
          if (!match16(b, 0x4fd6u, 0x0004u)) return -1;
          c->sr = (uint16_t)((c->sr & ~4u) | ((c->d[0] & (1u << 4)) ? 0u : 4u));
          c->cycles += 10u;
          if (!match16(b, 0x4fd8u, 0x6600u)) return -1;
          if (!match16(b, 0x4fdau, 0x000eu)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x004fe8u : 0x004fdcu;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x004fdcu:
        {
          if (!match16(b, 0x4fdcu, 0x33fcu)) return -1;
          if (!match16(b, 0x4fdeu, 0xfffeu) || !match32(b, 0x4fe0u, 0x00ff0146u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0146u, 0xfffeu) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xfffeu & 0x8000u) ? 8u : 0u) | (0xfffeu == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x4fe4u, 0x6000u)) return -1;
          if (!match16(b, 0x4fe6u, 0x0062u)) return -1;
          c->pc = (1) ? 0x005048u : 0x004fe8u;
          c->cycles += (1) ? 10u : 8u;
          return 0;
        }
      case 0x004fe8u:
        {
          if (!match16(b, 0x4fe8u, 0x5279u)) return -1;
          if (!match32(b,0x4feau,0x00ff0146u)) return -1;
          { uint16_t dst,src=1u,result; if (native_bus_read16(b,0x00ff0146u,&dst)!=0) return -3;
            result=(uint16_t)(dst + src);
            if (native_bus_write16((struct t2bus *)b,0x00ff0146u,result)!=0) return -3;
            uint16_t carry=(uint32_t)dst+src>0xffffu?1u:0u;
            uint16_t overflow=((~(dst^src))&(dst^result)&0x8000u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((result&0x8000u)?8u:0u)|(result==0u?4u:0u)|overflow|carry|(carry?16u:0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x4feeu, 0x3239u)) return -1;
          if (!match32(b, 0x4ff0u, 0x00ff0146u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0146u, &val) != 0) return -3;
            c->d[1] = (c->d[1] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x4ff4u, 0x0241u)) return -1;
          if (!match16(b, 0x4ff6u, 0xfff0u)) return -1;
          { uint16_t v=(uint16_t)c->d[1] & 0xfff0u; c->d[1]=(c->d[1] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x4ff8u, 0x6700u)) return -1;
          if (!match16(b, 0x4ffau, 0x004eu)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x005048u : 0x004ffcu;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x004ffcu:
        {
          if (!match16(b, 0x4ffcu, 0x0800u)) return -1;
          if (!match16(b, 0x4ffeu, 0x0004u)) return -1;
          c->sr = (uint16_t)((c->sr & ~4u) | ((c->d[0] & (1u << 4)) ? 0u : 4u));
          c->cycles += 10u;
          if (!match16(b, 0x5000u, 0x6700u)) return -1;
          if (!match16(b, 0x5002u, 0x001cu)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x00501eu : 0x005004u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x005004u:
        {
          if (!match16(b, 0x5004u, 0x1239u)) return -1;
          if (!match32(b,0x5006u,0x00ff013fu)) return -1;
          if (native_bus_read8(b,0x00ff013fu,&byte_value)!=0) return -3;
          c->d[1]=(c->d[1]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0x500au, 0x5201u)) return -1;
          { uint32_t dst=c->d[1]&255u,src=1u,r=(dst+src)&255u;
            c->d[1]=(c->d[1]&0xffffff00u)|r;
            uint16_t cy=((dst+src)>255u)?1u:0u;
            uint16_t ov=((~(dst^src)&(dst^r)&128u)!=0u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&128u)?8u:0u)|(r==0u?4u:0u)|ov|cy|(cy?16u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0x500cu, 0x0c01u)) return -1;
          if (!match16(b, 0x500eu, 0x0040u)) return -1;
          { uint8_t dst=(uint8_t)c->d[1], src=0x40u, result=(uint8_t)(dst-src);
            uint16_t n=(result&0x80u)?8u:0u, z=(result==0u)?4u:0u;
            uint16_t v=((dst^src)&(dst^result)&0x80u)?2u:0u;
            uint16_t carry=(dst<src)?1u:0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|n|z|v|carry);
          }
          c->cycles += 8u;
          if (!match16(b, 0x5010u, 0x6500u)) return -1;
          if (!match16(b, 0x5012u, 0x0006u)) return -1;
          c->pc = ((c->sr & 1u)) ? 0x005018u : 0x005014u;
          c->cycles += ((c->sr & 1u)) ? 10u : 8u;
          return 0;
        }
      case 0x005014u:
        {
          if (!match16(b, 0x5014u, 0x123cu)) return -1;
          byte_value=0xffu;
          c->d[1]=(c->d[1]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&128u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=8u;
          if (!match16(b, 0x5018u, 0x13c1u)) return -1;
          if (!match32(b,0x501au,0x00ff013fu)) return -1;
          byte_value=(uint8_t)c->d[1];
          if (native_bus_write8((struct t2bus *)b,0x00ff013fu,byte_value)!=0) return -3;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0x501eu, 0x0800u)) return -1;
          if (!match16(b, 0x5020u, 0x0005u)) return -1;
          c->sr = (uint16_t)((c->sr & ~4u) | ((c->d[0] & (1u << 5)) ? 0u : 4u));
          c->cycles += 10u;
          if (!match16(b, 0x5022u, 0x6700u)) return -1;
          if (!match16(b, 0x5024u, 0x0024u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x005048u : 0x005026u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x005018u:
        {
          if (!match16(b, 0x5018u, 0x13c1u)) return -1;
          if (!match32(b,0x501au,0x00ff013fu)) return -1;
          byte_value=(uint8_t)c->d[1];
          if (native_bus_write8((struct t2bus *)b,0x00ff013fu,byte_value)!=0) return -3;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0x501eu, 0x0800u)) return -1;
          if (!match16(b, 0x5020u, 0x0005u)) return -1;
          c->sr = (uint16_t)((c->sr & ~4u) | ((c->d[0] & (1u << 5)) ? 0u : 4u));
          c->cycles += 10u;
          if (!match16(b, 0x5022u, 0x6700u)) return -1;
          if (!match16(b, 0x5024u, 0x0024u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x005048u : 0x005026u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00501eu:
        {
          if (!match16(b, 0x501eu, 0x0800u)) return -1;
          if (!match16(b, 0x5020u, 0x0005u)) return -1;
          c->sr = (uint16_t)((c->sr & ~4u) | ((c->d[0] & (1u << 5)) ? 0u : 4u));
          c->cycles += 10u;
          if (!match16(b, 0x5022u, 0x6700u)) return -1;
          if (!match16(b, 0x5024u, 0x0024u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x005048u : 0x005026u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x005026u:
        {
          if (!match16(b, 0x5026u, 0x1239u)) return -1;
          if (!match32(b,0x5028u,0x00ff013fu)) return -1;
          if (native_bus_read8(b,0x00ff013fu,&byte_value)!=0) return -3;
          c->d[1]=(c->d[1]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0x502cu, 0x5301u)) return -1;
          { uint32_t x=c->d[1]&255u,r=(x-1u)&255u;
            c->d[1]=(c->d[1]&0xffffff00u)|r;
            uint16_t carry=x==0u;
            uint16_t ov=x==128u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&128u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?17u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0x502eu, 0x0c01u)) return -1;
          if (!match16(b, 0x5030u, 0x0040u)) return -1;
          { uint8_t dst=(uint8_t)c->d[1], src=0x40u, result=(uint8_t)(dst-src);
            uint16_t n=(result&0x80u)?8u:0u, z=(result==0u)?4u:0u;
            uint16_t v=((dst^src)&(dst^result)&0x80u)?2u:0u;
            uint16_t carry=(dst<src)?1u:0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|n|z|v|carry);
          }
          c->cycles += 8u;
          if (!match16(b, 0x5032u, 0x6500u)) return -1;
          if (!match16(b, 0x5034u, 0x000eu)) return -1;
          c->pc = ((c->sr & 1u)) ? 0x005042u : 0x005036u;
          c->cycles += ((c->sr & 1u)) ? 10u : 8u;
          return 0;
        }
      case 0x005036u:
        {
          if (!match16(b, 0x5036u, 0x0c01u)) return -1;
          if (!match16(b, 0x5038u, 0x00ffu)) return -1;
          { uint8_t dst=(uint8_t)c->d[1], src=0xffu, result=(uint8_t)(dst-src);
            uint16_t n=(result&0x80u)?8u:0u, z=(result==0u)?4u:0u;
            uint16_t v=((dst^src)&(dst^result)&0x80u)?2u:0u;
            uint16_t carry=(dst<src)?1u:0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|n|z|v|carry);
          }
          c->cycles += 8u;
          if (!match16(b, 0x503au, 0x6400u)) return -1;
          if (!match16(b, 0x503cu, 0x0006u)) return -1;
          c->pc = (!(c->sr & 1u)) ? 0x005042u : 0x00503eu;
          c->cycles += (!(c->sr & 1u)) ? 10u : 8u;
          return 0;
        }
      case 0x00503eu:
        {
          if (!match16(b, 0x503eu, 0x123cu)) return -1;
          byte_value=0x3fu;
          c->d[1]=(c->d[1]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&128u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=8u;
          if (!match16(b, 0x5042u, 0x13c1u)) return -1;
          if (!match32(b,0x5044u,0x00ff013fu)) return -1;
          byte_value=(uint8_t)c->d[1];
          if (native_bus_write8((struct t2bus *)b,0x00ff013fu,byte_value)!=0) return -3;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0x5048u, 0x0800u)) return -1;
          if (!match16(b, 0x504au, 0x0006u)) return -1;
          c->sr = (uint16_t)((c->sr & ~4u) | ((c->d[0] & (1u << 6)) ? 0u : 4u));
          c->cycles += 10u;
          if (!match16(b, 0x504cu, 0x6700u)) return -1;
          if (!match16(b, 0x504eu, 0x000au)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x005058u : 0x005050u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x005042u:
        {
          if (!match16(b, 0x5042u, 0x13c1u)) return -1;
          if (!match32(b,0x5044u,0x00ff013fu)) return -1;
          byte_value=(uint8_t)c->d[1];
          if (native_bus_write8((struct t2bus *)b,0x00ff013fu,byte_value)!=0) return -3;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0x5048u, 0x0800u)) return -1;
          if (!match16(b, 0x504au, 0x0006u)) return -1;
          c->sr = (uint16_t)((c->sr & ~4u) | ((c->d[0] & (1u << 6)) ? 0u : 4u));
          c->cycles += 10u;
          if (!match16(b, 0x504cu, 0x6700u)) return -1;
          if (!match16(b, 0x504eu, 0x000au)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x005058u : 0x005050u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x005048u:
        {
          if (!match16(b, 0x5048u, 0x0800u)) return -1;
          if (!match16(b, 0x504au, 0x0006u)) return -1;
          c->sr = (uint16_t)((c->sr & ~4u) | ((c->d[0] & (1u << 6)) ? 0u : 4u));
          c->cycles += 10u;
          if (!match16(b, 0x504cu, 0x6700u)) return -1;
          if (!match16(b, 0x504eu, 0x000au)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x005058u : 0x005050u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x005050u:
        {
          if (!match16(b, 0x5050u, 0x0679u)) return -1;
          { uint16_t v; if(native_bus_read16(b,0x00ff0140u,&v)!=0)return -3;
            uint32_t x=v,y=0x0100u,r=(v+(uint16_t)0x0100u)&65535u;
            if(native_bus_write16((struct t2bus *)b,0x00ff0140u,(uint16_t)r)!=0)return -3;
            uint16_t carry=(x+y)>65535u;
            uint16_t ov=((~(x^y))&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?1u:0u)|(carry?16u:0u));
          }
          c->cycles+=16u;
          if (!match16(b, 0x5058u, 0x0800u)) return -1;
          if (!match16(b, 0x505au, 0x0007u)) return -1;
          c->sr = (uint16_t)((c->sr & ~4u) | ((c->d[0] & (1u << 7)) ? 0u : 4u));
          c->cycles += 10u;
          if (!match16(b, 0x505cu, 0x6700u)) return -1;
          if (!match16(b, 0x505eu, 0x000au)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x005068u : 0x005060u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x005058u:
        {
          if (!match16(b, 0x5058u, 0x0800u)) return -1;
          if (!match16(b, 0x505au, 0x0007u)) return -1;
          c->sr = (uint16_t)((c->sr & ~4u) | ((c->d[0] & (1u << 7)) ? 0u : 4u));
          c->cycles += 10u;
          if (!match16(b, 0x505cu, 0x6700u)) return -1;
          if (!match16(b, 0x505eu, 0x000au)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x005068u : 0x005060u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x005060u:
        {
          if (!match16(b, 0x5060u, 0x0479u)) return -1;
          { uint16_t v; if(native_bus_read16(b,0x00ff0140u,&v)!=0)return -3;
            uint32_t x=v,y=0x0100u,r=(v-(uint16_t)0x0100u)&65535u;
            if(native_bus_write16((struct t2bus *)b,0x00ff0140u,(uint16_t)r)!=0)return -3;
            uint16_t carry=x<y;
            uint16_t ov=((x^y)&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?1u:0u)|(carry?16u:0u));
          }
          c->cycles+=16u;
          if (!match16(b, 0x5068u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x005068u:
        {
          if (!match16(b, 0x5068u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00506au:
        {
          if (!match16(b, 0x506au, 0x41f8u)) return -1;
          if (!match16(b, 0x506cu, 0x4f35u)) return -1;
          c->a[0] = 0x004f35u;
          c->cycles += 8u;
          if (!match16(b, 0x506eu, 0x6100u)) return -1;
          if (!match16(b, 0x5070u, 0x00ecu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005072u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00515cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005072u:
        {
          if (!match16(b, 0x5072u, 0x303cu)) return -1;
          if (!match16(b, 0x5074u, 0x0016u)) return -1;
          c->d[0] = (c->d[0] & 0xffff0000u) | 0x0016u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0016u & 0x8000u) ? 8u : 0u) | (0x0016u == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x5076u, 0x2f39u)) return -1;
          if (!match32(b, 0x5078u, 0x00ff013eu)) return -1;
          { uint32_t val; if (native_bus_read32(b, 0x00ff013eu, &val) != 0) return -3;
            c->a[7] = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, c->a[7], val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x80000000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 24u;
          if (!match16(b, 0x507cu, 0x3f00u)) return -1;
          c->a[7]=(c->a[7]-2u)&0xffffffu;
          if (native_bus_write16((struct t2bus *)b,c->a[7],(uint16_t)c->d[0]) != 0) return -3;
          { uint16_t v=(uint16_t)c->d[0]; c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x507eu, 0x6100u)) return -1;
          if (!match16(b, 0x5080u, 0x001eu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005082u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00509eu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00507cu:
        {
          if (!match16(b, 0x507cu, 0x3f00u)) return -1;
          c->a[7]=(c->a[7]-2u)&0xffffffu;
          if (native_bus_write16((struct t2bus *)b,c->a[7],(uint16_t)c->d[0]) != 0) return -3;
          { uint16_t v=(uint16_t)c->d[0]; c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x507eu, 0x6100u)) return -1;
          if (!match16(b, 0x5080u, 0x001eu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005082u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00509eu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005082u:
        {
          if (!match16(b, 0x5082u, 0x5079u)) return -1;
          if (!match32(b,0x5084u,0x00ff0140u)) return -1;
          { uint16_t dst,src=8u,result; if (native_bus_read16(b,0x00ff0140u,&dst)!=0) return -3;
            result=(uint16_t)(dst + src);
            if (native_bus_write16((struct t2bus *)b,0x00ff0140u,result)!=0) return -3;
            uint16_t carry=(uint32_t)dst+src>0xffffu?1u:0u;
            uint16_t overflow=((~(dst^src))&(dst^result)&0x8000u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((result&0x8000u)?8u:0u)|(result==0u?4u:0u)|overflow|carry|(carry?16u:0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x5088u, 0x41f8u)) return -1;
          if (!match16(b, 0x508au, 0x4f33u)) return -1;
          c->a[0] = 0x004f33u;
          c->cycles += 8u;
          if (!match16(b, 0x508cu, 0x6100u)) return -1;
          if (!match16(b, 0x508eu, 0x00ceu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005090u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00515cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005090u:
        {
          if (!match16(b, 0x5090u, 0x301fu)) return -1;
          { uint16_t v; if(native_bus_read16(b,c->a[7],&v)!=0) return -3;
            c->a[7]=(c->a[7]+2u)&0xffffffu;
            c->d[0]=(c->d[0]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=8u;
          if (!match16(b, 0x5092u, 0x51c8u)) return -1;
          { uint16_t count = (uint16_t)(c->d[0] - 1u);
            c->d[0] = (c->d[0] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00507cu : 0x005096u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x005096u:
        {
          if (!match16(b, 0x5096u, 0x23dfu)) return -1;
          { uint32_t v; if(native_bus_read32(b,c->a[7],&v)!=0)return -3;
            c->a[7]=(c->a[7]+4u)&0xffffffu;
            if(native_bus_write32((struct t2bus *)b,0x00ff013eu,v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=28u;
          if (!match16(b, 0x509cu, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00509eu:
        {
          if (!match16(b, 0x509eu, 0x41f8u)) return -1;
          if (!match16(b, 0x50a0u, 0x4f28u)) return -1;
          c->a[0] = 0x004f28u;
          c->cycles += 8u;
          if (!match16(b, 0x50a2u, 0x6100u)) return -1;
          if (!match16(b, 0x50a4u, 0x00b8u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0050a6u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00515cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0050a6u:
        {
          if (!match16(b, 0x50a6u, 0x2039u)) return -1;
          { uint32_t v; if(native_bus_read32(b,0x00ff013eu,&v)!=0)return -3;
            c->d[0]=v;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=16u;
          if (!match16(b, 0x50acu, 0x6100u)) return -1;
          if (!match16(b, 0x50aeu, 0x0066u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0050b0u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x005114u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0050b0u:
        {
          if (!match16(b, 0x50b0u, 0x41f8u)) return -1;
          if (!match16(b, 0x50b2u, 0x4f30u)) return -1;
          c->a[0] = 0x004f30u;
          c->cycles += 8u;
          if (!match16(b, 0x50b4u, 0x6100u)) return -1;
          if (!match16(b, 0x50b6u, 0x00a6u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0050b8u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00515cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0050b8u:
        {
          if (!match16(b, 0x50b8u, 0x2279u)) return -1;
          if (!match32(b, 0x50bau, 0x00ff013eu)) return -1;
          if (native_bus_read32(b, 0x00ff013eu, &c->a[1]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0x50beu, 0x363cu)) return -1;
          if (!match16(b, 0x50c0u, 0x0003u)) return -1;
          c->d[3] = (c->d[3] & 0xffff0000u) | 0x0003u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0003u & 0x8000u) ? 8u : 0u) | (0x0003u == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x50c2u, 0x103cu)) return -1;
          byte_value=0x20u;
          c->d[0]=(c->d[0]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&128u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=8u;
          if (!match16(b, 0x50c6u, 0x6100u)) return -1;
          if (!match16(b, 0x50c8u, 0x0172u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0050cau) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00523au;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0050c2u:
        {
          if (!match16(b, 0x50c2u, 0x103cu)) return -1;
          byte_value=0x20u;
          c->d[0]=(c->d[0]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&128u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=8u;
          if (!match16(b, 0x50c6u, 0x6100u)) return -1;
          if (!match16(b, 0x50c8u, 0x0172u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0050cau) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00523au;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0050cau:
        {
          if (!match16(b, 0x50cau, 0x3019u)) return -1;
          { uint16_t v; if(native_bus_read16(b,c->a[1],&v)!=0) return -3;
            c->a[1]=(c->a[1]+2u)&0xffffffu;
            c->d[0]=(c->d[0]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=8u;
          if (!match16(b, 0x50ccu, 0x6100u)) return -1;
          if (!match16(b, 0x50ceu, 0x002au)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0050d0u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0050f8u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0050d0u:
        {
          if (!match16(b, 0x50d0u, 0x51cbu)) return -1;
          { uint16_t count = (uint16_t)(c->d[3] - 1u);
            c->d[3] = (c->d[3] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x0050c2u : 0x0050d4u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x0050d4u:
        {
          if (!match16(b, 0x50d4u, 0x41f8u)) return -1;
          if (!match16(b, 0x50d6u, 0x4f2cu)) return -1;
          c->a[0] = 0x004f2cu;
          c->cycles += 8u;
          if (!match16(b, 0x50d8u, 0x6100u)) return -1;
          if (!match16(b, 0x50dau, 0x0082u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0050dcu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00515cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0050dcu:
        {
          if (!match16(b, 0x50dcu, 0x2279u)) return -1;
          if (!match32(b, 0x50deu, 0x00ff013eu)) return -1;
          if (native_bus_read32(b, 0x00ff013eu, &c->a[1]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0x50e2u, 0x363cu)) return -1;
          if (!match16(b, 0x50e4u, 0x0007u)) return -1;
          c->d[3] = (c->d[3] & 0xffff0000u) | 0x0007u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0007u & 0x8000u) ? 8u : 0u) | (0x0007u == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x50e6u, 0x1019u)) return -1;
          if (native_bus_read8(b, c->a[1], &byte_value) != 0) return -3;
          c->a[1] = (c->a[1] + 1u) & 0xffffffu;
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 128u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x50e8u, 0x6a00u)) return -1;
          if (!match16(b, 0x50eau, 0x0004u)) return -1;
          c->pc = (c->sr & 8u) ? 0x0050ecu : 0x0050eeu;
          c->cycles += 10u;
          return 0;
        }
      case 0x0050e6u:
        {
          if (!match16(b, 0x50e6u, 0x1019u)) return -1;
          if (native_bus_read8(b, c->a[1], &byte_value) != 0) return -3;
          c->a[1] = (c->a[1] + 1u) & 0xffffffu;
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 128u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x50e8u, 0x6a00u)) return -1;
          if (!match16(b, 0x50eau, 0x0004u)) return -1;
          c->pc = (c->sr & 8u) ? 0x0050ecu : 0x0050eeu;
          c->cycles += 10u;
          return 0;
        }
      case 0x0050ecu:
        {
          if (!match16(b, 0x50ecu, 0x4200u)) return -1;
          c->d[0] &= 0xffffff00u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 4u;
          if (!match16(b, 0x50eeu, 0x6100u)) return -1;
          if (!match16(b, 0x50f0u, 0x014au)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0050f2u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00523au;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0050eeu:
        {
          if (!match16(b, 0x50eeu, 0x6100u)) return -1;
          if (!match16(b, 0x50f0u, 0x014au)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0050f2u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00523au;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0050f2u:
        {
          if (!match16(b, 0x50f2u, 0x51cbu)) return -1;
          { uint16_t count = (uint16_t)(c->d[3] - 1u);
            c->d[3] = (c->d[3] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x0050e6u : 0x0050f6u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x0050f6u:
        {
          if (!match16(b, 0x50f6u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x0050f8u:
        {
          if (!match16(b, 0x50f8u, 0x33c0u)) return -1;
          if (!match32(b, 0x50fau, 0x00ff0142u)) return -1;
          { uint16_t v=(uint16_t)c->d[0];
            if (native_bus_write16((struct t2bus *)b,0x00ff0142u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x50feu, 0x1239u)) return -1;
          if (!match32(b,0x5100u,0x00ff0142u)) return -1;
          if (native_bus_read8(b,0x00ff0142u,&byte_value)!=0) return -3;
          c->d[1]=(c->d[1]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0x5104u, 0x6100u)) return -1;
          if (!match16(b, 0x5106u, 0x0034u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005108u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00513au;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005108u:
        {
          if (!match16(b, 0x5108u, 0x1239u)) return -1;
          if (!match32(b,0x510au,0x00ff0143u)) return -1;
          if (native_bus_read8(b,0x00ff0143u,&byte_value)!=0) return -3;
          c->d[1]=(c->d[1]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0x510eu, 0x6100u)) return -1;
          if (!match16(b, 0x5110u, 0x002au)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005112u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00513au;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005112u:
        {
          if (!match16(b, 0x5112u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x005114u:
        {
          if (!match16(b, 0x5114u, 0x23c0u)) return -1;
          { uint32_t v=c->d[0]; if(native_bus_write32((struct t2bus *)b,0x00ff0142u,v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=20u;
          if (!match16(b, 0x511au, 0x1239u)) return -1;
          if (!match32(b,0x511cu,0x00ff0143u)) return -1;
          if (native_bus_read8(b,0x00ff0143u,&byte_value)!=0) return -3;
          c->d[1]=(c->d[1]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0x5120u, 0x6100u)) return -1;
          if (!match16(b, 0x5122u, 0x0018u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005124u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00513au;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005124u:
        {
          if (!match16(b, 0x5124u, 0x1239u)) return -1;
          if (!match32(b,0x5126u,0x00ff0144u)) return -1;
          if (native_bus_read8(b,0x00ff0144u,&byte_value)!=0) return -3;
          c->d[1]=(c->d[1]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0x512au, 0x6100u)) return -1;
          if (!match16(b, 0x512cu, 0x000eu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00512eu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00513au;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00512eu:
        {
          if (!match16(b, 0x512eu, 0x1239u)) return -1;
          if (!match32(b,0x5130u,0x00ff0145u)) return -1;
          if (native_bus_read8(b,0x00ff0145u,&byte_value)!=0) return -3;
          c->d[1]=(c->d[1]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0x5134u, 0x6100u)) return -1;
          if (!match16(b, 0x5136u, 0x0004u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005138u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00513au;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005138u:
        {
          if (!match16(b, 0x5138u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00513au:
        {
          if (!match16(b, 0x513au, 0x41f8u)) return -1;
          if (!match16(b, 0x513cu, 0x4f38u)) return -1;
          c->a[0] = 0x004f38u;
          c->cycles += 8u;
          if (!match16(b, 0x513eu, 0x1401u)) return -1;
          byte_value=(uint8_t)c->d[1];
          c->d[2]=(c->d[2]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=4u;
          if (!match16(b, 0x5140u, 0xe80au)) return -1;
          { uint32_t old = c->d[2] & 255u;
            uint32_t carry = (old >> 3) & 1u;
            uint32_t result = old >> 4;
            c->d[2] = (c->d[2] & 0xffffff00u) | result;
            c->sr = (uint16_t)((c->sr & 0xffe0u) | (carry ? 0x11u : 0u) | (result == 0u ? 4u : 0u) | (result & 0x80u ? 8u : 0u));
            c->cycles += 6u + 2u * 4u;
          }
          if (!match16(b, 0x5142u, 0x0242u)) return -1;
          if (!match16(b, 0x5144u, 0x000fu)) return -1;
          { uint16_t v=(uint16_t)c->d[2] & 0x000fu; c->d[2]=(c->d[2] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x5146u, 0x1030u)) return -1;
          if(!match16(b,0x5148u,0x2000u))return -1;
          if(native_bus_read8(b,(c->a[0]+((uint32_t)(int32_t)(int16_t)c->d[2])+(uint32_t)(0))&0xffffffu,&byte_value)!=0)return -3;
          c->d[0]=(c->d[0]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&128u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=14u;
          if (!match16(b, 0x514au, 0x6100u)) return -1;
          if (!match16(b, 0x514cu, 0x00eeu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00514eu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00523au;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00514eu:
        {
          if (!match16(b, 0x514eu, 0x0241u)) return -1;
          if (!match16(b, 0x5150u, 0x000fu)) return -1;
          { uint16_t v=(uint16_t)c->d[1] & 0x000fu; c->d[1]=(c->d[1] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x5152u, 0x1030u)) return -1;
          if(!match16(b,0x5154u,0x1000u))return -1;
          if(native_bus_read8(b,(c->a[0]+((uint32_t)(int32_t)(int16_t)c->d[1])+(uint32_t)(0))&0xffffffu,&byte_value)!=0)return -3;
          c->d[0]=(c->d[0]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&128u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=14u;
          if (!match16(b, 0x5156u, 0x6100u)) return -1;
          if (!match16(b, 0x5158u, 0x00e2u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00515au) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00523au;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00515au:
        {
          if (!match16(b, 0x515au, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00515cu:
        {
          if (!match16(b, 0x515cu, 0x6100u)) return -1;
          if (!match16(b, 0x515eu, 0x00beu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005160u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00521cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005160u:
        {
          if (!match16(b, 0x5160u, 0x1018u)) return -1;
          if (native_bus_read8(b, c->a[0], &byte_value) != 0) return -3;
          c->a[0] = (c->a[0] + 1u) & 0xffffffu;
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 128u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x5162u, 0x6b00u)) return -1;
          if (!match16(b, 0x5164u, 0x0008u)) return -1;
          c->pc = (c->sr & 8u) ? 0x00516cu : 0x005166u;
          c->cycles += (c->sr & 8u) ? 10u : 8u;
          return 0;
        }
      case 0x005166u:
        {
          if (!match16(b, 0x5166u, 0x6100u)) return -1;
          if (!match16(b, 0x5168u, 0x00d2u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00516au) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00523au;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00516au:
        {
          if (!match16(b, 0x516au, 0x60f4u)) return -1;
          c->pc = (1) ? 0x005160u : 0x00516cu;
          c->cycles += (1) ? 10u : 8u;
          return 0;
        }
      case 0x00516cu:
        {
          if (!match16(b, 0x516cu, 0x0c00u)) return -1;
          if (!match16(b, 0x516eu, 0x00fau)) return -1;
          { uint8_t dst=(uint8_t)c->d[0], src=0xfau, result=(uint8_t)(dst-src);
            uint16_t n=(result&0x80u)?8u:0u, z=(result==0u)?4u:0u;
            uint16_t v=((dst^src)&(dst^result)&0x80u)?2u:0u;
            uint16_t carry=(dst<src)?1u:0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|n|z|v|carry);
          }
          c->cycles += 8u;
          if (!match16(b, 0x5170u, 0x6602u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x005174u : 0x005172u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x005172u:
        {
          if (!match16(b, 0x5172u, 0x60ecu)) return -1;
          c->pc = (1) ? 0x005160u : 0x005174u;
          c->cycles += (1) ? 10u : 8u;
          return 0;
        }
      case 0x005174u:
        {
          if (!match16(b, 0x5174u, 0x0c00u)) return -1;
          if (!match16(b, 0x5176u, 0x00feu)) return -1;
          { uint8_t dst=(uint8_t)c->d[0], src=0xfeu, result=(uint8_t)(dst-src);
            uint16_t n=(result&0x80u)?8u:0u, z=(result==0u)?4u:0u;
            uint16_t v=((dst^src)&(dst^result)&0x80u)?2u:0u;
            uint16_t carry=(dst<src)?1u:0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|n|z|v|carry);
          }
          c->cycles += 8u;
          if (!match16(b, 0x5178u, 0x6600u)) return -1;
          if (!match16(b, 0x517au, 0x0010u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x00518au : 0x00517cu;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00517cu:
        {
          if (!match16(b, 0x517cu, 0x33fcu)) return -1;
          if (!match16(b, 0x517eu, 0xe000u) || !match32(b, 0x5180u, 0x00ff013cu)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff013cu, 0xe000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xe000u & 0x8000u) ? 8u : 0u) | (0xe000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x5184u, 0x6100u)) return -1;
          if (!match16(b, 0x5186u, 0x0096u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005188u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00521cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005188u:
        {
          if (!match16(b, 0x5188u, 0x60d6u)) return -1;
          c->pc = (1) ? 0x005160u : 0x00518au;
          c->cycles += (1) ? 10u : 8u;
          return 0;
        }
      case 0x00518au:
        {
          if (!match16(b, 0x518au, 0x0c00u)) return -1;
          if (!match16(b, 0x518cu, 0x00ffu)) return -1;
          { uint8_t dst=(uint8_t)c->d[0], src=0xffu, result=(uint8_t)(dst-src);
            uint16_t n=(result&0x80u)?8u:0u, z=(result==0u)?4u:0u;
            uint16_t v=((dst^src)&(dst^result)&0x80u)?2u:0u;
            uint16_t carry=(dst<src)?1u:0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|n|z|v|carry);
          }
          c->cycles += 8u;
          if (!match16(b, 0x518eu, 0x6600u)) return -1;
          if (!match16(b, 0x5190u, 0x0014u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x0051a4u : 0x005192u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x005192u:
        {
          if (!match16(b, 0x5192u, 0x6100u)) return -1;
          if (!match16(b, 0x5194u, 0xf8bcu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005196u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004a50u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005196u:
        {
          if (!match16(b, 0x5196u, 0x33fcu)) return -1;
          if (!match16(b, 0x5198u, 0xe000u) || !match32(b, 0x519au, 0x00ff013cu)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff013cu, 0xe000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xe000u & 0x8000u) ? 8u : 0u) | (0xe000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x519eu, 0x6100u)) return -1;
          if (!match16(b, 0x51a0u, 0x007cu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0051a2u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00521cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0051a2u:
        {
          if (!match16(b, 0x51a2u, 0x60bcu)) return -1;
          c->pc = (1) ? 0x005160u : 0x0051a4u;
          c->cycles += (1) ? 10u : 8u;
          return 0;
        }
      case 0x0051a4u:
        {
          if (!match16(b, 0x51a4u, 0x0c00u)) return -1;
          if (!match16(b, 0x51a6u, 0x00fcu)) return -1;
          { uint8_t dst=(uint8_t)c->d[0], src=0xfcu, result=(uint8_t)(dst-src);
            uint16_t n=(result&0x80u)?8u:0u, z=(result==0u)?4u:0u;
            uint16_t v=((dst^src)&(dst^result)&0x80u)?2u:0u;
            uint16_t carry=(dst<src)?1u:0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|n|z|v|carry);
          }
          c->cycles += 8u;
          if (!match16(b, 0x51a8u, 0x6600u)) return -1;
          if (!match16(b, 0x51aau, 0x0020u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x0051cau : 0x0051acu;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x0051acu:
        {
          if (!match16(b, 0x51acu, 0x3039u)) return -1;
          if (!match32(b, 0x51aeu, 0x00ff013cu)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff013cu, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x51b2u, 0x0240u)) return -1;
          if (!match16(b, 0x51b4u, 0xff80u)) return -1;
          { uint16_t v=(uint16_t)c->d[0] & 0xff80u; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x51b6u, 0x4241u)) return -1;
          c->d[1] &= 0xffff0000u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 4u;
          if (!match16(b, 0x51b8u, 0x1218u)) return -1;
          if (native_bus_read8(b, c->a[0], &byte_value) != 0) return -3;
          c->a[0] = (c->a[0] + 1u) & 0xffffffu;
          c->d[1] = (c->d[1] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 128u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x51bau, 0xe349u)) return -1;
          { uint32_t x=c->d[1]&65535u,r=(x<<1)&65535u;
            uint16_t carry=(x>>15)&1u;
            c->d[1]=(c->d[1]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(carry?17u:0u));
          }
          c->cycles+=8u;
          if (!match16(b, 0x51bcu, 0xd041u)) return -1;
          { uint32_t x = c->d[1] & 65535u, y = c->d[0] & 65535u, r = (x+y) & 65535u;
            uint16_t flags = (uint16_t)(((r & 0x8000u) ? 8u : 0u) | ((r == 0u) ? 4u : 0u) | (((~(x ^ y) & (r ^ y)) & 0x8000u) ? 2u : 0u) | ((x+y > 65535u) ? 17u : 0u));
            c->d[0] = (c->d[0] & 0xffff0000u) | r;
            c->sr = (uint16_t)((c->sr & 0xffe0u) | flags);
          }
          c->cycles += 4u;
          if (!match16(b, 0x51beu, 0x33c0u)) return -1;
          if (!match32(b, 0x51c0u, 0x00ff013cu)) return -1;
          { uint16_t v=(uint16_t)c->d[0];
            if (native_bus_write16((struct t2bus *)b,0x00ff013cu,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x51c4u, 0x6100u)) return -1;
          if (!match16(b, 0x51c6u, 0x0056u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0051c8u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00521cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0051c8u:
        {
          if (!match16(b, 0x51c8u, 0x6096u)) return -1;
          c->pc = (1) ? 0x005160u : 0x0051cau;
          c->cycles += (1) ? 10u : 8u;
          return 0;
        }
      case 0x0051cau:
        {
          if (!match16(b, 0x51cau, 0x0c00u)) return -1;
          if (!match16(b, 0x51ccu, 0x00fbu)) return -1;
          { uint8_t dst=(uint8_t)c->d[0], src=0xfbu, result=(uint8_t)(dst-src);
            uint16_t n=(result&0x80u)?8u:0u, z=(result==0u)?4u:0u;
            uint16_t v=((dst^src)&(dst^result)&0x80u)?2u:0u;
            uint16_t carry=(dst<src)?1u:0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|n|z|v|carry);
          }
          c->cycles += 8u;
          if (!match16(b, 0x51ceu, 0x6600u)) return -1;
          if (!match16(b, 0x51d0u, 0x0026u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x0051f6u : 0x0051d2u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x0051d2u:
        {
          if (!match16(b, 0x51d2u, 0x3039u)) return -1;
          if (!match32(b, 0x51d4u, 0x00ff013cu)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff013cu, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x51d8u, 0x0240u)) return -1;
          if (!match16(b, 0x51dau, 0x003fu)) return -1;
          { uint16_t v=(uint16_t)c->d[0] & 0x003fu; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x51dcu, 0x0640u)) return -1;
          { uint32_t x=c->d[0]&65535u,y=0xe000u,r=(x+y)&65535u;
            c->d[0]=(c->d[0]&0xffff0000u)|r;
            uint16_t carry=(x+y)>65535u,ov=((~(x^y))&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?17u:0u));
          }
          c->cycles+=8u;
          if (!match16(b, 0x51e0u, 0x4241u)) return -1;
          c->d[1] &= 0xffff0000u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 4u;
          if (!match16(b, 0x51e2u, 0x1218u)) return -1;
          if (native_bus_read8(b, c->a[0], &byte_value) != 0) return -3;
          c->a[0] = (c->a[0] + 1u) & 0xffffffu;
          c->d[1] = (c->d[1] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 128u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x51e4u, 0xef49u)) return -1;
          { unsigned count=c->d[7]&63u,i;uint32_t v=c->d[1]&65535u;uint16_t carry=0;
            for(i=0;i<count;i++){carry=(v>>15)&1u;v=(v<<1)&65535u;}
            c->d[1]=(c->d[1]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&(count?0xffe0u:0xfff0u))|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)|(count&&carry?17u:0u)); c->cycles+=6u+2u*count; }
          if (!match16(b, 0x51e6u, 0xd041u)) return -1;
          { uint32_t x = c->d[1] & 65535u, y = c->d[0] & 65535u, r = (x+y) & 65535u;
            uint16_t flags = (uint16_t)(((r & 0x8000u) ? 8u : 0u) | ((r == 0u) ? 4u : 0u) | (((~(x ^ y) & (r ^ y)) & 0x8000u) ? 2u : 0u) | ((x+y > 65535u) ? 17u : 0u));
            c->d[0] = (c->d[0] & 0xffff0000u) | r;
            c->sr = (uint16_t)((c->sr & 0xffe0u) | flags);
          }
          c->cycles += 4u;
          if (!match16(b, 0x51e8u, 0x33c0u)) return -1;
          if (!match32(b, 0x51eau, 0x00ff013cu)) return -1;
          { uint16_t v=(uint16_t)c->d[0];
            if (native_bus_write16((struct t2bus *)b,0x00ff013cu,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x51eeu, 0x6100u)) return -1;
          if (!match16(b, 0x51f0u, 0x002cu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0051f2u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00521cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0051f2u:
        {
          if (!match16(b, 0x51f2u, 0x6000u)) return -1;
          if (!match16(b, 0x51f4u, 0xff6cu)) return -1;
          c->pc = (1) ? 0x005160u : 0x0051f6u;
          c->cycles += (1) ? 10u : 8u;
          return 0;
        }
      case 0x0051f6u:
        {
          if (!match16(b, 0x51f6u, 0x0c00u)) return -1;
          if (!match16(b, 0x51f8u, 0x00f9u)) return -1;
          { uint8_t dst=(uint8_t)c->d[0], src=0xf9u, result=(uint8_t)(dst-src);
            uint16_t n=(result&0x80u)?8u:0u, z=(result==0u)?4u:0u;
            uint16_t v=((dst^src)&(dst^result)&0x80u)?2u:0u;
            uint16_t carry=(dst<src)?1u:0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|n|z|v|carry);
          }
          c->cycles += 8u;
          if (!match16(b, 0x51fau, 0x6600u)) return -1;
          if (!match16(b, 0x51fcu, 0x001eu)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x00521au : 0x0051feu;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x0051feu:
        {
          if (!match16(b, 0x51feu, 0x3039u)) return -1;
          if (!match32(b, 0x5200u, 0x00ff013cu)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff013cu, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x5204u, 0x0240u)) return -1;
          if (!match16(b, 0x5206u, 0xff80u)) return -1;
          { uint16_t v=(uint16_t)c->d[0] & 0xff80u; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x5208u, 0x0640u)) return -1;
          { uint32_t x=c->d[0]&65535u,y=0x0080u,r=(x+y)&65535u;
            c->d[0]=(c->d[0]&0xffff0000u)|r;
            uint16_t carry=(x+y)>65535u,ov=((~(x^y))&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?17u:0u));
          }
          c->cycles+=8u;
          if (!match16(b, 0x520cu, 0x33c0u)) return -1;
          if (!match32(b, 0x520eu, 0x00ff013cu)) return -1;
          { uint16_t v=(uint16_t)c->d[0];
            if (native_bus_write16((struct t2bus *)b,0x00ff013cu,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x5212u, 0x6100u)) return -1;
          if (!match16(b, 0x5214u, 0x0008u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005216u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00521cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005216u:
        {
          if (!match16(b, 0x5216u, 0x6000u)) return -1;
          if (!match16(b, 0x5218u, 0xff48u)) return -1;
          c->pc = (1) ? 0x005160u : 0x00521au;
          c->cycles += (1) ? 10u : 8u;
          return 0;
        }
      case 0x00521au:
        {
          if (!match16(b, 0x521au, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00521cu:
        {
          if (!match16(b, 0x521cu, 0x3039u)) return -1;
          if (!match32(b, 0x521eu, 0x00ff013cu)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff013cu, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x5222u, 0xe588u)) return -1;
          { uint32_t x=c->d[0],r=x<<2;
            uint16_t carry=(uint16_t)((x>>30)&1u);
            c->d[0]=r;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x80000000u)?8u:0u)|(r==0u?4u:0u)|(carry?17u:0u));
          }
          c->cycles+=12u;
          if (!match16(b, 0x5224u, 0xe448u)) return -1;
          { uint16_t old=(uint16_t)c->d[0],r=(uint16_t)(old>>2);
            uint16_t carry=(old>>1)&1u;
            c->d[0]=(c->d[0]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xffe0u)|(r==0u?4u:0u)|(carry?17u:0u));
            c->cycles+=10u;
          }
          if (!match16(b, 0x5226u, 0x0280u)) return -1;
          c->d[0] &= 0x00033fffu;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((c->d[0]&0x80000000u)?8u:0u)|(c->d[0]==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0x522cu, 0x0040u)) return -1;
          if(!match16(b,0x522eu,0x4000u))return -1;
          {uint16_t v=(uint16_t)(c->d[0]|0x4000u);
           c->d[0]=(c->d[0]&0xffff0000u)|v;
           c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=8u;
          if (!match16(b, 0x5230u, 0x4840u)) return -1;
          c->d[0]=(c->d[0]<<16)|(c->d[0]>>16);
          c->sr=(uint16_t)((c->sr&0xfff0u)|((c->d[0]&0x80000000u)?8u:0u)|(c->d[0]==0u?4u:0u));
          c->cycles+=4u;
          if (!match16(b, 0x5232u, 0x23c0u)) return -1;
          { uint32_t v=c->d[0]; if(native_bus_write32((struct t2bus *)b,0x00c00004u,v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=20u;
          if (!match16(b, 0x5238u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00523au:
        {
          if (!match16(b, 0x523au, 0x0240u)) return -1;
          if (!match16(b, 0x523cu, 0x00ffu)) return -1;
          { uint16_t v=(uint16_t)c->d[0] & 0x00ffu; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x523eu, 0x5200u)) return -1;
          { uint32_t dst=c->d[0]&255u,src=1u,r=(dst+src)&255u;
            c->d[0]=(c->d[0]&0xffffff00u)|r;
            uint16_t cy=((dst+src)>255u)?1u:0u;
            uint16_t ov=((~(dst^src)&(dst^r)&128u)!=0u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&128u)?8u:0u)|(r==0u?4u:0u)|ov|cy|(cy?16u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0x5240u, 0x33c0u)) return -1;
          if (!match32(b, 0x5242u, 0x00c00000u)) return -1;
          { uint16_t v=(uint16_t)c->d[0];
            if (native_bus_write16((struct t2bus *)b,0x00c00000u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x5246u, 0x5479u)) return -1;
          if (!match32(b,0x5248u,0x00ff013cu)) return -1;
          { uint16_t dst,src=2u,result; if (native_bus_read16(b,0x00ff013cu,&dst)!=0) return -3;
            result=(uint16_t)(dst + src);
            if (native_bus_write16((struct t2bus *)b,0x00ff013cu,result)!=0) return -3;
            uint16_t carry=(uint32_t)dst+src>0xffffu?1u:0u;
            uint16_t overflow=((~(dst^src))&(dst^result)&0x8000u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((result&0x8000u)?8u:0u)|(result==0u?4u:0u)|overflow|carry|(carry?16u:0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x524cu, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00524eu:
        {
          if (!match16(b, 0x524eu, 0x41f8u)) return -1;
          if (!match16(b, 0x5250u, 0x4e04u)) return -1;
          c->a[0] = 0x004e04u;
          c->cycles += 8u;
          if (!match16(b, 0x5252u, 0x6100u)) return -1;
          if (!match16(b, 0x5254u, 0xf834u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005256u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004a88u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005256u:
        {
          if (!match16(b, 0x5256u, 0x23fcu)) return -1;
          if (!match32(b, 0x5258u, 0xc0000000u) || !match32(b, 0x525cu, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0xc0000000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=005256 addr=00c00004 value=c0000000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xc0000000u & 0x80000000u) ? 8u : 0u) | (0xc0000000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x5260u, 0x33fcu)) return -1;
          if (!match16(b, 0x5262u, 0x0f00u) || !match32(b, 0x5264u, 0x00c00000u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00c00000u, 0x0f00u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0f00u & 0x8000u) ? 8u : 0u) | (0x0f00u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x5268u, 0x23fcu)) return -1;
          if (!match32(b, 0x526au, 0xc0000000u) || !match32(b, 0x526eu, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0xc0000000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=005268 addr=00c00004 value=c0000000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xc0000000u & 0x80000000u) ? 8u : 0u) | (0xc0000000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x5272u, 0x33fcu)) return -1;
          if (!match16(b, 0x5274u, 0x00f0u) || !match32(b, 0x5276u, 0x00c00000u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00c00000u, 0x00f0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00f0u & 0x8000u) ? 8u : 0u) | (0x00f0u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x527au, 0x23fcu)) return -1;
          if (!match32(b, 0x527cu, 0xc0000000u) || !match32(b, 0x5280u, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0xc0000000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=00527a addr=00c00004 value=c0000000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xc0000000u & 0x80000000u) ? 8u : 0u) | (0xc0000000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x5284u, 0x33fcu)) return -1;
          if (!match16(b, 0x5286u, 0x000fu) || !match32(b, 0x5288u, 0x00c00000u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00c00000u, 0x000fu) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x000fu & 0x8000u) ? 8u : 0u) | (0x000fu == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x528cu, 0x4e71u)) return -1;
          c->cycles += 4u;
          if (!match16(b, 0x528eu, 0x4e71u)) return -1;
          c->cycles += 4u;
          if (!match16(b, 0x5290u, 0x4e71u)) return -1;
          c->cycles += 4u;
          if (!match16(b, 0x5292u, 0x4e71u)) return -1;
          c->cycles += 4u;
          if (!match16(b, 0x5294u, 0x4e71u)) return -1;
          c->cycles += 4u;
          if (!match16(b, 0x5296u, 0x4e71u)) return -1;
          c->cycles += 4u;
          if (!match16(b, 0x5298u, 0x4e71u)) return -1;
          c->cycles += 4u;
          if (!match16(b, 0x529au, 0x4e71u)) return -1;
          c->cycles += 4u;
          if (!match16(b, 0x529cu, 0x4e71u)) return -1;
          c->cycles += 4u;
          if (!match16(b, 0x529eu, 0x4e71u)) return -1;
          c->cycles += 4u;
          if (!match16(b, 0x52a0u, 0x4e71u)) return -1;
          c->cycles += 4u;
          if (!match16(b, 0x52a2u, 0x4e71u)) return -1;
          c->cycles += 4u;
          if (!match16(b, 0x52a4u, 0x4e71u)) return -1;
          c->cycles += 4u;
          if (!match16(b, 0x52a6u, 0x4e71u)) return -1;
          c->cycles += 4u;
          if (!match16(b, 0x52a8u, 0x4e71u)) return -1;
          c->cycles += 4u;
          if (!match16(b, 0x52aau, 0x4e71u)) return -1;
          c->cycles += 4u;
          if (!match16(b, 0x52acu, 0x4e71u)) return -1;
          c->cycles += 4u;
          if (!match16(b, 0x52aeu, 0x4e71u)) return -1;
          c->cycles += 4u;
          if (!match16(b, 0x52b0u, 0x4e71u)) return -1;
          c->cycles += 4u;
          if (!match16(b, 0x52b2u, 0x4e71u)) return -1;
          c->cycles += 4u;
          if (!match16(b, 0x52b4u, 0x4e71u)) return -1;
          c->cycles += 4u;
          if (!match16(b, 0x52b6u, 0x4ef8u)) return -1;
          if (!match16(b, 0x52b8u, 0x5256u)) return -1;
          c->pc = 0x005256u;
          c->cycles += 10u;
          return 0;
        }
      case 0x0052bau:
        {
          if (!match16(b, 0x52bau, 0x08b9u)) return -1;
          if (!match16(b, 0x52bcu, 0x0005u) || !match32(b, 0x52beu, 0x00ff010du)) return -1;
          if (native_bus_read8(b, 0x00ff010du, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 5)) ? 0u : 4u));
          if (native_bus_write8((struct t2bus *)b, 0x00ff010du, (uint8_t)(byte_value & ~(1u << 5))) != 0) return -3;
          c->cycles += 16u;
          if (!match16(b, 0x52c2u, 0x33f9u)) return -1;
          if (!match32(b, 0x52c4u, 0x00ff010cu) || !match32(b, 0x52c8u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x52ccu, 0x23fcu)) return -1;
          if (!match32(b, 0x52ceu, 0x00005692u) || !match32(b, 0x52d2u, 0x00ff0138u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff0138u, 0x00005692u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=0052cc addr=00ff0138 value=00005692\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00005692u & 0x80000000u) ? 8u : 0u) | (0x00005692u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x52d6u, 0x41f9u)) return -1;
          if (!match32(b, 0x52d8u, 0x00ff0218u)) return -1;
          c->a[0] = 0x00ff0218u;
          c->cycles += 12u;
          if (!match16(b, 0x52dcu, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x52deu, 0x20c0u)) return -1;
          {uint32_t v=c->d[0];
           if(native_bus_write32((struct t2bus *)b,c->a[0],v)!=0)return -3;
           c->a[0]=(c->a[0]+4u)&0xffffffu;
           c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=12u;
          if (!match16(b, 0x52e0u, 0x20c0u)) return -1;
          {uint32_t v=c->d[0];
           if(native_bus_write32((struct t2bus *)b,c->a[0],v)!=0)return -3;
           c->a[0]=(c->a[0]+4u)&0xffffffu;
           c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=12u;
          if (!match16(b, 0x52e2u, 0x20c0u)) return -1;
          {uint32_t v=c->d[0];
           if(native_bus_write32((struct t2bus *)b,c->a[0],v)!=0)return -3;
           c->a[0]=(c->a[0]+4u)&0xffffffu;
           c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=12u;
          if (!match16(b, 0x52e4u, 0x20c0u)) return -1;
          {uint32_t v=c->d[0];
           if(native_bus_write32((struct t2bus *)b,c->a[0],v)!=0)return -3;
           c->a[0]=(c->a[0]+4u)&0xffffffu;
           c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=12u;
          if (!match16(b, 0x52e6u, 0x20c0u)) return -1;
          {uint32_t v=c->d[0];
           if(native_bus_write32((struct t2bus *)b,c->a[0],v)!=0)return -3;
           c->a[0]=(c->a[0]+4u)&0xffffffu;
           c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=12u;
          if (!match16(b, 0x52e8u, 0x0279u)) return -1;
          if (!match16(b,0x52eau,0xfffeu)||!match32(b,0x52ecu,0x00ff03c4u))return -1;
          {uint16_t v,r; if(native_bus_read16(b,0x00ff03c4u,&v))return -3; r=v&0xfffeu; if(native_bus_write16((struct t2bus *)b,0x00ff03c4u,r))return -3; c->sr=(c->sr&0xfff0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u);}
          c->cycles+=20u;
          if (!match16(b, 0x52f0u, 0x23fcu)) return -1;
          if (!match32(b, 0x52f2u, 0x00ffb5d6u) || !match32(b, 0x52f6u, 0x00ff019au)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff019au, 0x00ffb5d6u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=0052f0 addr=00ff019a value=00ffb5d6\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00ffb5d6u & 0x80000000u) ? 8u : 0u) | (0x00ffb5d6u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x52fau, 0x33fcu)) return -1;
          if (!match16(b, 0x52fcu, 0x0080u) || !match32(b, 0x52feu, 0x00ff01a6u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff01a6u, 0x0080u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0080u & 0x8000u) ? 8u : 0u) | (0x0080u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x5302u, 0x4eb9u)) return -1;
          if (!match32(b, 0x5304u, 0x0000e100u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005308u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00e100u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005308u:
        {
          if (!match16(b, 0x5308u, 0x33fcu)) return -1;
          if (!match16(b, 0x530au, 0x0180u) || !match32(b, 0x530cu, 0x00ff0648u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0648u, 0x0180u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0180u & 0x8000u) ? 8u : 0u) | (0x0180u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x5310u, 0x33fcu)) return -1;
          if (!match16(b, 0x5312u, 0x007fu) || !match32(b, 0x5314u, 0x00ff061au)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff061au, 0x007fu) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x007fu & 0x8000u) ? 8u : 0u) | (0x007fu == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x5318u, 0x6100u)) return -1;
          if (!match16(b, 0x531au, 0x102cu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00531cu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x006346u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00531cu:
        {
          if (!match16(b, 0x531cu, 0x13f9u)) return -1;
          {uint8_t v;if(native_bus_read8(b,0xff0151u,&v)||native_bus_write8((struct t2bus *)b,0xff28dcu,v))return -3;c->sr=(c->sr&0xfff0u)|((v&128u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=28u;
          if (!match16(b, 0x5326u, 0x41f9u)) return -1;
          if (!match32(b, 0x5328u, 0x0006c69au)) return -1;
          c->a[0] = 0x0006c69au;
          c->cycles += 12u;
          if (!match16(b, 0x532cu, 0x2e28u)) return -1;
          if(!match16(b,0x532eu,0x0004u))return -1;
          {uint32_t v,addr=(c->a[0]+(int16_t)0x0004u)&0xffffffu; if(native_bus_read32(b,addr,&v))return -3; c->d[7]=v; c->sr=(c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=16u;
          if (!match16(b, 0x5330u, 0x43f9u)) return -1;
          if (!match32(b, 0x5332u, 0x00ff4690u)) return -1;
          c->a[1] = 0x00ff4690u;
          c->cycles += 12u;
          if (!match16(b, 0x5336u, 0x23c9u)) return -1;
          if (!match32(b, 0x5338u, 0x00ff01a2u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff01a2u, c->a[1]) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->a[1] & 0x80000000u) ? 8u : 0u) | (c->a[1] == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x533cu, 0x4eb9u)) return -1;
          if (!match32(b, 0x533eu, 0x0000df5eu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005342u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00df5eu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005342u:
        {
          if (!match16(b, 0x5342u, 0x41f9u)) return -1;
          if (!match32(b, 0x5344u, 0x00ff4690u)) return -1;
          c->a[0] = 0x00ff4690u;
          c->cycles += 12u;
          if (!match16(b, 0x5348u, 0x43f9u)) return -1;
          if (!match32(b, 0x534au, 0x0000b1eeu)) return -1;
          c->a[1] = 0x0000b1eeu;
          c->cycles += 12u;
          if (!match16(b, 0x534eu, 0x6100u)) return -1;
          if (!match16(b, 0x5350u, 0x5ebeu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005352u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00b20eu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005352u:
        {
          if (!match16(b, 0x5352u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x5354u, 0x7200u)) return -1;
          c->d[1] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x5356u, 0x6100u)) return -1;
          if (!match16(b, 0x5358u, 0x33e4u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00535au) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00873cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00535au:
        {
          if (!match16(b, 0x535au, 0x6100u)) return -1;
          if (!match16(b, 0x535cu, 0x2ee4u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00535eu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x008240u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00535eu:
        {
          if (!match16(b, 0x535eu, 0x23fcu)) return -1;
          if (!match32(b, 0x5360u, 0x00ff01ccu) || !match32(b, 0x5364u, 0x00ff01c8u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff01c8u, 0x00ff01ccu) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=00535e addr=00ff01c8 value=00ff01cc\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00ff01ccu & 0x80000000u) ? 8u : 0u) | (0x00ff01ccu == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x5368u, 0x33fcu)) return -1;
          if (!match16(b, 0x536au, 0xe000u) || !match32(b, 0x536cu, 0x00ff01ceu)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff01ceu, 0xe000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xe000u & 0x8000u) ? 8u : 0u) | (0xe000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x5370u, 0x33fcu)) return -1;
          if (!match16(b, 0x5372u, 0xe000u) || !match32(b, 0x5374u, 0x00ff01d6u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff01d6u, 0xe000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xe000u & 0x8000u) ? 8u : 0u) | (0xe000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x5378u, 0x23fcu)) return -1;
          if (!match32(b, 0x537au, 0xffffffffu) || !match32(b, 0x537eu, 0x00ff0278u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff0278u, 0xffffffffu) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=005378 addr=00ff0278 value=ffffffff\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xffffffffu & 0x80000000u) ? 8u : 0u) | (0xffffffffu == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x5382u, 0x33fcu)) return -1;
          if (!match16(b, 0x5384u, 0x0000u) || !match32(b, 0x5386u, 0x00ff01d2u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff01d2u, 0x0000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x538au, 0x33fcu)) return -1;
          if (!match16(b, 0x538cu, 0x0000u) || !match32(b, 0x538eu, 0x00ff01dau)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff01dau, 0x0000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x5392u, 0x4eb9u)) return -1;
          if (!match32(b, 0x5394u, 0x0000e90eu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005398u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00e90eu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005398u:
        {
          if (!match16(b, 0x5398u, 0x13f9u)) return -1;
          {uint8_t v;if(native_bus_read8(b,0xff2866u,&v)||native_bus_write8((struct t2bus *)b,0xff0169u,v))return -3;c->sr=(c->sr&0xfff0u)|((v&128u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=28u;
          if (!match16(b, 0x53a2u, 0x13f9u)) return -1;
          {uint8_t v;if(native_bus_read8(b,0xff2867u,&v)||native_bus_write8((struct t2bus *)b,0xff0168u,v))return -3;c->sr=(c->sr&0xfff0u)|((v&128u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=28u;
          if (!match16(b, 0x53acu, 0x13f9u)) return -1;
          {uint8_t v;if(native_bus_read8(b,0xff2868u,&v)||native_bus_write8((struct t2bus *)b,0xff016bu,v))return -3;c->sr=(c->sr&0xfff0u)|((v&128u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=28u;
          if (!match16(b, 0x53b6u, 0x13f9u)) return -1;
          {uint8_t v;if(native_bus_read8(b,0xff2869u,&v)||native_bus_write8((struct t2bus *)b,0xff016au,v))return -3;c->sr=(c->sr&0xfff0u)|((v&128u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=28u;
          if (!match16(b, 0x53c0u, 0x13f9u)) return -1;
          {uint8_t v;if(native_bus_read8(b,0xff26b7u,&v)||native_bus_write8((struct t2bus *)b,0xff03c7u,v))return -3;c->sr=(c->sr&0xfff0u)|((v&128u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=28u;
          if (!match16(b, 0x53cau, 0x3039u)) return -1;
          if (!match32(b, 0x53ccu, 0x00ff0248u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0248u, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x53d0u, 0x33c0u)) return -1;
          if (!match32(b, 0x53d2u, 0x00ff024au)) return -1;
          { uint16_t v=(uint16_t)c->d[0];
            if (native_bus_write16((struct t2bus *)b,0x00ff024au,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x53d6u, 0x0640u)) return -1;
          { uint32_t x=c->d[0]&65535u,y=0x8000u,r=(x+y)&65535u;
            c->d[0]=(c->d[0]&0xffff0000u)|r;
            uint16_t carry=(x+y)>65535u,ov=((~(x^y))&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?17u:0u));
          }
          c->cycles+=8u;
          if (!match16(b, 0x53dau, 0x33c0u)) return -1;
          if (!match32(b, 0x53dcu, 0x00ff024eu)) return -1;
          { uint16_t v=(uint16_t)c->d[0];
            if (native_bus_write16((struct t2bus *)b,0x00ff024eu,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x53e0u, 0x23fcu)) return -1;
          if (!match32(b, 0x53e2u, 0x00ff5252u) || !match32(b, 0x53e6u, 0x00ff019eu)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff019eu, 0x00ff5252u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=0053e0 addr=00ff019e value=00ff5252\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00ff5252u & 0x80000000u) ? 8u : 0u) | (0x00ff5252u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x53eau, 0x4279u)) return -1;
          if (!match32(b, 0x53ecu, 0x00ff0154u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0154u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x53f0u, 0x23fcu)) return -1;
          if (!match32(b, 0x53f2u, 0xc0000000u) || !match32(b, 0x53f6u, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0xc0000000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=0053f0 addr=00c00004 value=c0000000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xc0000000u & 0x80000000u) ? 8u : 0u) | (0xc0000000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x53fau, 0x7e3fu)) return -1;
          c->d[7] = (uint32_t)(int32_t)(63);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[7] & 0x80000000u) ? 8u : 0u) | (c->d[7] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x53fcu, 0x41f9u)) return -1;
          if (!match32(b, 0x53feu, 0x00ff02a8u)) return -1;
          c->a[0] = 0x00ff02a8u;
          c->cycles += 12u;
          if (!match16(b, 0x5402u, 0x33fcu)) return -1;
          if (!match16(b, 0x5404u, 0x0000u) || !match32(b, 0x5406u, 0x00c00000u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00c00000u, 0x0000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x540au, 0x30fcu)) return -1;
          if(native_bus_write16((struct t2bus *)b,c->a[0],0x0000u))return -3;
          c->a[0]=(c->a[0]+2u)&0xffffffu;
          c->sr=(c->sr&0xfff0u)|0u|4u;
          c->cycles+=12u;
          if (!match16(b, 0x540eu, 0x51cfu)) return -1;
          { uint16_t count = (uint16_t)(c->d[7] - 1u);
            c->d[7] = (c->d[7] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x005402u : 0x005412u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x005402u:
        {
          if (!match16(b, 0x5402u, 0x33fcu)) return -1;
          if (!match16(b, 0x5404u, 0x0000u) || !match32(b, 0x5406u, 0x00c00000u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00c00000u, 0x0000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x540au, 0x30fcu)) return -1;
          if(native_bus_write16((struct t2bus *)b,c->a[0],0x0000u))return -3;
          c->a[0]=(c->a[0]+2u)&0xffffffu;
          c->sr=(c->sr&0xfff0u)|0u|4u;
          c->cycles+=12u;
          if (!match16(b, 0x540eu, 0x51cfu)) return -1;
          { uint16_t count = (uint16_t)(c->d[7] - 1u);
            c->d[7] = (c->d[7] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x005402u : 0x005412u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x005412u:
        {
          if (!match16(b, 0x5412u, 0x6100u)) return -1;
          if (!match16(b, 0x5414u, 0x1a7cu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005416u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x006e90u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005416u:
        {
          if (!match16(b, 0x5416u, 0x6100u)) return -1;
          if (!match16(b, 0x5418u, 0x1cbeu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00541au) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0070d6u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00541au:
        {
          if (!match16(b, 0x541au, 0x6100u)) return -1;
          if (!match16(b, 0x541cu, 0x2112u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00541eu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00752eu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00541eu:
        {
          if (!match16(b, 0x541eu, 0x6100u)) return -1;
          if (!match16(b, 0x5420u, 0x34b4u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005422u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0088d4u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005422u:
        {
          if (!match16(b, 0x5422u, 0x6100u)) return -1;
          if (!match16(b, 0x5424u, 0x0fbau)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005426u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0063deu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005426u:
        {
          if (!match16(b, 0x5426u, 0x23fcu)) return -1;
          if (!match32(b, 0x5428u, 0x00010001u) || !match32(b, 0x542cu, 0x00ff016cu)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff016cu, 0x00010001u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=005426 addr=00ff016c value=00010001\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00010001u & 0x80000000u) ? 8u : 0u) | (0x00010001u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x5430u, 0x41f9u)) return -1;
          if (!match32(b, 0x5432u, 0x000fa0f6u)) return -1;
          c->a[0] = 0x000fa0f6u;
          c->cycles += 12u;
          if (!match16(b, 0x5436u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x5438u, 0x6100u)) return -1;
          if (!match16(b, 0x543au, 0x644au)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00543cu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00b884u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00543cu:
        {
          if (!match16(b, 0x543cu, 0x41f9u)) return -1;
          if (!match32(b, 0x543eu, 0x000fa116u)) return -1;
          c->a[0] = 0x000fa116u;
          c->cycles += 12u;
          if (!match16(b, 0x5442u, 0x7001u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(1);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x5444u, 0x6100u)) return -1;
          if (!match16(b, 0x5446u, 0x643eu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005448u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00b884u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005448u:
        {
          if (!match16(b, 0x5448u, 0x6100u)) return -1;
          if (!match16(b, 0x544au, 0x0e1au)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00544cu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x006264u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00544cu:
        {
          if (!match16(b, 0x544cu, 0x08f9u)) return -1;
          { uint8_t v; if(native_bus_read8(b,0x00ff010du,&v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&~4u)|((v&(1u<<5))?0u:4u));
            if(native_bus_write8((struct t2bus *)b,0x00ff010du,(uint8_t)(v|(1u<<5)))!=0)return -3; }
          c->cycles+=20u;
          if (!match16(b, 0x5454u, 0x33f9u)) return -1;
          if (!match32(b, 0x5456u, 0x00ff010cu) || !match32(b, 0x545au, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x545eu, 0x41f9u)) return -1;
          if (!match32(b, 0x5460u, 0x000fd4aeu)) return -1;
          c->a[0] = 0x000fd4aeu;
          c->cycles += 12u;
          if (!match16(b, 0x5464u, 0x6100u)) return -1;
          if (!match16(b, 0x5466u, 0x3f46u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005468u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0093acu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005468u:
        {
          if (!match16(b, 0x5468u, 0x4279u)) return -1;
          if (!match32(b, 0x546au, 0x00ff0162u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0162u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x546eu, 0x5479u)) return -1;
          if (!match32(b,0x5470u,0x00ff0162u)) return -1;
          { uint16_t dst,src=2u,result; if (native_bus_read16(b,0x00ff0162u,&dst)!=0) return -3;
            result=(uint16_t)(dst + src);
            if (native_bus_write16((struct t2bus *)b,0x00ff0162u,result)!=0) return -3;
            uint16_t carry=(uint32_t)dst+src>0xffffu?1u:0u;
            uint16_t overflow=((~(dst^src))&(dst^result)&0x8000u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((result&0x8000u)?8u:0u)|(result==0u?4u:0u)|overflow|carry|(carry?16u:0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x5474u, 0x6600u)) return -1;
          if (!match16(b, 0x5476u, 0x000au)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x005480u : 0x005478u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00546eu:
        {
          if (!match16(b, 0x546eu, 0x5479u)) return -1;
          if (!match32(b,0x5470u,0x00ff0162u)) return -1;
          { uint16_t dst,src=2u,result; if (native_bus_read16(b,0x00ff0162u,&dst)!=0) return -3;
            result=(uint16_t)(dst + src);
            if (native_bus_write16((struct t2bus *)b,0x00ff0162u,result)!=0) return -3;
            uint16_t carry=(uint32_t)dst+src>0xffffu?1u:0u;
            uint16_t overflow=((~(dst^src))&(dst^result)&0x8000u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((result&0x8000u)?8u:0u)|(result==0u?4u:0u)|overflow|carry|(carry?16u:0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x5474u, 0x6600u)) return -1;
          if (!match16(b, 0x5476u, 0x000au)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x005480u : 0x005478u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x005478u:
        {
          if (!match16(b, 0x5478u, 0x33fcu)) return -1;
          if (!match16(b, 0x547au, 0xffb0u) || !match32(b, 0x547cu, 0x00ff0162u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0162u, 0xffb0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xffb0u & 0x8000u) ? 8u : 0u) | (0xffb0u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x5480u, 0x4a79u)) return -1;
          if (!match32(b, 0x5482u, 0x00ff05e2u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff05e2u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x5486u, 0x6700u)) return -1;
          if (!match16(b, 0x5488u, 0x003cu)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x0054c4u : 0x00548au;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x005480u:
        {
          if (!match16(b, 0x5480u, 0x4a79u)) return -1;
          if (!match32(b, 0x5482u, 0x00ff05e2u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff05e2u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x5486u, 0x6700u)) return -1;
          if (!match16(b, 0x5488u, 0x003cu)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x0054c4u : 0x00548au;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x0054c4u:
        {
          if (!match16(b, 0x54c4u, 0x33fcu)) return -1;
          if (!match16(b, 0x54c6u, 0x0000u) || !match32(b, 0x54c8u, 0x00ff03b0u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff03b0u, 0x0000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x54ccu, 0x6100u)) return -1;
          if (!match16(b, 0x54ceu, 0x0c9cu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0054d0u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00616au;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0054d0u:
        {
          if (!match16(b, 0x54d0u, 0x6100u)) return -1;
          if (!match16(b, 0x54d2u, 0x0cfeu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0054d4u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0061d0u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0054d4u:
        {
          if (!match16(b, 0x54d4u, 0x08b9u)) return -1;
          if (!match16(b, 0x54d6u, 0x0005u) || !match32(b, 0x54d8u, 0x00ff010du)) return -1;
          if (native_bus_read8(b, 0x00ff010du, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 5)) ? 0u : 4u));
          if (native_bus_write8((struct t2bus *)b, 0x00ff010du, (uint8_t)(byte_value & ~(1u << 5))) != 0) return -3;
          c->cycles += 16u;
          if (!match16(b, 0x54dcu, 0x33f9u)) return -1;
          if (!match32(b, 0x54deu, 0x00ff010cu) || !match32(b, 0x54e2u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x54e6u, 0x6100u)) return -1;
          if (!match16(b, 0x54e8u, 0x3fd8u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0054eau) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0094c0u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0054eau:
        {
          if (!match16(b, 0x54eau, 0x6100u)) return -1;
          if (!match16(b, 0x54ecu, 0x4170u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0054eeu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00965cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0054eeu:
        {
          if (!match16(b, 0x54eeu, 0x6100u)) return -1;
          if (!match16(b, 0x54f0u, 0x43a0u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0054f2u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x009890u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0054f2u:
        {
          if (!match16(b, 0x54f2u, 0x08f9u)) return -1;
          { uint8_t v; if(native_bus_read8(b,0x00ff010du,&v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&~4u)|((v&(1u<<5))?0u:4u));
            if(native_bus_write8((struct t2bus *)b,0x00ff010du,(uint8_t)(v|(1u<<5)))!=0)return -3; }
          c->cycles+=20u;
          if (!match16(b, 0x54fau, 0x33f9u)) return -1;
          if (!match32(b, 0x54fcu, 0x00ff010cu) || !match32(b, 0x5500u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x5504u, 0x6100u)) return -1;
          if (!match16(b, 0x5506u, 0x1c70u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005508u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x007176u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005508u:
        {
          if (!match16(b, 0x5508u, 0x6100u)) return -1;
          if (!match16(b, 0x550au, 0x1e5au)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00550cu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x007364u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00550cu:
        {
          if (!match16(b, 0x550cu, 0x6100u)) return -1;
          if (!match16(b, 0x550eu, 0x2730u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005510u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x007c3eu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005510u:
        {
          if (!match16(b, 0x5510u, 0x4a79u)) return -1;
          if (!match32(b, 0x5512u, 0x00ff05d8u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff05d8u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x5516u, 0x6600u)) return -1;
          if (!match16(b, 0x5518u, 0x0012u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x00552au : 0x00551au;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00551au:
        {
          if (!match16(b, 0x551au, 0x1039u)) return -1;
          if (!match32(b, 0x551cu, 0x00ff26b7u)) return -1;
          if (native_bus_read8(b, 0x00ff26b7u, &byte_value) != 0) return -3;
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 0x80u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 16u;
          c->pc = 0x005520u;
          return 0;
        }
      case 0x00552au:
        {
          if (!match16(b, 0x552au, 0x4279u)) return -1;
          if (!match32(b, 0x552cu, 0x00ff05d8u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff05d8u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x5530u, 0x6100u)) return -1;
          if (!match16(b, 0x5532u, 0x026au)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005534u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00579cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005534u:
        {
          if (!match16(b, 0x5534u, 0x08f9u)) return -1;
          { uint8_t v; if(native_bus_read8(b,0x00ff05c8u,&v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&~4u)|((v&(1u<<7))?0u:4u));
            if(native_bus_write8((struct t2bus *)b,0x00ff05c8u,(uint8_t)(v|(1u<<7)))!=0)return -3; }
          c->cycles+=20u;
          if (!match16(b, 0x553cu, 0x4a79u)) return -1;
          if (!match32(b, 0x553eu, 0x00ff03a8u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff03a8u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x5542u, 0x6600u)) return -1;
          if (!match16(b, 0x5544u, 0x0026u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x00556au : 0x005546u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x005546u:
        {
          if (!match16(b, 0x5546u, 0x0839u)) return -1;
          if (!match16(b, 0x5548u, 0x0007u) || !match32(b, 0x554au, 0x00ff05c8u)) return -1;
          if (native_bus_read8(b, 0x00ff05c8u, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 7)) ? 0u : 4u));
          c->cycles += 16u;
          if (!match16(b, 0x554eu, 0x6600u)) return -1;
          if (!match16(b, 0x5550u, 0x001au)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x00556au : 0x005552u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x005552u:
        {
          if (!match16(b, 0x5552u, 0x0839u)) return -1;
          if (!match16(b, 0x5554u, 0x0007u) || !match32(b, 0x5556u, 0x00ff0006u)) return -1;
          if (native_bus_read8(b, 0x00ff0006u, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 7)) ? 0u : 4u));
          c->cycles += 16u;
          if (!match16(b, 0x555au, 0x6700u)) return -1;
          if (!match16(b, 0x555cu, 0x000eu)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x00556au : 0x00555eu;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00555eu:
        {
          if (!match16(b, 0x555eu, 0x08f9u)) return -1;
          { uint8_t v; if(native_bus_read8(b,0x00ff05c8u,&v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&~4u)|((v&(1u<<7))?0u:4u));
            if(native_bus_write8((struct t2bus *)b,0x00ff05c8u,(uint8_t)(v|(1u<<7)))!=0)return -3; }
          c->cycles+=20u;
          if (!match16(b, 0x5566u, 0x6100u)) return -1;
          if (!match16(b, 0x5568u, 0x0352u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00556au) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0058bau;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00556au:
        {
          if (!match16(b, 0x556au, 0x08b9u)) return -1;
          if (!match16(b, 0x556cu, 0x0002u) || !match32(b, 0x556eu, 0x00ff2803u)) return -1;
          if (native_bus_read8(b, 0x00ff2803u, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 2)) ? 0u : 4u));
          if (native_bus_write8((struct t2bus *)b, 0x00ff2803u, (uint8_t)(byte_value & ~(1u << 2))) != 0) return -3;
          c->cycles += 16u;
          if (!match16(b, 0x5572u, 0x6700u)) return -1;
          if (!match16(b, 0x5574u, 0x0074u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x0055e8u : 0x005576u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x005576u:
        {
          if (!match16(b, 0x5576u, 0x08b9u)) return -1;
          if (!match16(b, 0x5578u, 0x0005u) || !match32(b, 0x557au, 0x00ff010du)) return -1;
          if (native_bus_read8(b, 0x00ff010du, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 5)) ? 0u : 4u));
          if (native_bus_write8((struct t2bus *)b, 0x00ff010du, (uint8_t)(byte_value & ~(1u << 5))) != 0) return -3;
          c->cycles += 16u;
          if (!match16(b, 0x557eu, 0x33f9u)) return -1;
          if (!match32(b, 0x5580u, 0x00ff010cu) || !match32(b, 0x5584u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x5588u, 0x4279u)) return -1;
          if (!match32(b, 0x558au, 0x00ff0218u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0218u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x558eu, 0x4279u)) return -1;
          if (!match32(b, 0x5590u, 0x00ff0622u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0622u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x5594u, 0x4279u)) return -1;
          if (!match32(b, 0x5596u, 0x00ff0624u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0624u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x559au, 0x4279u)) return -1;
          if (!match32(b, 0x559cu, 0x00ff05e8u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff05e8u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x55a0u, 0x4279u)) return -1;
          if (!match32(b, 0x55a2u, 0x00ff0658u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0658u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x55a6u, 0x4279u)) return -1;
          if (!match32(b, 0x55a8u, 0x00ff0656u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0656u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x55acu, 0x4279u)) return -1;
          if (!match32(b, 0x55aeu, 0x00ff0226u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0226u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x55b2u, 0x4279u)) return -1;
          if (!match32(b, 0x55b4u, 0x00ff0228u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0228u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x55b8u, 0x4279u)) return -1;
          if (!match32(b, 0x55bau, 0x00ff0220u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0220u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x55beu, 0x33fcu)) return -1;
          if (!match16(b, 0x55c0u, 0xffffu) || !match32(b, 0x55c2u, 0x00ff01a8u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff01a8u, 0xffffu) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xffffu & 0x8000u) ? 8u : 0u) | (0xffffu == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x55c6u, 0x4239u)) return -1;
          if (!match32(b, 0x55c8u, 0x00ff278eu)) return -1;
          if (native_bus_write8((struct t2bus *)b, 0x00ff278eu, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x55ccu, 0x4239u)) return -1;
          if (!match32(b, 0x55ceu, 0x00ff277cu)) return -1;
          if (native_bus_write8((struct t2bus *)b, 0x00ff277cu, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x55d2u, 0x6100u)) return -1;
          if (!match16(b, 0x55d4u, 0x1b4cu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0055d6u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x007120u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0055d6u:
        {
          if (!match16(b, 0x55d6u, 0x08f9u)) return -1;
          { uint8_t v; if(native_bus_read8(b,0x00ff010du,&v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&~4u)|((v&(1u<<5))?0u:4u));
            if(native_bus_write8((struct t2bus *)b,0x00ff010du,(uint8_t)(v|(1u<<5)))!=0)return -3; }
          c->cycles+=20u;
          if (!match16(b, 0x55deu, 0x33f9u)) return -1;
          if (!match32(b, 0x55e0u, 0x00ff010cu) || !match32(b, 0x55e4u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x55e8u, 0x4a79u)) return -1;
          if (!match32(b, 0x55eau, 0x00ff0218u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff0218u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x55eeu, 0x6600u)) return -1;
          if (!match16(b, 0x55f0u, 0x0042u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x005632u : 0x0055f2u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x0055e8u:
        {
          if (!match16(b, 0x55e8u, 0x4a79u)) return -1;
          if (!match32(b, 0x55eau, 0x00ff0218u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff0218u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x55eeu, 0x6600u)) return -1;
          if (!match16(b, 0x55f0u, 0x0042u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x005632u : 0x0055f2u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x0055f2u:
        {
          if (!match16(b, 0x55f2u, 0x4239u)) return -1;
          if (!match32(b, 0x55f4u, 0x00ff27a8u)) return -1;
          if (native_bus_write8((struct t2bus *)b, 0x00ff27a8u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x55f8u, 0x4239u)) return -1;
          if (!match32(b, 0x55fau, 0x00ff27a7u)) return -1;
          if (native_bus_write8((struct t2bus *)b, 0x00ff27a7u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x55feu, 0x4a39u)) return -1;
          if (!match32(b, 0x5600u, 0x00ff278eu)) return -1;
          { uint8_t value;
            if (native_bus_read8(b, 0x00ff278eu, &value) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((value & 0x80u) ? 8u : 0u) | (value == 0u ? 4u : 0u));
          }
          c->cycles += 12u;
          if (!match16(b, 0x5604u, 0x6700u)) return -1;
          if (!match16(b, 0x5606u, 0x0016u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x00561cu : 0x005608u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x005608u:
        {
          if (!match16(b, 0x5608u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x560au, 0x1039u)) return -1;
          if (!match32(b, 0x560cu, 0x00ff278eu)) return -1;
          if (native_bus_read8(b, 0x00ff278eu, &byte_value) != 0) return -3;
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 0x80u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 16u;
          if (!match16(b, 0x5610u, 0x6100u)) return -1;
          if (!match16(b, 0x5612u, 0x3d6cu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005614u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00937eu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005614u:
        {
          if (!match16(b, 0x5614u, 0x13fcu)) return -1;
          byte_value=0xffu;
          if(native_bus_write8((struct t2bus *)b,0x00ff27a8u,byte_value)!=0)return -3;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&128u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=20u;
          if (!match16(b, 0x561cu, 0x4a39u)) return -1;
          if (!match32(b, 0x561eu, 0x00ff277cu)) return -1;
          { uint8_t value;
            if (native_bus_read8(b, 0x00ff277cu, &value) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((value & 0x80u) ? 8u : 0u) | (value == 0u ? 4u : 0u));
          }
          c->cycles += 12u;
          if (!match16(b, 0x5622u, 0x6700u)) return -1;
          if (!match16(b, 0x5624u, 0x000eu)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x005632u : 0x005626u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00561cu:
        {
          if (!match16(b, 0x561cu, 0x4a39u)) return -1;
          if (!match32(b, 0x561eu, 0x00ff277cu)) return -1;
          { uint8_t value;
            if (native_bus_read8(b, 0x00ff277cu, &value) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((value & 0x80u) ? 8u : 0u) | (value == 0u ? 4u : 0u));
          }
          c->cycles += 12u;
          if (!match16(b, 0x5622u, 0x6700u)) return -1;
          if (!match16(b, 0x5624u, 0x000eu)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x005632u : 0x005626u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x005626u:
        {
          if (!match16(b, 0x5626u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x5628u, 0x1039u)) return -1;
          if (!match32(b, 0x562au, 0x00ff277cu)) return -1;
          if (native_bus_read8(b, 0x00ff277cu, &byte_value) != 0) return -3;
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 0x80u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 16u;
          if (!match16(b, 0x562eu, 0x6100u)) return -1;
          if (!match16(b, 0x5630u, 0x3d6cu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005632u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00939cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005632u:
        {
          if (!match16(b, 0x5632u, 0x4a79u)) return -1;
          if (!match32(b, 0x5634u, 0x00ff0658u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff0658u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x5638u, 0x6700u)) return -1;
          if (!match16(b, 0x563au, 0x0010u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x00564au : 0x00563cu;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00563cu:
        {
          if (!match16(b, 0x563cu, 0x4a79u)) return -1;
          if (!match32(b, 0x563eu, 0x00ff03beu)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff03beu, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x5642u, 0x6600u)) return -1;
          if (!match16(b, 0x5644u, 0x0006u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x00564au : 0x005646u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x005646u:
        {
          if (!match16(b, 0x5646u, 0x6100u)) return -1;
          if (!match16(b, 0x5648u, 0x0a12u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00564au) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00605au;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00564au:
        {
          if (!match16(b, 0x564au, 0x0839u)) return -1;
          if (!match16(b, 0x564cu, 0x0006u) || !match32(b, 0x564eu, 0x00ff0006u)) return -1;
          if (native_bus_read8(b, 0x00ff0006u, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 6)) ? 0u : 4u));
          c->cycles += 16u;
          if (!match16(b, 0x5652u, 0x6700u)) return -1;
          if (!match16(b, 0x5654u, 0x000au)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x00565eu : 0x005656u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x005656u:
        {
          if (!match16(b, 0x5656u, 0x08f9u)) return -1;
          { uint8_t v; if(native_bus_read8(b,0x00ff05c8u,&v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&~4u)|((v&(1u<<6))?0u:4u));
            if(native_bus_write8((struct t2bus *)b,0x00ff05c8u,(uint8_t)(v|(1u<<6)))!=0)return -3; }
          c->cycles+=20u;
          if (!match16(b, 0x565eu, 0x6100u)) return -1;
          if (!match16(b, 0x5660u, 0x2ea6u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005662u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x008506u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00565eu:
        {
          if (!match16(b, 0x565eu, 0x6100u)) return -1;
          if (!match16(b, 0x5660u, 0x2ea6u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005662u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x008506u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005662u:
        {
          if (!match16(b, 0x5662u, 0x4eb9u)) return -1;
          if (!match32(b, 0x5664u, 0x0000ee7eu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005668u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00ee7eu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005668u:
        {
          if (!match16(b, 0x5668u, 0x33fcu)) return -1;
          if (!match16(b, 0x566au, 0xffffu) || !match32(b, 0x566cu, 0x00ff05eeu)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff05eeu, 0xffffu) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xffffu & 0x8000u) ? 8u : 0u) | (0xffffu == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x5670u, 0x4a79u)) return -1;
          if (!match32(b, 0x5672u, 0x00ff03b0u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff03b0u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x5676u, 0x67f8u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x005670u : 0x005678u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x005670u:
        {
          if (!match16(b, 0x5670u, 0x4a79u)) return -1;
          if (!match32(b, 0x5672u, 0x00ff03b0u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff03b0u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x5676u, 0x67f8u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x005670u : 0x005678u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x005678u:
        {
          if (!match16(b, 0x5678u, 0x6100u)) return -1;
          if (!match16(b, 0x567au, 0x0aa0u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00567cu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00611au;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00567cu:
        {
          if (!match16(b, 0x567cu, 0x4a79u)) return -1;
          if (!match32(b, 0x567eu, 0x00ff0174u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff0174u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x5682u, 0x6700u)) return -1;
          if (!match16(b, 0x5684u, 0xfdeau)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x00546eu : 0x005686u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x005686u:
        {
          if (!match16(b, 0x5686u, 0x6100u)) return -1;
          if (!match16(b, 0x5688u, 0x0718u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00568au) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x005da0u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00568au:
        {
          if (!match16(b, 0x568au, 0x4279u)) return -1;
          if (!match32(b, 0x568cu, 0x00ff0174u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0174u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x5690u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00579cu:
        {
          if (!match16(b, 0x579cu, 0x6100u)) return -1;
          if (!match16(b, 0x579eu, 0x097cu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0057a0u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00611au;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0057a0u:
        {
          if (!match16(b, 0x57a0u, 0x41f9u)) return -1;
          if (!match32(b, 0x57a2u, 0x000fd474u)) return -1;
          c->a[0] = 0x000fd474u;
          c->cycles += 12u;
          if (!match16(b, 0x57a6u, 0x6100u)) return -1;
          if (!match16(b, 0x57a8u, 0x4210u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0057aau) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0099b8u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0057aau:
        {
          if (!match16(b, 0x57aau, 0x6100u)) return -1;
          if (!match16(b, 0x57acu, 0x424eu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0057aeu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0099fau;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0057aeu:
        {
          if (!match16(b, 0x57aeu, 0x6100u)) return -1;
          if (!match16(b, 0x57b0u, 0x096au)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0057b2u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00611au;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0057b2u:
        {
          if (!match16(b, 0x57b2u, 0x4a79u)) return -1;
          if (!match32(b, 0x57b4u, 0x00ff021au)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff021au, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x57b8u, 0x6600u)) return -1;
          if (!match16(b, 0x57bau, 0x0006u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x0057c0u : 0x0057bcu;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x0057bcu:
        {
          if (!match16(b, 0x57bcu, 0x6100u)) return -1;
          if (!match16(b, 0x57beu, 0x1962u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0057c0u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x007120u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0057c0u:
        {
          if (!match16(b, 0x57c0u, 0x4279u)) return -1;
          if (!match32(b, 0x57c2u, 0x00ff0622u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0622u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x57c6u, 0x4279u)) return -1;
          if (!match32(b, 0x57c8u, 0x00ff0624u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0624u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x57ccu, 0x4279u)) return -1;
          if (!match32(b, 0x57ceu, 0x00ff05e8u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff05e8u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x57d2u, 0x4279u)) return -1;
          if (!match32(b, 0x57d4u, 0x00ff0226u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0226u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x57d8u, 0x4279u)) return -1;
          if (!match32(b, 0x57dau, 0x00ff0220u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0220u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x57deu, 0x4279u)) return -1;
          if (!match32(b, 0x57e0u, 0x00ff0228u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0228u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x57e4u, 0x4279u)) return -1;
          if (!match32(b, 0x57e6u, 0x00ff0656u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0656u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x57eau, 0x4279u)) return -1;
          if (!match32(b, 0x57ecu, 0x00ff062eu)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff062eu, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x57f0u, 0x4279u)) return -1;
          if (!match32(b, 0x57f2u, 0x00ff0632u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0632u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x57f6u, 0x4279u)) return -1;
          if (!match32(b, 0x57f8u, 0x00ff062cu)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff062cu, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x57fcu, 0x33fcu)) return -1;
          if (!match16(b, 0x57feu, 0xffffu) || !match32(b, 0x5800u, 0x00ff05eeu)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff05eeu, 0xffffu) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xffffu & 0x8000u) ? 8u : 0u) | (0xffffu == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x5804u, 0x6100u)) return -1;
          if (!match16(b, 0x5806u, 0x0914u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005808u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00611au;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005808u:
        {
          if (!match16(b, 0x5808u, 0x13f9u)) return -1;
          {uint8_t v;if(native_bus_read8(b,0xff26b7u,&v)||native_bus_write8((struct t2bus *)b,0xff03c7u,v))return -3;c->sr=(c->sr&0xfff0u)|((v&128u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=28u;
          if (!match16(b, 0x5812u, 0x6100u)) return -1;
          if (!match16(b, 0x5814u, 0x167cu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005816u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x006e90u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005816u:
        {
          if (!match16(b, 0x5816u, 0x08b9u)) return -1;
          if (!match16(b, 0x5818u, 0x0005u) || !match32(b, 0x581au, 0x00ff010du)) return -1;
          if (native_bus_read8(b, 0x00ff010du, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 5)) ? 0u : 4u));
          if (native_bus_write8((struct t2bus *)b, 0x00ff010du, (uint8_t)(byte_value & ~(1u << 5))) != 0) return -3;
          c->cycles += 16u;
          if (!match16(b, 0x581eu, 0x33f9u)) return -1;
          if (!match32(b, 0x5820u, 0x00ff010cu) || !match32(b, 0x5824u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x5828u, 0x6100u)) return -1;
          if (!match16(b, 0x582au, 0x0bb4u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00582cu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0063deu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00582cu:
        {
          if (!match16(b, 0x582cu, 0x08f9u)) return -1;
          { uint8_t v; if(native_bus_read8(b,0x00ff010du,&v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&~4u)|((v&(1u<<5))?0u:4u));
            if(native_bus_write8((struct t2bus *)b,0x00ff010du,(uint8_t)(v|(1u<<5)))!=0)return -3; }
          c->cycles+=20u;
          if (!match16(b, 0x5834u, 0x33f9u)) return -1;
          if (!match32(b, 0x5836u, 0x00ff010cu) || !match32(b, 0x583au, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x583eu, 0x4a79u)) return -1;
          if (!match32(b, 0x5840u, 0x00ff021au)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff021au, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x5844u, 0x6600u)) return -1;
          if (!match16(b, 0x5846u, 0x0060u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x0058a6u : 0x005848u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x005848u:
        {
          if (!match16(b, 0x5848u, 0x4a79u)) return -1;
          if (!match32(b, 0x584au, 0x00ff0226u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff0226u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x584eu, 0x6600u)) return -1;
          if (!match16(b, 0x5850u, 0x0056u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x0058a6u : 0x005852u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x005852u:
        {
          if (!match16(b, 0x5852u, 0x4a79u)) return -1;
          if (!match32(b, 0x5854u, 0x00ff0656u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff0656u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x5858u, 0x6600u)) return -1;
          if (!match16(b, 0x585au, 0x004cu)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x0058a6u : 0x00585cu;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00585cu:
        {
          if (!match16(b, 0x585cu, 0x4279u)) return -1;
          if (!match32(b, 0x585eu, 0x00ff0218u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0218u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x5862u, 0x4239u)) return -1;
          if (!match32(b, 0x5864u, 0x00ff27a8u)) return -1;
          if (native_bus_write8((struct t2bus *)b, 0x00ff27a8u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x5868u, 0x4239u)) return -1;
          if (!match32(b, 0x586au, 0x00ff27a7u)) return -1;
          if (native_bus_write8((struct t2bus *)b, 0x00ff27a7u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x586eu, 0x13fcu)) return -1;
          byte_value=0x00u;
          if(native_bus_write8((struct t2bus *)b,0x00ff278eu,byte_value)!=0)return -3;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&128u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=20u;
          if (!match16(b, 0x5876u, 0x13fcu)) return -1;
          byte_value=0x00u;
          if(native_bus_write8((struct t2bus *)b,0x00ff277cu,byte_value)!=0)return -3;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&128u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=20u;
          if (!match16(b, 0x587eu, 0x08b9u)) return -1;
          if (!match16(b, 0x5880u, 0x0005u) || !match32(b, 0x5882u, 0x00ff010du)) return -1;
          if (native_bus_read8(b, 0x00ff010du, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 5)) ? 0u : 4u));
          if (native_bus_write8((struct t2bus *)b, 0x00ff010du, (uint8_t)(byte_value & ~(1u << 5))) != 0) return -3;
          c->cycles += 16u;
          if (!match16(b, 0x5886u, 0x33f9u)) return -1;
          if (!match32(b, 0x5888u, 0x00ff010cu) || !match32(b, 0x588cu, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x5890u, 0x6100u)) return -1;
          if (!match16(b, 0x5892u, 0x188eu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005894u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x007120u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005894u:
        {
          if (!match16(b, 0x5894u, 0x08f9u)) return -1;
          { uint8_t v; if(native_bus_read8(b,0x00ff010du,&v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&~4u)|((v&(1u<<5))?0u:4u));
            if(native_bus_write8((struct t2bus *)b,0x00ff010du,(uint8_t)(v|(1u<<5)))!=0)return -3; }
          c->cycles+=20u;
          if (!match16(b, 0x589cu, 0x33f9u)) return -1;
          if (!match32(b, 0x589eu, 0x00ff010cu) || !match32(b, 0x58a2u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x58a6u, 0x33fcu)) return -1;
          if (!match16(b, 0x58a8u, 0xffffu) || !match32(b, 0x58aau, 0x00ff05e2u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff05e2u, 0xffffu) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xffffu & 0x8000u) ? 8u : 0u) | (0xffffu == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x58aeu, 0x23fcu)) return -1;
          if (!match32(b, 0x58b0u, 0x000fd4a4u) || !match32(b, 0x58b4u, 0x00ff05deu)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff05deu, 0x000fd4a4u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=0058ae addr=00ff05de value=000fd4a4\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x000fd4a4u & 0x80000000u) ? 8u : 0u) | (0x000fd4a4u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x58b8u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x0058a6u:
        {
          if (!match16(b, 0x58a6u, 0x33fcu)) return -1;
          if (!match16(b, 0x58a8u, 0xffffu) || !match32(b, 0x58aau, 0x00ff05e2u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff05e2u, 0xffffu) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xffffu & 0x8000u) ? 8u : 0u) | (0xffffu == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x58aeu, 0x23fcu)) return -1;
          if (!match32(b, 0x58b0u, 0x000fd4a4u) || !match32(b, 0x58b4u, 0x00ff05deu)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff05deu, 0x000fd4a4u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=0058ae addr=00ff05de value=000fd4a4\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x000fd4a4u & 0x80000000u) ? 8u : 0u) | (0x000fd4a4u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x58b8u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x0058bau:
        {
          if (!match16(b, 0x58bau, 0x706fu)) return -1;
          c->d[0] = (uint32_t)(int32_t)(111);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x58bcu, 0x4eb9u)) return -1;
          if (!match32(b, 0x58beu, 0x0000eb44u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0058c2u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00eb44u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0058c2u:
        {
          if (!match16(b, 0x58c2u, 0x33fcu)) return -1;
          if (!match16(b, 0x58c4u, 0x0001u) || !match32(b, 0x58c6u, 0x00ff05dau)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff05dau, 0x0001u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0001u & 0x8000u) ? 8u : 0u) | (0x0001u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x58cau, 0x4279u)) return -1;
          if (!match32(b, 0x58ccu, 0x00ff0658u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0658u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x58d0u, 0x41f9u)) return -1;
          if (!match32(b, 0x58d2u, 0x000fd4bcu)) return -1;
          c->a[0] = 0x000fd4bcu;
          c->cycles += 12u;
          if (!match16(b, 0x58d6u, 0x6100u)) return -1;
          if (!match16(b, 0x58d8u, 0x40e0u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0058dau) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0099b8u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0058dau:
        {
          if (!match16(b, 0x58dau, 0x6100u)) return -1;
          if (!match16(b, 0x58dcu, 0x40cau)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0058deu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0099a6u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0058deu:
        {
          if (!match16(b, 0x58deu, 0x33fcu)) return -1;
          if (!match16(b, 0x58e0u, 0xffffu) || !match32(b, 0x58e2u, 0x00ff05eeu)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff05eeu, 0xffffu) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xffffu & 0x8000u) ? 8u : 0u) | (0xffffu == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x58e6u, 0x6100u)) return -1;
          if (!match16(b, 0x58e8u, 0x0832u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0058eau) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00611au;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0058eau:
        {
          if (!match16(b, 0x58eau, 0x08b9u)) return -1;
          if (!match16(b, 0x58ecu, 0x0005u) || !match32(b, 0x58eeu, 0x00ff010du)) return -1;
          if (native_bus_read8(b, 0x00ff010du, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 5)) ? 0u : 4u));
          if (native_bus_write8((struct t2bus *)b, 0x00ff010du, (uint8_t)(byte_value & ~(1u << 5))) != 0) return -3;
          c->cycles += 16u;
          if (!match16(b, 0x58f2u, 0x33f9u)) return -1;
          if (!match32(b, 0x58f4u, 0x00ff010cu) || !match32(b, 0x58f8u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x58fcu, 0x203cu)) return -1;
          if (!match32(b, 0x58feu, 0xa600a600u)) return -1;
          c->d[0] = 0xa600a600u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xa600a600u & 0x80000000u) ? 8u : 0u) | (0xa600a600u == 0u ? 4u : 0u));
          c->cycles += 12u;
          if (!match16(b, 0x5902u, 0x6100u)) return -1;
          if (!match16(b, 0x5904u, 0xf14cu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005906u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004a50u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005906u:
        {
          if (!match16(b, 0x5906u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x5908u, 0x6100u)) return -1;
          if (!match16(b, 0x590au, 0xf162u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00590cu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004a6cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00590cu:
        {
          if (!match16(b, 0x590cu, 0x23fcu)) return -1;
          if (!match32(b, 0x590eu, 0x50000003u) || !match32(b, 0x5912u, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0x50000003u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=00590c addr=00c00004 value=50000003\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x50000003u & 0x80000000u) ? 8u : 0u) | (0x50000003u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x5916u, 0x23fcu)) return -1;
          if (!match32(b, 0x5918u, 0x00000000u) || !match32(b, 0x591cu, 0x00c00000u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00000u, 0x00000000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=005916 addr=00c00000 value=00000000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00000000u & 0x80000000u) ? 8u : 0u) | (0x00000000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x5920u, 0x41f9u)) return -1;
          if (!match32(b, 0x5922u, 0x000fa136u)) return -1;
          c->a[0] = 0x000fa136u;
          c->cycles += 12u;
          if (!match16(b, 0x5926u, 0x7001u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(1);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x5928u, 0x6100u)) return -1;
          if (!match16(b, 0x592au, 0x5f5au)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00592cu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00b884u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00592cu:
        {
          if (!match16(b, 0x592cu, 0x6100u)) return -1;
          if (!match16(b, 0x592eu, 0x0420u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005930u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x005d4eu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005930u:
        {
          if (!match16(b, 0x5930u, 0x23fcu)) return -1;
          if (!match32(b, 0x5932u, 0x40000003u) || !match32(b, 0x5936u, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0x40000003u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=005930 addr=00c00004 value=40000003\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x40000003u & 0x80000000u) ? 8u : 0u) | (0x40000003u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x593au, 0x2079u)) return -1;
          if (!match32(b, 0x593cu, 0x00ff01a2u)) return -1;
          if (native_bus_read32(b, 0x00ff01a2u, &c->a[0]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0x5940u, 0x2039u)) return -1;
          { uint32_t v; if(native_bus_read32(b,0x0006c69eu,&v)!=0)return -3;
            c->d[0]=v;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=16u;
          if (!match16(b, 0x5946u, 0xe448u)) return -1;
          { uint16_t old=(uint16_t)c->d[0],r=(uint16_t)(old>>2);
            uint16_t carry=(old>>1)&1u;
            c->d[0]=(c->d[0]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xffe0u)|(r==0u?4u:0u)|(carry?17u:0u));
            c->cycles+=10u;
          }
          if (!match16(b, 0x5948u, 0x5340u)) return -1;
          {uint32_t dst=c->d[0]&65535u,src=1u,r=(dst-src)&65535u;
           c->d[0]=(c->d[0]&0xffff0000u)|r;
           uint16_t cy=(dst<src),ov=((dst^src)&(dst^r)&32768u)!=0u;
           c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(cy?17u:0u));}
          c->cycles+=4u;
          if (!match16(b, 0x594au, 0x4eb8u)) return -1;
          if (!match16(b, 0x594cu, 0x4a00u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00594eu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004a00u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00594eu:
        {
          if (!match16(b, 0x594eu, 0x6100u)) return -1;
          if (!match16(b, 0x5950u, 0x03feu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005952u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x005d4eu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005952u:
        {
          if (!match16(b, 0x5952u, 0x33fcu)) return -1;
          if (!match16(b, 0x5954u, 0x0000u) || !match32(b, 0x5956u, 0x00ff01ccu)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff01ccu, 0x0000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x595au, 0x303cu)) return -1;
          if (!match16(b, 0x595cu, 0x0000u)) return -1;
          c->d[0] = (c->d[0] & 0xffff0000u) | 0x0000u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x595eu, 0x6100u)) return -1;
          if (!match16(b, 0x5960u, 0x2e68u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005962u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0087c8u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005962u:
        {
          if (!match16(b, 0x5962u, 0x303cu)) return -1;
          if (!match16(b, 0x5964u, 0x0001u)) return -1;
          c->d[0] = (c->d[0] & 0xffff0000u) | 0x0001u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0001u & 0x8000u) ? 8u : 0u) | (0x0001u == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x5966u, 0x6100u)) return -1;
          if (!match16(b, 0x5968u, 0x2e60u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00596au) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0087c8u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00596au:
        {
          if (!match16(b, 0x596au, 0x0c79u)) return -1;
          { uint16_t v; if(native_bus_read16(b,0x00ff03c4u,&v)!=0)return -3;
            uint32_t x=v,y=0x000cu,r=(x-y)&65535u;
            uint16_t carry=x<y;
            uint16_t ov=((x^y)&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?1u:0u));
          }
          c->cycles+=16u;
          if (!match16(b, 0x5972u, 0x6600u)) return -1;
          if (!match16(b, 0x5974u, 0x000au)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x00597eu : 0x005976u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x005976u:
        {
          if (!match16(b, 0x5976u, 0x303cu)) return -1;
          if (!match16(b, 0x5978u, 0x0002u)) return -1;
          c->d[0] = (c->d[0] & 0xffff0000u) | 0x0002u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0002u & 0x8000u) ? 8u : 0u) | (0x0002u == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x597au, 0x6100u)) return -1;
          if (!match16(b, 0x597cu, 0x2e4cu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00597eu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0087c8u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00597eu:
        {
          if (!match16(b, 0x597eu, 0x33fcu)) return -1;
          if (!match16(b, 0x5980u, 0xffffu) || !match32(b, 0x5982u, 0x00ff01d2u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff01d2u, 0xffffu) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xffffu & 0x8000u) ? 8u : 0u) | (0xffffu == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x5986u, 0x33fcu)) return -1;
          if (!match16(b, 0x5988u, 0x0600u) || !match32(b, 0x598au, 0x00ff01c6u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff01c6u, 0x0600u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0600u & 0x8000u) ? 8u : 0u) | (0x0600u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x598eu, 0x3639u)) return -1;
          if (!match32(b, 0x5990u, 0x00ff0652u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0652u, &val) != 0) return -3;
            c->d[3] = (c->d[3] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x5994u, 0x5d43u)) return -1;
          {uint32_t dst=c->d[3]&65535u,src=6u,r=(dst-src)&65535u;
           c->d[3]=(c->d[3]&0xffff0000u)|r;
           uint16_t cy=(dst<src),ov=((dst^src)&(dst^r)&32768u)!=0u;
           c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(cy?17u:0u));}
          c->cycles+=4u;
          if (!match16(b, 0x5996u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x5998u, 0x3003u)) return -1;
          { uint16_t v=(uint16_t)c->d[3]; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0x599au, 0xe588u)) return -1;
          { uint32_t x=c->d[0],r=x<<2;
            uint16_t carry=(uint16_t)((x>>30)&1u);
            c->d[0]=r;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x80000000u)?8u:0u)|(r==0u?4u:0u)|(carry?17u:0u));
          }
          c->cycles+=12u;
          if (!match16(b, 0x599cu, 0x3003u)) return -1;
          { uint16_t v=(uint16_t)c->d[3]; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0x599eu, 0x0240u)) return -1;
          if (!match16(b, 0x59a0u, 0x3ffeu)) return -1;
          { uint16_t v=(uint16_t)c->d[0] & 0x3ffeu; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x59a2u, 0x0040u)) return -1;
          if(!match16(b,0x59a4u,0x4000u))return -1;
          {uint16_t v=(uint16_t)(c->d[0]|0x4000u);
           c->d[0]=(c->d[0]&0xffff0000u)|v;
           c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=8u;
          if (!match16(b, 0x59a6u, 0x4840u)) return -1;
          c->d[0]=(c->d[0]<<16)|(c->d[0]>>16);
          c->sr=(uint16_t)((c->sr&0xfff0u)|((c->d[0]&0x80000000u)?8u:0u)|(c->d[0]==0u?4u:0u));
          c->cycles+=4u;
          if (!match16(b, 0x59a8u, 0x23c0u)) return -1;
          { uint32_t v=c->d[0]; if(native_bus_write32((struct t2bus *)b,0x00c00004u,v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=20u;
          if (!match16(b, 0x59aeu, 0x33fcu)) return -1;
          if (!match16(b, 0x59b0u, 0x0f00u) || !match32(b, 0x59b2u, 0x00c00000u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00c00000u, 0x0f00u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0f00u & 0x8000u) ? 8u : 0u) | (0x0f00u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x59b6u, 0x2f39u)) return -1;
          if (!match32(b, 0x59b8u, 0x00ff0168u)) return -1;
          { uint32_t val; if (native_bus_read32(b, 0x00ff0168u, &val) != 0) return -3;
            c->a[7] = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, c->a[7], val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x80000000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 24u;
          if (!match16(b, 0x59bcu, 0x2f39u)) return -1;
          if (!match32(b, 0x59beu, 0x00ff016cu)) return -1;
          { uint32_t val; if (native_bus_read32(b, 0x00ff016cu, &val) != 0) return -3;
            c->a[7] = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, c->a[7], val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x80000000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 24u;
          if (!match16(b, 0x59c2u, 0x23fcu)) return -1;
          if (!match32(b, 0x59c4u, 0x00000000u) || !match32(b, 0x59c8u, 0x00ff0168u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff0168u, 0x00000000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=0059c2 addr=00ff0168 value=00000000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00000000u & 0x80000000u) ? 8u : 0u) | (0x00000000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x59ccu, 0x23fcu)) return -1;
          if (!match32(b, 0x59ceu, 0x00000000u) || !match32(b, 0x59d2u, 0x00ff016cu)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff016cu, 0x00000000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=0059cc addr=00ff016c value=00000000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00000000u & 0x80000000u) ? 8u : 0u) | (0x00000000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x59d6u, 0x6100u)) return -1;
          if (!match16(b, 0x59d8u, 0x088cu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0059dau) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x006264u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0059dau:
        {
          if (!match16(b, 0x59dau, 0x08f9u)) return -1;
          { uint8_t v; if(native_bus_read8(b,0x00ff010du,&v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&~4u)|((v&(1u<<5))?0u:4u));
            if(native_bus_write8((struct t2bus *)b,0x00ff010du,(uint8_t)(v|(1u<<5)))!=0)return -3; }
          c->cycles+=20u;
          if (!match16(b, 0x59e2u, 0x33f9u)) return -1;
          if (!match32(b, 0x59e4u, 0x00ff010cu) || !match32(b, 0x59e8u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x59ecu, 0x41f9u)) return -1;
          if (!match32(b, 0x59eeu, 0x0000b1beu)) return -1;
          c->a[0] = 0x0000b1beu;
          c->cycles += 12u;
          if (!match16(b, 0x59f2u, 0x6100u)) return -1;
          if (!match16(b, 0x59f4u, 0x3fc4u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0059f6u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0099b8u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0059f6u:
        {
          if (!match16(b, 0x59f6u, 0x6100u)) return -1;
          if (!match16(b, 0x59f8u, 0x3faeu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0059fau) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0099a6u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0059fau:
        {
          if (!match16(b, 0x59fau, 0x303cu)) return -1;
          if (!match16(b, 0x59fcu, 0x00b3u)) return -1;
          c->d[0] = (c->d[0] & 0xffff0000u) | 0x00b3u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00b3u & 0x8000u) ? 8u : 0u) | (0x00b3u == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x59feu, 0x6100u)) return -1;
          if (!match16(b, 0x5a00u, 0x30f6u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005a02u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x008af6u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005a02u:
        {
          if (!match16(b, 0x5a02u, 0x3039u)) return -1;
          if (!match32(b, 0x5a04u, 0x00ff03c4u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff03c4u, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x5a08u, 0xe248u)) return -1;
          { uint16_t old=(uint16_t)c->d[0],r=(uint16_t)(old>>1);
            uint16_t carry=(old>>0)&1u;
            c->d[0]=(c->d[0]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xffe0u)|(r==0u?4u:0u)|(carry?17u:0u));
            c->cycles+=8u;
          }
          if (!match16(b, 0x5a0au, 0x0640u)) return -1;
          { uint32_t x=c->d[0]&65535u,y=0x00c0u,r=(x+y)&65535u;
            c->d[0]=(c->d[0]&0xffff0000u)|r;
            uint16_t carry=(x+y)>65535u,ov=((~(x^y))&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?17u:0u));
          }
          c->cycles+=8u;
          if (!match16(b, 0x5a0eu, 0x6100u)) return -1;
          if (!match16(b, 0x5a10u, 0x30e6u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005a12u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x008af6u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005a12u:
        {
          if (!match16(b, 0x5a12u, 0x41f9u)) return -1;
          if (!match32(b, 0x5a14u, 0x00ff2a9du)) return -1;
          c->a[0] = 0x00ff2a9du;
          c->cycles += 12u;
          if (!match16(b, 0x5a18u, 0x103cu)) return -1;
          byte_value=0x5au;
          c->d[0]=(c->d[0]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&128u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=8u;
          if (!match16(b, 0x5a1cu, 0x3200u)) return -1;
          { uint16_t v=(uint16_t)c->d[0]; c->d[1]=(c->d[1] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0x5a1eu, 0x0240u)) return -1;
          if (!match16(b, 0x5a20u, 0x0007u)) return -1;
          { uint16_t v=(uint16_t)c->d[0] & 0x0007u; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x5a22u, 0xe649u)) return -1;
          { uint16_t old=(uint16_t)c->d[1],r=(uint16_t)(old>>3);
            uint16_t carry=(old>>2)&1u;
            c->d[1]=(c->d[1]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xffe0u)|(r==0u?4u:0u)|(carry?17u:0u));
            c->cycles+=12u;
          }
          c->pc = 0x005a24u;
          return 0;
        }
      case 0x005da0u:
        {
          if (!match16(b, 0x5da0u, 0x41f9u)) return -1;
          if (!match32(b, 0x5da2u, 0x000fd4bau)) return -1;
          c->a[0] = 0x000fd4bau;
          c->cycles += 12u;
          if (!match16(b, 0x5da6u, 0x6100u)) return -1;
          if (!match16(b, 0x5da8u, 0x3604u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005daau) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0093acu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005daau:
        {
          if (!match16(b, 0x5daau, 0x6100u)) return -1;
          if (!match16(b, 0x5dacu, 0x036eu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005daeu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00611au;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005daeu:
        {
          if (!match16(b, 0x5daeu, 0x6100u)) return -1;
          if (!match16(b, 0x5db0u, 0x4334u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005db2u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a0e4u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005db2u:
        {
          if (!match16(b, 0x5db2u, 0x33fcu)) return -1;
          if (!match16(b, 0x5db4u, 0xffffu) || !match32(b, 0x5db6u, 0x00ff05eeu)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff05eeu, 0xffffu) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xffffu & 0x8000u) ? 8u : 0u) | (0xffffu == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x5dbau, 0x6100u)) return -1;
          if (!match16(b, 0x5dbcu, 0x035eu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005dbeu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00611au;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005dbeu:
        {
          if (!match16(b, 0x5dbeu, 0x08b9u)) return -1;
          if (!match16(b, 0x5dc0u, 0x0005u) || !match32(b, 0x5dc2u, 0x00ff010du)) return -1;
          if (native_bus_read8(b, 0x00ff010du, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 5)) ? 0u : 4u));
          if (native_bus_write8((struct t2bus *)b, 0x00ff010du, (uint8_t)(byte_value & ~(1u << 5))) != 0) return -3;
          c->cycles += 16u;
          if (!match16(b, 0x5dc6u, 0x33f9u)) return -1;
          if (!match32(b, 0x5dc8u, 0x00ff010cu) || !match32(b, 0x5dccu, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x5dd0u, 0x6100u)) return -1;
          if (!match16(b, 0x5dd2u, 0x1370u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005dd4u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x007142u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005dd4u:
        {
          if (!match16(b, 0x5dd4u, 0x23fcu)) return -1;
          if (!match32(b, 0x5dd6u, 0x74000003u) || !match32(b, 0x5ddau, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0x74000003u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=005dd4 addr=00c00004 value=74000003\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x74000003u & 0x80000000u) ? 8u : 0u) | (0x74000003u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x5ddeu, 0x2079u)) return -1;
          if (!match32(b, 0x5de0u, 0x00ff01a2u)) return -1;
          if (native_bus_read32(b, 0x00ff01a2u, &c->a[0]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0x5de4u, 0x2039u)) return -1;
          { uint32_t v; if(native_bus_read32(b,0x0006c69eu,&v)!=0)return -3;
            c->d[0]=v;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=16u;
          if (!match16(b, 0x5deau, 0xe448u)) return -1;
          { uint16_t old=(uint16_t)c->d[0],r=(uint16_t)(old>>2);
            uint16_t carry=(old>>1)&1u;
            c->d[0]=(c->d[0]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xffe0u)|(r==0u?4u:0u)|(carry?17u:0u));
            c->cycles+=10u;
          }
          if (!match16(b, 0x5decu, 0x5340u)) return -1;
          {uint32_t dst=c->d[0]&65535u,src=1u,r=(dst-src)&65535u;
           c->d[0]=(c->d[0]&0xffff0000u)|r;
           uint16_t cy=(dst<src),ov=((dst^src)&(dst^r)&32768u)!=0u;
           c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(cy?17u:0u));}
          c->cycles+=4u;
          if (!match16(b, 0x5deeu, 0x4eb8u)) return -1;
          if (!match16(b, 0x5df0u, 0x4a00u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005df2u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004a00u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005df2u:
        {
          if (!match16(b, 0x5df2u, 0x33fcu)) return -1;
          if (!match16(b, 0x5df4u, 0xffffu) || !match32(b, 0x5df6u, 0x00ff01dau)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff01dau, 0xffffu) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xffffu & 0x8000u) ? 8u : 0u) | (0xffffu == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x5dfau, 0x33fcu)) return -1;
          if (!match16(b, 0x5dfcu, 0x07a0u) || !match32(b, 0x5dfeu, 0x00ff01c6u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff01c6u, 0x07a0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x07a0u & 0x8000u) ? 8u : 0u) | (0x07a0u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x5e02u, 0x23fcu)) return -1;
          if (!match32(b, 0x5e04u, 0x50000003u) || !match32(b, 0x5e08u, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0x50000003u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=005e02 addr=00c00004 value=50000003\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x50000003u & 0x80000000u) ? 8u : 0u) | (0x50000003u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x5e0cu, 0x23fcu)) return -1;
          if (!match32(b, 0x5e0eu, 0x00000000u) || !match32(b, 0x5e12u, 0x00c00000u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00000u, 0x00000000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=005e0c addr=00c00000 value=00000000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00000000u & 0x80000000u) ? 8u : 0u) | (0x00000000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x5e16u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x5e18u, 0x6100u)) return -1;
          if (!match16(b, 0x5e1au, 0xec36u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005e1cu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004a50u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005e1cu:
        {
          if (!match16(b, 0x5e1cu, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x5e1eu, 0x6100u)) return -1;
          if (!match16(b, 0x5e20u, 0xec4cu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005e22u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004a6cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005e22u:
        {
          if (!match16(b, 0x5e22u, 0x23fcu)) return -1;
          if (!match32(b, 0x5e24u, 0x00000000u) || !match32(b, 0x5e28u, 0x00ff0168u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff0168u, 0x00000000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=005e22 addr=00ff0168 value=00000000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00000000u & 0x80000000u) ? 8u : 0u) | (0x00000000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x5e2cu, 0x23fcu)) return -1;
          if (!match32(b, 0x5e2eu, 0x00000000u) || !match32(b, 0x5e32u, 0x00ff016cu)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff016cu, 0x00000000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=005e2c addr=00ff016c value=00000000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00000000u & 0x80000000u) ? 8u : 0u) | (0x00000000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x5e36u, 0x6100u)) return -1;
          if (!match16(b, 0x5e38u, 0x042cu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005e3au) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x006264u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005e3au:
        {
          if (!match16(b, 0x5e3au, 0x08f9u)) return -1;
          { uint8_t v; if(native_bus_read8(b,0x00ff010du,&v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&~4u)|((v&(1u<<5))?0u:4u));
            if(native_bus_write8((struct t2bus *)b,0x00ff010du,(uint8_t)(v|(1u<<5)))!=0)return -3; }
          c->cycles+=20u;
          if (!match16(b, 0x5e42u, 0x33f9u)) return -1;
          if (!match32(b, 0x5e44u, 0x00ff010cu) || !match32(b, 0x5e48u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x5e4cu, 0x41f9u)) return -1;
          if (!match32(b, 0x5e4eu, 0x0000b1bcu)) return -1;
          c->a[0] = 0x0000b1bcu;
          c->cycles += 12u;
          if (!match16(b, 0x5e52u, 0x6100u)) return -1;
          if (!match16(b, 0x5e54u, 0x3558u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005e56u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0093acu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005e56u:
        {
          if (!match16(b, 0x5e56u, 0x6100u)) return -1;
          if (!match16(b, 0x5e58u, 0x4282u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005e5au) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a0dau;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005e5au:
        {
          if (!match16(b, 0x5e5au, 0x303cu)) return -1;
          if (!match16(b, 0x5e5cu, 0x009bu)) return -1;
          c->d[0] = (c->d[0] & 0xffff0000u) | 0x009bu;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x009bu & 0x8000u) ? 8u : 0u) | (0x009bu == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x5e5eu, 0x6100u)) return -1;
          if (!match16(b, 0x5e60u, 0x353cu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005e62u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00939cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005e62u:
        {
          if (!match16(b, 0x5e62u, 0x6100u)) return -1;
          if (!match16(b, 0x5e64u, 0x4276u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005e66u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a0dau;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005e66u:
        {
          if (!match16(b, 0x5e66u, 0x1239u)) return -1;
          if (!match32(b,0x5e68u,0x00ff2bf1u)) return -1;
          if (native_bus_read8(b,0x00ff2bf1u,&byte_value)!=0) return -3;
          c->d[1]=(c->d[1]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0x5e6cu, 0x0241u)) return -1;
          if (!match16(b, 0x5e6eu, 0x000fu)) return -1;
          { uint16_t v=(uint16_t)c->d[1] & 0x000fu; c->d[1]=(c->d[1] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x5e70u, 0x7001u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(1);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x5e72u, 0x0c41u)) return -1;
          if(!match16(b,0x5e74u,0x0001u))return -1;
          {uint32_t x=c->d[1]&65535u,y=0x0001u,r=(x-y)&65535u; c->sr=(c->sr&0xfff0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u)|(((x^y)&(x^r)&0x8000u)?2u:0u)|(x<y?1u:0u);}
          c->cycles+=8u;
          if (!match16(b, 0x5e76u, 0x6700u)) return -1;
          if (!match16(b, 0x5e78u, 0x001au)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x005e92u : 0x005e7au;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x005e7au:
        {
          if (!match16(b, 0x5e7au, 0x7002u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(2);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x5e7cu, 0x0c41u)) return -1;
          if(!match16(b,0x5e7eu,0x0003u))return -1;
          {uint32_t x=c->d[1]&65535u,y=0x0003u,r=(x-y)&65535u; c->sr=(c->sr&0xfff0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u)|(((x^y)&(x^r)&0x8000u)?2u:0u)|(x<y?1u:0u);}
          c->cycles+=8u;
          if (!match16(b, 0x5e80u, 0x6700u)) return -1;
          if (!match16(b, 0x5e82u, 0x0010u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x005e92u : 0x005e84u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x005e84u:
        {
          if (!match16(b, 0x5e84u, 0x7003u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(3);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x5e86u, 0x0c41u)) return -1;
          if(!match16(b,0x5e88u,0x0004u))return -1;
          {uint32_t x=c->d[1]&65535u,y=0x0004u,r=(x-y)&65535u; c->sr=(c->sr&0xfff0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u)|(((x^y)&(x^r)&0x8000u)?2u:0u)|(x<y?1u:0u);}
          c->cycles+=8u;
          if (!match16(b, 0x5e8au, 0x6700u)) return -1;
          if (!match16(b, 0x5e8cu, 0x0006u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x005e92u : 0x005e8eu;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x005e8eu:
        {
          if (!match16(b, 0x5e8eu, 0x7006u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(6);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x5e90u, 0x7206u)) return -1;
          c->d[1] = (uint32_t)(int32_t)(6);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x5e92u, 0x0640u)) return -1;
          { uint32_t x=c->d[0]&65535u,y=0x00a3u,r=(x+y)&65535u;
            c->d[0]=(c->d[0]&0xffff0000u)|r;
            uint16_t carry=(x+y)>65535u,ov=((~(x^y))&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?17u:0u));
          }
          c->cycles+=8u;
          if (!match16(b, 0x5e96u, 0x6100u)) return -1;
          if (!match16(b, 0x5e98u, 0x3504u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005e9au) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00939cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005e92u:
        {
          if (!match16(b, 0x5e92u, 0x0640u)) return -1;
          { uint32_t x=c->d[0]&65535u,y=0x00a3u,r=(x+y)&65535u;
            c->d[0]=(c->d[0]&0xffff0000u)|r;
            uint16_t carry=(x+y)>65535u,ov=((~(x^y))&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?17u:0u));
          }
          c->cycles+=8u;
          if (!match16(b, 0x5e96u, 0x6100u)) return -1;
          if (!match16(b, 0x5e98u, 0x3504u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005e9au) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00939cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005e9au:
        {
          if (!match16(b, 0x5e9au, 0x6100u)) return -1;
          if (!match16(b, 0x5e9cu, 0x423eu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005e9eu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a0dau;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005e9eu:
        {
          if (!match16(b, 0x5e9eu, 0x13f9u)) return -1;
          {uint8_t v;if(native_bus_read8(b,0xff2812u,&v)||native_bus_write8((struct t2bus *)b,0xff0299u,v))return -3;c->sr=(c->sr&0xfff0u)|((v&128u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=28u;
          if (!match16(b, 0x5ea8u, 0x13f9u)) return -1;
          {uint8_t v;if(native_bus_read8(b,0xff2813u,&v)||native_bus_write8((struct t2bus *)b,0xff0298u,v))return -3;c->sr=(c->sr&0xfff0u)|((v&128u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=28u;
          if (!match16(b, 0x5eb2u, 0x303cu)) return -1;
          if (!match16(b, 0x5eb4u, 0x00acu)) return -1;
          c->d[0] = (c->d[0] & 0xffff0000u) | 0x00acu;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00acu & 0x8000u) ? 8u : 0u) | (0x00acu == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x5eb6u, 0x6100u)) return -1;
          if (!match16(b, 0x5eb8u, 0x34e4u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005ebau) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00939cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005ebau:
        {
          if (!match16(b, 0x5ebau, 0x6100u)) return -1;
          if (!match16(b, 0x5ebcu, 0x421eu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005ebeu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a0dau;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005ebeu:
        {
          if (!match16(b, 0x5ebeu, 0x1039u)) return -1;
          if (!match32(b, 0x5ec0u, 0x00ff2b26u)) return -1;
          if (native_bus_read8(b, 0x00ff2b26u, &byte_value) != 0) return -3;
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 0x80u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 16u;
          if (!match16(b, 0x5ec4u, 0xe148u)) return -1;
          { unsigned count=c->d[0]&63u,i;uint32_t v=c->d[0]&65535u;uint16_t carry=0;
            for(i=0;i<count;i++){carry=(v>>15)&1u;v=(v<<1)&65535u;}
            c->d[0]=(c->d[0]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&(count?0xffe0u:0xfff0u))|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)|(count&&carry?17u:0u)); c->cycles+=6u+2u*count; }
          if (!match16(b, 0x5ec6u, 0x1039u)) return -1;
          if (!match32(b, 0x5ec8u, 0x00ff2b25u)) return -1;
          if (native_bus_read8(b, 0x00ff2b25u, &byte_value) != 0) return -3;
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 0x80u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 16u;
          if (!match16(b, 0x5eccu, 0x4a40u)) return -1;
          { uint32_t value = c->d[0] & 0x0000ffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((value & 0x8000u) ? 8u : 0u) | (value == 0u ? 4u : 0u));
          }
          c->cycles += 4u;
          if (!match16(b, 0x5eceu, 0x6600u)) return -1;
          if (!match16(b, 0x5ed0u, 0x0008u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x005ed8u : 0x005ed2u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x005ed2u:
        {
          if (!match16(b, 0x5ed2u, 0x7400u)) return -1;
          c->d[2] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[2] & 0x80000000u) ? 8u : 0u) | (c->d[2] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x5ed4u, 0x6000u)) return -1;
          if (!match16(b, 0x5ed6u, 0x0010u)) return -1;
          c->pc = (1) ? 0x005ee6u : 0x005ed8u;
          c->cycles += (1) ? 10u : 8u;
          return 0;
        }
      case 0x005ed8u:
        {
          if (!match16(b, 0x5ed8u, 0x3439u)) return -1;
          if (!match32(b, 0x5edau, 0x00ff0298u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0298u, &val) != 0) return -3;
            c->d[2] = (c->d[2] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x5edeu, 0xc0fcu)) return -1;
          if(!match16(b,0x5ee0u,0x0064u))return -1;
          {uint32_t r=(c->d[0]&65535u)*0x0064u; c->d[0]=r; c->sr=(c->sr&0xfff0u)|((r&0x80000000u)?8u:0u)|(r==0u?4u:0u);}
          c->cycles+=70u;
          c->pc = 0x005ee2u;
          return 0;
        }
      case 0x005ee6u:
        {
          if (!match16(b, 0x5ee6u, 0x33c2u)) return -1;
          if (!match32(b, 0x5ee8u, 0x00ff0298u)) return -1;
          { uint16_t v=(uint16_t)c->d[2];
            if (native_bus_write16((struct t2bus *)b,0x00ff0298u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x5eecu, 0x303cu)) return -1;
          if (!match16(b, 0x5eeeu, 0x00adu)) return -1;
          c->d[0] = (c->d[0] & 0xffff0000u) | 0x00adu;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00adu & 0x8000u) ? 8u : 0u) | (0x00adu == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x5ef0u, 0x6100u)) return -1;
          if (!match16(b, 0x5ef2u, 0x34aau)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005ef4u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00939cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005ef4u:
        {
          if (!match16(b, 0x5ef4u, 0x6100u)) return -1;
          if (!match16(b, 0x5ef6u, 0x41e4u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x005ef8u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a0dau;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x005ef8u:
        {
          if (!match16(b, 0x5ef8u, 0x1039u)) return -1;
          if (!match32(b, 0x5efau, 0x00ff2ae6u)) return -1;
          if (native_bus_read8(b, 0x00ff2ae6u, &byte_value) != 0) return -3;
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 0x80u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 16u;
          if (!match16(b, 0x5efeu, 0xe148u)) return -1;
          { unsigned count=c->d[0]&63u,i;uint32_t v=c->d[0]&65535u;uint16_t carry=0;
            for(i=0;i<count;i++){carry=(v>>15)&1u;v=(v<<1)&65535u;}
            c->d[0]=(c->d[0]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&(count?0xffe0u:0xfff0u))|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)|(count&&carry?17u:0u)); c->cycles+=6u+2u*count; }
          if (!match16(b, 0x5f00u, 0x1039u)) return -1;
          if (!match32(b, 0x5f02u, 0x00ff2ae5u)) return -1;
          if (native_bus_read8(b, 0x00ff2ae5u, &byte_value) != 0) return -3;
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 0x80u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 16u;
          if (!match16(b, 0x5f06u, 0xc0fcu)) return -1;
          if(!match16(b,0x5f08u,0x0064u))return -1;
          {uint32_t r=(c->d[0]&65535u)*0x0064u; c->d[0]=r; c->sr=(c->sr&0xfff0u)|((r&0x80000000u)?8u:0u)|(r==0u?4u:0u);}
          c->cycles+=70u;
          if (!match16(b, 0x5f0au, 0x3239u)) return -1;
          if (!match32(b, 0x5f0cu, 0x00ff03c4u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff03c4u, &val) != 0) return -3;
            c->d[1] = (c->d[1] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x5f10u, 0x0241u)) return -1;
          if (!match16(b, 0x5f12u, 0x00feu)) return -1;
          { uint16_t v=(uint16_t)c->d[1] & 0x00feu; c->d[1]=(c->d[1] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x5f14u, 0x41f9u)) return -1;
          if (!match32(b, 0x5f16u, 0x0000602au)) return -1;
          c->a[0] = 0x0000602au;
          c->cycles += 12u;
          c->pc = 0x005f1au;
          return 0;
        }
      case 0x00605au:
        {
          if (!match16(b, 0x605au, 0x08b9u)) return -1;
          if (!match16(b, 0x605cu, 0x0005u) || !match32(b, 0x605eu, 0x00ff010du)) return -1;
          if (native_bus_read8(b, 0x00ff010du, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 5)) ? 0u : 4u));
          if (native_bus_write8((struct t2bus *)b, 0x00ff010du, (uint8_t)(byte_value & ~(1u << 5))) != 0) return -3;
          c->cycles += 16u;
          if (!match16(b, 0x6062u, 0x33f9u)) return -1;
          if (!match32(b, 0x6064u, 0x00ff010cu) || !match32(b, 0x6068u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x606cu, 0x23fcu)) return -1;
          if (!match32(b, 0x606eu, 0x00005d66u) || !match32(b, 0x6072u, 0x00ff0138u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff0138u, 0x00005d66u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=00606c addr=00ff0138 value=00005d66\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00005d66u & 0x80000000u) ? 8u : 0u) | (0x00005d66u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x6076u, 0x08f9u)) return -1;
          { uint8_t v; if(native_bus_read8(b,0x00ff010du,&v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&~4u)|((v&(1u<<5))?0u:4u));
            if(native_bus_write8((struct t2bus *)b,0x00ff010du,(uint8_t)(v|(1u<<5)))!=0)return -3; }
          c->cycles+=20u;
          if (!match16(b, 0x607eu, 0x33f9u)) return -1;
          if (!match32(b, 0x6080u, 0x00ff010cu) || !match32(b, 0x6084u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x6088u, 0x41f8u)) return -1;
          if (!match16(b, 0x608au, 0x604au)) return -1;
          c->a[0] = 0x00604au;
          c->cycles += 8u;
          if (!match16(b, 0x608cu, 0x6100u)) return -1;
          if (!match16(b, 0x608eu, 0x392au)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x006090u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0099b8u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x006090u:
        {
          if (!match16(b, 0x6090u, 0x4a79u)) return -1;
          if (!match32(b, 0x6092u, 0x00ff0222u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff0222u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x6096u, 0x66f8u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x006090u : 0x006098u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x006098u:
        {
          if (!match16(b, 0x6098u, 0x08f9u)) return -1;
          { uint8_t v; if(native_bus_read8(b,0x00ff05c8u,&v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&~4u)|((v&(1u<<7))?0u:4u));
            if(native_bus_write8((struct t2bus *)b,0x00ff05c8u,(uint8_t)(v|(1u<<7)))!=0)return -3; }
          c->cycles+=20u;
          if (!match16(b, 0x60a0u, 0x7e00u)) return -1;
          c->d[7] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[7] & 0x80000000u) ? 8u : 0u) | (c->d[7] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x60a2u, 0x4a47u)) return -1;
          { uint32_t value = c->d[7] & 0x0000ffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((value & 0x8000u) ? 8u : 0u) | (value == 0u ? 4u : 0u));
          }
          c->cycles += 4u;
          if (!match16(b, 0x60a4u, 0x6600u)) return -1;
          if (!match16(b, 0x60a6u, 0x0024u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x0060cau : 0x0060a8u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x0060a2u:
        {
          if (!match16(b, 0x60a2u, 0x4a47u)) return -1;
          { uint32_t value = c->d[7] & 0x0000ffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((value & 0x8000u) ? 8u : 0u) | (value == 0u ? 4u : 0u));
          }
          c->cycles += 4u;
          if (!match16(b, 0x60a4u, 0x6600u)) return -1;
          if (!match16(b, 0x60a6u, 0x0024u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x0060cau : 0x0060a8u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x0060a8u:
        {
          if (!match16(b, 0x60a8u, 0x0839u)) return -1;
          if (!match16(b, 0x60aau, 0x0007u) || !match32(b, 0x60acu, 0x00ff05c8u)) return -1;
          if (native_bus_read8(b, 0x00ff05c8u, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 7)) ? 0u : 4u));
          c->cycles += 16u;
          if (!match16(b, 0x60b0u, 0x6600u)) return -1;
          if (!match16(b, 0x60b2u, 0x0020u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x0060d2u : 0x0060b4u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x0060b4u:
        {
          if (!match16(b, 0x60b4u, 0x0839u)) return -1;
          if (!match16(b, 0x60b6u, 0x0007u) || !match32(b, 0x60b8u, 0x00ff0006u)) return -1;
          if (native_bus_read8(b, 0x00ff0006u, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 7)) ? 0u : 4u));
          c->cycles += 16u;
          if (!match16(b, 0x60bcu, 0x6700u)) return -1;
          if (!match16(b, 0x60beu, 0x0014u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x0060d2u : 0x0060c0u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x0060c0u:
        {
          if (!match16(b, 0x60c0u, 0x08f9u)) return -1;
          { uint8_t v; if(native_bus_read8(b,0x00ff05c8u,&v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&~4u)|((v&(1u<<7))?0u:4u));
            if(native_bus_write8((struct t2bus *)b,0x00ff05c8u,(uint8_t)(v|(1u<<7)))!=0)return -3; }
          c->cycles+=20u;
          if (!match16(b, 0x60c8u, 0x7effu)) return -1;
          c->d[7] = (uint32_t)(int32_t)(-1);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[7] & 0x80000000u) ? 8u : 0u) | (c->d[7] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x60cau, 0x33fcu)) return -1;
          if (!match16(b, 0x60ccu, 0xffffu) || !match32(b, 0x60ceu, 0x00ff01a8u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff01a8u, 0xffffu) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xffffu & 0x8000u) ? 8u : 0u) | (0xffffu == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x60d2u, 0x4a79u)) return -1;
          if (!match32(b, 0x60d4u, 0x00ff0658u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff0658u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x60d8u, 0x66c8u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x0060a2u : 0x0060dau;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x0060cau:
        {
          if (!match16(b, 0x60cau, 0x33fcu)) return -1;
          if (!match16(b, 0x60ccu, 0xffffu) || !match32(b, 0x60ceu, 0x00ff01a8u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff01a8u, 0xffffu) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xffffu & 0x8000u) ? 8u : 0u) | (0xffffu == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x60d2u, 0x4a79u)) return -1;
          if (!match32(b, 0x60d4u, 0x00ff0658u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff0658u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x60d8u, 0x66c8u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x0060a2u : 0x0060dau;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x0060d2u:
        {
          if (!match16(b, 0x60d2u, 0x4a79u)) return -1;
          if (!match32(b, 0x60d4u, 0x00ff0658u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff0658u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x60d8u, 0x66c8u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x0060a2u : 0x0060dau;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x0060dau:
        {
          if (!match16(b, 0x60dau, 0x41f8u)) return -1;
          if (!match16(b, 0x60dcu, 0x6052u)) return -1;
          c->a[0] = 0x006052u;
          c->cycles += 8u;
          if (!match16(b, 0x60deu, 0x6100u)) return -1;
          if (!match16(b, 0x60e0u, 0x38d8u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0060e2u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0099b8u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0060e2u:
        {
          if (!match16(b, 0x60e2u, 0x4a79u)) return -1;
          if (!match32(b, 0x60e4u, 0x00ff0222u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff0222u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x60e8u, 0x66f8u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x0060e2u : 0x0060eau;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x0060eau:
        {
          if (!match16(b, 0x60eau, 0x08b9u)) return -1;
          if (!match16(b, 0x60ecu, 0x0005u) || !match32(b, 0x60eeu, 0x00ff010du)) return -1;
          if (native_bus_read8(b, 0x00ff010du, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 5)) ? 0u : 4u));
          if (native_bus_write8((struct t2bus *)b, 0x00ff010du, (uint8_t)(byte_value & ~(1u << 5))) != 0) return -3;
          c->cycles += 16u;
          if (!match16(b, 0x60f2u, 0x33f9u)) return -1;
          if (!match32(b, 0x60f4u, 0x00ff010cu) || !match32(b, 0x60f8u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x60fcu, 0x23fcu)) return -1;
          if (!match32(b, 0x60feu, 0x00005692u) || !match32(b, 0x6102u, 0x00ff0138u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff0138u, 0x00005692u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=0060fc addr=00ff0138 value=00005692\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00005692u & 0x80000000u) ? 8u : 0u) | (0x00005692u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x6106u, 0x08f9u)) return -1;
          { uint8_t v; if(native_bus_read8(b,0x00ff010du,&v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&~4u)|((v&(1u<<5))?0u:4u));
            if(native_bus_write8((struct t2bus *)b,0x00ff010du,(uint8_t)(v|(1u<<5)))!=0)return -3; }
          c->cycles+=20u;
          if (!match16(b, 0x610eu, 0x33f9u)) return -1;
          if (!match32(b, 0x6110u, 0x00ff010cu) || !match32(b, 0x6114u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x6118u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00611au:
        {
          if (!match16(b, 0x611au, 0x3039u)) return -1;
          if (!match32(b, 0x611cu, 0x00ff03b0u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff03b0u, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x6120u, 0xb079u)) return -1;
          { uint16_t v; if(native_bus_read16(b,0x00ff03b0u,&v)!=0)return -3;
            uint32_t x=(c->d[0]&65535u),y=v,r=(x-y)&65535u;
            uint16_t carry=x<y;
            uint16_t ov=((x^y)&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?1u:0u));
          }
          c->cycles+=16u;
          if (!match16(b, 0x6126u, 0x67f8u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x006120u : 0x006128u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x006120u:
        {
          if (!match16(b, 0x6120u, 0xb079u)) return -1;
          { uint16_t v; if(native_bus_read16(b,0x00ff03b0u,&v)!=0)return -3;
            uint32_t x=(c->d[0]&65535u),y=v,r=(x-y)&65535u;
            uint16_t carry=x<y;
            uint16_t ov=((x^y)&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?1u:0u));
          }
          c->cycles+=16u;
          if (!match16(b, 0x6126u, 0x67f8u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x006120u : 0x006128u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x006128u:
        {
          if (!match16(b, 0x6128u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00616au:
        {
          if (!match16(b, 0x616au, 0x1039u)) return -1;
          if (!match32(b, 0x616cu, 0x00ff0006u)) return -1;
          if (native_bus_read8(b, 0x00ff0006u, &byte_value) != 0) return -3;
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 0x80u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 16u;
          if (!match16(b, 0x6170u, 0x7200u)) return -1;
          c->d[1] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x6172u, 0x7400u)) return -1;
          c->d[2] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[2] & 0x80000000u) ? 8u : 0u) | (c->d[2] == 0u ? 4u : 0u));
          c->cycles += 4u;
          c->pc = 0x006174u;
          return 0;
        }
      case 0x0061d0u:
        {
          if (!match16(b, 0x61d0u, 0x1c39u)) return -1;
          if (!match32(b,0x61d2u,0x00ff2867u)) return -1;
          if (native_bus_read8(b,0x00ff2867u,&byte_value)!=0) return -3;
          c->d[6]=(c->d[6]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0x61d6u, 0xe14eu)) return -1;
          { unsigned count=c->d[0]&63u,i;uint32_t v=c->d[6]&65535u;uint16_t carry=0;
            for(i=0;i<count;i++){carry=(v>>15)&1u;v=(v<<1)&65535u;}
            c->d[6]=(c->d[6]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&(count?0xffe0u:0xfff0u))|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)|(count&&carry?17u:0u)); c->cycles+=6u+2u*count; }
          if (!match16(b, 0x61d8u, 0x1c39u)) return -1;
          if (!match32(b,0x61dau,0x00ff2866u)) return -1;
          if (native_bus_read8(b,0x00ff2866u,&byte_value)!=0) return -3;
          c->d[6]=(c->d[6]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0x61deu, 0x1e39u)) return -1;
          if (!match32(b,0x61e0u,0x00ff2869u)) return -1;
          if (native_bus_read8(b,0x00ff2869u,&byte_value)!=0) return -3;
          c->d[7]=(c->d[7]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0x61e4u, 0xe14fu)) return -1;
          { unsigned count=c->d[0]&63u,i;uint32_t v=c->d[7]&65535u;uint16_t carry=0;
            for(i=0;i<count;i++){carry=(v>>15)&1u;v=(v<<1)&65535u;}
            c->d[7]=(c->d[7]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&(count?0xffe0u:0xfff0u))|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)|(count&&carry?17u:0u)); c->cycles+=6u+2u*count; }
          if (!match16(b, 0x61e6u, 0x1e39u)) return -1;
          if (!match32(b,0x61e8u,0x00ff2868u)) return -1;
          if (native_bus_read8(b,0x00ff2868u,&byte_value)!=0) return -3;
          c->d[7]=(c->d[7]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          c->pc = 0x0061ecu;
          return 0;
        }
      case 0x006264u:
        {
          if (!match16(b, 0x6264u, 0x4a79u)) return -1;
          if (!match32(b, 0x6266u, 0x00ff0684u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff0684u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x626au, 0x6600u)) return -1;
          if (!match16(b, 0x626cu, 0x0046u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x0062b2u : 0x00626eu;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00626eu:
        {
          if (!match16(b, 0x626eu, 0x23fcu)) return -1;
          if (!match32(b, 0x6270u, 0x40000010u) || !match32(b, 0x6274u, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0x40000010u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=00626e addr=00c00004 value=40000010\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x40000010u & 0x80000000u) ? 8u : 0u) | (0x40000010u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x6278u, 0x3039u)) return -1;
          if (!match32(b, 0x627au, 0x00ff016au)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff016au, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x627eu, 0x0240u)) return -1;
          if (!match16(b, 0x6280u, 0x00ffu)) return -1;
          { uint16_t v=(uint16_t)c->d[0] & 0x00ffu; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x6282u, 0x33c0u)) return -1;
          if (!match32(b, 0x6284u, 0x00c00000u)) return -1;
          { uint16_t v=(uint16_t)c->d[0];
            if (native_bus_write16((struct t2bus *)b,0x00c00000u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x6288u, 0x33c0u)) return -1;
          if (!match32(b, 0x628au, 0x00c00000u)) return -1;
          { uint16_t v=(uint16_t)c->d[0];
            if (native_bus_write16((struct t2bus *)b,0x00c00000u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x628eu, 0x23fcu)) return -1;
          if (!match32(b, 0x6290u, 0x70000003u) || !match32(b, 0x6294u, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0x70000003u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=00628e addr=00c00004 value=70000003\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x70000003u & 0x80000000u) ? 8u : 0u) | (0x70000003u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x6298u, 0x3039u)) return -1;
          if (!match32(b, 0x629au, 0x00ff0168u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0168u, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x629eu, 0x4440u)) return -1;
          { uint32_t x=c->d[0]&65535u,r=(-x)&65535u;
            c->d[0]=(c->d[0]&0xffff0000u)|r;
            uint16_t carry=x!=0u?1u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(x==32768u?2u:0u)|carry|(carry?16u:0u)); }
          c->cycles+=4u;
          if (!match16(b, 0x62a0u, 0x0240u)) return -1;
          if (!match16(b, 0x62a2u, 0x01ffu)) return -1;
          { uint16_t v=(uint16_t)c->d[0] & 0x01ffu; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x62a4u, 0x33c0u)) return -1;
          if (!match32(b, 0x62a6u, 0x00c00000u)) return -1;
          { uint16_t v=(uint16_t)c->d[0];
            if (native_bus_write16((struct t2bus *)b,0x00c00000u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x62aau, 0x33c0u)) return -1;
          if (!match32(b, 0x62acu, 0x00c00000u)) return -1;
          { uint16_t v=(uint16_t)c->d[0];
            if (native_bus_write16((struct t2bus *)b,0x00c00000u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x62b0u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x0062b2u:
        {
          if (!match16(b, 0x62b2u, 0x23fcu)) return -1;
          if (!match32(b, 0x62b4u, 0x40000010u) || !match32(b, 0x62b8u, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0x40000010u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=0062b2 addr=00c00004 value=40000010\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x40000010u & 0x80000000u) ? 8u : 0u) | (0x40000010u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x62bcu, 0x3039u)) return -1;
          if (!match32(b, 0x62beu, 0x00ff016au)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff016au, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x62c2u, 0x0240u)) return -1;
          if (!match16(b, 0x62c4u, 0x00ffu)) return -1;
          { uint16_t v=(uint16_t)c->d[0] & 0x00ffu; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x62c6u, 0x33c0u)) return -1;
          if (!match32(b, 0x62c8u, 0x00c00000u)) return -1;
          { uint16_t v=(uint16_t)c->d[0];
            if (native_bus_write16((struct t2bus *)b,0x00c00000u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x62ccu, 0x3039u)) return -1;
          if (!match32(b, 0x62ceu, 0x00ff016au)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff016au, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          c->pc = 0x0062d2u;
          return 0;
        }
      case 0x006346u:
        {
          if (!match16(b, 0x6346u, 0x0c79u)) return -1;
          { uint16_t v; if(native_bus_read16(b,0x00ff03c4u,&v)!=0)return -3;
            uint32_t x=v,y=0x0006u,r=(x-y)&65535u;
            uint16_t carry=x<y;
            uint16_t ov=((x^y)&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?1u:0u));
          }
          c->cycles+=16u;
          if (!match16(b, 0x634eu, 0x6700u)) return -1;
          if (!match16(b, 0x6350u, 0x000eu)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x00635eu : 0x006352u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x006352u:
        {
          if (!match16(b, 0x6352u, 0x0c79u)) return -1;
          { uint16_t v; if(native_bus_read16(b,0x00ff03c4u,&v)!=0)return -3;
            uint32_t x=v,y=0x000cu,r=(x-y)&65535u;
            uint16_t carry=x<y;
            uint16_t ov=((x^y)&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?1u:0u));
          }
          c->cycles+=16u;
          if (!match16(b, 0x635au, 0x6600u)) return -1;
          if (!match16(b, 0x635cu, 0x0060u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x0063bcu : 0x00635eu;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00635eu:
        {
          if (!match16(b, 0x635eu, 0x41f9u)) return -1;
          if (!match32(b, 0x6360u, 0x000063beu)) return -1;
          c->a[0] = 0x000063beu;
          c->cycles += 12u;
          if (!match16(b, 0x6364u, 0x0c79u)) return -1;
          { uint16_t v; if(native_bus_read16(b,0x00ff03c4u,&v)!=0)return -3;
            uint32_t x=v,y=0x000cu,r=(x-y)&65535u;
            uint16_t carry=x<y;
            uint16_t ov=((x^y)&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?1u:0u));
          }
          c->cycles+=16u;
          if (!match16(b, 0x636cu, 0x6600u)) return -1;
          if (!match16(b, 0x636eu, 0x0008u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x006376u : 0x006370u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x006370u:
        {
          if (!match16(b, 0x6370u, 0x41f9u)) return -1;
          if (!match32(b, 0x6372u, 0x000063ceu)) return -1;
          c->a[0] = 0x000063ceu;
          c->cycles += 12u;
          if (!match16(b, 0x6376u, 0x23c8u)) return -1;
          if (!match32(b, 0x6378u, 0x00ff0644u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff0644u, c->a[0]) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->a[0] & 0x80000000u) ? 8u : 0u) | (c->a[0] == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x637cu, 0x33e8u)) return -1;
          {uint16_t v;uint32_t a=(c->a[0]+(int16_t)0x000eu)&0xffffffu;if(native_bus_read16(b,a,&v)||native_bus_write16((struct t2bus *)b,0xff061au,v))return -3;c->sr=(c->sr&0xfff0u)|((v&32768u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=24u;
          c->pc = 0x006384u;
          return 0;
        }
      case 0x006376u:
        {
          if (!match16(b, 0x6376u, 0x23c8u)) return -1;
          if (!match32(b, 0x6378u, 0x00ff0644u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff0644u, c->a[0]) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->a[0] & 0x80000000u) ? 8u : 0u) | (c->a[0] == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x637cu, 0x33e8u)) return -1;
          {uint16_t v;uint32_t a=(c->a[0]+(int16_t)0x000eu)&0xffffffu;if(native_bus_read16(b,a,&v)||native_bus_write16((struct t2bus *)b,0xff061au,v))return -3;c->sr=(c->sr&0xfff0u)|((v&32768u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=24u;
          c->pc = 0x006384u;
          return 0;
        }
      case 0x0063bcu:
        {
          if (!match16(b, 0x63bcu, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x0063deu:
        {
          if (!match16(b, 0x63deu, 0x4a79u)) return -1;
          if (!match32(b, 0x63e0u, 0x00ff0684u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff0684u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x63e4u, 0x6600u)) return -1;
          if (!match16(b, 0x63e6u, 0x008eu)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x006474u : 0x0063e8u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x0063e8u:
        {
          if (!match16(b, 0x63e8u, 0x23fcu)) return -1;
          if (!match32(b, 0x63eau, 0x40000003u) || !match32(b, 0x63eeu, 0x00ff017eu)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff017eu, 0x40000003u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=0063e8 addr=00ff017e value=40000003\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x40000003u & 0x80000000u) ? 8u : 0u) | (0x40000003u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x63f2u, 0x23fcu)) return -1;
          if (!match32(b, 0x63f4u, 0x50000003u) || !match32(b, 0x63f8u, 0x00ff018au)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff018au, 0x50000003u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=0063f2 addr=00ff018a value=50000003\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x50000003u & 0x80000000u) ? 8u : 0u) | (0x50000003u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x63fcu, 0x23fcu)) return -1;
          if (!match32(b, 0x63feu, 0x00ff05f8u) || !match32(b, 0x6402u, 0x00ff0182u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff0182u, 0x00ff05f8u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=0063fc addr=00ff0182 value=00ff05f8\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00ff05f8u & 0x80000000u) ? 8u : 0u) | (0x00ff05f8u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x6406u, 0x23fcu)) return -1;
          if (!match32(b, 0x6408u, 0x0000bb7au) || !match32(b, 0x640cu, 0x00ff0192u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff0192u, 0x0000bb7au) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=006406 addr=00ff0192 value=0000bb7a\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000bb7au & 0x80000000u) ? 8u : 0u) | (0x0000bb7au == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x6410u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x6412u, 0x7200u)) return -1;
          c->d[1] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x6414u, 0x7414u)) return -1;
          c->d[2] = (uint32_t)(int32_t)(20);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[2] & 0x80000000u) ? 8u : 0u) | (c->d[2] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x6416u, 0x760eu)) return -1;
          c->d[3] = (uint32_t)(int32_t)(14);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[3] & 0x80000000u) ? 8u : 0u) | (c->d[3] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x6418u, 0x6100u)) return -1;
          if (!match16(b, 0x641au, 0x0290u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00641cu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0066aau;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00641cu:
        {
          if (!match16(b, 0x641cu, 0x23fcu)) return -1;
          if (!match32(b, 0x641eu, 0x60000003u) || !match32(b, 0x6422u, 0x00ff017eu)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff017eu, 0x60000003u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=00641c addr=00ff017e value=60000003\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x60000003u & 0x80000000u) ? 8u : 0u) | (0x60000003u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x6426u, 0x23fcu)) return -1;
          if (!match32(b, 0x6428u, 0x70000003u) || !match32(b, 0x642cu, 0x00ff018au)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff018au, 0x70000003u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=006426 addr=00ff018a value=70000003\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x70000003u & 0x80000000u) ? 8u : 0u) | (0x70000003u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x6430u, 0x23fcu)) return -1;
          if (!match32(b, 0x6432u, 0x00ff0608u) || !match32(b, 0x6436u, 0x00ff0182u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff0182u, 0x00ff0608u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=006430 addr=00ff0182 value=00ff0608\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00ff0608u & 0x80000000u) ? 8u : 0u) | (0x00ff0608u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x643au, 0x23fcu)) return -1;
          if (!match32(b, 0x643cu, 0x0000bb9au) || !match32(b, 0x6440u, 0x00ff0192u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff0192u, 0x0000bb9au) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=00643a addr=00ff0192 value=0000bb9a\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000bb9au & 0x80000000u) ? 8u : 0u) | (0x0000bb9au == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x6444u, 0x0c79u)) return -1;
          { uint16_t v; if(native_bus_read16(b,0x00ff03c4u,&v)!=0)return -3;
            uint32_t x=v,y=0x0002u,r=(x-y)&65535u;
            uint16_t carry=x<y;
            uint16_t ov=((x^y)&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?1u:0u));
          }
          c->cycles+=16u;
          if (!match16(b, 0x644cu, 0x6600u)) return -1;
          if (!match16(b, 0x644eu, 0x0018u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x006466u : 0x006450u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x006450u:
        {
          if (!match16(b, 0x6450u, 0x0c79u)) return -1;
          { uint16_t v; if(native_bus_read16(b,0x00ff03c6u,&v)!=0)return -3;
            uint32_t x=v,y=0x0002u,r=(x-y)&65535u;
            uint16_t carry=x<y;
            uint16_t ov=((x^y)&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?1u:0u));
          }
          c->cycles+=16u;
          if (!match16(b, 0x6458u, 0x6600u)) return -1;
          if (!match16(b, 0x645au, 0x000cu)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x006466u : 0x00645cu;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00645cu:
        {
          if (!match16(b, 0x645cu, 0x23fcu)) return -1;
          if (!match32(b, 0x645eu, 0x0000bb7au) || !match32(b, 0x6462u, 0x00ff0192u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff0192u, 0x0000bb7au) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=00645c addr=00ff0192 value=0000bb7a\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000bb7au & 0x80000000u) ? 8u : 0u) | (0x0000bb7au == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x6466u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x6468u, 0x7200u)) return -1;
          c->d[1] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x646au, 0x7414u)) return -1;
          c->d[2] = (uint32_t)(int32_t)(20);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[2] & 0x80000000u) ? 8u : 0u) | (c->d[2] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x646cu, 0x760eu)) return -1;
          c->d[3] = (uint32_t)(int32_t)(14);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[3] & 0x80000000u) ? 8u : 0u) | (c->d[3] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x646eu, 0x6100u)) return -1;
          if (!match16(b, 0x6470u, 0x023au)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x006472u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0066aau;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x006466u:
        {
          if (!match16(b, 0x6466u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x6468u, 0x7200u)) return -1;
          c->d[1] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x646au, 0x7414u)) return -1;
          c->d[2] = (uint32_t)(int32_t)(20);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[2] & 0x80000000u) ? 8u : 0u) | (c->d[2] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x646cu, 0x760eu)) return -1;
          c->d[3] = (uint32_t)(int32_t)(14);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[3] & 0x80000000u) ? 8u : 0u) | (c->d[3] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x646eu, 0x6100u)) return -1;
          if (!match16(b, 0x6470u, 0x023au)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x006472u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0066aau;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x006472u:
        {
          if (!match16(b, 0x6472u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x006474u:
        {
          if (!match16(b, 0x6474u, 0x3039u)) return -1;
          if (!match32(b, 0x6476u, 0x00ff0168u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0168u, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x647au, 0x3239u)) return -1;
          if (!match32(b, 0x647cu, 0x00ff016au)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff016au, &val) != 0) return -3;
            c->d[1] = (c->d[1] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x6480u, 0x3f00u)) return -1;
          c->a[7]=(c->a[7]-2u)&0xffffffu;
          if (native_bus_write16((struct t2bus *)b,c->a[7],(uint16_t)c->d[0]) != 0) return -3;
          { uint16_t v=(uint16_t)c->d[0]; c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x6482u, 0x3f01u)) return -1;
          c->a[7]=(c->a[7]-2u)&0xffffffu;
          if (native_bus_write16((struct t2bus *)b,c->a[7],(uint16_t)c->d[1]) != 0) return -3;
          { uint16_t v=(uint16_t)c->d[1]; c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles += 8u;
          c->pc = 0x006484u;
          return 0;
        }
      case 0x0066aau:
        {
          if (!match16(b, 0x66aau, 0x3e39u)) return -1;
          if (!match32(b, 0x66acu, 0x00ff0168u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0168u, &val) != 0) return -3;
            c->d[7] = (c->d[7] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x66b0u, 0xde40u)) return -1;
          { uint32_t x = c->d[0] & 65535u, y = c->d[7] & 65535u, r = (x+y) & 65535u;
            uint16_t flags = (uint16_t)(((r & 0x8000u) ? 8u : 0u) | ((r == 0u) ? 4u : 0u) | (((~(x ^ y) & (r ^ y)) & 0x8000u) ? 2u : 0u) | ((x+y > 65535u) ? 17u : 0u));
            c->d[7] = (c->d[7] & 0xffff0000u) | r;
            c->sr = (uint16_t)((c->sr & 0xffe0u) | flags);
          }
          c->cycles += 4u;
          if (!match16(b, 0x66b2u, 0xe84fu)) return -1;
          { uint16_t old=(uint16_t)c->d[7],r=(uint16_t)(old>>4);
            uint16_t carry=(old>>3)&1u;
            c->d[7]=(c->d[7]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xffe0u)|(r==0u?4u:0u)|(carry?17u:0u));
            c->cycles+=14u;
          }
          if (!match16(b, 0x66b4u, 0x3c07u)) return -1;
          { uint16_t v=(uint16_t)c->d[7]; c->d[6]=(c->d[6] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0x66b6u, 0xdc42u)) return -1;
          { uint32_t x = c->d[2] & 65535u, y = c->d[6] & 65535u, r = (x+y) & 65535u;
            uint16_t flags = (uint16_t)(((r & 0x8000u) ? 8u : 0u) | ((r == 0u) ? 4u : 0u) | (((~(x ^ y) & (r ^ y)) & 0x8000u) ? 2u : 0u) | ((x+y > 65535u) ? 17u : 0u));
            c->d[6] = (c->d[6] & 0xffff0000u) | r;
            c->sr = (uint16_t)((c->sr & 0xffe0u) | flags);
          }
          c->cycles += 4u;
          if (!match16(b, 0x66b8u, 0x3a07u)) return -1;
          { uint16_t v=(uint16_t)c->d[7]; c->d[5]=(c->d[5] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0x66bau, 0x0247u)) return -1;
          if (!match16(b, 0x66bcu, 0xffe0u)) return -1;
          { uint16_t v=(uint16_t)c->d[7] & 0xffe0u; c->d[7]=(c->d[7] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x66beu, 0x0246u)) return -1;
          if (!match16(b, 0x66c0u, 0xffe0u)) return -1;
          { uint16_t v=(uint16_t)c->d[6] & 0xffe0u; c->d[6]=(c->d[6] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x66c2u, 0xbc47u)) return -1;
          { uint32_t x=c->d[7]&0xffffu,y=c->d[6]&0xffffu,r=(y-x)&0xffffu;
            uint16_t f=(uint16_t)(((r&0x8000u)?8u:0u)|((r==0u)?4u:0u)|(((y^x)&(y^r)&0x8000u)?2u:0u)|((x>y)?1u:0u));
            c->sr=(uint16_t)((c->sr&0xfff0u)|f);
          }
          c->cycles += 4u;
          if (!match16(b, 0x66c4u, 0x6700u)) return -1;
          if (!match16(b, 0x66c6u, 0x002au)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x0066f0u : 0x0066c8u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x0066c8u:
        {
          if (!match16(b, 0x66c8u, 0x0245u)) return -1;
          if (!match16(b, 0x66cau, 0x001fu)) return -1;
          { uint16_t v=(uint16_t)c->d[5] & 0x001fu; c->d[5]=(c->d[5] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x66ccu, 0x383cu)) return -1;
          if (!match16(b, 0x66ceu, 0x001fu)) return -1;
          c->d[4] = (c->d[4] & 0xffff0000u) | 0x001fu;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x001fu & 0x8000u) ? 8u : 0u) | (0x001fu == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x66d0u, 0x9845u)) return -1;
          { uint16_t x=(uint16_t)c->d[5], y=(uint16_t)c->d[4],r=(uint16_t)(x - y);
            c->d[5]=(c->d[5]&0xffff0000u)|r;
            uint16_t carry=(x<y)?1u:0u;
            uint16_t ov=((x^y)&(x^r)&0x8000u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u)|ov|carry|(carry?16u:0u));
          }
          c->cycles+=4u;
          c->pc = 0x0066d2u;
          return 0;
        }
      case 0x006e90u:
        {
          if (!match16(b, 0x6e90u, 0x08b9u)) return -1;
          if (!match16(b, 0x6e92u, 0x0005u) || !match32(b, 0x6e94u, 0x00ff010du)) return -1;
          if (native_bus_read8(b, 0x00ff010du, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 5)) ? 0u : 4u));
          if (native_bus_write8((struct t2bus *)b, 0x00ff010du, (uint8_t)(byte_value & ~(1u << 5))) != 0) return -3;
          c->cycles += 16u;
          if (!match16(b, 0x6e98u, 0x56f9u)) return -1;
          if (!match32(b, 0x6e9au, 0x00ff0008u)) return -1;
          if (native_bus_write8((struct t2bus *)b, 0x00ff0008u, (c->sr & 4u) ? 0u : 0xffu) != 0) return -3;
          c->cycles += 16u;
          if (!match16(b, 0x6e9eu, 0x33f9u)) return -1;
          if (!match32(b, 0x6ea0u, 0x00ff010cu) || !match32(b, 0x6ea4u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x6ea8u, 0x3039u)) return -1;
          if (!match32(b, 0x6eaau, 0x00ff03c6u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff03c6u, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x6eaeu, 0x2a79u)) return -1;
          if (!match32(b, 0x6eb0u, 0x00ff066eu)) return -1;
          if (native_bus_read32(b, 0x00ff066eu, &c->a[5]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0x6eb4u, 0xc0fcu)) return -1;
          if(!match16(b,0x6eb6u,0x000cu))return -1;
          {uint32_t r=(c->d[0]&65535u)*0x000cu; c->d[0]=r; c->sr=(c->sr&0xfff0u)|((r&0x80000000u)?8u:0u)|(r==0u?4u:0u);}
          c->cycles+=70u;
          if (!match16(b, 0x6eb8u, 0xdac0u)) return -1;
          c->a[5]=(c->a[5]+(int16_t)(c->d[0]&65535u))&0xffffffu;
          c->cycles+=8u;
          if (!match16(b, 0x6ebau, 0x33ddu)) return -1;
          {uint16_t v;if(native_bus_read16(b,c->a[5],&v))return -3;c->a[5]=(c->a[5]+2u)&0xffffffu;if(native_bus_write16((struct t2bus *)b,0xff0684u,v))return -3;c->sr=(c->sr&0xfff0u)|((v&32768u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=20u;
          if (!match16(b, 0x6ec0u, 0x301du)) return -1;
          { uint16_t v; if(native_bus_read16(b,c->a[5],&v)!=0) return -3;
            c->a[5]=(c->a[5]+2u)&0xffffffu;
            c->d[0]=(c->d[0]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=8u;
          if (!match16(b, 0x6ec2u, 0xed48u)) return -1;
          { unsigned count=c->d[6]&63u,i;uint32_t v=c->d[0]&65535u;uint16_t carry=0;
            for(i=0;i<count;i++){carry=(v>>15)&1u;v=(v<<1)&65535u;}
            c->d[0]=(c->d[0]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&(count?0xffe0u:0xfff0u))|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)|(count&&carry?17u:0u)); c->cycles+=6u+2u*count; }
          if (!match16(b, 0x6ec4u, 0x2079u)) return -1;
          if (!match32(b, 0x6ec6u, 0x00ff0676u)) return -1;
          if (native_bus_read32(b, 0x00ff0676u, &c->a[0]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0x6ecau, 0xd0c0u)) return -1;
          c->a[0]=(c->a[0]+(int16_t)(c->d[0]&65535u))&0xffffffu;
          c->cycles+=8u;
          if (!match16(b, 0x6eccu, 0x7002u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(2);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x6eceu, 0x6100u)) return -1;
          if (!match16(b, 0x6ed0u, 0x49b4u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x006ed2u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00b884u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x006ed2u:
        {
          if (!match16(b, 0x6ed2u, 0xd0fcu)) return -1;
          c->a[0]=(c->a[0]+(int16_t)0x0020u)&0xffffffu;
          c->cycles+=8u;
          if (!match16(b, 0x6ed6u, 0x7003u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(3);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x6ed8u, 0x6100u)) return -1;
          if (!match16(b, 0x6edau, 0x49aau)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x006edcu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00b884u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x006edcu:
        {
          if (!match16(b, 0x6edcu, 0x2879u)) return -1;
          if (!match32(b, 0x6edeu, 0x00ff0672u)) return -1;
          if (native_bus_read32(b, 0x00ff0672u, &c->a[4]) != 0) return -3;
          c->cycles += 20u;
          c->pc = 0x006ee2u;
          return 0;
        }
      case 0x006f94u:
        {
          if (!match16(b, 0x6f94u, 0x23fcu)) return -1;
          if (!match32(b, 0x6f96u, 0x50120003u) || !match32(b, 0x6f9au, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0x50120003u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=006f94 addr=00c00004 value=50120003\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x50120003u & 0x80000000u) ? 8u : 0u) | (0x50120003u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x6f9eu, 0x33fcu)) return -1;
          if (!match16(b, 0x6fa0u, 0x0f03u) || !match32(b, 0x6fa2u, 0x00c00000u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00c00000u, 0x0f03u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0f03u & 0x8000u) ? 8u : 0u) | (0x0f03u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x6fa6u, 0x23fcu)) return -1;
          if (!match32(b, 0x6fa8u, 0x50180003u) || !match32(b, 0x6facu, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0x50180003u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=006fa6 addr=00c00004 value=50180003\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x50180003u & 0x80000000u) ? 8u : 0u) | (0x50180003u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x6fb0u, 0x33fcu)) return -1;
          if (!match16(b, 0x6fb2u, 0x0088u) || !match32(b, 0x6fb4u, 0x00c00000u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00c00000u, 0x0088u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0088u & 0x8000u) ? 8u : 0u) | (0x0088u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x6fb8u, 0x33fcu)) return -1;
          if (!match16(b, 0x6fbau, 0x0f04u) || !match32(b, 0x6fbcu, 0x00c00000u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00c00000u, 0x0f04u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0f04u & 0x8000u) ? 8u : 0u) | (0x0f04u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x6fc0u, 0x33fcu)) return -1;
          if (!match16(b, 0x6fc2u, 0x8781u) || !match32(b, 0x6fc4u, 0x00c00000u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00c00000u, 0x8781u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x8781u & 0x8000u) ? 8u : 0u) | (0x8781u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x6fc8u, 0x33fcu)) return -1;
          if (!match16(b, 0x6fcau, 0x0138u) || !match32(b, 0x6fccu, 0x00c00000u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00c00000u, 0x0138u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0138u & 0x8000u) ? 8u : 0u) | (0x0138u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x6fd0u, 0x33fcu)) return -1;
          if (!match16(b, 0x6fd2u, 0x0088u) || !match32(b, 0x6fd4u, 0x00c00000u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00c00000u, 0x0088u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0088u & 0x8000u) ? 8u : 0u) | (0x0088u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x6fd8u, 0x33fcu)) return -1;
          if (!match16(b, 0x6fdau, 0x0f05u) || !match32(b, 0x6fdcu, 0x00c00000u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00c00000u, 0x0f05u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0f05u & 0x8000u) ? 8u : 0u) | (0x0f05u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x6fe0u, 0x33fcu)) return -1;
          if (!match16(b, 0x6fe2u, 0x8791u) || !match32(b, 0x6fe4u, 0x00c00000u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00c00000u, 0x8791u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x8791u & 0x8000u) ? 8u : 0u) | (0x8791u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x6fe8u, 0x33fcu)) return -1;
          if (!match16(b, 0x6feau, 0x0158u) || !match32(b, 0x6fecu, 0x00c00000u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00c00000u, 0x0158u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0158u & 0x8000u) ? 8u : 0u) | (0x0158u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x6ff0u, 0x33fcu)) return -1;
          if (!match16(b, 0x6ff2u, 0x00a8u) || !match32(b, 0x6ff4u, 0x00c00000u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00c00000u, 0x00a8u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00a8u & 0x8000u) ? 8u : 0u) | (0x00a8u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x6ff8u, 0x33fcu)) return -1;
          if (!match16(b, 0x6ffau, 0x0f06u) || !match32(b, 0x6ffcu, 0x00c00000u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00c00000u, 0x0f06u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0f06u & 0x8000u) ? 8u : 0u) | (0x0f06u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x7000u, 0x33fcu)) return -1;
          if (!match16(b, 0x7002u, 0x87a1u) || !match32(b, 0x7004u, 0x00c00000u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00c00000u, 0x87a1u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x87a1u & 0x8000u) ? 8u : 0u) | (0x87a1u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x7008u, 0x33fcu)) return -1;
          if (!match16(b, 0x700au, 0x0138u) || !match32(b, 0x700cu, 0x00c00000u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00c00000u, 0x0138u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0138u & 0x8000u) ? 8u : 0u) | (0x0138u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x7010u, 0x33fcu)) return -1;
          if (!match16(b, 0x7012u, 0x00a8u) || !match32(b, 0x7014u, 0x00c00000u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00c00000u, 0x00a8u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00a8u & 0x8000u) ? 8u : 0u) | (0x00a8u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x7018u, 0x33fcu)) return -1;
          if (!match16(b, 0x701au, 0x0f07u) || !match32(b, 0x701cu, 0x00c00000u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00c00000u, 0x0f07u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0f07u & 0x8000u) ? 8u : 0u) | (0x0f07u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x7020u, 0x33fcu)) return -1;
          if (!match16(b, 0x7022u, 0x87b1u) || !match32(b, 0x7024u, 0x00c00000u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00c00000u, 0x87b1u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x87b1u & 0x8000u) ? 8u : 0u) | (0x87b1u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x7028u, 0x33fcu)) return -1;
          if (!match16(b, 0x702au, 0x0158u) || !match32(b, 0x702cu, 0x00c00000u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00c00000u, 0x0158u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0158u & 0x8000u) ? 8u : 0u) | (0x0158u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x7030u, 0x33fcu)) return -1;
          if (!match16(b, 0x7032u, 0xd038u) || !match32(b, 0x7034u, 0x00ff0652u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0652u, 0xd038u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xd038u & 0x8000u) ? 8u : 0u) | (0xd038u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x7038u, 0x33fcu)) return -1;
          if (!match16(b, 0x703au, 0x0005u) || !match32(b, 0x703cu, 0x00ff0620u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0620u, 0x0005u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0005u & 0x8000u) ? 8u : 0u) | (0x0005u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x7040u, 0x23fcu)) return -1;
          if (!match32(b, 0x7042u, 0x00000000u) || !match32(b, 0x7046u, 0x00c00000u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00000u, 0x00000000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=007040 addr=00c00000 value=00000000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00000000u & 0x80000000u) ? 8u : 0u) | (0x00000000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x704au, 0x33fcu)) return -1;
          if (!match16(b, 0x704cu, 0x0000u) || !match32(b, 0x704eu, 0x00ff03beu)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff03beu, 0x0000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x7052u, 0x33fcu)) return -1;
          if (!match16(b, 0x7054u, 0x0000u) || !match32(b, 0x7056u, 0x00ff03c0u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff03c0u, 0x0000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x705au, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00705cu:
        {
          if (!match16(b, 0x705cu, 0x4a79u)) return -1;
          if (!match32(b, 0x705eu, 0x00ff03c0u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff03c0u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x7062u, 0x6b00u)) return -1;
          if (!match16(b, 0x7064u, 0xff30u)) return -1;
          c->pc = (c->sr & 8u) ? 0x006f94u : 0x007066u;
          c->cycles += (c->sr & 8u) ? 10u : 8u;
          return 0;
        }
      case 0x007066u:
        {
          if (!match16(b, 0x7066u, 0x33fcu)) return -1;
          if (!match16(b, 0x7068u, 0xd280u) || !match32(b, 0x706au, 0x00ff05cau)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff05cau, 0xd280u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xd280u & 0x8000u) ? 8u : 0u) | (0xd280u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x706eu, 0x23fcu)) return -1;
          if (!match32(b, 0x7070u, 0x50000003u) || !match32(b, 0x7074u, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0x50000003u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=00706e addr=00c00004 value=50000003\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x50000003u & 0x80000000u) ? 8u : 0u) | (0x50000003u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x7078u, 0x303cu)) return -1;
          if (!match16(b, 0x707au, 0x0088u)) return -1;
          c->d[0] = (c->d[0] & 0xffff0000u) | 0x0088u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0088u & 0x8000u) ? 8u : 0u) | (0x0088u == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x707cu, 0x323cu)) return -1;
          if (!match16(b, 0x707eu, 0x0f01u)) return -1;
          c->d[1] = (c->d[1] & 0xffff0000u) | 0x0f01u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0f01u & 0x8000u) ? 8u : 0u) | (0x0f01u == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x7080u, 0x343cu)) return -1;
          if (!match16(b, 0x7082u, 0xa694u)) return -1;
          c->d[2] = (c->d[2] & 0xffff0000u) | 0xa694u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xa694u & 0x8000u) ? 8u : 0u) | (0xa694u == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x7084u, 0x3c39u)) return -1;
          if (!match32(b, 0x7086u, 0x00ff0650u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0650u, &val) != 0) return -3;
            c->d[6] = (c->d[6] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x708au, 0x5346u)) return -1;
          {uint32_t dst=c->d[6]&65535u,src=1u,r=(dst-src)&65535u;
           c->d[6]=(c->d[6]&0xffff0000u)|r;
           uint16_t cy=(dst<src),ov=((dst^src)&(dst^r)&32768u)!=0u;
           c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(cy?17u:0u));}
          c->cycles+=4u;
          if (!match16(b, 0x708cu, 0x363cu)) return -1;
          if (!match16(b, 0x708eu, 0x0090u)) return -1;
          c->d[3] = (c->d[3] & 0xffff0000u) | 0x0090u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0090u & 0x8000u) ? 8u : 0u) | (0x0090u == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x7090u, 0x3e39u)) return -1;
          if (!match32(b, 0x7092u, 0x00ff064eu)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff064eu, &val) != 0) return -3;
            c->d[7] = (c->d[7] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x7096u, 0x5347u)) return -1;
          {uint32_t dst=c->d[7]&65535u,src=1u,r=(dst-src)&65535u;
           c->d[7]=(c->d[7]&0xffff0000u)|r;
           uint16_t cy=(dst<src),ov=((dst^src)&(dst^r)&32768u)!=0u;
           c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(cy?17u:0u));}
          c->cycles+=4u;
          if (!match16(b, 0x7098u, 0x33c0u)) return -1;
          if (!match32(b, 0x709au, 0x00c00000u)) return -1;
          { uint16_t v=(uint16_t)c->d[0];
            if (native_bus_write16((struct t2bus *)b,0x00c00000u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x709eu, 0x33c1u)) return -1;
          if (!match32(b, 0x70a0u, 0x00c00000u)) return -1;
          { uint16_t v=(uint16_t)c->d[1];
            if (native_bus_write16((struct t2bus *)b,0x00c00000u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x70a4u, 0x33c2u)) return -1;
          if (!match32(b, 0x70a6u, 0x00c00000u)) return -1;
          { uint16_t v=(uint16_t)c->d[2];
            if (native_bus_write16((struct t2bus *)b,0x00c00000u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x70aau, 0x33c3u)) return -1;
          if (!match32(b, 0x70acu, 0x00c00000u)) return -1;
          { uint16_t v=(uint16_t)c->d[3];
            if (native_bus_write16((struct t2bus *)b,0x00c00000u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x70b0u, 0x5241u)) return -1;
          { uint16_t dst=(uint16_t)c->d[1],r=(uint16_t)(dst+1u);
            c->d[1]=(c->d[1]&0xffff0000u)|r;
            uint16_t carry=(dst==0xffffu)?1u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u)|(dst==0x7fffu?2u:0u)|carry|(carry?16u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0x70b2u, 0x0642u)) return -1;
          { uint32_t x=c->d[2]&65535u,y=0x0010u,r=(x+y)&65535u;
            c->d[2]=(c->d[2]&0xffff0000u)|r;
            uint16_t carry=(x+y)>65535u,ov=((~(x^y))&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?17u:0u));
          }
          c->cycles+=8u;
          if (!match16(b, 0x70b6u, 0x0643u)) return -1;
          { uint32_t x=c->d[3]&65535u,y=0x0020u,r=(x+y)&65535u;
            c->d[3]=(c->d[3]&0xffff0000u)|r;
            uint16_t carry=(x+y)>65535u,ov=((~(x^y))&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?17u:0u));
          }
          c->cycles+=8u;
          if (!match16(b, 0x70bau, 0x51cfu)) return -1;
          { uint16_t count = (uint16_t)(c->d[7] - 1u);
            c->d[7] = (c->d[7] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x007098u : 0x0070beu;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00708cu:
        {
          if (!match16(b, 0x708cu, 0x363cu)) return -1;
          if (!match16(b, 0x708eu, 0x0090u)) return -1;
          c->d[3] = (c->d[3] & 0xffff0000u) | 0x0090u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0090u & 0x8000u) ? 8u : 0u) | (0x0090u == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x7090u, 0x3e39u)) return -1;
          if (!match32(b, 0x7092u, 0x00ff064eu)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff064eu, &val) != 0) return -3;
            c->d[7] = (c->d[7] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x7096u, 0x5347u)) return -1;
          {uint32_t dst=c->d[7]&65535u,src=1u,r=(dst-src)&65535u;
           c->d[7]=(c->d[7]&0xffff0000u)|r;
           uint16_t cy=(dst<src),ov=((dst^src)&(dst^r)&32768u)!=0u;
           c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(cy?17u:0u));}
          c->cycles+=4u;
          if (!match16(b, 0x7098u, 0x33c0u)) return -1;
          if (!match32(b, 0x709au, 0x00c00000u)) return -1;
          { uint16_t v=(uint16_t)c->d[0];
            if (native_bus_write16((struct t2bus *)b,0x00c00000u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x709eu, 0x33c1u)) return -1;
          if (!match32(b, 0x70a0u, 0x00c00000u)) return -1;
          { uint16_t v=(uint16_t)c->d[1];
            if (native_bus_write16((struct t2bus *)b,0x00c00000u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x70a4u, 0x33c2u)) return -1;
          if (!match32(b, 0x70a6u, 0x00c00000u)) return -1;
          { uint16_t v=(uint16_t)c->d[2];
            if (native_bus_write16((struct t2bus *)b,0x00c00000u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x70aau, 0x33c3u)) return -1;
          if (!match32(b, 0x70acu, 0x00c00000u)) return -1;
          { uint16_t v=(uint16_t)c->d[3];
            if (native_bus_write16((struct t2bus *)b,0x00c00000u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x70b0u, 0x5241u)) return -1;
          { uint16_t dst=(uint16_t)c->d[1],r=(uint16_t)(dst+1u);
            c->d[1]=(c->d[1]&0xffff0000u)|r;
            uint16_t carry=(dst==0xffffu)?1u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u)|(dst==0x7fffu?2u:0u)|carry|(carry?16u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0x70b2u, 0x0642u)) return -1;
          { uint32_t x=c->d[2]&65535u,y=0x0010u,r=(x+y)&65535u;
            c->d[2]=(c->d[2]&0xffff0000u)|r;
            uint16_t carry=(x+y)>65535u,ov=((~(x^y))&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?17u:0u));
          }
          c->cycles+=8u;
          if (!match16(b, 0x70b6u, 0x0643u)) return -1;
          { uint32_t x=c->d[3]&65535u,y=0x0020u,r=(x+y)&65535u;
            c->d[3]=(c->d[3]&0xffff0000u)|r;
            uint16_t carry=(x+y)>65535u,ov=((~(x^y))&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?17u:0u));
          }
          c->cycles+=8u;
          if (!match16(b, 0x70bau, 0x51cfu)) return -1;
          { uint16_t count = (uint16_t)(c->d[7] - 1u);
            c->d[7] = (c->d[7] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x007098u : 0x0070beu;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x007098u:
        {
          if (!match16(b, 0x7098u, 0x33c0u)) return -1;
          if (!match32(b, 0x709au, 0x00c00000u)) return -1;
          { uint16_t v=(uint16_t)c->d[0];
            if (native_bus_write16((struct t2bus *)b,0x00c00000u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x709eu, 0x33c1u)) return -1;
          if (!match32(b, 0x70a0u, 0x00c00000u)) return -1;
          { uint16_t v=(uint16_t)c->d[1];
            if (native_bus_write16((struct t2bus *)b,0x00c00000u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x70a4u, 0x33c2u)) return -1;
          if (!match32(b, 0x70a6u, 0x00c00000u)) return -1;
          { uint16_t v=(uint16_t)c->d[2];
            if (native_bus_write16((struct t2bus *)b,0x00c00000u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x70aau, 0x33c3u)) return -1;
          if (!match32(b, 0x70acu, 0x00c00000u)) return -1;
          { uint16_t v=(uint16_t)c->d[3];
            if (native_bus_write16((struct t2bus *)b,0x00c00000u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x70b0u, 0x5241u)) return -1;
          { uint16_t dst=(uint16_t)c->d[1],r=(uint16_t)(dst+1u);
            c->d[1]=(c->d[1]&0xffff0000u)|r;
            uint16_t carry=(dst==0xffffu)?1u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u)|(dst==0x7fffu?2u:0u)|carry|(carry?16u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0x70b2u, 0x0642u)) return -1;
          { uint32_t x=c->d[2]&65535u,y=0x0010u,r=(x+y)&65535u;
            c->d[2]=(c->d[2]&0xffff0000u)|r;
            uint16_t carry=(x+y)>65535u,ov=((~(x^y))&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?17u:0u));
          }
          c->cycles+=8u;
          if (!match16(b, 0x70b6u, 0x0643u)) return -1;
          { uint32_t x=c->d[3]&65535u,y=0x0020u,r=(x+y)&65535u;
            c->d[3]=(c->d[3]&0xffff0000u)|r;
            uint16_t carry=(x+y)>65535u,ov=((~(x^y))&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?17u:0u));
          }
          c->cycles+=8u;
          if (!match16(b, 0x70bau, 0x51cfu)) return -1;
          { uint16_t count = (uint16_t)(c->d[7] - 1u);
            c->d[7] = (c->d[7] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x007098u : 0x0070beu;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x0070beu:
        {
          if (!match16(b, 0x70beu, 0x0640u)) return -1;
          { uint32_t x=c->d[0]&65535u,y=0x0020u,r=(x+y)&65535u;
            c->d[0]=(c->d[0]&0xffff0000u)|r;
            uint16_t carry=(x+y)>65535u,ov=((~(x^y))&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?17u:0u));
          }
          c->cycles+=8u;
          if (!match16(b, 0x70c2u, 0x343cu)) return -1;
          if (!match16(b, 0x70c4u, 0xa781u)) return -1;
          c->d[2] = (c->d[2] & 0xffff0000u) | 0xa781u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xa781u & 0x8000u) ? 8u : 0u) | (0xa781u == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x70c6u, 0x51ceu)) return -1;
          { uint16_t count = (uint16_t)(c->d[6] - 1u);
            c->d[6] = (c->d[6] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00708cu : 0x0070cau;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x0070cau:
        {
          if (!match16(b, 0x70cau, 0x23fcu)) return -1;
          if (!match32(b, 0x70ccu, 0x00000000u) || !match32(b, 0x70d0u, 0x00c00000u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00000u, 0x00000000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=0070ca addr=00c00000 value=00000000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00000000u & 0x80000000u) ? 8u : 0u) | (0x00000000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x70d4u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x0070d6u:
        {
          if (!match16(b, 0x70d6u, 0x33fcu)) return -1;
          if (!match16(b, 0x70d8u, 0x0003u) || !match32(b, 0x70dau, 0x00ff064eu)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff064eu, 0x0003u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0003u & 0x8000u) ? 8u : 0u) | (0x0003u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x70deu, 0x33fcu)) return -1;
          if (!match16(b, 0x70e0u, 0x0001u) || !match32(b, 0x70e2u, 0x00ff0650u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0650u, 0x0001u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0001u & 0x8000u) ? 8u : 0u) | (0x0001u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x70e6u, 0x6100u)) return -1;
          if (!match16(b, 0x70e8u, 0x000cu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0070eau) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0070f4u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0070eau:
        {
          if (!match16(b, 0x70eau, 0x6100u)) return -1;
          if (!match16(b, 0x70ecu, 0xff70u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0070eeu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00705cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0070eeu:
        {
          if (!match16(b, 0x70eeu, 0x6100u)) return -1;
          if (!match16(b, 0x70f0u, 0x0052u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0070f2u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x007142u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0070f2u:
        {
          if (!match16(b, 0x70f2u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x0070f4u:
        {
          if (!match16(b, 0x70f4u, 0x3039u)) return -1;
          if (!match32(b, 0x70f6u, 0x00ff064eu)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff064eu, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x70fau, 0x0c79u)) return -1;
          { uint16_t v; if(native_bus_read16(b,0x00ff0650u,&v)!=0)return -3;
            uint32_t x=v,y=0x0001u,r=(x-y)&65535u;
            uint16_t carry=x<y;
            uint16_t ov=((x^y)&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?1u:0u));
          }
          c->cycles+=16u;
          if (!match16(b, 0x7102u, 0x6700u)) return -1;
          if (!match16(b, 0x7104u, 0x0004u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x007108u : 0x007106u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x007106u:
        {
          if (!match16(b, 0x7106u, 0xd040u)) return -1;
          { uint32_t x = c->d[0] & 65535u, y = c->d[0] & 65535u, r = (x+y) & 65535u;
            uint16_t flags = (uint16_t)(((r & 0x8000u) ? 8u : 0u) | ((r == 0u) ? 4u : 0u) | (((~(x ^ y) & (r ^ y)) & 0x8000u) ? 2u : 0u) | ((x+y > 65535u) ? 17u : 0u));
            c->d[0] = (c->d[0] & 0xffff0000u) | r;
            c->sr = (uint16_t)((c->sr & 0xffe0u) | flags);
          }
          c->cycles += 4u;
          if (!match16(b, 0x7108u, 0x3200u)) return -1;
          { uint16_t v=(uint16_t)c->d[0]; c->d[1]=(c->d[1] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0x710au, 0xe748u)) return -1;
          { unsigned count=c->d[3]&63u,i;uint32_t v=c->d[0]&65535u;uint16_t carry=0;
            for(i=0;i<count;i++){carry=(v>>15)&1u;v=(v<<1)&65535u;}
            c->d[0]=(c->d[0]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&(count?0xffe0u:0xfff0u))|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)|(count&&carry?17u:0u)); c->cycles+=6u+2u*count; }
          if (!match16(b, 0x710cu, 0x0640u)) return -1;
          { uint32_t x=c->d[0]&65535u,y=0xd000u,r=(x+y)&65535u;
            c->d[0]=(c->d[0]&0xffff0000u)|r;
            uint16_t carry=(x+y)>65535u,ov=((~(x^y))&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?17u:0u));
          }
          c->cycles+=8u;
          if (!match16(b, 0x7110u, 0x33c0u)) return -1;
          if (!match32(b, 0x7112u, 0x00ff0652u)) return -1;
          { uint16_t v=(uint16_t)c->d[0];
            if (native_bus_write16((struct t2bus *)b,0x00ff0652u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x7116u, 0x5541u)) return -1;
          {uint32_t dst=c->d[1]&65535u,src=2u,r=(dst-src)&65535u;
           c->d[1]=(c->d[1]&0xffff0000u)|r;
           uint16_t cy=(dst<src),ov=((dst^src)&(dst^r)&32768u)!=0u;
           c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(cy?17u:0u));}
          c->cycles+=4u;
          if (!match16(b, 0x7118u, 0x33c1u)) return -1;
          if (!match32(b, 0x711au, 0x00ff0620u)) return -1;
          { uint16_t v=(uint16_t)c->d[1];
            if (native_bus_write16((struct t2bus *)b,0x00ff0620u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x711eu, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x007108u:
        {
          if (!match16(b, 0x7108u, 0x3200u)) return -1;
          { uint16_t v=(uint16_t)c->d[0]; c->d[1]=(c->d[1] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0x710au, 0xe748u)) return -1;
          { unsigned count=c->d[3]&63u,i;uint32_t v=c->d[0]&65535u;uint16_t carry=0;
            for(i=0;i<count;i++){carry=(v>>15)&1u;v=(v<<1)&65535u;}
            c->d[0]=(c->d[0]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&(count?0xffe0u:0xfff0u))|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)|(count&&carry?17u:0u)); c->cycles+=6u+2u*count; }
          if (!match16(b, 0x710cu, 0x0640u)) return -1;
          { uint32_t x=c->d[0]&65535u,y=0xd000u,r=(x+y)&65535u;
            c->d[0]=(c->d[0]&0xffff0000u)|r;
            uint16_t carry=(x+y)>65535u,ov=((~(x^y))&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?17u:0u));
          }
          c->cycles+=8u;
          if (!match16(b, 0x7110u, 0x33c0u)) return -1;
          if (!match32(b, 0x7112u, 0x00ff0652u)) return -1;
          { uint16_t v=(uint16_t)c->d[0];
            if (native_bus_write16((struct t2bus *)b,0x00ff0652u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x7116u, 0x5541u)) return -1;
          {uint32_t dst=c->d[1]&65535u,src=2u,r=(dst-src)&65535u;
           c->d[1]=(c->d[1]&0xffff0000u)|r;
           uint16_t cy=(dst<src),ov=((dst^src)&(dst^r)&32768u)!=0u;
           c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(cy?17u:0u));}
          c->cycles+=4u;
          if (!match16(b, 0x7118u, 0x33c1u)) return -1;
          if (!match32(b, 0x711au, 0x00ff0620u)) return -1;
          { uint16_t v=(uint16_t)c->d[1];
            if (native_bus_write16((struct t2bus *)b,0x00ff0620u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x711eu, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x007120u:
        {
          if (!match16(b, 0x7120u, 0x303cu)) return -1;
          if (!match16(b, 0x7122u, 0x0003u)) return -1;
          c->d[0] = (c->d[0] & 0xffff0000u) | 0x0003u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0003u & 0x8000u) ? 8u : 0u) | (0x0003u == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x7124u, 0x6100u)) return -1;
          if (!match16(b, 0x7126u, 0x16a2u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x007128u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0087c8u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x007128u:
        {
          if (!match16(b, 0x7128u, 0x0c79u)) return -1;
          { uint16_t v; if(native_bus_read16(b,0x00ff03c4u,&v)!=0)return -3;
            uint32_t x=v,y=0x000cu,r=(x-y)&65535u;
            uint16_t carry=x<y;
            uint16_t ov=((x^y)&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?1u:0u));
          }
          c->cycles+=16u;
          if (!match16(b, 0x7130u, 0x6700u)) return -1;
          if (!match16(b, 0x7132u, 0x000au)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x00713cu : 0x007134u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x007134u:
        {
          if (!match16(b, 0x7134u, 0x303cu)) return -1;
          if (!match16(b, 0x7136u, 0x0002u)) return -1;
          c->d[0] = (c->d[0] & 0xffff0000u) | 0x0002u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0002u & 0x8000u) ? 8u : 0u) | (0x0002u == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x7138u, 0x6100u)) return -1;
          if (!match16(b, 0x713au, 0x168eu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00713cu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0087c8u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00713cu:
        {
          if (!match16(b, 0x713cu, 0x7200u)) return -1;
          c->d[1] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x713eu, 0x6000u)) return -1;
          if (!match16(b, 0x7140u, 0x001cu)) return -1;
          c->pc = (1) ? 0x00715cu : 0x007142u;
          c->cycles += (1) ? 10u : 8u;
          return 0;
        }
      case 0x007142u:
        {
          if (!match16(b, 0x7142u, 0x23fcu)) return -1;
          if (!match32(b, 0x7144u, 0x52800003u) || !match32(b, 0x7148u, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0x52800003u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=007142 addr=00c00004 value=52800003\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x52800003u & 0x80000000u) ? 8u : 0u) | (0x52800003u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x714cu, 0x7200u)) return -1;
          c->d[1] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x714eu, 0x3e3cu)) return -1;
          if (!match16(b, 0x7150u, 0x027fu)) return -1;
          c->d[7] = (c->d[7] & 0xffff0000u) | 0x027fu;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x027fu & 0x8000u) ? 8u : 0u) | (0x027fu == 0u ? 4u : 0u));
          c->cycles += 8u;
          c->pc = 0x007152u;
          return 0;
        }
      case 0x00715cu:
        {
          if (!match16(b, 0x715cu, 0x23fcu)) return -1;
          if (!match32(b, 0x715eu, 0x70200003u) || !match32(b, 0x7162u, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0x70200003u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=00715c addr=00c00004 value=70200003\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x70200003u & 0x80000000u) ? 8u : 0u) | (0x70200003u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x7166u, 0x3e3cu)) return -1;
          if (!match16(b, 0x7168u, 0x027fu)) return -1;
          c->d[7] = (c->d[7] & 0xffff0000u) | 0x027fu;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x027fu & 0x8000u) ? 8u : 0u) | (0x027fu == 0u ? 4u : 0u));
          c->cycles += 8u;
          c->pc = 0x00716au;
          return 0;
        }
      case 0x007176u:
        {
          if (!match16(b, 0x7176u, 0x33fcu)) return -1;
          if (!match16(b, 0x7178u, 0x0000u) || !match32(b, 0x717au, 0x00ff062cu)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff062cu, 0x0000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x717eu, 0x4df9u)) return -1;
          if (!match32(b, 0x7180u, 0x00ff3775u)) return -1;
          c->a[6] = 0x00ff3775u;
          c->cycles += 12u;
          if (!match16(b, 0x7184u, 0x4a39u)) return -1;
          if (!match32(b, 0x7186u, 0x00ff274bu)) return -1;
          { uint8_t value;
            if (native_bus_read8(b, 0x00ff274bu, &value) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((value & 0x80u) ? 8u : 0u) | (value == 0u ? 4u : 0u));
          }
          c->cycles += 12u;
          if (!match16(b, 0x718au, 0x6700u)) return -1;
          if (!match16(b, 0x718cu, 0x00e2u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x00726eu : 0x00718eu;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00726eu:
        {
          if (!match16(b, 0x726eu, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x007364u:
        {
          if (!match16(b, 0x7364u, 0x7e00u)) return -1;
          c->d[7] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[7] & 0x80000000u) ? 8u : 0u) | (c->d[7] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x7366u, 0x1e39u)) return -1;
          if (!match32(b,0x7368u,0x00ff2749u)) return -1;
          if (native_bus_read8(b,0x00ff2749u,&byte_value)!=0) return -3;
          c->d[7]=(c->d[7]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0x736cu, 0x5347u)) return -1;
          {uint32_t dst=c->d[7]&65535u,src=1u,r=(dst-src)&65535u;
           c->d[7]=(c->d[7]&0xffff0000u)|r;
           uint16_t cy=(dst<src),ov=((dst^src)&(dst^r)&32768u)!=0u;
           c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(cy?17u:0u));}
          c->cycles+=4u;
          if (!match16(b, 0x736eu, 0x6b00u)) return -1;
          if (!match16(b, 0x7370u, 0x00f6u)) return -1;
          c->pc = (c->sr & 8u) ? 0x007466u : 0x007372u;
          c->cycles += (c->sr & 8u) ? 10u : 8u;
          return 0;
        }
      case 0x007372u:
        {
          if (!match16(b, 0x7372u, 0x4df9u)) return -1;
          if (!match32(b, 0x7374u, 0x00ff2bbbu)) return -1;
          c->a[6] = 0x00ff2bbbu;
          c->cycles += 12u;
          c->pc = 0x007378u;
          return 0;
        }
      case 0x007466u:
        {
          if (!match16(b, 0x7466u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00752eu:
        {
          if (!match16(b, 0x752eu, 0x41f9u)) return -1;
          if (!match32(b, 0x7530u, 0x00ff8e52u)) return -1;
          c->a[0] = 0x00ff8e52u;
          c->cycles += 12u;
          if (!match16(b, 0x7534u, 0x3e3cu)) return -1;
          if (!match16(b, 0x7536u, 0x03ffu)) return -1;
          c->d[7] = (c->d[7] & 0xffff0000u) | 0x03ffu;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x03ffu & 0x8000u) ? 8u : 0u) | (0x03ffu == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x7538u, 0x70ffu)) return -1;
          c->d[0] = (uint32_t)(int32_t)(-1);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x753au, 0x20c0u)) return -1;
          {uint32_t v=c->d[0];
           if(native_bus_write32((struct t2bus *)b,c->a[0],v)!=0)return -3;
           c->a[0]=(c->a[0]+4u)&0xffffffu;
           c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=12u;
          if (!match16(b, 0x753cu, 0x51cfu)) return -1;
          { uint16_t count = (uint16_t)(c->d[7] - 1u);
            c->d[7] = (c->d[7] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00753au : 0x007540u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00753au:
        {
          if (!match16(b, 0x753au, 0x20c0u)) return -1;
          {uint32_t v=c->d[0];
           if(native_bus_write32((struct t2bus *)b,c->a[0],v)!=0)return -3;
           c->a[0]=(c->a[0]+4u)&0xffffffu;
           c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=12u;
          if (!match16(b, 0x753cu, 0x51cfu)) return -1;
          { uint16_t count = (uint16_t)(c->d[7] - 1u);
            c->d[7] = (c->d[7] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00753au : 0x007540u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x007540u:
        {
          if (!match16(b, 0x7540u, 0x43f9u)) return -1;
          if (!match32(b, 0x7542u, 0x00ff9e54u)) return -1;
          c->a[1] = 0x00ff9e54u;
          c->cycles += 12u;
          if (!match16(b, 0x7546u, 0x45f9u)) return -1;
          if (!match32(b, 0x7548u, 0x00ff9ed4u)) return -1;
          c->a[2] = 0x00ff9ed4u;
          c->cycles += 12u;
          if (!match16(b, 0x754cu, 0x47f9u)) return -1;
          if (!match32(b, 0x754eu, 0x00ff9f54u)) return -1;
          c->a[3] = 0x00ff9f54u;
          c->cycles += 12u;
          if (!match16(b, 0x7552u, 0x70ffu)) return -1;
          c->d[0] = (uint32_t)(int32_t)(-1);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x7554u, 0x7201u)) return -1;
          c->d[1] = (uint32_t)(int32_t)(1);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x7556u, 0x343cu)) return -1;
          if (!match16(b, 0x7558u, 0x1000u)) return -1;
          c->d[2] = (c->d[2] & 0xffff0000u) | 0x1000u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x1000u & 0x8000u) ? 8u : 0u) | (0x1000u == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x755au, 0x3e39u)) return -1;
          if (!match32(b, 0x755cu, 0x00ff061au)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff061au, &val) != 0) return -3;
            c->d[7] = (c->d[7] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x7560u, 0x12c0u)) return -1;
          {uint8_t v=(uint8_t)c->d[0];if(native_bus_write8((struct t2bus *)b,c->a[1],v))return -3;c->a[1]=(c->a[1]+1u)&0xffffffu;c->sr=(c->sr&0xfff0u)|((v&128u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=8u;
          if (!match16(b, 0x7562u, 0x14c1u)) return -1;
          {uint8_t v=(uint8_t)c->d[1];if(native_bus_write8((struct t2bus *)b,c->a[2],v))return -3;c->a[2]=(c->a[2]+1u)&0xffffffu;c->sr=(c->sr&0xfff0u)|((v&128u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=8u;
          if (!match16(b, 0x7564u, 0x36c2u)) return -1;
          { uint16_t v=(uint16_t)c->d[2];
            if(native_bus_write16((struct t2bus *)b,c->a[3],v)!=0)return -3;
            c->a[3]=(c->a[3]+2u)&0xffffffu;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u));
          }
          c->cycles+=8u;
          if (!match16(b, 0x7566u, 0x5240u)) return -1;
          { uint16_t dst=(uint16_t)c->d[0],r=(uint16_t)(dst+1u);
            c->d[0]=(c->d[0]&0xffff0000u)|r;
            uint16_t carry=(dst==0xffffu)?1u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u)|(dst==0x7fffu?2u:0u)|carry|(carry?16u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0x7568u, 0x5241u)) return -1;
          { uint16_t dst=(uint16_t)c->d[1],r=(uint16_t)(dst+1u);
            c->d[1]=(c->d[1]&0xffff0000u)|r;
            uint16_t carry=(dst==0xffffu)?1u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u)|(dst==0x7fffu?2u:0u)|carry|(carry?16u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0x756au, 0x51cfu)) return -1;
          { uint16_t count = (uint16_t)(c->d[7] - 1u);
            c->d[7] = (c->d[7] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x007560u : 0x00756eu;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x007560u:
        {
          if (!match16(b, 0x7560u, 0x12c0u)) return -1;
          {uint8_t v=(uint8_t)c->d[0];if(native_bus_write8((struct t2bus *)b,c->a[1],v))return -3;c->a[1]=(c->a[1]+1u)&0xffffffu;c->sr=(c->sr&0xfff0u)|((v&128u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=8u;
          if (!match16(b, 0x7562u, 0x14c1u)) return -1;
          {uint8_t v=(uint8_t)c->d[1];if(native_bus_write8((struct t2bus *)b,c->a[2],v))return -3;c->a[2]=(c->a[2]+1u)&0xffffffu;c->sr=(c->sr&0xfff0u)|((v&128u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=8u;
          if (!match16(b, 0x7564u, 0x36c2u)) return -1;
          { uint16_t v=(uint16_t)c->d[2];
            if(native_bus_write16((struct t2bus *)b,c->a[3],v)!=0)return -3;
            c->a[3]=(c->a[3]+2u)&0xffffffu;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u));
          }
          c->cycles+=8u;
          if (!match16(b, 0x7566u, 0x5240u)) return -1;
          { uint16_t dst=(uint16_t)c->d[0],r=(uint16_t)(dst+1u);
            c->d[0]=(c->d[0]&0xffff0000u)|r;
            uint16_t carry=(dst==0xffffu)?1u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u)|(dst==0x7fffu?2u:0u)|carry|(carry?16u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0x7568u, 0x5241u)) return -1;
          { uint16_t dst=(uint16_t)c->d[1],r=(uint16_t)(dst+1u);
            c->d[1]=(c->d[1]&0xffff0000u)|r;
            uint16_t carry=(dst==0xffffu)?1u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u)|(dst==0x7fffu?2u:0u)|carry|(carry?16u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0x756au, 0x51cfu)) return -1;
          { uint16_t count = (uint16_t)(c->d[7] - 1u);
            c->d[7] = (c->d[7] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x007560u : 0x00756eu;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00756eu:
        {
          if (!match16(b, 0x756eu, 0x13f9u)) return -1;
          {uint8_t v;if(native_bus_read8(b,0xff061bu,&v)||native_bus_write8((struct t2bus *)b,0xff9e54u,v))return -3;c->sr=(c->sr&0xfff0u)|((v&128u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=28u;
          c->pc = 0x007578u;
          return 0;
        }
      case 0x007c3eu:
        {
          if (!match16(b, 0x7c3eu, 0x7e00u)) return -1;
          c->d[7] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[7] & 0x80000000u) ? 8u : 0u) | (c->d[7] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x7c40u, 0x1e39u)) return -1;
          if (!match32(b,0x7c42u,0x00ff274fu)) return -1;
          if (native_bus_read8(b,0x00ff274fu,&byte_value)!=0) return -3;
          c->d[7]=(c->d[7]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0x7c46u, 0x5347u)) return -1;
          {uint32_t dst=c->d[7]&65535u,src=1u,r=(dst-src)&65535u;
           c->d[7]=(c->d[7]&0xffff0000u)|r;
           uint16_t cy=(dst<src),ov=((dst^src)&(dst^r)&32768u)!=0u;
           c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(cy?17u:0u));}
          c->cycles+=4u;
          if (!match16(b, 0x7c48u, 0x6b00u)) return -1;
          if (!match16(b, 0x7c4au, 0x0100u)) return -1;
          c->pc = (c->sr & 8u) ? 0x007d4au : 0x007c4cu;
          c->cycles += (c->sr & 8u) ? 10u : 8u;
          return 0;
        }
      case 0x007c4cu:
        {
          if (!match16(b, 0x7c4cu, 0x3039u)) return -1;
          if (!match32(b, 0x7c4eu, 0x00ff0168u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0168u, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x7c52u, 0xe440u)) return -1;
          {uint16_t x=(uint16_t)c->d[0],r=(uint16_t)((int16_t)x>>2),carry=(x>>1)&1u;c->d[0]=(c->d[0]&0xffff0000u)|r;c->sr=(c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(carry?17u:0u);}
          c->cycles+=10u;
          if (!match16(b, 0x7c54u, 0x0240u)) return -1;
          if (!match16(b, 0x7c56u, 0xfffeu)) return -1;
          { uint16_t v=(uint16_t)c->d[0] & 0xfffeu; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x7c58u, 0x33c0u)) return -1;
          if (!match32(b, 0x7c5au, 0x00ff5238u)) return -1;
          { uint16_t v=(uint16_t)c->d[0];
            if (native_bus_write16((struct t2bus *)b,0x00ff5238u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x7c5eu, 0x3039u)) return -1;
          if (!match32(b, 0x7c60u, 0x00ff016au)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff016au, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          c->pc = 0x007c64u;
          return 0;
        }
      case 0x007d4au:
        {
          if (!match16(b, 0x7d4au, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x008240u:
        {
          if (!match16(b, 0x8240u, 0x3039u)) return -1;
          if (!match32(b, 0x8242u, 0x00ff03c4u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff03c4u, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x8246u, 0xe248u)) return -1;
          { uint16_t old=(uint16_t)c->d[0],r=(uint16_t)(old>>1);
            uint16_t carry=(old>>0)&1u;
            c->d[0]=(c->d[0]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xffe0u)|(r==0u?4u:0u)|(carry?17u:0u));
            c->cycles+=8u;
          }
          if (!match16(b, 0x8248u, 0xc0fcu)) return -1;
          if(!match16(b,0x824au,0x0028u))return -1;
          {uint32_t r=(c->d[0]&65535u)*0x0028u; c->d[0]=r; c->sr=(c->sr&0xfff0u)|((r&0x80000000u)?8u:0u)|(r==0u?4u:0u);}
          c->cycles+=70u;
          if (!match16(b, 0x824cu, 0x41f9u)) return -1;
          if (!match32(b, 0x824eu, 0x0006ca74u)) return -1;
          c->a[0] = 0x0006ca74u;
          c->cycles += 12u;
          if (!match16(b, 0x8252u, 0xd0c0u)) return -1;
          c->a[0]=(c->a[0]+(int16_t)(c->d[0]&65535u))&0xffffffu;
          c->cycles+=8u;
          if (!match16(b, 0x8254u, 0x23d8u)) return -1;
          { uint32_t v; if(native_bus_read32(b,c->a[0],&v)!=0)return -3;
            c->a[0]=(c->a[0]+4u)&0xffffffu;
            if(native_bus_write32((struct t2bus *)b,0x00ff065au,v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=28u;
          if (!match16(b, 0x825au, 0x23d8u)) return -1;
          { uint32_t v; if(native_bus_read32(b,c->a[0],&v)!=0)return -3;
            c->a[0]=(c->a[0]+4u)&0xffffffu;
            if(native_bus_write32((struct t2bus *)b,0x00ff065eu,v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=28u;
          if (!match16(b, 0x8260u, 0x23d8u)) return -1;
          { uint32_t v; if(native_bus_read32(b,c->a[0],&v)!=0)return -3;
            c->a[0]=(c->a[0]+4u)&0xffffffu;
            if(native_bus_write32((struct t2bus *)b,0x00ff0662u,v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=28u;
          if (!match16(b, 0x8266u, 0x23d8u)) return -1;
          { uint32_t v; if(native_bus_read32(b,c->a[0],&v)!=0)return -3;
            c->a[0]=(c->a[0]+4u)&0xffffffu;
            if(native_bus_write32((struct t2bus *)b,0x00ff0666u,v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=28u;
          if (!match16(b, 0x826cu, 0x23d8u)) return -1;
          { uint32_t v; if(native_bus_read32(b,c->a[0],&v)!=0)return -3;
            c->a[0]=(c->a[0]+4u)&0xffffffu;
            if(native_bus_write32((struct t2bus *)b,0x00ff066au,v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=28u;
          if (!match16(b, 0x8272u, 0x23d8u)) return -1;
          { uint32_t v; if(native_bus_read32(b,c->a[0],&v)!=0)return -3;
            c->a[0]=(c->a[0]+4u)&0xffffffu;
            if(native_bus_write32((struct t2bus *)b,0x00ff066eu,v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=28u;
          if (!match16(b, 0x8278u, 0x23d8u)) return -1;
          { uint32_t v; if(native_bus_read32(b,c->a[0],&v)!=0)return -3;
            c->a[0]=(c->a[0]+4u)&0xffffffu;
            if(native_bus_write32((struct t2bus *)b,0x00ff0672u,v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=28u;
          if (!match16(b, 0x827eu, 0x23d8u)) return -1;
          { uint32_t v; if(native_bus_read32(b,c->a[0],&v)!=0)return -3;
            c->a[0]=(c->a[0]+4u)&0xffffffu;
            if(native_bus_write32((struct t2bus *)b,0x00ff0676u,v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=28u;
          if (!match16(b, 0x8284u, 0x23d8u)) return -1;
          { uint32_t v; if(native_bus_read32(b,c->a[0],&v)!=0)return -3;
            c->a[0]=(c->a[0]+4u)&0xffffffu;
            if(native_bus_write32((struct t2bus *)b,0x00ff067au,v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=28u;
          if (!match16(b, 0x828au, 0x23d8u)) return -1;
          { uint32_t v; if(native_bus_read32(b,c->a[0],&v)!=0)return -3;
            c->a[0]=(c->a[0]+4u)&0xffffffu;
            if(native_bus_write32((struct t2bus *)b,0x00ff067eu,v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=28u;
          if (!match16(b, 0x8290u, 0x2079u)) return -1;
          if (!match32(b, 0x8292u, 0x00ff0662u)) return -1;
          if (native_bus_read32(b, 0x00ff0662u, &c->a[0]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0x8296u, 0x43f9u)) return -1;
          if (!match32(b, 0x8298u, 0x00ff0690u)) return -1;
          c->a[1] = 0x00ff0690u;
          c->cycles += 12u;
          if (!match16(b, 0x829cu, 0x6100u)) return -1;
          if (!match16(b, 0x829eu, 0x5cc0u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0082a0u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00df5eu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0082a0u:
        {
          if (!match16(b, 0x82a0u, 0x0c79u)) return -1;
          { uint16_t v; if(native_bus_read16(b,0x00ff03c4u,&v)!=0)return -3;
            uint32_t x=v,y=0x0004u,r=(x-y)&65535u;
            uint16_t carry=x<y;
            uint16_t ov=((x^y)&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?1u:0u));
          }
          c->cycles+=16u;
          if (!match16(b, 0x82a8u, 0x6700u)) return -1;
          if (!match16(b, 0x82aau, 0x0024u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x0082ceu : 0x0082acu;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x0082acu:
        {
          if (!match16(b, 0x82acu, 0x0c79u)) return -1;
          { uint16_t v; if(native_bus_read16(b,0x00ff03c4u,&v)!=0)return -3;
            uint32_t x=v,y=0x000cu,r=(x-y)&65535u;
            uint16_t carry=x<y;
            uint16_t ov=((x^y)&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?1u:0u));
          }
          c->cycles+=16u;
          c->pc = 0x0082b4u;
          return 0;
        }
      case 0x0082ceu:
        {
          if (!match16(b, 0x82ceu, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x008506u:
        {
          if (!match16(b, 0x8506u, 0x4a79u)) return -1;
          if (!match32(b, 0x8508u, 0x00ff05e2u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff05e2u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x850cu, 0x6600u)) return -1;
          if (!match16(b, 0x850eu, 0x00c8u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x0085d6u : 0x008510u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x008510u:
        {
          if (!match16(b, 0x8510u, 0x4a79u)) return -1;
          if (!match32(b, 0x8512u, 0x00ff0222u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff0222u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x8516u, 0x6600u)) return -1;
          if (!match16(b, 0x8518u, 0x00beu)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x0085d6u : 0x00851au;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00851au:
        {
          if (!match16(b, 0x851au, 0x4a79u)) return -1;
          if (!match32(b, 0x851cu, 0x00ff05e4u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff05e4u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x8520u, 0x6700u)) return -1;
          if (!match16(b, 0x8522u, 0x0034u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x008556u : 0x008524u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x0085d6u:
        {
          if (!match16(b, 0x85d6u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x0085d8u:
        {
          if (!match16(b, 0x85d8u, 0x48e7u)) return -1;
          if (!match16(b, 0x85dau, 0xc0c2u)) return -1;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->a[6]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->a[1]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->a[0]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[1]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[0]) != 0) return -3;
          c->cycles += 48u;
          if (!match16(b, 0x85dcu, 0x2c79u)) return -1;
          if (!match32(b, 0x85deu, 0x00ff01c8u)) return -1;
          if (native_bus_read32(b, 0x00ff01c8u, &c->a[6]) != 0) return -3;
          c->cycles += 20u;
          c->pc = 0x0085e2u;
          return 0;
        }
      case 0x008712u:
        {
          if (!match16(b, 0x8712u, 0x41f9u)) return -1;
          if (!match32(b, 0x8714u, 0x0006c69au)) return -1;
          c->a[0] = 0x0006c69au;
          c->cycles += 12u;
          if (!match16(b, 0x8718u, 0x2028u)) return -1;
          if(!match16(b,0x871au,0x0004u))return -1;
          {uint32_t v,addr=(c->a[0]+(int16_t)0x0004u)&0xffffffu; if(native_bus_read32(b,addr,&v))return -3; c->d[0]=v; c->sr=(c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=16u;
          if (!match16(b, 0x871cu, 0x2279u)) return -1;
          if (!match32(b, 0x871eu, 0x00ff019au)) return -1;
          if (native_bus_read32(b, 0x00ff019au, &c->a[1]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0x8722u, 0x23c9u)) return -1;
          if (!match32(b, 0x8724u, 0x00ff01a2u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff01a2u, c->a[1]) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->a[1] & 0x80000000u) ? 8u : 0u) | (c->a[1] == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x8728u, 0xd1b9u)) return -1;
          {uint32_t x,y=c->d[0],r;uint64_t wide;if(native_bus_read32(b,0xff019au,&x))return -3;wide=(uint64_t)x+y;r=(uint32_t)wide;if(native_bus_write32((struct t2bus *)b,0xff019au,r))return -3;c->sr=(c->sr&0xffe0u)|((r&0x80000000u)?8u:0u)|(r==0u?4u:0u)|((~(x^y)&(x^r)&0x80000000u)?2u:0u)|((wide>>32)?17u:0u);}
          c->cycles+=24u;
          if (!match16(b, 0x872eu, 0x6100u)) return -1;
          if (!match16(b, 0x8730u, 0x582eu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x008732u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00df5eu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x008732u:
        {
          if (!match16(b, 0x8732u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x8734u, 0x7200u)) return -1;
          c->d[1] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x8736u, 0x6100u)) return -1;
          if (!match16(b, 0x8738u, 0x0004u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00873au) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00873cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00873au:
        {
          if (!match16(b, 0x873au, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00873cu:
        {
          if (!match16(b, 0x873cu, 0x2c79u)) return -1;
          if (!match32(b, 0x873eu, 0x00ff01c8u)) return -1;
          if (native_bus_read32(b, 0x00ff01c8u, &c->a[6]) != 0) return -3;
          c->cycles += 20u;
          c->pc = 0x008742u;
          return 0;
        }
      case 0x0087c8u:
        {
          if (!match16(b, 0x87c8u, 0x2c79u)) return -1;
          if (!match32(b, 0x87cau, 0x00ff01c8u)) return -1;
          if (native_bus_read32(b, 0x00ff01c8u, &c->a[6]) != 0) return -3;
          c->cycles += 20u;
          c->pc = 0x0087ceu;
          return 0;
        }
      case 0x0088c4u:
        {
          if (!match16(b, 0x88c4u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x88c6u, 0x1018u)) return -1;
          if (native_bus_read8(b, c->a[0], &byte_value) != 0) return -3;
          c->a[0] = (c->a[0] + 1u) & 0xffffffu;
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 128u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x88c8u, 0x6700u)) return -1;
          if (!match16(b, 0x88cau, 0x0008u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x0088d2u : 0x0088ccu;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x0088c6u:
        {
          if (!match16(b, 0x88c6u, 0x1018u)) return -1;
          if (native_bus_read8(b, c->a[0], &byte_value) != 0) return -3;
          c->a[0] = (c->a[0] + 1u) & 0xffffffu;
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 128u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x88c8u, 0x6700u)) return -1;
          if (!match16(b, 0x88cau, 0x0008u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x0088d2u : 0x0088ccu;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x0088ccu:
        {
          if (!match16(b, 0x88ccu, 0x6100u)) return -1;
          if (!match16(b, 0x88ceu, 0xfd0au)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0088d0u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0085d8u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0088d0u:
        {
          if (!match16(b, 0x88d0u, 0x60f4u)) return -1;
          c->pc = (1) ? 0x0088c6u : 0x0088d2u;
          c->cycles += (1) ? 10u : 8u;
          return 0;
        }
      case 0x0088d2u:
        {
          if (!match16(b, 0x88d2u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x0088d4u:
        {
          if (!match16(b, 0x88d4u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x88d6u, 0x7201u)) return -1;
          c->d[1] = (uint32_t)(int32_t)(1);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x88d8u, 0x6100u)) return -1;
          if (!match16(b, 0x88dau, 0xfe62u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0088dcu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00873cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0088dcu:
        {
          if (!match16(b, 0x88dcu, 0x41f9u)) return -1;
          if (!match32(b, 0x88deu, 0x00008960u)) return -1;
          c->a[0] = 0x00008960u;
          c->cycles += 12u;
          if (!match16(b, 0x88e2u, 0x61e0u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0088e4u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0088c4u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0088e4u:
        {
          if (!match16(b, 0x88e4u, 0x6100u)) return -1;
          if (!match16(b, 0x88e6u, 0x010cu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0088e8u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0089f2u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0088e8u:
        {
          if (!match16(b, 0x88e8u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x88eau, 0x7200u)) return -1;
          c->d[1] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x88ecu, 0x6100u)) return -1;
          if (!match16(b, 0x88eeu, 0xfe4eu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0088f0u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00873cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0088f0u:
        {
          if (!match16(b, 0x88f0u, 0x41f9u)) return -1;
          if (!match32(b, 0x88f2u, 0x00008953u)) return -1;
          c->a[0] = 0x00008953u;
          c->cycles += 12u;
          if (!match16(b, 0x88f6u, 0x61ccu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0088f8u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0088c4u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0088f8u:
        {
          if (!match16(b, 0x88f8u, 0x6100u)) return -1;
          if (!match16(b, 0x88fau, 0x00bau)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0088fcu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0089b4u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0088fcu:
        {
          if (!match16(b, 0x88fcu, 0x0c79u)) return -1;
          { uint16_t v; if(native_bus_read16(b,0x00ff03c4u,&v)!=0)return -3;
            uint32_t x=v,y=0x000cu,r=(x-y)&65535u;
            uint16_t carry=x<y;
            uint16_t ov=((x^y)&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?1u:0u));
          }
          c->cycles+=16u;
          if (!match16(b, 0x8904u, 0x6600u)) return -1;
          if (!match16(b, 0x8906u, 0x0028u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x00892eu : 0x008908u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x008908u:
        {
          if (!match16(b, 0x8908u, 0x4a79u)) return -1;
          if (!match32(b, 0x890au, 0x00ff5248u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff5248u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x890eu, 0x6700u)) return -1;
          if (!match16(b, 0x8910u, 0x000au)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x00891au : 0x008912u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x008912u:
        {
          if (!match16(b, 0x8912u, 0x6100u)) return -1;
          if (!match16(b, 0x8914u, 0x010cu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x008916u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x008a20u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x008916u:
        {
          if (!match16(b, 0x8916u, 0x6000u)) return -1;
          if (!match16(b, 0x8918u, 0x0016u)) return -1;
          c->pc = (1) ? 0x00892eu : 0x00891au;
          c->cycles += (1) ? 10u : 8u;
          return 0;
        }
      case 0x00891au:
        {
          if (!match16(b, 0x891au, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x891cu, 0x7202u)) return -1;
          c->d[1] = (uint32_t)(int32_t)(2);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x891eu, 0x6100u)) return -1;
          if (!match16(b, 0x8920u, 0xfe1cu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x008922u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00873cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x008922u:
        {
          if (!match16(b, 0x8922u, 0x41f9u)) return -1;
          if (!match32(b, 0x8924u, 0x00008946u)) return -1;
          c->a[0] = 0x00008946u;
          c->cycles += 12u;
          if (!match16(b, 0x8928u, 0x619au)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00892au) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0088c4u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00892au:
        {
          if (!match16(b, 0x892au, 0x6100u)) return -1;
          if (!match16(b, 0x892cu, 0x004au)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00892eu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x008976u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00892eu:
        {
          if (!match16(b, 0x892eu, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x008976u:
        {
          if (!match16(b, 0x8976u, 0x7008u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(8);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x8978u, 0x7202u)) return -1;
          c->d[1] = (uint32_t)(int32_t)(2);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x897au, 0x6100u)) return -1;
          if (!match16(b, 0x897cu, 0xfdc0u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00897eu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00873cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00897eu:
        {
          if (!match16(b, 0x897eu, 0x1039u)) return -1;
          if (!match32(b, 0x8980u, 0x00ff2ae6u)) return -1;
          if (native_bus_read8(b, 0x00ff2ae6u, &byte_value) != 0) return -3;
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 0x80u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 16u;
          if (!match16(b, 0x8984u, 0xe148u)) return -1;
          { unsigned count=c->d[0]&63u,i;uint32_t v=c->d[0]&65535u;uint16_t carry=0;
            for(i=0;i<count;i++){carry=(v>>15)&1u;v=(v<<1)&65535u;}
            c->d[0]=(c->d[0]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&(count?0xffe0u:0xfff0u))|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)|(count&&carry?17u:0u)); c->cycles+=6u+2u*count; }
          if (!match16(b, 0x8986u, 0x1039u)) return -1;
          if (!match32(b, 0x8988u, 0x00ff2ae5u)) return -1;
          if (native_bus_read8(b, 0x00ff2ae5u, &byte_value) != 0) return -3;
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 0x80u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 16u;
          if (!match16(b, 0x898cu, 0xc0fcu)) return -1;
          if(!match16(b,0x898eu,0x0064u))return -1;
          {uint32_t r=(c->d[0]&65535u)*0x0064u; c->d[0]=r; c->sr=(c->sr&0xfff0u)|((r&0x80000000u)?8u:0u)|(r==0u?4u:0u);}
          c->cycles+=70u;
          c->pc = 0x008990u;
          return 0;
        }
      case 0x0089b4u:
        {
          if (!match16(b, 0x89b4u, 0x7e00u)) return -1;
          c->d[7] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[7] & 0x80000000u) ? 8u : 0u) | (c->d[7] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x89b6u, 0x1e39u)) return -1;
          if (!match32(b,0x89b8u,0x00ff2726u)) return -1;
          if (native_bus_read8(b,0x00ff2726u,&byte_value)!=0) return -3;
          c->d[7]=(c->d[7]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0x89bcu, 0x6000u)) return -1;
          if (!match16(b, 0x89beu, 0x000au)) return -1;
          c->pc = (1) ? 0x0089c8u : 0x0089c0u;
          c->cycles += (1) ? 10u : 8u;
          return 0;
        }
      case 0x0089c8u:
        {
          if (!match16(b, 0x89c8u, 0x7008u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(8);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x89cau, 0x7200u)) return -1;
          c->d[1] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x89ccu, 0x6100u)) return -1;
          if (!match16(b, 0x89ceu, 0xfd6eu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0089d0u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00873cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0089d0u:
        {
          if (!match16(b, 0x89d0u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x89d2u, 0x3007u)) return -1;
          { uint16_t v=(uint16_t)c->d[7]; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          c->pc = 0x0089d4u;
          return 0;
        }
      case 0x0089f2u:
        {
          if (!match16(b, 0x89f2u, 0x7008u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(8);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x89f4u, 0x7201u)) return -1;
          c->d[1] = (uint32_t)(int32_t)(1);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x89f6u, 0x6100u)) return -1;
          if (!match16(b, 0x89f8u, 0xfd44u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0089fau) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00873cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0089fau:
        {
          if (!match16(b, 0x89fau, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x89fcu, 0x3039u)) return -1;
          if (!match32(b, 0x89feu, 0x00ff0260u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0260u, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          c->pc = 0x008a02u;
          return 0;
        }
      case 0x008a20u:
        {
          if (!match16(b, 0x8a20u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x8a22u, 0x7202u)) return -1;
          c->d[1] = (uint32_t)(int32_t)(2);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x8a24u, 0x6100u)) return -1;
          if (!match16(b, 0x8a26u, 0xfd16u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x008a28u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00873cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x008a28u:
        {
          if (!match16(b, 0x8a28u, 0x41fau)) return -1;
          if (!match16(b, 0x8a2au, 0xff3eu)) return -1;
          c->a[0] = 0x008968u;
          c->cycles += 8u;
          if (!match16(b, 0x8a2cu, 0x6100u)) return -1;
          if (!match16(b, 0x8a2eu, 0xfe96u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x008a30u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0088c4u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x008a30u:
        {
          if (!match16(b, 0x8a30u, 0x4a79u)) return -1;
          if (!match32(b, 0x8a32u, 0x00ff5248u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff5248u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x8a36u, 0x6600u)) return -1;
          if (!match16(b, 0x8a38u, 0x000au)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x008a42u : 0x008a3au;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x008a3au:
        {
          if (!match16(b, 0x8a3au, 0x33fcu)) return -1;
          if (!match16(b, 0x8a3cu, 0x0001u) || !match32(b, 0x8a3eu, 0x00ff5248u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff5248u, 0x0001u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0001u & 0x8000u) ? 8u : 0u) | (0x0001u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x8a42u, 0x7e02u)) return -1;
          c->d[7] = (uint32_t)(int32_t)(2);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[7] & 0x80000000u) ? 8u : 0u) | (c->d[7] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x8a44u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x8a46u, 0x6100u)) return -1;
          if (!match16(b, 0x8a48u, 0x0084u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x008a4au) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x008accu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x008a42u:
        {
          if (!match16(b, 0x8a42u, 0x7e02u)) return -1;
          c->d[7] = (uint32_t)(int32_t)(2);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[7] & 0x80000000u) ? 8u : 0u) | (c->d[7] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x8a44u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x8a46u, 0x6100u)) return -1;
          if (!match16(b, 0x8a48u, 0x0084u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x008a4au) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x008accu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x008a4au:
        {
          if (!match16(b, 0x8a4au, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x008accu:
        {
          if (!match16(b, 0x8accu, 0x7202u)) return -1;
          c->d[1] = (uint32_t)(int32_t)(2);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x8aceu, 0x6100u)) return -1;
          if (!match16(b, 0x8ad0u, 0xfc6cu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x008ad2u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00873cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x008ad2u:
        {
          if (!match16(b, 0x8ad2u, 0x41f9u)) return -1;
          if (!match32(b, 0x8ad4u, 0x00ff2804u)) return -1;
          c->a[0] = 0x00ff2804u;
          c->cycles += 12u;
          if (!match16(b, 0x8ad8u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x8adau, 0x1030u)) return -1;
          if(!match16(b,0x8adcu,0x7000u))return -1;
          if(native_bus_read8(b,(c->a[0]+((uint32_t)(int32_t)(int16_t)c->d[7])+(uint32_t)(0))&0xffffffu,&byte_value)!=0)return -3;
          c->d[0]=(c->d[0]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&128u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=14u;
          c->pc = 0x008adeu;
          return 0;
        }
      case 0x008af6u:
        {
          if (!match16(b, 0x8af6u, 0x2c79u)) return -1;
          if (!match32(b, 0x8af8u, 0x00ff01c8u)) return -1;
          if (native_bus_read32(b, 0x00ff01c8u, &c->a[6]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0x8afcu, 0x5340u)) return -1;
          {uint32_t dst=c->d[0]&65535u,src=1u,r=(dst-src)&65535u;
           c->d[0]=(c->d[0]&0xffff0000u)|r;
           uint16_t cy=(dst<src),ov=((dst^src)&(dst^r)&32768u)!=0u;
           c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(cy?17u:0u));}
          c->cycles+=4u;
          if (!match16(b, 0x8afeu, 0x43f9u)) return -1;
          if (!match32(b, 0x8b00u, 0x000faa68u)) return -1;
          c->a[1] = 0x000faa68u;
          c->cycles += 12u;
          if (!match16(b, 0x8b04u, 0xd2c0u)) return -1;
          c->a[1]=(c->a[1]+(int16_t)(c->d[0]&65535u))&0xffffffu;
          c->cycles+=8u;
          if (!match16(b, 0x8b06u, 0xd2c0u)) return -1;
          c->a[1]=(c->a[1]+(int16_t)(c->d[0]&65535u))&0xffffffu;
          c->cycles+=8u;
          if (!match16(b, 0x8b08u, 0x41f9u)) return -1;
          if (!match32(b, 0x8b0au, 0x000faa68u)) return -1;
          c->a[0] = 0x000faa68u;
          c->cycles += 12u;
          c->pc = 0x008b0eu;
          return 0;
        }
      case 0x00937eu:
        {
          if (!match16(b, 0x937eu, 0x41fau)) return -1;
          if (!match16(b, 0x9380u, 0xff8eu)) return -1;
          c->a[0] = 0x00930eu;
          c->cycles += 8u;
          if (!match16(b, 0x9382u, 0x5340u)) return -1;
          {uint32_t dst=c->d[0]&65535u,src=1u,r=(dst-src)&65535u;
           c->d[0]=(c->d[0]&0xffff0000u)|r;
           uint16_t cy=(dst<src),ov=((dst^src)&(dst^r)&32768u)!=0u;
           c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(cy?17u:0u));}
          c->cycles+=4u;
          if (!match16(b, 0x9384u, 0xe548u)) return -1;
          { unsigned count=c->d[2]&63u,i;uint32_t v=c->d[0]&65535u;uint16_t carry=0;
            for(i=0;i<count;i++){carry=(v>>15)&1u;v=(v<<1)&65535u;}
            c->d[0]=(c->d[0]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&(count?0xffe0u:0xfff0u))|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)|(count&&carry?17u:0u)); c->cycles+=6u+2u*count; }
          c->pc = 0x009386u;
          return 0;
        }
      case 0x00939cu:
        {
          if (!match16(b, 0x939cu, 0x41f9u)) return -1;
          if (!match32(b, 0x939eu, 0x00ff05ceu)) return -1;
          c->a[0] = 0x00ff05ceu;
          c->cycles += 12u;
          c->pc = 0x0093a2u;
          return 0;
        }
      case 0x0093acu:
        {
          if (!match16(b, 0x93acu, 0x13fcu)) return -1;
          byte_value=0xffu;
          if(native_bus_write8((struct t2bus *)b,0x00ff27a7u,byte_value)!=0)return -3;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&128u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=20u;
          if (!match16(b, 0x93b4u, 0x23c8u)) return -1;
          if (!match32(b, 0x93b6u, 0x00ff0238u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff0238u, c->a[0]) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->a[0] & 0x80000000u) ? 8u : 0u) | (c->a[0] == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x93bau, 0x41f9u)) return -1;
          if (!match32(b, 0x93bcu, 0x00ff0238u)) return -1;
          c->a[0] = 0x00ff0238u;
          c->cycles += 12u;
          if (!match16(b, 0x93c0u, 0x6100u)) return -1;
          if (!match16(b, 0x93c2u, 0x0004u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0093c4u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0093c6u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0093c4u:
        {
          if (!match16(b, 0x93c4u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x0093c6u:
        {
          printf("T2GEN V1.01 INIT_STEP: pc=0093c6 kind=movel_postinc_absl A0=%06lx D0=%08lx FF0230=%08lx FF0234=%08lx FF0238=%08lx\n",(unsigned long)(c->a[0]&0xffffffu),(unsigned long)c->d[0],(unsigned long)t2gen_v100_read32(b,0xff0230u),(unsigned long)t2gen_v100_read32(b,0xff0234u),(unsigned long)t2gen_v100_read32(b,0xff0238u));
          {uint32_t v=0;int rc=native_bus_read32(b,c->a[0],&v);printf("T2GEN V1.01 INIT_SOURCE: A0=%06lx read_rc=%d long=%08lx\n",(unsigned long)(c->a[0]&0xffffffu),rc,(unsigned long)v);}
          printf("T2GEN V1.01 INIT_BEFORE: pc=0093c6 FF0230=%08lx FF0234=%08lx FF0238=%08lx\n",(unsigned long)t2gen_v100_read32(b,0xff0230u),(unsigned long)t2gen_v100_read32(b,0xff0234u),(unsigned long)t2gen_v100_read32(b,0xff0238u));
          if (!match16(b, 0x93c6u, 0x23d8u)) return -1;
          { uint32_t v; if(native_bus_read32(b,c->a[0],&v)!=0)return -3;
            c->a[0]=(c->a[0]+4u)&0xffffffu;
            if(native_bus_write32((struct t2bus *)b,0x00ff0230u,v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=28u;
          printf("T2GEN V1.01 INIT_STEP: pc=0093cc kind=v90_movel_mem_mem A0=%06lx D0=%08lx FF0230=%08lx FF0234=%08lx FF0238=%08lx\n",(unsigned long)(c->a[0]&0xffffffu),(unsigned long)c->d[0],(unsigned long)t2gen_v100_read32(b,0xff0230u),(unsigned long)t2gen_v100_read32(b,0xff0234u),(unsigned long)t2gen_v100_read32(b,0xff0238u));
          printf("T2GEN V1.01 INIT_BEFORE: pc=0093cc FF0230=%08lx FF0234=%08lx FF0238=%08lx\n",(unsigned long)t2gen_v100_read32(b,0xff0230u),(unsigned long)t2gen_v100_read32(b,0xff0234u),(unsigned long)t2gen_v100_read32(b,0xff0238u));
          if (!match16(b, 0x93ccu, 0x23f9u)) return -1;
          if(!match32(b,0x93ceu,0x00ff0230u)||!match32(b,0x93d2u,0x00ff0234u))return -1;
          {uint32_t v;if(native_bus_read32(b,0x00ff0230u,&v)!=0)return -3;
           if(native_bus_write32((struct t2bus *)b,0x00ff0234u,v)!=0)return -3;
           c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=36u;
          printf("T2GEN V1.01 INIT_STEP: pc=0093d6 kind=movel_imm_absl A0=%06lx D0=%08lx FF0230=%08lx FF0234=%08lx FF0238=%08lx\n",(unsigned long)(c->a[0]&0xffffffu),(unsigned long)c->d[0],(unsigned long)t2gen_v100_read32(b,0xff0230u),(unsigned long)t2gen_v100_read32(b,0xff0234u),(unsigned long)t2gen_v100_read32(b,0xff0238u));
          printf("T2GEN V1.01 INIT_BEFORE: pc=0093d6 FF0230=%08lx FF0234=%08lx FF0238=%08lx\n",(unsigned long)t2gen_v100_read32(b,0xff0230u),(unsigned long)t2gen_v100_read32(b,0xff0234u),(unsigned long)t2gen_v100_read32(b,0xff0238u));
          if (!match16(b, 0x93d6u, 0x23fcu)) return -1;
          if (!match32(b, 0x93d8u, 0x00009192u) || !match32(b, 0x93dcu, 0x00ff0238u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff0238u, 0x00009192u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=0093d6 addr=00ff0238 value=00009192\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00009192u & 0x80000000u) ? 8u : 0u) | (0x00009192u == 0u ? 4u : 0u));
          c->cycles += 28u;
          printf("T2GEN V1.01 INIT_STEP: pc=0093e0 kind=movew_imm_absl A0=%06lx D0=%08lx FF0230=%08lx FF0234=%08lx FF0238=%08lx\n",(unsigned long)(c->a[0]&0xffffffu),(unsigned long)c->d[0],(unsigned long)t2gen_v100_read32(b,0xff0230u),(unsigned long)t2gen_v100_read32(b,0xff0234u),(unsigned long)t2gen_v100_read32(b,0xff0238u));
          printf("T2GEN V1.01 INIT_BEFORE: pc=0093e0 FF0230=%08lx FF0234=%08lx FF0238=%08lx\n",(unsigned long)t2gen_v100_read32(b,0xff0230u),(unsigned long)t2gen_v100_read32(b,0xff0234u),(unsigned long)t2gen_v100_read32(b,0xff0238u));
          if (!match16(b, 0x93e0u, 0x33fcu)) return -1;
          if (!match16(b, 0x93e2u, 0xffffu) || !match32(b, 0x93e4u, 0x00ff0218u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0218u, 0xffffu) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xffffu & 0x8000u) ? 8u : 0u) | (0xffffu == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x93e8u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x0093eau:
        {
          printf("T2GEN V1.01 INIT_STEP: pc=0093ea kind=tstw_absl A0=%06lx D0=%08lx FF0230=%08lx FF0234=%08lx FF0238=%08lx\n",(unsigned long)(c->a[0]&0xffffffu),(unsigned long)c->d[0],(unsigned long)t2gen_v100_read32(b,0xff0230u),(unsigned long)t2gen_v100_read32(b,0xff0234u),(unsigned long)t2gen_v100_read32(b,0xff0238u));
          if (!match16(b, 0x93eau, 0x4a79u)) return -1;
          if (!match32(b, 0x93ecu, 0x00ff0218u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff0218u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x93f0u, 0x6700u)) return -1;
          if (!match16(b, 0x93f2u, 0x0064u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x009456u : 0x0093f4u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x0093f4u:
        {
          if (!match16(b, 0x93f4u, 0x2079u)) return -1;
          if (!match32(b, 0x93f6u, 0x00ff0238u)) return -1;
          if (native_bus_read32(b, 0x00ff0238u, &c->a[0]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0x93fau, 0x4a50u)) return -1;
          {uint16_t v; if(native_bus_read16(b,c->a[0],&v))return -3; c->sr=(c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=8u;
          if (!match16(b, 0x93fcu, 0x6600u)) return -1;
          if (!match16(b, 0x93feu, 0x0050u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x00944eu : 0x009400u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x009400u:
        {
          printf("T2GEN V1.00 STEP: pc=009400 kind=movea_absl D0=%08lx A0=%06lx A1=%06lx FF0230=%08lx FF0238=%08lx FF023C=%08lx\n",(unsigned long)c->d[0],(unsigned long)(c->a[0]&0xffffffu),(unsigned long)(c->a[1]&0xffffffu),(unsigned long)t2gen_v100_read32(b,0xff0230u),(unsigned long)t2gen_v100_read32(b,0xff0238u),(unsigned long)t2gen_v100_read32(b,0xff023cu));
          printf("T2GEN V1.01 INIT_STEP: pc=009400 kind=movea_absl A0=%06lx D0=%08lx FF0230=%08lx FF0234=%08lx FF0238=%08lx\n",(unsigned long)(c->a[0]&0xffffffu),(unsigned long)c->d[0],(unsigned long)t2gen_v100_read32(b,0xff0230u),(unsigned long)t2gen_v100_read32(b,0xff0234u),(unsigned long)t2gen_v100_read32(b,0xff0238u));
          if (!match16(b, 0x9400u, 0x2079u)) return -1;
          if (!match32(b, 0x9402u, 0x00ff0230u)) return -1;
          if (native_bus_read32(b, 0x00ff0230u, &c->a[0]) != 0) return -3;
          c->cycles += 20u;
          printf("T2GEN V1.00 STEP: pc=009406 kind=movew_postinc_dn D0=%08lx A0=%06lx A1=%06lx FF0230=%08lx FF0238=%08lx FF023C=%08lx\n",(unsigned long)c->d[0],(unsigned long)(c->a[0]&0xffffffu),(unsigned long)(c->a[1]&0xffffffu),(unsigned long)t2gen_v100_read32(b,0xff0230u),(unsigned long)t2gen_v100_read32(b,0xff0238u),(unsigned long)t2gen_v100_read32(b,0xff023cu));
          printf("T2GEN V1.00 WORD: pc=009406 A0=%06lx value=%04lx\n",(unsigned long)(c->a[0]&0xffffffu),(unsigned long)t2gen_v100_read16(b,c->a[0]));
          {unsigned k;printf("T2GEN V1.00 RAM_DUMP: FF0230=");for(k=0;k<48;k++){uint8_t x=0;native_bus_read8(b,0xff0230u+k,&x);printf("%02x",x);}printf("\n");}
          {unsigned k;printf("T2GEN V1.00 RAM_DUMP: FF0410=");for(k=0;k<48;k++){uint8_t x=0;native_bus_read8(b,0xff0410u+k,&x);printf("%02x",x);}printf("\n");}
          if (!match16(b, 0x9406u, 0x3018u)) return -1;
          { uint16_t v; if(native_bus_read16(b,c->a[0],&v)!=0) return -3;
            c->a[0]=(c->a[0]+2u)&0xffffffu;
            c->d[0]=(c->d[0]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=8u;
          printf("T2GEN V1.00 STEP: pc=009408 kind=bpl_w D0=%08lx A0=%06lx A1=%06lx FF0230=%08lx FF0238=%08lx FF023C=%08lx\n",(unsigned long)c->d[0],(unsigned long)(c->a[0]&0xffffffu),(unsigned long)(c->a[1]&0xffffffu),(unsigned long)t2gen_v100_read32(b,0xff0230u),(unsigned long)t2gen_v100_read32(b,0xff0238u),(unsigned long)t2gen_v100_read32(b,0xff023cu));
          if (!match16(b, 0x9408u, 0x6a00u)) return -1;
          if (!match16(b, 0x940au, 0x0016u)) return -1;
          c->pc = (c->sr & 8u) ? 0x00940cu : 0x009420u;
          c->cycles += 10u;
          return 0;
        }
      case 0x00940cu:
        {
          if (!match16(b, 0x940cu, 0x33fcu)) return -1;
          if (!match16(b, 0x940eu, 0x0000u) || !match32(b, 0x9410u, 0x00ff0218u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0218u, 0x0000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x9414u, 0x13fcu)) return -1;
          byte_value=0x00u;
          if(native_bus_write8((struct t2bus *)b,0x00ff27a7u,byte_value)!=0)return -3;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&128u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=20u;
          if (!match16(b, 0x941cu, 0x6000u)) return -1;
          if (!match16(b, 0x941eu, 0x0038u)) return -1;
          c->pc = (1) ? 0x009456u : 0x009420u;
          c->cycles += (1) ? 10u : 8u;
          return 0;
        }
      case 0x009420u:
        {
          printf("T2GEN V1.00 STEP: pc=009420 kind=addw_dn D0=%08lx A0=%06lx A1=%06lx FF0230=%08lx FF0238=%08lx FF023C=%08lx\n",(unsigned long)c->d[0],(unsigned long)(c->a[0]&0xffffffu),(unsigned long)(c->a[1]&0xffffffu),(unsigned long)t2gen_v100_read32(b,0xff0230u),(unsigned long)t2gen_v100_read32(b,0xff0238u),(unsigned long)t2gen_v100_read32(b,0xff023cu));
          if (!match16(b, 0x9420u, 0xd040u)) return -1;
          { uint32_t x = c->d[0] & 65535u, y = c->d[0] & 65535u, r = (x+y) & 65535u;
            uint16_t flags = (uint16_t)(((r & 0x8000u) ? 8u : 0u) | ((r == 0u) ? 4u : 0u) | (((~(x ^ y) & (r ^ y)) & 0x8000u) ? 2u : 0u) | ((x+y > 65535u) ? 17u : 0u));
            c->d[0] = (c->d[0] & 0xffff0000u) | r;
            c->sr = (uint16_t)((c->sr & 0xffe0u) | flags);
          }
          c->cycles += 4u;
          if (!match16(b, 0x9422u, 0x43f9u)) return -1;
          if (!match32(b, 0x9424u, 0x00ff0218u)) return -1;
          c->a[1] = 0x00ff0218u;
          c->cycles += 12u;
          if (!match16(b, 0x9428u, 0xd2c0u)) return -1;
          c->a[1]=(c->a[1]+(int16_t)(c->d[0]&65535u))&0xffffffu;
          c->cycles+=8u;
          if (!match16(b, 0x942au, 0x23c9u)) return -1;
          if (!match32(b, 0x942cu, 0x00ff0238u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff0238u, c->a[1]) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->a[1] & 0x80000000u) ? 8u : 0u) | (c->a[1] == 0u ? 4u : 0u));
          c->cycles += 20u;
          printf("T2GEN V1.00 STEP: pc=009430 kind=addw_dn D0=%08lx A0=%06lx A1=%06lx FF0230=%08lx FF0238=%08lx FF023C=%08lx\n",(unsigned long)c->d[0],(unsigned long)(c->a[0]&0xffffffu),(unsigned long)(c->a[1]&0xffffffu),(unsigned long)t2gen_v100_read32(b,0xff0230u),(unsigned long)t2gen_v100_read32(b,0xff0238u),(unsigned long)t2gen_v100_read32(b,0xff023cu));
          if (!match16(b, 0x9430u, 0xd040u)) return -1;
          { uint32_t x = c->d[0] & 65535u, y = c->d[0] & 65535u, r = (x+y) & 65535u;
            uint16_t flags = (uint16_t)(((r & 0x8000u) ? 8u : 0u) | ((r == 0u) ? 4u : 0u) | (((~(x ^ y) & (r ^ y)) & 0x8000u) ? 2u : 0u) | ((x+y > 65535u) ? 17u : 0u));
            c->d[0] = (c->d[0] & 0xffff0000u) | r;
            c->sr = (uint16_t)((c->sr & 0xffe0u) | flags);
          }
          c->cycles += 4u;
          if (!match16(b, 0x9432u, 0x43fau)) return -1;
          if (!match16(b, 0x9434u, 0xfd32u)) return -1;
          c->a[1] = 0x009166u;
          c->cycles += 8u;
          if (!match16(b, 0x9436u, 0x23f1u)) return -1;
          printf("T2GEN V0.99 IDX_MOVE: pc=009436 base=%06lx index=%08lx disp=%d ea=%06lx\n",(unsigned long)c->a[1],(unsigned long)((int32_t)(int16_t)(c->d[0]&65535u)),(int)(int8_t)0x00u,(unsigned long)((c->a[1]+((int32_t)(int16_t)(c->d[0]&65535u))+(int8_t)0x00u)&0xffffffu));
          {uint32_t ea=(c->a[1]+((int32_t)(int16_t)(c->d[0]&65535u))+(int8_t)0x00u)&0xffffffu,v;if(native_bus_read32(b,ea,&v)||native_bus_write32((struct t2bus *)b,0xff023cu,v))return -3;c->sr=(c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=28u;
          {uint32_t v=0;native_bus_read32(b,0xff023cu,&v);printf("T2GEN V0.99 IDX_MOVE_RESULT: FF023C=%08lx\n",(unsigned long)v);}
          if (!match16(b, 0x943eu, 0x43fau)) return -1;
          if (!match16(b, 0x9440u, 0xfcfau)) return -1;
          c->a[1] = 0x00913au;
          c->cycles += 8u;
          if (!match16(b, 0x9442u, 0x2271u)) return -1;
          printf("T2GEN V0.99 IDX_MOVEA: pc=009442 base=%06lx index=%08lx disp=%d ea=%06lx\n",(unsigned long)c->a[1],(unsigned long)((int32_t)(int16_t)(c->d[0]&65535u)),(int)(int8_t)0x00u,(unsigned long)((c->a[1]+((int32_t)(int16_t)(c->d[0]&65535u))+(int8_t)0x00u)&0xffffffu));
          {uint32_t ea=(c->a[1]+((int32_t)(int16_t)(c->d[0]&65535u))+(int8_t)0x00u)&0xffffffu,v;if(native_bus_read32(b,ea,&v))return -3;c->a[1]=v&0xffffffu;}
          c->cycles+=18u;
          printf("T2GEN V0.99 IDX_MOVEA_RESULT: A1=%06lx\n",(unsigned long)c->a[1]);
          if (!match16(b, 0x9446u, 0x4e91u)) return -1;
          printf("T2GEN V0.99 JSR: pc=009446 target=%06lx FF0238/FF023C follow\n",(unsigned long)(c->a[1]&0xffffffu));
          { uint32_t target=c->a[1] & 0xffffffu;
            uint32_t sp=(c->a[7]-4u)&0xffffffu;
            if(native_bus_write32((struct t2bus *)b,sp,0x009448u)!=0)return -3;
            c->a[7]=sp; c->pc=target; c->cycles+=16u;
            printf("T2GEN V0.94 IRQ6_CALLBACK: pointer_addr=FF0138 target=%06lx return=009448\n",(unsigned long)target);
          }
          return 0;
        }
      case 0x009448u:
        {
          if (!match16(b, 0x9448u, 0x23c8u)) return -1;
          if (!match32(b, 0x944au, 0x00ff0230u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff0230u, c->a[0]) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->a[0] & 0x80000000u) ? 8u : 0u) | (c->a[0] == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x944eu, 0x2279u)) return -1;
          if (!match32(b, 0x9450u, 0x00ff023cu)) return -1;
          if (native_bus_read32(b, 0x00ff023cu, &c->a[1]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0x9454u, 0x4e91u)) return -1;
          { uint32_t target=c->a[1] & 0xffffffu;
            uint32_t sp=(c->a[7]-4u)&0xffffffu;
            if(native_bus_write32((struct t2bus *)b,sp,0x009456u)!=0)return -3;
            c->a[7]=sp; c->pc=target; c->cycles+=16u;
            printf("T2GEN V0.94 IRQ6_CALLBACK: pointer_addr=FF0138 target=%06lx return=009456\n",(unsigned long)target);
          }
          return 0;
        }
      case 0x00944eu:
        {
          if (!match16(b, 0x944eu, 0x2279u)) return -1;
          if (!match32(b, 0x9450u, 0x00ff023cu)) return -1;
          if (native_bus_read32(b, 0x00ff023cu, &c->a[1]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0x9454u, 0x4e91u)) return -1;
          { uint32_t target=c->a[1] & 0xffffffu;
            uint32_t sp=(c->a[7]-4u)&0xffffffu;
            if(native_bus_write32((struct t2bus *)b,sp,0x009456u)!=0)return -3;
            c->a[7]=sp; c->pc=target; c->cycles+=16u;
            printf("T2GEN V0.94 IRQ6_CALLBACK: pointer_addr=FF0138 target=%06lx return=009456\n",(unsigned long)target);
          }
          return 0;
        }
      case 0x009456u:
        {
          if (!match16(b, 0x9456u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x0094c0u:
        {
          if (!match16(b, 0x94c0u, 0x4a79u)) return -1;
          if (!match32(b, 0x94c2u, 0x00ff0226u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff0226u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x94c6u, 0x6700u)) return -1;
          if (!match16(b, 0x94c8u, 0x0056u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x00951eu : 0x0094cau;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x0094cau:
        {
          if (!match16(b, 0x94cau, 0x0c79u)) return -1;
          { uint16_t v; if(native_bus_read16(b,0x00ff0226u,&v)!=0)return -3;
            uint32_t x=v,y=0x0002u,r=(x-y)&65535u;
            uint16_t carry=x<y;
            uint16_t ov=((x^y)&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?1u:0u));
          }
          c->cycles+=16u;
          if (!match16(b, 0x94d2u, 0x6700u)) return -1;
          if (!match16(b, 0x94d4u, 0x0030u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x009504u : 0x0094d6u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x0094d6u:
        {
          if (!match16(b, 0x94d6u, 0x41f9u)) return -1;
          if (!match32(b, 0x94d8u, 0x00020000u)) return -1;
          c->a[0] = 0x00020000u;
          c->cycles += 12u;
          if (!match16(b, 0x94dcu, 0x2279u)) return -1;
          if (!match32(b, 0x94deu, 0x00ff0626u)) return -1;
          if (native_bus_read32(b, 0x00ff0626u, &c->a[1]) != 0) return -3;
          c->cycles += 20u;
          c->pc = 0x0094e2u;
          return 0;
        }
      case 0x009504u:
        {
          if (!match16(b, 0x9504u, 0x33fcu)) return -1;
          if (!match16(b, 0x9506u, 0xffffu) || !match32(b, 0x9508u, 0x00ff0656u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0656u, 0xffffu) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xffffu & 0x8000u) ? 8u : 0u) | (0xffffu == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x950cu, 0x33fcu)) return -1;
          if (!match16(b, 0x950eu, 0x0000u) || !match32(b, 0x9510u, 0x00ff0226u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0226u, 0x0000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x9514u, 0x33fcu)) return -1;
          if (!match16(b, 0x9516u, 0xffbau) || !match32(b, 0x9518u, 0x00ff0624u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0624u, 0xffbau) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xffbau & 0x8000u) ? 8u : 0u) | (0xffbau == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x951cu, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00951eu:
        {
          if (!match16(b, 0x951eu, 0x4a79u)) return -1;
          if (!match32(b, 0x9520u, 0x00ff0624u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff0624u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x9524u, 0x6700u)) return -1;
          if (!match16(b, 0x9526u, 0x0028u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x00954eu : 0x009528u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x009528u:
        {
          if (!match16(b, 0x9528u, 0x6a00u)) return -1;
          if (!match16(b, 0x952au, 0x0026u)) return -1;
          c->pc = (c->sr & 8u) ? 0x00952cu : 0x009550u;
          c->cycles += 10u;
          return 0;
        }
      case 0x00952cu:
        {
          if (!match16(b, 0x952cu, 0x5279u)) return -1;
          if (!match32(b,0x952eu,0x00ff0624u)) return -1;
          { uint16_t dst,src=1u,result; if (native_bus_read16(b,0x00ff0624u,&dst)!=0) return -3;
            result=(uint16_t)(dst + src);
            if (native_bus_write16((struct t2bus *)b,0x00ff0624u,result)!=0) return -3;
            uint16_t carry=(uint32_t)dst+src>0xffffu?1u:0u;
            uint16_t overflow=((~(dst^src))&(dst^result)&0x8000u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((result&0x8000u)?8u:0u)|(result==0u?4u:0u)|overflow|carry|(carry?16u:0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9532u, 0x6600u)) return -1;
          if (!match16(b, 0x9534u, 0x001au)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x00954eu : 0x009536u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x009536u:
        {
          if (!match16(b, 0x9536u, 0x33fcu)) return -1;
          if (!match16(b, 0x9538u, 0x0002u) || !match32(b, 0x953au, 0x00ff0624u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0624u, 0x0002u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0002u & 0x8000u) ? 8u : 0u) | (0x0002u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x953eu, 0x33fcu)) return -1;
          if (!match16(b, 0x9540u, 0x0003u) || !match32(b, 0x9542u, 0x00ff03beu)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff03beu, 0x0003u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0003u & 0x8000u) ? 8u : 0u) | (0x0003u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x9546u, 0x33fcu)) return -1;
          if (!match16(b, 0x9548u, 0x0001u) || !match32(b, 0x954au, 0x00ff03c0u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff03c0u, 0x0001u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0001u & 0x8000u) ? 8u : 0u) | (0x0001u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x954eu, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00954eu:
        {
          if (!match16(b, 0x954eu, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x009550u:
        {
          if (!match16(b, 0x9550u, 0x0c79u)) return -1;
          { uint16_t v; if(native_bus_read16(b,0x00ff0624u,&v)!=0)return -3;
            uint32_t x=v,y=0x0002u,r=(x-y)&65535u;
            uint16_t carry=x<y;
            uint16_t ov=((x^y)&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?1u:0u));
          }
          c->cycles+=16u;
          if (!match16(b, 0x9558u, 0x6600u)) return -1;
          if (!match16(b, 0x955au, 0x0006u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x009560u : 0x00955cu;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00955cu:
        {
          if (!match16(b, 0x955cu, 0x6100u)) return -1;
          if (!match16(b, 0x955eu, 0xdbc2u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x009560u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x007120u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x009560u:
        {
          if (!match16(b, 0x9560u, 0x41f9u)) return -1;
          if (!match32(b, 0x9562u, 0x00020000u)) return -1;
          c->a[0] = 0x00020000u;
          c->cycles += 12u;
          if (!match16(b, 0x9566u, 0x2279u)) return -1;
          if (!match32(b, 0x9568u, 0x00ff0626u)) return -1;
          if (native_bus_read32(b, 0x00ff0626u, &c->a[1]) != 0) return -3;
          c->cycles += 20u;
          c->pc = 0x00956cu;
          return 0;
        }
      case 0x00965cu:
        {
          if (!match16(b, 0x965cu, 0x4a79u)) return -1;
          if (!match32(b, 0x965eu, 0x00ff0220u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff0220u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x9662u, 0x6700u)) return -1;
          if (!match16(b, 0x9664u, 0x0086u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x0096eau : 0x009666u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x009666u:
        {
          if (!match16(b, 0x9666u, 0x6100u)) return -1;
          if (!match16(b, 0x9668u, 0x01b2u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00966au) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00981au;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00966au:
        {
          if (!match16(b, 0x966au, 0x3a39u)) return -1;
          if (!match32(b, 0x966cu, 0x00ff01dcu)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff01dcu, &val) != 0) return -3;
            c->d[5] = (c->d[5] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x9670u, 0x3239u)) return -1;
          if (!match32(b, 0x9672u, 0x00ff0220u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0220u, &val) != 0) return -3;
            c->d[1] = (c->d[1] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x9676u, 0x5341u)) return -1;
          {uint32_t dst=c->d[1]&65535u,src=1u,r=(dst-src)&65535u;
           c->d[1]=(c->d[1]&0xffff0000u)|r;
           uint16_t cy=(dst<src),ov=((dst^src)&(dst^r)&32768u)!=0u;
           c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(cy?17u:0u));}
          c->cycles+=4u;
          c->pc = 0x009678u;
          return 0;
        }
      case 0x0096eau:
        {
          if (!match16(b, 0x96eau, 0x4a79u)) return -1;
          if (!match32(b, 0x96ecu, 0x00ff0622u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff0622u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x96f0u, 0x6700u)) return -1;
          if (!match16(b, 0x96f2u, 0x007cu)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x00976eu : 0x0096f4u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x0096f4u:
        {
          if (!match16(b, 0x96f4u, 0x6a00u)) return -1;
          if (!match16(b, 0x96f6u, 0x00c4u)) return -1;
          c->pc = (c->sr & 8u) ? 0x0096f8u : 0x0097bau;
          c->cycles += 10u;
          return 0;
        }
      case 0x0096f8u:
        {
          if (!match16(b, 0x96f8u, 0x6100u)) return -1;
          if (!match16(b, 0x96fau, 0x0120u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0096fcu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00981au;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0096fcu:
        {
          if (!match16(b, 0x96fcu, 0x2a79u)) return -1;
          if (!match32(b, 0x96feu, 0x00ff01e0u)) return -1;
          if (native_bus_read32(b, 0x00ff01e0u, &c->a[5]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0x9702u, 0x49f9u)) return -1;
          if (!match32(b, 0x9704u, 0x000fd5a6u)) return -1;
          c->a[4] = 0x000fd5a6u;
          c->cycles += 12u;
          c->pc = 0x009708u;
          return 0;
        }
      case 0x00976eu:
        {
          if (!match16(b, 0x976eu, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x0097bau:
        {
          if (!match16(b, 0x97bau, 0x6100u)) return -1;
          if (!match16(b, 0x97bcu, 0x005eu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0097beu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00981au;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0097beu:
        {
          if (!match16(b, 0x97beu, 0x45f9u)) return -1;
          if (!match32(b, 0x97c0u, 0x000fd64au)) return -1;
          c->a[2] = 0x000fd64au;
          c->cycles += 12u;
          if (!match16(b, 0x97c4u, 0x47f9u)) return -1;
          if (!match32(b, 0x97c6u, 0x00ff01e8u)) return -1;
          c->a[3] = 0x00ff01e8u;
          c->cycles += 12u;
          if (!match16(b, 0x97cau, 0x49f9u)) return -1;
          if (!match32(b, 0x97ccu, 0x000fd516u)) return -1;
          c->a[4] = 0x000fd516u;
          c->cycles += 12u;
          c->pc = 0x0097d0u;
          return 0;
        }
      case 0x00981au:
        {
          if (!match16(b, 0x981au, 0x2879u)) return -1;
          if (!match32(b, 0x981cu, 0x00ff066au)) return -1;
          if (native_bus_read32(b, 0x00ff066au, &c->a[4]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0x9820u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x9822u, 0x1039u)) return -1;
          if (!match32(b, 0x9824u, 0x00ff2794u)) return -1;
          if (native_bus_read8(b, 0x00ff2794u, &byte_value) != 0) return -3;
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 0x80u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 16u;
          if (!match16(b, 0x9828u, 0x7200u)) return -1;
          c->d[1] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x982au, 0x1239u)) return -1;
          if (!match32(b,0x982cu,0x00ff2795u)) return -1;
          if (native_bus_read8(b,0x00ff2795u,&byte_value)!=0) return -3;
          c->d[1]=(c->d[1]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0x9830u, 0x7400u)) return -1;
          c->d[2] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[2] & 0x80000000u) ? 8u : 0u) | (c->d[2] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x9832u, 0x1439u)) return -1;
          if (!match32(b,0x9834u,0x00ff2796u)) return -1;
          if (native_bus_read8(b,0x00ff2796u,&byte_value)!=0) return -3;
          c->d[2]=(c->d[2]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0x9838u, 0xd442u)) return -1;
          { uint32_t x = c->d[2] & 65535u, y = c->d[2] & 65535u, r = (x+y) & 65535u;
            uint16_t flags = (uint16_t)(((r & 0x8000u) ? 8u : 0u) | ((r == 0u) ? 4u : 0u) | (((~(x ^ y) & (r ^ y)) & 0x8000u) ? 2u : 0u) | ((x+y > 65535u) ? 17u : 0u));
            c->d[2] = (c->d[2] & 0xffff0000u) | r;
            c->sr = (uint16_t)((c->sr & 0xffe0u) | flags);
          }
          c->cycles += 4u;
          c->pc = 0x00983au;
          return 0;
        }
      case 0x009890u:
        {
          if (!match16(b, 0x9890u, 0x4a79u)) return -1;
          if (!match32(b, 0x9892u, 0x00ff0228u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff0228u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x9896u, 0x6700u)) return -1;
          if (!match16(b, 0x9898u, 0x004au)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x0098e2u : 0x00989au;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00989au:
        {
          if (!match16(b, 0x989au, 0x6100u)) return -1;
          if (!match16(b, 0x989cu, 0x00aeu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00989eu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00994au;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00989eu:
        {
          if (!match16(b, 0x989eu, 0x3039u)) return -1;
          if (!match32(b, 0x98a0u, 0x00ff0212u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0212u, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x98a4u, 0x3239u)) return -1;
          if (!match32(b, 0x98a6u, 0x00ff0214u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0214u, &val) != 0) return -3;
            c->d[1] = (c->d[1] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x98aau, 0x2079u)) return -1;
          if (!match32(b, 0x98acu, 0x00ff05eau)) return -1;
          if (native_bus_read32(b, 0x00ff05eau, &c->a[0]) != 0) return -3;
          c->cycles += 20u;
          c->pc = 0x0098b0u;
          return 0;
        }
      case 0x0098e2u:
        {
          if (!match16(b, 0x98e2u, 0x4a79u)) return -1;
          if (!match32(b, 0x98e4u, 0x00ff05e8u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff05e8u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x98e8u, 0x6700u)) return -1;
          if (!match16(b, 0x98eau, 0x0034u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x00991eu : 0x0098ecu;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x0098ecu:
        {
          if (!match16(b, 0x98ecu, 0x6a00u)) return -1;
          if (!match16(b, 0x98eeu, 0x0032u)) return -1;
          c->pc = (c->sr & 8u) ? 0x0098f0u : 0x009920u;
          c->cycles += 10u;
          return 0;
        }
      case 0x0098f0u:
        {
          if (!match16(b, 0x98f0u, 0x6100u)) return -1;
          if (!match16(b, 0x98f2u, 0x0058u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0098f4u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00994au;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0098f4u:
        {
          if (!match16(b, 0x98f4u, 0x3039u)) return -1;
          if (!match32(b, 0x98f6u, 0x00ff0212u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0212u, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x98fau, 0x3239u)) return -1;
          if (!match32(b, 0x98fcu, 0x00ff0214u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0214u, &val) != 0) return -3;
            c->d[1] = (c->d[1] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x9900u, 0x2079u)) return -1;
          if (!match32(b, 0x9902u, 0x00ff05eau)) return -1;
          if (native_bus_read32(b, 0x00ff05eau, &c->a[0]) != 0) return -3;
          c->cycles += 20u;
          c->pc = 0x009906u;
          return 0;
        }
      case 0x00991eu:
        {
          if (!match16(b, 0x991eu, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x009920u:
        {
          if (!match16(b, 0x9920u, 0x6100u)) return -1;
          if (!match16(b, 0x9922u, 0x0028u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x009924u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00994au;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x009924u:
        {
          if (!match16(b, 0x9924u, 0x3039u)) return -1;
          if (!match32(b, 0x9926u, 0x00ff0212u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0212u, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x992au, 0x3239u)) return -1;
          if (!match32(b, 0x992cu, 0x00ff0214u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0214u, &val) != 0) return -3;
            c->d[1] = (c->d[1] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x9930u, 0x2079u)) return -1;
          if (!match32(b, 0x9932u, 0x00ff05eau)) return -1;
          if (native_bus_read32(b, 0x00ff05eau, &c->a[0]) != 0) return -3;
          c->cycles += 20u;
          c->pc = 0x009936u;
          return 0;
        }
      case 0x00994au:
        {
          if (!match16(b, 0x994au, 0x2879u)) return -1;
          if (!match32(b, 0x994cu, 0x00ff066au)) return -1;
          if (native_bus_read32(b, 0x00ff066au, &c->a[4]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0x9950u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x9952u, 0x1039u)) return -1;
          if (!match32(b, 0x9954u, 0x00ff2794u)) return -1;
          if (native_bus_read8(b, 0x00ff2794u, &byte_value) != 0) return -3;
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 0x80u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 16u;
          if (!match16(b, 0x9958u, 0x7200u)) return -1;
          c->d[1] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x995au, 0x1239u)) return -1;
          if (!match32(b,0x995cu,0x00ff2795u)) return -1;
          if (native_bus_read8(b,0x00ff2795u,&byte_value)!=0) return -3;
          c->d[1]=(c->d[1]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0x9960u, 0x7400u)) return -1;
          c->d[2] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[2] & 0x80000000u) ? 8u : 0u) | (c->d[2] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x9962u, 0x1439u)) return -1;
          if (!match32(b,0x9964u,0x00ff2796u)) return -1;
          if (native_bus_read8(b,0x00ff2796u,&byte_value)!=0) return -3;
          c->d[2]=(c->d[2]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0x9968u, 0xd442u)) return -1;
          { uint32_t x = c->d[2] & 65535u, y = c->d[2] & 65535u, r = (x+y) & 65535u;
            uint16_t flags = (uint16_t)(((r & 0x8000u) ? 8u : 0u) | ((r == 0u) ? 4u : 0u) | (((~(x ^ y) & (r ^ y)) & 0x8000u) ? 2u : 0u) | ((x+y > 65535u) ? 17u : 0u));
            c->d[2] = (c->d[2] & 0xffff0000u) | r;
            c->sr = (uint16_t)((c->sr & 0xffe0u) | flags);
          }
          c->cycles += 4u;
          c->pc = 0x00996au;
          return 0;
        }
      case 0x0099a6u:
        {
          if (!match16(b, 0x99a6u, 0x6100u)) return -1;
          if (!match16(b, 0x99a8u, 0x0052u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0099aau) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0099fau;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0099aau:
        {
          if (!match16(b, 0x99aau, 0x6100u)) return -1;
          if (!match16(b, 0x99acu, 0xc76eu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0099aeu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00611au;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0099aeu:
        {
          if (!match16(b, 0x99aeu, 0x4a79u)) return -1;
          if (!match32(b, 0x99b0u, 0x00ff0222u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff0222u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x99b4u, 0x66f0u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x0099a6u : 0x0099b6u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x0099b6u:
        {
          if (!match16(b, 0x99b6u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x0099b8u:
        {
          if (!match16(b, 0x99b8u, 0x4c98u)) return -1;
          if (!match16(b, 0x99bau, 0x000fu)) return -1;
          { uint32_t addr = c->a[0]; uint32_t val; uint16_t word; unsigned idx;
            for (idx = 0; idx < 16u; ++idx)
              {
                if (!(0x000fu & (1u << idx))) continue;
                if (native_bus_read16(b, addr, &word) != 0) return -3;
                val = (uint32_t)(int32_t)(int16_t)word;
                if (idx < 8u) c->d[idx] = val;
                else c->a[idx - 8u] = val;
                addr = (addr + 2u) & 0xffffffu;
              }
            c->a[0] = addr; /* postincrement wins if base An is in mask */
          }
          c->cycles += 24u;
          if (!match16(b, 0x99bcu, 0x33c1u)) return -1;
          if (!match32(b, 0x99beu, 0x00ff02a2u)) return -1;
          { uint16_t v=(uint16_t)c->d[1];
            if (native_bus_write16((struct t2bus *)b,0x00ff02a2u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x99c2u, 0x33fcu)) return -1;
          if (!match16(b, 0x99c4u, 0x0000u) || !match32(b, 0x99c6u, 0x00ff02a4u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff02a4u, 0x0000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x99cau, 0x33c0u)) return -1;
          if (!match32(b, 0x99ccu, 0x00ff0222u)) return -1;
          { uint16_t v=(uint16_t)c->d[0];
            if (native_bus_write16((struct t2bus *)b,0x00ff0222u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x99d0u, 0x33c2u)) return -1;
          if (!match32(b, 0x99d2u, 0x00ff029cu)) return -1;
          { uint16_t v=(uint16_t)c->d[2];
            if (native_bus_write16((struct t2bus *)b,0x00ff029cu,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x99d6u, 0x33c3u)) return -1;
          if (!match32(b, 0x99d8u, 0x00ff029eu)) return -1;
          { uint16_t v=(uint16_t)c->d[3];
            if (native_bus_write16((struct t2bus *)b,0x00ff029eu,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x99dcu, 0x33fcu)) return -1;
          if (!match16(b, 0x99deu, 0x0000u) || !match32(b, 0x99e0u, 0x00ff02a0u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff02a0u, 0x0000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x99e4u, 0x7001u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(1);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x99e6u, 0xb642u)) return -1;
          { uint32_t x=c->d[2]&0xffffu,y=c->d[3]&0xffffu,r=(y-x)&0xffffu;
            uint16_t f=(uint16_t)(((r&0x8000u)?8u:0u)|((r==0u)?4u:0u)|(((y^x)&(y^r)&0x8000u)?2u:0u)|((x>y)?1u:0u));
            c->sr=(uint16_t)((c->sr&0xfff0u)|f);
          }
          c->cycles += 4u;
          if (!match16(b, 0x99e8u, 0x6700u)) return -1;
          if (!match16(b, 0x99eau, 0x000eu)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x0099f8u : 0x0099ecu;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x0099bcu:
        {
          if (!match16(b, 0x99bcu, 0x33c1u)) return -1;
          if (!match32(b, 0x99beu, 0x00ff02a2u)) return -1;
          { uint16_t v=(uint16_t)c->d[1];
            if (native_bus_write16((struct t2bus *)b,0x00ff02a2u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x99c2u, 0x33fcu)) return -1;
          if (!match16(b, 0x99c4u, 0x0000u) || !match32(b, 0x99c6u, 0x00ff02a4u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff02a4u, 0x0000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x99cau, 0x33c0u)) return -1;
          if (!match32(b, 0x99ccu, 0x00ff0222u)) return -1;
          { uint16_t v=(uint16_t)c->d[0];
            if (native_bus_write16((struct t2bus *)b,0x00ff0222u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x99d0u, 0x33c2u)) return -1;
          if (!match32(b, 0x99d2u, 0x00ff029cu)) return -1;
          { uint16_t v=(uint16_t)c->d[2];
            if (native_bus_write16((struct t2bus *)b,0x00ff029cu,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x99d6u, 0x33c3u)) return -1;
          if (!match32(b, 0x99d8u, 0x00ff029eu)) return -1;
          { uint16_t v=(uint16_t)c->d[3];
            if (native_bus_write16((struct t2bus *)b,0x00ff029eu,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x99dcu, 0x33fcu)) return -1;
          if (!match16(b, 0x99deu, 0x0000u) || !match32(b, 0x99e0u, 0x00ff02a0u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff02a0u, 0x0000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x99e4u, 0x7001u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(1);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x99e6u, 0xb642u)) return -1;
          { uint32_t x=c->d[2]&0xffffu,y=c->d[3]&0xffffu,r=(y-x)&0xffffu;
            uint16_t f=(uint16_t)(((r&0x8000u)?8u:0u)|((r==0u)?4u:0u)|(((y^x)&(y^r)&0x8000u)?2u:0u)|((x>y)?1u:0u));
            c->sr=(uint16_t)((c->sr&0xfff0u)|f);
          }
          c->cycles += 4u;
          if (!match16(b, 0x99e8u, 0x6700u)) return -1;
          if (!match16(b, 0x99eau, 0x000eu)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x0099f8u : 0x0099ecu;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x0099ecu:
        {
          if (!match16(b, 0x99ecu, 0x6e00u)) return -1;
          if (!match16(b,0x99eeu,0x0004u)) return -1;
          c->pc=((!(c->sr & 4u) && (!!(c->sr & 8u)==!!(c->sr & 2u))))?0x0099f2u:0x0099f0u;
          c->cycles+=((!(c->sr & 4u) && (!!(c->sr & 8u)==!!(c->sr & 2u))))?10u:8u;
          return 0;
        }
      case 0x0099f0u:
        {
          if (!match16(b, 0x99f0u, 0x70ffu)) return -1;
          c->d[0] = (uint32_t)(int32_t)(-1);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x99f2u, 0x33c0u)) return -1;
          if (!match32(b, 0x99f4u, 0x00ff02a0u)) return -1;
          { uint16_t v=(uint16_t)c->d[0];
            if (native_bus_write16((struct t2bus *)b,0x00ff02a0u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x99f8u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x0099f2u:
        {
          if (!match16(b, 0x99f2u, 0x33c0u)) return -1;
          if (!match32(b, 0x99f4u, 0x00ff02a0u)) return -1;
          { uint16_t v=(uint16_t)c->d[0];
            if (native_bus_write16((struct t2bus *)b,0x00ff02a0u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x99f8u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x0099f8u:
        {
          if (!match16(b, 0x99f8u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x0099fau:
        {
          if (!match16(b, 0x99fau, 0x4a79u)) return -1;
          if (!match32(b, 0x99fcu, 0x00ff0222u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff0222u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x9a00u, 0x6700u)) return -1;
          if (!match16(b, 0x9a02u, 0x00aeu)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x009ab0u : 0x009a04u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x009a04u:
        {
          if (!match16(b, 0x9a04u, 0x5379u)) return -1;
          if (!match32(b,0x9a06u,0x00ff02a4u)) return -1;
          { uint16_t dst,src=1u,result; if (native_bus_read16(b,0x00ff02a4u,&dst)!=0) return -3;
            result=(uint16_t)(dst - src);
            if (native_bus_write16((struct t2bus *)b,0x00ff02a4u,result)!=0) return -3;
            uint16_t carry=dst<src?1u:0u;
            uint16_t overflow=((dst^src)&(dst^result)&0x8000u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((result&0x8000u)?8u:0u)|(result==0u?4u:0u)|overflow|carry|(carry?16u:0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9a0au, 0x6a00u)) return -1;
          if (!match16(b, 0x9a0cu, 0x00a4u)) return -1;
          c->pc = (c->sr & 8u) ? 0x009a0eu : 0x009ab0u;
          c->cycles += 10u;
          return 0;
        }
      case 0x009a0eu:
        {
          if (!match16(b, 0x9a0eu, 0x33f9u)) return -1;
          if (!match32(b, 0x9a10u, 0x00ff02a2u) || !match32(b, 0x9a14u, 0x00ff02a4u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff02a2u, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00ff02a4u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x9a18u, 0x41f9u)) return -1;
          if (!match32(b, 0x9a1au, 0x00ff0388u)) return -1;
          c->a[0] = 0x00ff0388u;
          c->cycles += 12u;
          if (!match16(b, 0x9a1eu, 0x3c3cu)) return -1;
          if (!match16(b, 0x9a20u, 0x0060u)) return -1;
          c->d[6] = (c->d[6] & 0xffff0000u) | 0x0060u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0060u & 0x8000u) ? 8u : 0u) | (0x0060u == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x9a22u, 0x7e03u)) return -1;
          c->d[7] = (uint32_t)(int32_t)(3);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[7] & 0x80000000u) ? 8u : 0u) | (c->d[7] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x9a24u, 0x45f9u)) return -1;
          if (!match32(b, 0x9a26u, 0x00ff0308u)) return -1;
          c->a[2] = 0x00ff0308u;
          c->cycles += 12u;
          if (!match16(b, 0x9a2au, 0x0f39u)) return -1;
          if (!match32(b,0x9a2cu,0x00ff0223u)) return -1;
          if (native_bus_read8(b,0x00ff0223u,&byte_value)!=0) return -3;
          c->sr=(uint16_t)((c->sr&~4u)|((byte_value&(1u<<(c->d[7]&7u)))?0u:4u));
          c->cycles+=12u;
          if (!match16(b, 0x9a30u, 0x6700u)) return -1;
          if (!match16(b, 0x9a32u, 0x004au)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x009a7cu : 0x009a34u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x009a2au:
        {
          if (!match16(b, 0x9a2au, 0x0f39u)) return -1;
          if (!match32(b,0x9a2cu,0x00ff0223u)) return -1;
          if (native_bus_read8(b,0x00ff0223u,&byte_value)!=0) return -3;
          c->sr=(uint16_t)((c->sr&~4u)|((byte_value&(1u<<(c->d[7]&7u)))?0u:4u));
          c->cycles+=12u;
          if (!match16(b, 0x9a30u, 0x6700u)) return -1;
          if (!match16(b, 0x9a32u, 0x004au)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x009a7cu : 0x009a34u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x009a34u:
        {
          if (!match16(b, 0x9a34u, 0x3439u)) return -1;
          if (!match32(b, 0x9a36u, 0x00ff029cu)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff029cu, &val) != 0) return -3;
            c->d[2] = (c->d[2] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x9a3au, 0x2248u)) return -1;
          c->a[1]=c->a[0];
          c->cycles+=4u;
          if (!match16(b, 0x9a3cu, 0x3639u)) return -1;
          if (!match32(b, 0x9a3eu, 0x00ff02a6u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff02a6u, &val) != 0) return -3;
            c->d[3] = (c->d[3] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x9a42u, 0x7a0fu)) return -1;
          c->d[5] = (uint32_t)(int32_t)(15);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[5] & 0x80000000u) ? 8u : 0u) | (c->d[5] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x9a44u, 0x3219u)) return -1;
          { uint16_t v; if(native_bus_read16(b,c->a[1],&v)!=0) return -3;
            c->a[1]=(c->a[1]+2u)&0xffffffu;
            c->d[1]=(c->d[1]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=8u;
          if (!match16(b, 0x9a46u, 0xb741u)) return -1;
          { uint16_t x=(uint16_t)c->d[1], y=(uint16_t)c->d[3],r=(uint16_t)(x ^ y);
            c->d[1]=(c->d[1]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0x9a48u, 0x3801u)) return -1;
          { uint16_t v=(uint16_t)c->d[1]; c->d[4]=(c->d[4] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0x9a4au, 0x0244u)) return -1;
          if (!match16(b, 0x9a4cu, 0x000fu)) return -1;
          { uint16_t v=(uint16_t)c->d[4] & 0x000fu; c->d[4]=(c->d[4] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x9a4eu, 0xc8c2u)) return -1;
          c->d[4] = (uint32_t)((c->d[4] & 0xffffu) * (c->d[2] & 0xffffu));
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[4] & 0x80000000u) ? 8u : 0u) | (c->d[4] == 0u ? 4u : 0u));
          c->cycles += 70u;
          if (!match16(b, 0x9a50u, 0xe84cu)) return -1;
          { uint16_t old=(uint16_t)c->d[4],r=(uint16_t)(old>>4);
            uint16_t carry=(old>>3)&1u;
            c->d[4]=(c->d[4]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xffe0u)|(r==0u?4u:0u)|(carry?17u:0u));
            c->cycles+=14u;
          }
          if (!match16(b, 0x9a52u, 0x3001u)) return -1;
          { uint16_t v=(uint16_t)c->d[1]; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0x9a54u, 0x0240u)) return -1;
          if (!match16(b, 0x9a56u, 0x00f0u)) return -1;
          { uint16_t v=(uint16_t)c->d[0] & 0x00f0u; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x9a58u, 0xc0c2u)) return -1;
          c->d[0] = (uint32_t)((c->d[0] & 0xffffu) * (c->d[2] & 0xffffu));
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 70u;
          if (!match16(b, 0x9a5au, 0xe848u)) return -1;
          { uint16_t old=(uint16_t)c->d[0],r=(uint16_t)(old>>4);
            uint16_t carry=(old>>3)&1u;
            c->d[0]=(c->d[0]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xffe0u)|(r==0u?4u:0u)|(carry?17u:0u));
            c->cycles+=14u;
          }
          if (!match16(b, 0x9a5cu, 0x0240u)) return -1;
          if (!match16(b, 0x9a5eu, 0x00f0u)) return -1;
          { uint16_t v=(uint16_t)c->d[0] & 0x00f0u; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x9a60u, 0x8840u)) return -1;
          { uint16_t x=(uint16_t)c->d[0], y=(uint16_t)c->d[4],r=(uint16_t)(x | y);
            c->d[0]=(c->d[0]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0x9a62u, 0x0241u)) return -1;
          if (!match16(b, 0x9a64u, 0x0f00u)) return -1;
          { uint16_t v=(uint16_t)c->d[1] & 0x0f00u; c->d[1]=(c->d[1] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x9a66u, 0xc2c2u)) return -1;
          c->d[1] = (uint32_t)((c->d[1] & 0xffffu) * (c->d[2] & 0xffffu));
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 70u;
          if (!match16(b, 0x9a68u, 0xe849u)) return -1;
          { uint16_t old=(uint16_t)c->d[1],r=(uint16_t)(old>>4);
            uint16_t carry=(old>>3)&1u;
            c->d[1]=(c->d[1]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xffe0u)|(r==0u?4u:0u)|(carry?17u:0u));
            c->cycles+=14u;
          }
          if (!match16(b, 0x9a6au, 0x0241u)) return -1;
          if (!match16(b, 0x9a6cu, 0x0f00u)) return -1;
          { uint16_t v=(uint16_t)c->d[1] & 0x0f00u; c->d[1]=(c->d[1] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x9a6eu, 0x8841u)) return -1;
          { uint16_t x=(uint16_t)c->d[1], y=(uint16_t)c->d[4],r=(uint16_t)(x | y);
            c->d[1]=(c->d[1]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0x9a70u, 0xb744u)) return -1;
          { uint16_t x=(uint16_t)c->d[4], y=(uint16_t)c->d[3],r=(uint16_t)(x ^ y);
            c->d[4]=(c->d[4]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0x9a72u, 0x34c4u)) return -1;
          { uint16_t v=(uint16_t)c->d[4];
            if(native_bus_write16((struct t2bus *)b,c->a[2],v)!=0)return -3;
            c->a[2]=(c->a[2]+2u)&0xffffffu;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u));
          }
          c->cycles+=8u;
          if (!match16(b, 0x9a74u, 0x51cdu)) return -1;
          { uint16_t count = (uint16_t)(c->d[5] - 1u);
            c->d[5] = (c->d[5] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x009a44u : 0x009a78u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x009a44u:
        {
          if (!match16(b, 0x9a44u, 0x3219u)) return -1;
          { uint16_t v; if(native_bus_read16(b,c->a[1],&v)!=0) return -3;
            c->a[1]=(c->a[1]+2u)&0xffffffu;
            c->d[1]=(c->d[1]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=8u;
          if (!match16(b, 0x9a46u, 0xb741u)) return -1;
          { uint16_t x=(uint16_t)c->d[1], y=(uint16_t)c->d[3],r=(uint16_t)(x ^ y);
            c->d[1]=(c->d[1]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0x9a48u, 0x3801u)) return -1;
          { uint16_t v=(uint16_t)c->d[1]; c->d[4]=(c->d[4] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0x9a4au, 0x0244u)) return -1;
          if (!match16(b, 0x9a4cu, 0x000fu)) return -1;
          { uint16_t v=(uint16_t)c->d[4] & 0x000fu; c->d[4]=(c->d[4] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x9a4eu, 0xc8c2u)) return -1;
          c->d[4] = (uint32_t)((c->d[4] & 0xffffu) * (c->d[2] & 0xffffu));
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[4] & 0x80000000u) ? 8u : 0u) | (c->d[4] == 0u ? 4u : 0u));
          c->cycles += 70u;
          if (!match16(b, 0x9a50u, 0xe84cu)) return -1;
          { uint16_t old=(uint16_t)c->d[4],r=(uint16_t)(old>>4);
            uint16_t carry=(old>>3)&1u;
            c->d[4]=(c->d[4]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xffe0u)|(r==0u?4u:0u)|(carry?17u:0u));
            c->cycles+=14u;
          }
          if (!match16(b, 0x9a52u, 0x3001u)) return -1;
          { uint16_t v=(uint16_t)c->d[1]; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0x9a54u, 0x0240u)) return -1;
          if (!match16(b, 0x9a56u, 0x00f0u)) return -1;
          { uint16_t v=(uint16_t)c->d[0] & 0x00f0u; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x9a58u, 0xc0c2u)) return -1;
          c->d[0] = (uint32_t)((c->d[0] & 0xffffu) * (c->d[2] & 0xffffu));
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 70u;
          if (!match16(b, 0x9a5au, 0xe848u)) return -1;
          { uint16_t old=(uint16_t)c->d[0],r=(uint16_t)(old>>4);
            uint16_t carry=(old>>3)&1u;
            c->d[0]=(c->d[0]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xffe0u)|(r==0u?4u:0u)|(carry?17u:0u));
            c->cycles+=14u;
          }
          if (!match16(b, 0x9a5cu, 0x0240u)) return -1;
          if (!match16(b, 0x9a5eu, 0x00f0u)) return -1;
          { uint16_t v=(uint16_t)c->d[0] & 0x00f0u; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x9a60u, 0x8840u)) return -1;
          { uint16_t x=(uint16_t)c->d[0], y=(uint16_t)c->d[4],r=(uint16_t)(x | y);
            c->d[0]=(c->d[0]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0x9a62u, 0x0241u)) return -1;
          if (!match16(b, 0x9a64u, 0x0f00u)) return -1;
          { uint16_t v=(uint16_t)c->d[1] & 0x0f00u; c->d[1]=(c->d[1] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x9a66u, 0xc2c2u)) return -1;
          c->d[1] = (uint32_t)((c->d[1] & 0xffffu) * (c->d[2] & 0xffffu));
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 70u;
          if (!match16(b, 0x9a68u, 0xe849u)) return -1;
          { uint16_t old=(uint16_t)c->d[1],r=(uint16_t)(old>>4);
            uint16_t carry=(old>>3)&1u;
            c->d[1]=(c->d[1]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xffe0u)|(r==0u?4u:0u)|(carry?17u:0u));
            c->cycles+=14u;
          }
          if (!match16(b, 0x9a6au, 0x0241u)) return -1;
          if (!match16(b, 0x9a6cu, 0x0f00u)) return -1;
          { uint16_t v=(uint16_t)c->d[1] & 0x0f00u; c->d[1]=(c->d[1] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x9a6eu, 0x8841u)) return -1;
          { uint16_t x=(uint16_t)c->d[1], y=(uint16_t)c->d[4],r=(uint16_t)(x | y);
            c->d[1]=(c->d[1]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0x9a70u, 0xb744u)) return -1;
          { uint16_t x=(uint16_t)c->d[4], y=(uint16_t)c->d[3],r=(uint16_t)(x ^ y);
            c->d[4]=(c->d[4]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0x9a72u, 0x34c4u)) return -1;
          { uint16_t v=(uint16_t)c->d[4];
            if(native_bus_write16((struct t2bus *)b,c->a[2],v)!=0)return -3;
            c->a[2]=(c->a[2]+2u)&0xffffffu;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u));
          }
          c->cycles+=8u;
          if (!match16(b, 0x9a74u, 0x51cdu)) return -1;
          { uint16_t count = (uint16_t)(c->d[5] - 1u);
            c->d[5] = (c->d[5] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x009a44u : 0x009a78u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x009a46u:
        {
          if (!match16(b, 0x9a46u, 0xb741u)) return -1;
          { uint16_t x=(uint16_t)c->d[1], y=(uint16_t)c->d[3],r=(uint16_t)(x ^ y);
            c->d[1]=(c->d[1]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0x9a48u, 0x3801u)) return -1;
          { uint16_t v=(uint16_t)c->d[1]; c->d[4]=(c->d[4] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0x9a4au, 0x0244u)) return -1;
          if (!match16(b, 0x9a4cu, 0x000fu)) return -1;
          { uint16_t v=(uint16_t)c->d[4] & 0x000fu; c->d[4]=(c->d[4] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x9a4eu, 0xc8c2u)) return -1;
          c->d[4] = (uint32_t)((c->d[4] & 0xffffu) * (c->d[2] & 0xffffu));
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[4] & 0x80000000u) ? 8u : 0u) | (c->d[4] == 0u ? 4u : 0u));
          c->cycles += 70u;
          if (!match16(b, 0x9a50u, 0xe84cu)) return -1;
          { uint16_t old=(uint16_t)c->d[4],r=(uint16_t)(old>>4);
            uint16_t carry=(old>>3)&1u;
            c->d[4]=(c->d[4]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xffe0u)|(r==0u?4u:0u)|(carry?17u:0u));
            c->cycles+=14u;
          }
          if (!match16(b, 0x9a52u, 0x3001u)) return -1;
          { uint16_t v=(uint16_t)c->d[1]; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0x9a54u, 0x0240u)) return -1;
          if (!match16(b, 0x9a56u, 0x00f0u)) return -1;
          { uint16_t v=(uint16_t)c->d[0] & 0x00f0u; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x9a58u, 0xc0c2u)) return -1;
          c->d[0] = (uint32_t)((c->d[0] & 0xffffu) * (c->d[2] & 0xffffu));
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 70u;
          if (!match16(b, 0x9a5au, 0xe848u)) return -1;
          { uint16_t old=(uint16_t)c->d[0],r=(uint16_t)(old>>4);
            uint16_t carry=(old>>3)&1u;
            c->d[0]=(c->d[0]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xffe0u)|(r==0u?4u:0u)|(carry?17u:0u));
            c->cycles+=14u;
          }
          if (!match16(b, 0x9a5cu, 0x0240u)) return -1;
          if (!match16(b, 0x9a5eu, 0x00f0u)) return -1;
          { uint16_t v=(uint16_t)c->d[0] & 0x00f0u; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x9a60u, 0x8840u)) return -1;
          { uint16_t x=(uint16_t)c->d[0], y=(uint16_t)c->d[4],r=(uint16_t)(x | y);
            c->d[0]=(c->d[0]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0x9a62u, 0x0241u)) return -1;
          if (!match16(b, 0x9a64u, 0x0f00u)) return -1;
          { uint16_t v=(uint16_t)c->d[1] & 0x0f00u; c->d[1]=(c->d[1] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x9a66u, 0xc2c2u)) return -1;
          c->d[1] = (uint32_t)((c->d[1] & 0xffffu) * (c->d[2] & 0xffffu));
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 70u;
          if (!match16(b, 0x9a68u, 0xe849u)) return -1;
          { uint16_t old=(uint16_t)c->d[1],r=(uint16_t)(old>>4);
            uint16_t carry=(old>>3)&1u;
            c->d[1]=(c->d[1]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xffe0u)|(r==0u?4u:0u)|(carry?17u:0u));
            c->cycles+=14u;
          }
          if (!match16(b, 0x9a6au, 0x0241u)) return -1;
          if (!match16(b, 0x9a6cu, 0x0f00u)) return -1;
          { uint16_t v=(uint16_t)c->d[1] & 0x0f00u; c->d[1]=(c->d[1] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x9a6eu, 0x8841u)) return -1;
          { uint16_t x=(uint16_t)c->d[1], y=(uint16_t)c->d[4],r=(uint16_t)(x | y);
            c->d[1]=(c->d[1]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0x9a70u, 0xb744u)) return -1;
          { uint16_t x=(uint16_t)c->d[4], y=(uint16_t)c->d[3],r=(uint16_t)(x ^ y);
            c->d[4]=(c->d[4]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0x9a72u, 0x34c4u)) return -1;
          { uint16_t v=(uint16_t)c->d[4];
            if(native_bus_write16((struct t2bus *)b,c->a[2],v)!=0)return -3;
            c->a[2]=(c->a[2]+2u)&0xffffffu;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u));
          }
          c->cycles+=8u;
          if (!match16(b, 0x9a74u, 0x51cdu)) return -1;
          { uint16_t count = (uint16_t)(c->d[5] - 1u);
            c->d[5] = (c->d[5] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x009a44u : 0x009a78u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x009a78u:
        {
          if (!match16(b, 0x9a78u, 0x94fcu)) return -1;
          if(!match16(b,0x9a7au,0x0020u))return -1;
          c->a[2]=(c->a[2]-(uint32_t)(int32_t)(int16_t)0x0020u)&0xffffffu;
          c->cycles+=8u;
          if (!match16(b, 0x9a7cu, 0x94fcu)) return -1;
          if(!match16(b,0x9a7eu,0x0020u))return -1;
          c->a[2]=(c->a[2]-(uint32_t)(int32_t)(int16_t)0x0020u)&0xffffffu;
          c->cycles+=8u;
          if (!match16(b, 0x9a80u, 0x0446u)) return -1;
          if(!match16(b,0x9a82u,0x0020u))return -1;
          { uint32_t x=c->d[6]&65535u,y=0x0020u,r=(x-y)&65535u;
            c->d[6]=(c->d[6]&0xffff0000u)|r;
            uint16_t carry=(x<y)?1u:0u;
            uint16_t overflow=((x^y)&(x^r)&0x8000u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u)|overflow|carry|(carry?16u:0u));
          }
          c->cycles+=8u;
          if (!match16(b, 0x9a84u, 0x90fcu)) return -1;
          if(!match16(b,0x9a86u,0x0020u))return -1;
          c->a[0]=(c->a[0]-(uint32_t)(int32_t)(int16_t)0x0020u)&0xffffffu;
          c->cycles+=8u;
          if (!match16(b, 0x9a88u, 0x51cfu)) return -1;
          { uint16_t count = (uint16_t)(c->d[7] - 1u);
            c->d[7] = (c->d[7] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x009a2au : 0x009a8cu;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x009a7cu:
        {
          if (!match16(b, 0x9a7cu, 0x94fcu)) return -1;
          if(!match16(b,0x9a7eu,0x0020u))return -1;
          c->a[2]=(c->a[2]-(uint32_t)(int32_t)(int16_t)0x0020u)&0xffffffu;
          c->cycles+=8u;
          if (!match16(b, 0x9a80u, 0x0446u)) return -1;
          if(!match16(b,0x9a82u,0x0020u))return -1;
          { uint32_t x=c->d[6]&65535u,y=0x0020u,r=(x-y)&65535u;
            c->d[6]=(c->d[6]&0xffff0000u)|r;
            uint16_t carry=(x<y)?1u:0u;
            uint16_t overflow=((x^y)&(x^r)&0x8000u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u)|overflow|carry|(carry?16u:0u));
          }
          c->cycles+=8u;
          if (!match16(b, 0x9a84u, 0x90fcu)) return -1;
          if(!match16(b,0x9a86u,0x0020u))return -1;
          c->a[0]=(c->a[0]-(uint32_t)(int32_t)(int16_t)0x0020u)&0xffffffu;
          c->cycles+=8u;
          if (!match16(b, 0x9a88u, 0x51cfu)) return -1;
          { uint16_t count = (uint16_t)(c->d[7] - 1u);
            c->d[7] = (c->d[7] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x009a2au : 0x009a8cu;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x009a80u:
        {
          if (!match16(b, 0x9a80u, 0x0446u)) return -1;
          if(!match16(b,0x9a82u,0x0020u))return -1;
          { uint32_t x=c->d[6]&65535u,y=0x0020u,r=(x-y)&65535u;
            c->d[6]=(c->d[6]&0xffff0000u)|r;
            uint16_t carry=(x<y)?1u:0u;
            uint16_t overflow=((x^y)&(x^r)&0x8000u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u)|overflow|carry|(carry?16u:0u));
          }
          c->cycles+=8u;
          if (!match16(b, 0x9a84u, 0x90fcu)) return -1;
          if(!match16(b,0x9a86u,0x0020u))return -1;
          c->a[0]=(c->a[0]-(uint32_t)(int32_t)(int16_t)0x0020u)&0xffffffu;
          c->cycles+=8u;
          if (!match16(b, 0x9a88u, 0x51cfu)) return -1;
          { uint16_t count = (uint16_t)(c->d[7] - 1u);
            c->d[7] = (c->d[7] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x009a2au : 0x009a8cu;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x009a8cu:
        {
          if (!match16(b, 0x9a8cu, 0x33fcu)) return -1;
          if (!match16(b, 0x9a8eu, 0x0001u) || !match32(b, 0x9a90u, 0x00ff0154u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0154u, 0x0001u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0001u & 0x8000u) ? 8u : 0u) | (0x0001u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x9a94u, 0xb479u)) return -1;
          { uint16_t v; if(native_bus_read16(b,0x00ff029eu,&v)!=0)return -3;
            uint32_t x=(c->d[2]&65535u),y=v,r=(x-y)&65535u;
            uint16_t carry=x<y;
            uint16_t ov=((x^y)&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?1u:0u));
          }
          c->cycles+=16u;
          if (!match16(b, 0x9a9au, 0x6600u)) return -1;
          if (!match16(b, 0x9a9cu, 0x0008u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x009aa4u : 0x009a9eu;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x009a9eu:
        {
          if (!match16(b, 0x9a9eu, 0x4279u)) return -1;
          if (!match32(b, 0x9aa0u, 0x00ff0222u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0222u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0x9aa4u, 0xd479u)) return -1;
          { uint16_t v; if(native_bus_read16(b,0x00ff02a0u,&v)!=0)return -3;
            uint32_t x=c->d[2]&65535u,y=v,r=(x+y)&65535u;
            c->d[2]=(c->d[2]&0xffff0000u)|r;
            uint16_t carry=((x+y)>65535u)?1u:0u,ov=((~(x^y))&(x^r)&32768u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|ov|carry|(carry?16u:0u)); }
          c->cycles+=12u;
          if (!match16(b, 0x9aaau, 0x33c2u)) return -1;
          if (!match32(b, 0x9aacu, 0x00ff029cu)) return -1;
          { uint16_t v=(uint16_t)c->d[2];
            if (native_bus_write16((struct t2bus *)b,0x00ff029cu,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x9ab0u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x009aa4u:
        {
          if (!match16(b, 0x9aa4u, 0xd479u)) return -1;
          { uint16_t v; if(native_bus_read16(b,0x00ff02a0u,&v)!=0)return -3;
            uint32_t x=c->d[2]&65535u,y=v,r=(x+y)&65535u;
            c->d[2]=(c->d[2]&0xffff0000u)|r;
            uint16_t carry=((x+y)>65535u)?1u:0u,ov=((~(x^y))&(x^r)&32768u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|ov|carry|(carry?16u:0u)); }
          c->cycles+=12u;
          if (!match16(b, 0x9aaau, 0x33c2u)) return -1;
          if (!match32(b, 0x9aacu, 0x00ff029cu)) return -1;
          { uint16_t v=(uint16_t)c->d[2];
            if (native_bus_write16((struct t2bus *)b,0x00ff029cu,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x9ab0u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x009ab0u:
        {
          if (!match16(b, 0x9ab0u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x009ab2u:
        {
          if (!match16(b, 0x9ab2u, 0x4a79u)) return -1;
          if (!match32(b, 0x9ab4u, 0x00ff0242u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff0242u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x9ab8u, 0x6700u)) return -1;
          if (!match16(b, 0x9abau, 0x0016u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x009ad0u : 0x009abcu;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x009abcu:
        {
          if (!match16(b, 0x9abcu, 0x3039u)) return -1;
          if (!match32(b, 0x9abeu, 0x00c00008u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00c00008u, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x9ac2u, 0x0c40u)) return -1;
          if(!match16(b,0x9ac4u,0xc000u))return -1;
          {uint32_t x=c->d[0]&65535u,y=0xc000u,r=(x-y)&65535u; c->sr=(c->sr&0xfff0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u)|(((x^y)&(x^r)&0x8000u)?2u:0u)|(x<y?1u:0u);}
          c->cycles+=8u;
          if (!match16(b, 0x9ac6u, 0x6500u)) return -1;
          if (!match16(b, 0x9ac8u, 0x0008u)) return -1;
          c->pc = ((c->sr & 1u)) ? 0x009ad0u : 0x009acau;
          c->cycles += ((c->sr & 1u)) ? 10u : 8u;
          return 0;
        }
      case 0x009acau:
        {
          if (!match16(b, 0x9acau, 0x0c40u)) return -1;
          if(!match16(b,0x9accu,0xf000u))return -1;
          {uint32_t x=c->d[0]&65535u,y=0xf000u,r=(x-y)&65535u; c->sr=(c->sr&0xfff0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u)|(((x^y)&(x^r)&0x8000u)?2u:0u)|(x<y?1u:0u);}
          c->cycles+=8u;
          if (!match16(b, 0x9aceu, 0x65ecu)) return -1;
          c->pc = ((c->sr & 1u)) ? 0x009abcu : 0x009ad0u;
          c->cycles += ((c->sr & 1u)) ? 10u : 8u;
          return 0;
        }
      case 0x009ad0u:
        {
          if (!match16(b, 0x9ad0u, 0x23fcu)) return -1;
          if (!match32(b, 0x9ad2u, 0xc0000000u) || !match32(b, 0x9ad6u, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0xc0000000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=009ad0 addr=00c00004 value=c0000000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xc0000000u & 0x80000000u) ? 8u : 0u) | (0xc0000000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x9adau, 0x43f9u)) return -1;
          if (!match32(b, 0x9adcu, 0x00ff02a8u)) return -1;
          c->a[1] = 0x00ff02a8u;
          c->cycles += 12u;
          if (!match16(b, 0x9ae0u, 0x45f9u)) return -1;
          if (!match32(b, 0x9ae2u, 0x00c00000u)) return -1;
          c->a[2] = 0x00c00000u;
          c->cycles += 12u;
          if (!match16(b, 0x9ae6u, 0x2499u)) return -1;
          { uint32_t long_value; uint32_t source = c->a[1];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=009ae6 addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[2], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=009ae6 addr=%06lx value=%08lx\n", (unsigned long)c->a[2], (unsigned long)long_value); return -3; }
            c->a[1] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9ae8u, 0x2499u)) return -1;
          { uint32_t long_value; uint32_t source = c->a[1];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=009ae8 addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[2], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=009ae8 addr=%06lx value=%08lx\n", (unsigned long)c->a[2], (unsigned long)long_value); return -3; }
            c->a[1] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9aeau, 0x2499u)) return -1;
          { uint32_t long_value; uint32_t source = c->a[1];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=009aea addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[2], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=009aea addr=%06lx value=%08lx\n", (unsigned long)c->a[2], (unsigned long)long_value); return -3; }
            c->a[1] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9aecu, 0x2499u)) return -1;
          { uint32_t long_value; uint32_t source = c->a[1];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=009aec addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[2], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=009aec addr=%06lx value=%08lx\n", (unsigned long)c->a[2], (unsigned long)long_value); return -3; }
            c->a[1] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9aeeu, 0x2499u)) return -1;
          { uint32_t long_value; uint32_t source = c->a[1];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=009aee addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[2], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=009aee addr=%06lx value=%08lx\n", (unsigned long)c->a[2], (unsigned long)long_value); return -3; }
            c->a[1] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9af0u, 0x2499u)) return -1;
          { uint32_t long_value; uint32_t source = c->a[1];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=009af0 addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[2], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=009af0 addr=%06lx value=%08lx\n", (unsigned long)c->a[2], (unsigned long)long_value); return -3; }
            c->a[1] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9af2u, 0x2499u)) return -1;
          { uint32_t long_value; uint32_t source = c->a[1];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=009af2 addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[2], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=009af2 addr=%06lx value=%08lx\n", (unsigned long)c->a[2], (unsigned long)long_value); return -3; }
            c->a[1] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9af4u, 0x2499u)) return -1;
          { uint32_t long_value; uint32_t source = c->a[1];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=009af4 addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[2], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=009af4 addr=%06lx value=%08lx\n", (unsigned long)c->a[2], (unsigned long)long_value); return -3; }
            c->a[1] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9af6u, 0x2499u)) return -1;
          { uint32_t long_value; uint32_t source = c->a[1];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=009af6 addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[2], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=009af6 addr=%06lx value=%08lx\n", (unsigned long)c->a[2], (unsigned long)long_value); return -3; }
            c->a[1] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9af8u, 0x2499u)) return -1;
          { uint32_t long_value; uint32_t source = c->a[1];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=009af8 addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[2], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=009af8 addr=%06lx value=%08lx\n", (unsigned long)c->a[2], (unsigned long)long_value); return -3; }
            c->a[1] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9afau, 0x2499u)) return -1;
          { uint32_t long_value; uint32_t source = c->a[1];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=009afa addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[2], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=009afa addr=%06lx value=%08lx\n", (unsigned long)c->a[2], (unsigned long)long_value); return -3; }
            c->a[1] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9afcu, 0x2499u)) return -1;
          { uint32_t long_value; uint32_t source = c->a[1];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=009afc addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[2], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=009afc addr=%06lx value=%08lx\n", (unsigned long)c->a[2], (unsigned long)long_value); return -3; }
            c->a[1] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9afeu, 0x2499u)) return -1;
          { uint32_t long_value; uint32_t source = c->a[1];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=009afe addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[2], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=009afe addr=%06lx value=%08lx\n", (unsigned long)c->a[2], (unsigned long)long_value); return -3; }
            c->a[1] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9b00u, 0x2499u)) return -1;
          { uint32_t long_value; uint32_t source = c->a[1];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=009b00 addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[2], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=009b00 addr=%06lx value=%08lx\n", (unsigned long)c->a[2], (unsigned long)long_value); return -3; }
            c->a[1] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9b02u, 0x2499u)) return -1;
          { uint32_t long_value; uint32_t source = c->a[1];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=009b02 addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[2], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=009b02 addr=%06lx value=%08lx\n", (unsigned long)c->a[2], (unsigned long)long_value); return -3; }
            c->a[1] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9b04u, 0x2499u)) return -1;
          { uint32_t long_value; uint32_t source = c->a[1];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=009b04 addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[2], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=009b04 addr=%06lx value=%08lx\n", (unsigned long)c->a[2], (unsigned long)long_value); return -3; }
            c->a[1] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9b06u, 0x2499u)) return -1;
          { uint32_t long_value; uint32_t source = c->a[1];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=009b06 addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[2], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=009b06 addr=%06lx value=%08lx\n", (unsigned long)c->a[2], (unsigned long)long_value); return -3; }
            c->a[1] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9b08u, 0x2499u)) return -1;
          { uint32_t long_value; uint32_t source = c->a[1];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=009b08 addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[2], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=009b08 addr=%06lx value=%08lx\n", (unsigned long)c->a[2], (unsigned long)long_value); return -3; }
            c->a[1] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9b0au, 0x2499u)) return -1;
          { uint32_t long_value; uint32_t source = c->a[1];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=009b0a addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[2], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=009b0a addr=%06lx value=%08lx\n", (unsigned long)c->a[2], (unsigned long)long_value); return -3; }
            c->a[1] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9b0cu, 0x2499u)) return -1;
          { uint32_t long_value; uint32_t source = c->a[1];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=009b0c addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[2], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=009b0c addr=%06lx value=%08lx\n", (unsigned long)c->a[2], (unsigned long)long_value); return -3; }
            c->a[1] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9b0eu, 0x2499u)) return -1;
          { uint32_t long_value; uint32_t source = c->a[1];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=009b0e addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[2], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=009b0e addr=%06lx value=%08lx\n", (unsigned long)c->a[2], (unsigned long)long_value); return -3; }
            c->a[1] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9b10u, 0x2499u)) return -1;
          { uint32_t long_value; uint32_t source = c->a[1];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=009b10 addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[2], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=009b10 addr=%06lx value=%08lx\n", (unsigned long)c->a[2], (unsigned long)long_value); return -3; }
            c->a[1] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9b12u, 0x2499u)) return -1;
          { uint32_t long_value; uint32_t source = c->a[1];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=009b12 addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[2], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=009b12 addr=%06lx value=%08lx\n", (unsigned long)c->a[2], (unsigned long)long_value); return -3; }
            c->a[1] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9b14u, 0x2499u)) return -1;
          { uint32_t long_value; uint32_t source = c->a[1];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=009b14 addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[2], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=009b14 addr=%06lx value=%08lx\n", (unsigned long)c->a[2], (unsigned long)long_value); return -3; }
            c->a[1] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9b16u, 0x2499u)) return -1;
          { uint32_t long_value; uint32_t source = c->a[1];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=009b16 addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[2], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=009b16 addr=%06lx value=%08lx\n", (unsigned long)c->a[2], (unsigned long)long_value); return -3; }
            c->a[1] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9b18u, 0x2499u)) return -1;
          { uint32_t long_value; uint32_t source = c->a[1];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=009b18 addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[2], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=009b18 addr=%06lx value=%08lx\n", (unsigned long)c->a[2], (unsigned long)long_value); return -3; }
            c->a[1] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9b1au, 0x2499u)) return -1;
          { uint32_t long_value; uint32_t source = c->a[1];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=009b1a addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[2], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=009b1a addr=%06lx value=%08lx\n", (unsigned long)c->a[2], (unsigned long)long_value); return -3; }
            c->a[1] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9b1cu, 0x2499u)) return -1;
          { uint32_t long_value; uint32_t source = c->a[1];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=009b1c addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[2], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=009b1c addr=%06lx value=%08lx\n", (unsigned long)c->a[2], (unsigned long)long_value); return -3; }
            c->a[1] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9b1eu, 0x2499u)) return -1;
          { uint32_t long_value; uint32_t source = c->a[1];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=009b1e addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[2], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=009b1e addr=%06lx value=%08lx\n", (unsigned long)c->a[2], (unsigned long)long_value); return -3; }
            c->a[1] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9b20u, 0x2499u)) return -1;
          { uint32_t long_value; uint32_t source = c->a[1];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=009b20 addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[2], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=009b20 addr=%06lx value=%08lx\n", (unsigned long)c->a[2], (unsigned long)long_value); return -3; }
            c->a[1] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9b22u, 0x2499u)) return -1;
          { uint32_t long_value; uint32_t source = c->a[1];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=009b22 addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[2], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=009b22 addr=%06lx value=%08lx\n", (unsigned long)c->a[2], (unsigned long)long_value); return -3; }
            c->a[1] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9b24u, 0x2499u)) return -1;
          { uint32_t long_value; uint32_t source = c->a[1];
            if (native_bus_read32(b, source, &long_value) != 0) { printf("T2GEN V0.57 READ32_STOP: pc=009b24 addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write32((struct t2bus *)b, c->a[2], long_value) != 0) { printf("T2GEN V0.57 WRITE32_STOP: pc=009b24 addr=%06lx value=%08lx\n", (unsigned long)c->a[2], (unsigned long)long_value); return -3; }
            c->a[1] = (source + 4u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((long_value & 0x80000000u) ? 8u : 0u) | (long_value == 0u ? 4u : 0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9b26u, 0x33fcu)) return -1;
          if (!match16(b, 0x9b28u, 0x0000u) || !match32(b, 0x9b2au, 0x00ff0154u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0154u, 0x0000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x9b2eu, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x009b30u:
        {
          if (!match16(b, 0x9b30u, 0x33fcu)) return -1;
          if (!match16(b, 0x9b32u, 0xffffu) || !match32(b, 0x9b34u, 0x00ff05dcu)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff05dcu, 0xffffu) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xffffu & 0x8000u) ? 8u : 0u) | (0xffffu == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x9b38u, 0x4a79u)) return -1;
          if (!match32(b, 0x9b3au, 0x00ff0154u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff0154u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x9b3eu, 0x6700u)) return -1;
          if (!match16(b, 0x9b40u, 0x0006u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x009b46u : 0x009b42u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x009b42u:
        {
          if (!match16(b, 0x9b42u, 0x6100u)) return -1;
          if (!match16(b, 0x9b44u, 0xff6eu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x009b46u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x009ab2u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x009b46u:
        {
          if (!match16(b, 0x9b46u, 0x6100u)) return -1;
          if (!match16(b, 0x9b48u, 0xaf78u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x009b4au) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004ac0u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x009b4au:
        {
          if (!match16(b, 0x9b4au, 0x6100u)) return -1;
          if (!match16(b, 0x9b4cu, 0xf89eu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x009b4eu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0093eau;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x009b4eu:
        {
          if (!match16(b, 0x9b4eu, 0x6100u)) return -1;
          if (!match16(b, 0x9b50u, 0xfeaau)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x009b52u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0099fau;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x009b52u:
        {
          if (!match16(b, 0x9b52u, 0x6100u)) return -1;
          if (!match16(b, 0x9b54u, 0x0934u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x009b56u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a488u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x009b56u:
        {
          if (!match16(b, 0x9b56u, 0x1039u)) return -1;
          if (!match32(b, 0x9b58u, 0x00ff0006u)) return -1;
          if (native_bus_read8(b, 0x00ff0006u, &byte_value) != 0) return -3;
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 0x80u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 16u;
          if (!match16(b, 0x9b5cu, 0xc139u)) return -1;
          if(!match32(b,0x9b5eu,0x00ff05c8u))return -1;
          {uint8_t v,r; if(native_bus_read8(b,0x00ff05c8u,&v))return -3; r=v&(uint8_t)c->d[0]; if(native_bus_write8((struct t2bus *)b,0x00ff05c8u,r))return -3; c->sr=(c->sr&0xfff0u)|((r&128u)?8u:0u)|(r==0u?4u:0u);}
          c->cycles+=20u;
          if (!match16(b, 0x9b62u, 0x5279u)) return -1;
          if (!match32(b,0x9b64u,0x00ff03b0u)) return -1;
          { uint16_t dst,src=1u,result; if (native_bus_read16(b,0x00ff03b0u,&dst)!=0) return -3;
            result=(uint16_t)(dst + src);
            if (native_bus_write16((struct t2bus *)b,0x00ff03b0u,result)!=0) return -3;
            uint16_t carry=(uint32_t)dst+src>0xffffu?1u:0u;
            uint16_t overflow=((~(dst^src))&(dst^result)&0x8000u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((result&0x8000u)?8u:0u)|(result==0u?4u:0u)|overflow|carry|(carry?16u:0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0x9b68u, 0x4a79u)) return -1;
          if (!match32(b, 0x9b6au, 0x00ff03b6u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff03b6u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0x9b6eu, 0x6700u)) return -1;
          if (!match16(b, 0x9b70u, 0x0006u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x009b76u : 0x009b72u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x009b72u:
        {
          if (!match16(b, 0x9b72u, 0x6100u)) return -1;
          if (!match16(b, 0x9b74u, 0x0456u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x009b76u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x009fcau;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x009b76u:
        {
          if (!match16(b, 0x9b76u, 0x33fcu)) return -1;
          if (!match16(b, 0x9b78u, 0x0000u) || !match32(b, 0x9b7au, 0x00ff05dcu)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff05dcu, 0x0000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x9b7eu, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x009b80u:
        {
          if (!match16(b, 0x9b80u, 0x33fcu)) return -1;
          if (!match16(b, 0x9b82u, 0x0001u) || !match32(b, 0x9b84u, 0x00ff0150u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0150u, 0x0001u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0001u & 0x8000u) ? 8u : 0u) | (0x0001u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x9b88u, 0x08b9u)) return -1;
          if (!match16(b, 0x9b8au, 0x0005u) || !match32(b, 0x9b8cu, 0x00ff010du)) return -1;
          if (native_bus_read8(b, 0x00ff010du, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 5)) ? 0u : 4u));
          if (native_bus_write8((struct t2bus *)b, 0x00ff010du, (uint8_t)(byte_value & ~(1u << 5))) != 0) return -3;
          c->cycles += 16u;
          if (!match16(b, 0x9b90u, 0x33f9u)) return -1;
          if (!match32(b, 0x9b92u, 0x00ff010cu) || !match32(b, 0x9b96u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x9b9au, 0x23fcu)) return -1;
          if (!match32(b, 0x9b9cu, 0x00009b30u) || !match32(b, 0x9ba0u, 0x00ff0138u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff0138u, 0x00009b30u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=009b9a addr=00ff0138 value=00009b30\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00009b30u & 0x80000000u) ? 8u : 0u) | (0x00009b30u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x9ba4u, 0x08f9u)) return -1;
          { uint8_t v; if(native_bus_read8(b,0x00ff010du,&v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&~4u)|((v&(1u<<5))?0u:4u));
            if(native_bus_write8((struct t2bus *)b,0x00ff010du,(uint8_t)(v|(1u<<5)))!=0)return -3; }
          c->cycles+=20u;
          if (!match16(b, 0x9bacu, 0x33f9u)) return -1;
          if (!match32(b, 0x9baeu, 0x00ff010cu) || !match32(b, 0x9bb2u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x9bb6u, 0x41f9u)) return -1;
          if (!match32(b, 0x9bb8u, 0x000fd472u)) return -1;
          c->a[0] = 0x000fd472u;
          c->cycles += 12u;
          if (!match16(b, 0x9bbcu, 0x6100u)) return -1;
          if (!match16(b, 0x9bbeu, 0xf7eeu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x009bc0u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0093acu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x009bc0u:
        {
          if (!match16(b, 0x9bc0u, 0x6100u)) return -1;
          if (!match16(b, 0x9bc2u, 0x0518u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x009bc4u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a0dau;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x009bc4u:
        {
          if (!match16(b, 0x9bc4u, 0x6100u)) return -1;
          if (!match16(b, 0x9bc6u, 0xc554u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x009bc8u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00611au;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x009bc8u:
        {
          if (!match16(b, 0x9bc8u, 0x08b9u)) return -1;
          if (!match16(b, 0x9bcau, 0x0005u) || !match32(b, 0x9bccu, 0x00ff010du)) return -1;
          if (native_bus_read8(b, 0x00ff010du, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 5)) ? 0u : 4u));
          if (native_bus_write8((struct t2bus *)b, 0x00ff010du, (uint8_t)(byte_value & ~(1u << 5))) != 0) return -3;
          c->cycles += 16u;
          if (!match16(b, 0x9bd0u, 0x33f9u)) return -1;
          if (!match32(b, 0x9bd2u, 0x00ff010cu) || !match32(b, 0x9bd6u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x9bdau, 0x23fcu)) return -1;
          if (!match32(b, 0x9bdcu, 0x50000003u) || !match32(b, 0x9be0u, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0x50000003u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=009bda addr=00c00004 value=50000003\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x50000003u & 0x80000000u) ? 8u : 0u) | (0x50000003u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x9be4u, 0x23fcu)) return -1;
          if (!match32(b, 0x9be6u, 0x00000000u) || !match32(b, 0x9beau, 0x00c00000u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00000u, 0x00000000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=009be4 addr=00c00000 value=00000000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00000000u & 0x80000000u) ? 8u : 0u) | (0x00000000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x9beeu, 0x33fcu)) return -1;
          if (!match16(b, 0x9bf0u, 0x0000u) || !match32(b, 0x9bf2u, 0x00ff0168u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0168u, 0x0000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x9bf6u, 0x33fcu)) return -1;
          if (!match16(b, 0x9bf8u, 0x0000u) || !match32(b, 0x9bfau, 0x00ff016au)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff016au, 0x0000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x9bfeu, 0x6100u)) return -1;
          if (!match16(b, 0x9c00u, 0x20b6u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x009c02u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00bcb6u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x009c02u:
        {
          if (!match16(b, 0x9c02u, 0x2f39u)) return -1;
          if (!match32(b, 0x9c04u, 0x00ff019au)) return -1;
          { uint32_t val; if (native_bus_read32(b, 0x00ff019au, &val) != 0) return -3;
            c->a[7] = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, c->a[7], val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x80000000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 24u;
          if (!match16(b, 0x9c08u, 0x23f9u)) return -1;
          if(!match32(b,0x9c0au,0x00ff019au)||!match32(b,0x9c0eu,0x00ff03b2u))return -1;
          {uint32_t v;if(native_bus_read32(b,0x00ff019au,&v)!=0)return -3;
           if(native_bus_write32((struct t2bus *)b,0x00ff03b2u,v)!=0)return -3;
           c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=36u;
          if (!match16(b, 0x9c12u, 0x06b9u)) return -1;
          if(!match32(b,0x9c14u,0x00000400u)||!match32(b,0x9c18u,0x00ff019au))return -1;
          {uint32_t old,r;uint64_t wide;
           if(native_bus_read32(b,0x00ff019au,&old)!=0)return -3;
           wide=(uint64_t)old+0x00000400u;r=(uint32_t)wide;
           if(native_bus_write32((struct t2bus *)b,0x00ff019au,r)!=0)return -3;
           c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x80000000u)?8u:0u)|(r==0u?4u:0u)|((~(old^0x00000400u)&(r^old)&0x80000000u)?2u:0u)|((wide>>32)?17u:0u)); }
          c->cycles+=28u;
          if (!match16(b, 0x9c1cu, 0x33fcu)) return -1;
          if (!match16(b, 0x9c1eu, 0x0004u) || !match32(b, 0x9c20u, 0x00ff03bau)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff03bau, 0x0004u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0004u & 0x8000u) ? 8u : 0u) | (0x0004u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0x9c24u, 0x6100u)) return -1;
          if (!match16(b, 0x9c26u, 0x4502u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x009c28u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00e128u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x009c28u:
        {
          if (!match16(b, 0x9c28u, 0x08f9u)) return -1;
          { uint8_t v; if(native_bus_read8(b,0x00ff010du,&v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&~4u)|((v&(1u<<5))?0u:4u));
            if(native_bus_write8((struct t2bus *)b,0x00ff010du,(uint8_t)(v|(1u<<5)))!=0)return -3; }
          c->cycles+=20u;
          if (!match16(b, 0x9c30u, 0x33f9u)) return -1;
          if (!match32(b, 0x9c32u, 0x00ff010cu) || !match32(b, 0x9c36u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x9c3au, 0x6100u)) return -1;
          if (!match16(b, 0x9c3cu, 0x06b2u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x009c3eu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a2eeu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x009c3eu:
        {
          if (!match16(b, 0x9c3eu, 0x6100u)) return -1;
          if (!match16(b, 0x9c40u, 0x08b8u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x009c42u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a4f8u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x009c42u:
        {
          if (!match16(b, 0x9c42u, 0x41f9u)) return -1;
          if (!match32(b, 0x9c44u, 0x000ac800u)) return -1;
          c->a[0] = 0x000ac800u;
          c->cycles += 12u;
          if (!match16(b, 0x9c48u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x9c4au, 0x6100u)) return -1;
          if (!match16(b, 0x9c4cu, 0x1c38u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x009c4eu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00b884u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x009c4eu:
        {
          if (!match16(b, 0x9c4eu, 0x41f9u)) return -1;
          if (!match32(b, 0x9c50u, 0x000ac820u)) return -1;
          c->a[0] = 0x000ac820u;
          c->cycles += 12u;
          if (!match16(b, 0x9c54u, 0x7001u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(1);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x9c56u, 0x6100u)) return -1;
          if (!match16(b, 0x9c58u, 0x1c2cu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x009c5au) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00b884u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x009c5au:
        {
          if (!match16(b, 0x9c5au, 0x41f9u)) return -1;
          if (!match32(b, 0x9c5cu, 0x000ac840u)) return -1;
          c->a[0] = 0x000ac840u;
          c->cycles += 12u;
          if (!match16(b, 0x9c60u, 0x7002u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(2);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x9c62u, 0x6100u)) return -1;
          if (!match16(b, 0x9c64u, 0x1c20u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x009c66u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00b884u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x009c66u:
        {
          if (!match16(b, 0x9c66u, 0x41f9u)) return -1;
          if (!match32(b, 0x9c68u, 0x000ac860u)) return -1;
          c->a[0] = 0x000ac860u;
          c->cycles += 12u;
          if (!match16(b, 0x9c6cu, 0x7003u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(3);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x9c6eu, 0x6100u)) return -1;
          if (!match16(b, 0x9c70u, 0x1c14u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x009c72u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00b884u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x009c72u:
        {
          if (!match16(b, 0x9c72u, 0x08b9u)) return -1;
          if (!match16(b, 0x9c74u, 0x0005u) || !match32(b, 0x9c76u, 0x00ff010du)) return -1;
          if (native_bus_read8(b, 0x00ff010du, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 5)) ? 0u : 4u));
          if (native_bus_write8((struct t2bus *)b, 0x00ff010du, (uint8_t)(byte_value & ~(1u << 5))) != 0) return -3;
          c->cycles += 16u;
          if (!match16(b, 0x9c7au, 0x33f9u)) return -1;
          if (!match32(b, 0x9c7cu, 0x00ff010cu) || !match32(b, 0x9c80u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0x9c84u, 0x41f9u)) return -1;
          if (!match32(b, 0x9c86u, 0x000a9092u)) return -1;
          c->a[0] = 0x000a9092u;
          c->cycles += 12u;
          if (!match16(b, 0x9c8au, 0x2628u)) return -1;
          if(!match16(b,0x9c8cu,0x0004u))return -1;
          {uint32_t v,addr=(c->a[0]+(int16_t)0x0004u)&0xffffffu; if(native_bus_read32(b,addr,&v))return -3; c->d[3]=v; c->sr=(c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=16u;
          if (!match16(b, 0x9c8eu, 0x2279u)) return -1;
          if (!match32(b, 0x9c90u, 0x00ff019au)) return -1;
          if (native_bus_read32(b, 0x00ff019au, &c->a[1]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0x9c94u, 0x6100u)) return -1;
          if (!match16(b, 0x9c96u, 0x42c8u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x009c98u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00df5eu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x009c98u:
        {
          if (!match16(b, 0x9c98u, 0x23fcu)) return -1;
          if (!match32(b, 0x9c9au, 0x48800000u) || !match32(b, 0x9c9eu, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0x48800000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=009c98 addr=00c00004 value=48800000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x48800000u & 0x80000000u) ? 8u : 0u) | (0x48800000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x9ca2u, 0x2079u)) return -1;
          if (!match32(b, 0x9ca4u, 0x00ff019au)) return -1;
          if (native_bus_read32(b, 0x00ff019au, &c->a[0]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0x9ca8u, 0x3003u)) return -1;
          { uint16_t v=(uint16_t)c->d[3]; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0x9caau, 0xe440u)) return -1;
          {uint16_t x=(uint16_t)c->d[0],r=(uint16_t)((int16_t)x>>2),carry=(x>>1)&1u;c->d[0]=(c->d[0]&0xffff0000u)|r;c->sr=(c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(carry?17u:0u);}
          c->cycles+=10u;
          if (!match16(b, 0x9cacu, 0x5340u)) return -1;
          {uint32_t dst=c->d[0]&65535u,src=1u,r=(dst-src)&65535u;
           c->d[0]=(c->d[0]&0xffff0000u)|r;
           uint16_t cy=(dst<src),ov=((dst^src)&(dst^r)&32768u)!=0u;
           c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(cy?17u:0u));}
          c->cycles+=4u;
          if (!match16(b, 0x9caeu, 0x6100u)) return -1;
          if (!match16(b, 0x9cb0u, 0xad50u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x009cb2u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004a00u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x009cb2u:
        {
          if (!match16(b, 0x9cb2u, 0x41f9u)) return -1;
          if (!match32(b, 0x9cb4u, 0x000a967cu)) return -1;
          c->a[0] = 0x000a967cu;
          c->cycles += 12u;
          if (!match16(b, 0x9cb8u, 0x2828u)) return -1;
          if(!match16(b,0x9cbau,0x0004u))return -1;
          {uint32_t v,addr=(c->a[0]+(int16_t)0x0004u)&0xffffffu; if(native_bus_read32(b,addr,&v))return -3; c->d[4]=v; c->sr=(c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=16u;
          if (!match16(b, 0x9cbcu, 0x2279u)) return -1;
          if (!match32(b, 0x9cbeu, 0x00ff019au)) return -1;
          if (native_bus_read32(b, 0x00ff019au, &c->a[1]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0x9cc2u, 0x6100u)) return -1;
          if (!match16(b, 0x9cc4u, 0x429au)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x009cc6u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00df5eu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x009cc6u:
        {
          if (!match16(b, 0x9cc6u, 0x23fcu)) return -1;
          if (!match32(b, 0x9cc8u, 0x40000000u) || !match32(b, 0x9cccu, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0x40000000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=009cc6 addr=00c00004 value=40000000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x40000000u & 0x80000000u) ? 8u : 0u) | (0x40000000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x9cd0u, 0x2079u)) return -1;
          if (!match32(b, 0x9cd2u, 0x00ff019au)) return -1;
          if (native_bus_read32(b, 0x00ff019au, &c->a[0]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0x9cd6u, 0x3004u)) return -1;
          { uint16_t v=(uint16_t)c->d[4]; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0x9cd8u, 0xe440u)) return -1;
          {uint16_t x=(uint16_t)c->d[0],r=(uint16_t)((int16_t)x>>2),carry=(x>>1)&1u;c->d[0]=(c->d[0]&0xffff0000u)|r;c->sr=(c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(carry?17u:0u);}
          c->cycles+=10u;
          if (!match16(b, 0x9cdau, 0x5340u)) return -1;
          {uint32_t dst=c->d[0]&65535u,src=1u,r=(dst-src)&65535u;
           c->d[0]=(c->d[0]&0xffff0000u)|r;
           uint16_t cy=(dst<src),ov=((dst^src)&(dst^r)&32768u)!=0u;
           c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(cy?17u:0u));}
          c->cycles+=4u;
          if (!match16(b, 0x9cdcu, 0x6100u)) return -1;
          if (!match16(b, 0x9cdeu, 0xad22u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x009ce0u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004a00u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x009ce0u:
        {
          if (!match16(b, 0x9ce0u, 0x41f9u)) return -1;
          if (!match32(b, 0x9ce2u, 0x000aabfcu)) return -1;
          c->a[0] = 0x000aabfcu;
          c->cycles += 12u;
          if (!match16(b, 0x9ce6u, 0x2828u)) return -1;
          if(!match16(b,0x9ce8u,0x0004u))return -1;
          {uint32_t v,addr=(c->a[0]+(int16_t)0x0004u)&0xffffffu; if(native_bus_read32(b,addr,&v))return -3; c->d[4]=v; c->sr=(c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=16u;
          if (!match16(b, 0x9ceau, 0x2279u)) return -1;
          if (!match32(b, 0x9cecu, 0x00ff019au)) return -1;
          if (native_bus_read32(b, 0x00ff019au, &c->a[1]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0x9cf0u, 0x6100u)) return -1;
          if (!match16(b, 0x9cf2u, 0x426cu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x009cf4u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00df5eu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x009cf4u:
        {
          if (!match16(b, 0x9cf4u, 0x363cu)) return -1;
          if (!match16(b, 0x9cf6u, 0x6000u)) return -1;
          c->d[3] = (c->d[3] & 0xffff0000u) | 0x6000u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x6000u & 0x8000u) ? 8u : 0u) | (0x6000u == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x9cf8u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x9cfau, 0x3003u)) return -1;
          { uint16_t v=(uint16_t)c->d[3]; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0x9cfcu, 0xe588u)) return -1;
          { uint32_t x=c->d[0],r=x<<2;
            uint16_t carry=(uint16_t)((x>>30)&1u);
            c->d[0]=r;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x80000000u)?8u:0u)|(r==0u?4u:0u)|(carry?17u:0u));
          }
          c->cycles+=12u;
          if (!match16(b, 0x9cfeu, 0x3003u)) return -1;
          { uint16_t v=(uint16_t)c->d[3]; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0x9d00u, 0x0240u)) return -1;
          if (!match16(b, 0x9d02u, 0x3ffeu)) return -1;
          { uint16_t v=(uint16_t)c->d[0] & 0x3ffeu; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x9d04u, 0x0040u)) return -1;
          if(!match16(b,0x9d06u,0x4000u))return -1;
          {uint16_t v=(uint16_t)(c->d[0]|0x4000u);
           c->d[0]=(c->d[0]&0xffff0000u)|v;
           c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=8u;
          if (!match16(b, 0x9d08u, 0x4840u)) return -1;
          c->d[0]=(c->d[0]<<16)|(c->d[0]>>16);
          c->sr=(uint16_t)((c->sr&0xfff0u)|((c->d[0]&0x80000000u)?8u:0u)|(c->d[0]==0u?4u:0u));
          c->cycles+=4u;
          if (!match16(b, 0x9d0au, 0x23c0u)) return -1;
          { uint32_t v=c->d[0]; if(native_bus_write32((struct t2bus *)b,0x00c00004u,v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=20u;
          if (!match16(b, 0x9d10u, 0x2079u)) return -1;
          if (!match32(b, 0x9d12u, 0x00ff019au)) return -1;
          if (native_bus_read32(b, 0x00ff019au, &c->a[0]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0x9d16u, 0x3004u)) return -1;
          { uint16_t v=(uint16_t)c->d[4]; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0x9d18u, 0xe440u)) return -1;
          {uint16_t x=(uint16_t)c->d[0],r=(uint16_t)((int16_t)x>>2),carry=(x>>1)&1u;c->d[0]=(c->d[0]&0xffff0000u)|r;c->sr=(c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(carry?17u:0u);}
          c->cycles+=10u;
          if (!match16(b, 0x9d1au, 0x5340u)) return -1;
          {uint32_t dst=c->d[0]&65535u,src=1u,r=(dst-src)&65535u;
           c->d[0]=(c->d[0]&0xffff0000u)|r;
           uint16_t cy=(dst<src),ov=((dst^src)&(dst^r)&32768u)!=0u;
           c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(cy?17u:0u));}
          c->cycles+=4u;
          if (!match16(b, 0x9d1cu, 0x6100u)) return -1;
          if (!match16(b, 0x9d1eu, 0xace2u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x009d20u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004a00u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x009d20u:
        {
          if (!match16(b, 0x9d20u, 0xea4bu)) return -1;
          { uint16_t old=(uint16_t)c->d[3],r=(uint16_t)(old>>5);
            uint16_t carry=(old>>4)&1u;
            c->d[3]=(c->d[3]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xffe0u)|(r==0u?4u:0u)|(carry?17u:0u));
            c->cycles+=16u;
          }
          if (!match16(b, 0x9d22u, 0x33c3u)) return -1;
          if (!match32(b, 0x9d24u, 0x00ff05ccu)) return -1;
          { uint16_t v=(uint16_t)c->d[3];
            if (native_bus_write16((struct t2bus *)b,0x00ff05ccu,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x9d28u, 0x23fcu)) return -1;
          if (!match32(b, 0x9d2au, 0x50000003u) || !match32(b, 0x9d2eu, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0x50000003u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=009d28 addr=00c00004 value=50000003\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x50000003u & 0x80000000u) ? 8u : 0u) | (0x50000003u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x9d32u, 0x23fcu)) return -1;
          if (!match32(b, 0x9d34u, 0x01480501u) || !match32(b, 0x9d38u, 0x00c00000u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00000u, 0x01480501u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=009d32 addr=00c00000 value=01480501\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x01480501u & 0x80000000u) ? 8u : 0u) | (0x01480501u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x9d3cu, 0x23fcu)) return -1;
          if (!match32(b, 0x9d3eu, 0x27fc0138u) || !match32(b, 0x9d42u, 0x00c00000u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00000u, 0x27fc0138u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=009d3c addr=00c00000 value=27fc0138\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x27fc0138u & 0x80000000u) ? 8u : 0u) | (0x27fc0138u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x9d46u, 0x23fcu)) return -1;
          if (!match32(b, 0x9d48u, 0x00000000u) || !match32(b, 0x9d4cu, 0x00c00000u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00000u, 0x00000000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=009d46 addr=00c00000 value=00000000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00000000u & 0x80000000u) ? 8u : 0u) | (0x00000000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x9d50u, 0x23fcu)) return -1;
          if (!match32(b, 0x9d52u, 0x7f800003u) || !match32(b, 0x9d56u, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0x7f800003u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=009d50 addr=00c00004 value=7f800003\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x7f800003u & 0x80000000u) ? 8u : 0u) | (0x7f800003u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0x9d5au, 0x41f9u)) return -1;
          if (!match32(b, 0x9d5cu, 0x000acb72u)) return -1;
          c->a[0] = 0x000acb72u;
          c->cycles += 12u;
          if (!match16(b, 0x9d60u, 0x701fu)) return -1;
          c->d[0] = (uint32_t)(int32_t)(31);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x9d62u, 0x6100u)) return -1;
          if (!match16(b, 0x9d64u, 0xac9cu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x009d66u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004a00u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x009d66u:
        {
          if (!match16(b, 0x9d66u, 0x08b9u)) return -1;
          if (!match16(b, 0x9d68u, 0x0007u) || !match32(b, 0x9d6au, 0x00ff05c8u)) return -1;
          if (native_bus_read8(b, 0x00ff05c8u, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 7)) ? 0u : 4u));
          if (native_bus_write8((struct t2bus *)b, 0x00ff05c8u, (uint8_t)(byte_value & ~(1u << 7))) != 0) return -3;
          c->cycles += 16u;
          if (!match16(b, 0x9d6eu, 0x207cu)) return -1;
          if (!match32(b, 0x9d70u, 0x000a8a90u)) return -1;
          c->a[0] = 0x000a8a90u;
          c->cycles += 12u;
          if (!match16(b, 0x9d74u, 0x2279u)) return -1;
          if (!match32(b, 0x9d76u, 0x00ff019au)) return -1;
          if (native_bus_read32(b, 0x00ff019au, &c->a[1]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0x9d7au, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x9d7cu, 0x72ffu)) return -1;
          c->d[1] = (uint32_t)(int32_t)(-1);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x9d7eu, 0x6100u)) return -1;
          if (!match16(b, 0x9d80u, 0x04e4u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x009d82u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a264u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x009d82u:
        {
          if (!match16(b, 0x9d82u, 0x6100u)) return -1;
          if (!match16(b, 0x9d84u, 0x0528u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x009d86u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a2acu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x009d86u:
        {
          if (!match16(b, 0x9d86u, 0x303cu)) return -1;
          if (!match16(b, 0x9d88u, 0xe000u)) return -1;
          c->d[0] = (c->d[0] & 0xffff0000u) | 0xe000u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xe000u & 0x8000u) ? 8u : 0u) | (0xe000u == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x9d8au, 0x2079u)) return -1;
          if (!match32(b, 0x9d8cu, 0x00ff019au)) return -1;
          if (native_bus_read32(b, 0x00ff019au, &c->a[0]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0x9d90u, 0xd0fcu)) return -1;
          c->a[0]=(c->a[0]+(int16_t)0x1000u)&0xffffffu;
          c->cycles+=8u;
          if (!match16(b, 0x9d94u, 0x3239u)) return -1;
          if (!match32(b, 0x9d96u, 0x00ff05ccu)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff05ccu, &val) != 0) return -3;
            c->d[1] = (c->d[1] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x9d9au, 0x6100u)) return -1;
          if (!match16(b, 0x9d9cu, 0x039cu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x009d9eu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a138u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x009d9eu:
        {
          if (!match16(b, 0x9d9eu, 0x207cu)) return -1;
          if (!match32(b, 0x9da0u, 0x000a7e90u)) return -1;
          c->a[0] = 0x000a7e90u;
          c->cycles += 12u;
          c->pc = 0x009da4u;
          return 0;
        }
      case 0x009fcau:
        {
          if (!match16(b, 0x9fcau, 0x2079u)) return -1;
          if (!match32(b, 0x9fccu, 0x00ff03b2u)) return -1;
          if (native_bus_read32(b, 0x00ff03b2u, &c->a[0]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0x9fd0u, 0x43f9u)) return -1;
          if (!match32(b, 0x9fd2u, 0x0000a0a0u)) return -1;
          c->a[1] = 0x0000a0a0u;
          c->cycles += 12u;
          if (!match16(b, 0x9fd6u, 0x3c39u)) return -1;
          if (!match32(b, 0x9fd8u, 0x00ff03b8u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff03b8u, &val) != 0) return -3;
            c->d[6] = (c->d[6] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0x9fdcu, 0x92c6u)) return -1;
          c->a[1]=(c->a[1]-(int32_t)(int16_t)c->d[6])&0xffffffu;
          c->cycles+=8u;
          if (!match16(b, 0x9fdeu, 0x92c6u)) return -1;
          c->a[1]=(c->a[1]-(int32_t)(int16_t)c->d[6])&0xffffffu;
          c->cycles+=8u;
          if (!match16(b, 0x9fe0u, 0x3e3cu)) return -1;
          if (!match16(b, 0x9fe2u, 0x00ffu)) return -1;
          c->d[7] = (c->d[7] & 0xffff0000u) | 0x00ffu;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00ffu & 0x8000u) ? 8u : 0u) | (0x00ffu == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x9fe4u, 0x30fcu)) return -1;
          if(native_bus_write16((struct t2bus *)b,c->a[0],0x0000u))return -3;
          c->a[0]=(c->a[0]+2u)&0xffffffu;
          c->sr=(c->sr&0xfff0u)|0u|4u;
          c->cycles+=12u;
          c->pc = 0x009fe8u;
          return 0;
        }
      case 0x00a0dau:
        {
          if (!match16(b, 0xa0dau, 0x4a79u)) return -1;
          if (!match32(b, 0xa0dcu, 0x00ff0218u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff0218u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0xa0e0u, 0x66f8u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x00a0dau : 0x00a0e2u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00a0e2u:
        {
          if (!match16(b, 0xa0e2u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00a0e4u:
        {
          if (!match16(b, 0xa0e4u, 0x4a79u)) return -1;
          if (!match32(b, 0xa0e6u, 0x00ff0222u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff0222u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0xa0eau, 0x66f8u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x00a0e4u : 0x00a0ecu;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00a0ecu:
        {
          if (!match16(b, 0xa0ecu, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00a11eu:
        {
          if (!match16(b, 0xa11eu, 0x6100u)) return -1;
          if (!match16(b, 0xa120u, 0x0008u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00a122u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a128u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00a122u:
        {
          if (!match16(b, 0xa122u, 0x51c8u)) return -1;
          { uint16_t count = (uint16_t)(c->d[0] - 1u);
            c->d[0] = (c->d[0] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00a11eu : 0x00a126u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00a126u:
        {
          if (!match16(b, 0xa126u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00a128u:
        {
          if (!match16(b, 0xa128u, 0x3239u)) return -1;
          if (!match32(b, 0xa12au, 0x00ff03b0u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff03b0u, &val) != 0) return -3;
            c->d[1] = (c->d[1] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0xa12eu, 0xb279u)) return -1;
          { uint16_t v; if(native_bus_read16(b,0x00ff03b0u,&v)!=0)return -3;
            uint32_t x=(c->d[1]&65535u),y=v,r=(x-y)&65535u;
            uint16_t carry=x<y;
            uint16_t ov=((x^y)&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?1u:0u));
          }
          c->cycles+=16u;
          if (!match16(b, 0xa134u, 0x67f8u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x00a12eu : 0x00a136u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00a12eu:
        {
          if (!match16(b, 0xa12eu, 0xb279u)) return -1;
          { uint16_t v; if(native_bus_read16(b,0x00ff03b0u,&v)!=0)return -3;
            uint32_t x=(c->d[1]&65535u),y=v,r=(x-y)&65535u;
            uint16_t carry=x<y;
            uint16_t ov=((x^y)&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?1u:0u));
          }
          c->cycles+=16u;
          if (!match16(b, 0xa134u, 0x67f8u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x00a12eu : 0x00a136u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00a136u:
        {
          if (!match16(b, 0xa136u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00a138u:
        {
          if (!match16(b, 0xa138u, 0x781fu)) return -1;
          c->d[4] = (uint32_t)(int32_t)(31);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[4] & 0x80000000u) ? 8u : 0u) | (c->d[4] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xa13au, 0x7a1bu)) return -1;
          c->d[5] = (uint32_t)(int32_t)(27);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[5] & 0x80000000u) ? 8u : 0u) | (c->d[5] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xa13cu, 0x6100u)) return -1;
          if (!match16(b, 0xa13eu, 0x0004u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00a140u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a142u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00a140u:
        {
          if (!match16(b, 0xa140u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00a142u:
        {
          if (!match16(b, 0xa142u, 0x3400u)) return -1;
          { uint16_t v=(uint16_t)c->d[0]; c->d[2]=(c->d[2] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0xa144u, 0x3604u)) return -1;
          { uint16_t v=(uint16_t)c->d[4]; c->d[3]=(c->d[3] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0xa146u, 0x5243u)) return -1;
          { uint16_t dst=(uint16_t)c->d[3],r=(uint16_t)(dst+1u);
            c->d[3]=(c->d[3]&0xffff0000u)|r;
            uint16_t carry=(dst==0xffffu)?1u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u)|(dst==0x7fffu?2u:0u)|carry|(carry?16u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0xa148u, 0xd643u)) return -1;
          { uint32_t x = c->d[3] & 65535u, y = c->d[3] & 65535u, r = (x+y) & 65535u;
            uint16_t flags = (uint16_t)(((r & 0x8000u) ? 8u : 0u) | ((r == 0u) ? 4u : 0u) | (((~(x ^ y) & (r ^ y)) & 0x8000u) ? 2u : 0u) | ((x+y > 65535u) ? 17u : 0u));
            c->d[3] = (c->d[3] & 0xffff0000u) | r;
            c->sr = (uint16_t)((c->sr & 0xffe0u) | flags);
          }
          c->cycles += 4u;
          if (!match16(b, 0xa14au, 0x4443u)) return -1;
          { uint32_t x=c->d[3]&65535u,r=(-x)&65535u;
            c->d[3]=(c->d[3]&0xffff0000u)|r;
            uint16_t carry=x!=0u?1u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(x==32768u?2u:0u)|carry|(carry?16u:0u)); }
          c->cycles+=4u;
          if (!match16(b, 0xa14cu, 0x0643u)) return -1;
          { uint32_t x=c->d[3]&65535u,y=0x0040u,r=(x+y)&65535u;
            c->d[3]=(c->d[3]&0xffff0000u)|r;
            uint16_t carry=(x+y)>65535u,ov=((~(x^y))&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?17u:0u));
          }
          c->cycles+=8u;
          if (!match16(b, 0xa150u, 0x08b9u)) return -1;
          if (!match16(b, 0xa152u, 0x0005u) || !match32(b, 0xa154u, 0x00ff010du)) return -1;
          if (native_bus_read8(b, 0x00ff010du, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 5)) ? 0u : 4u));
          if (native_bus_write8((struct t2bus *)b, 0x00ff010du, (uint8_t)(byte_value & ~(1u << 5))) != 0) return -3;
          c->cycles += 16u;
          if (!match16(b, 0xa158u, 0x56f9u)) return -1;
          if (!match32(b, 0xa15au, 0x00ff0008u)) return -1;
          if (native_bus_write8((struct t2bus *)b, 0x00ff0008u, (c->sr & 4u) ? 0u : 0xffu) != 0) return -3;
          c->cycles += 16u;
          if (!match16(b, 0xa15eu, 0x33f9u)) return -1;
          if (!match32(b, 0xa160u, 0x00ff010cu) || !match32(b, 0xa164u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0xa168u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xa16au, 0x3002u)) return -1;
          { uint16_t v=(uint16_t)c->d[2]; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0xa16cu, 0xe588u)) return -1;
          { uint32_t x=c->d[0],r=x<<2;
            uint16_t carry=(uint16_t)((x>>30)&1u);
            c->d[0]=r;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x80000000u)?8u:0u)|(r==0u?4u:0u)|(carry?17u:0u));
          }
          c->cycles+=12u;
          if (!match16(b, 0xa16eu, 0x3002u)) return -1;
          { uint16_t v=(uint16_t)c->d[2]; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0xa170u, 0x0240u)) return -1;
          if (!match16(b, 0xa172u, 0x3ffeu)) return -1;
          { uint16_t v=(uint16_t)c->d[0] & 0x3ffeu; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0xa174u, 0x0040u)) return -1;
          if(!match16(b,0xa176u,0x4000u))return -1;
          {uint16_t v=(uint16_t)(c->d[0]|0x4000u);
           c->d[0]=(c->d[0]&0xffff0000u)|v;
           c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=8u;
          if (!match16(b, 0xa178u, 0x4840u)) return -1;
          c->d[0]=(c->d[0]<<16)|(c->d[0]>>16);
          c->sr=(uint16_t)((c->sr&0xfff0u)|((c->d[0]&0x80000000u)?8u:0u)|(c->d[0]==0u?4u:0u));
          c->cycles+=4u;
          if (!match16(b, 0xa17au, 0x23c0u)) return -1;
          { uint32_t v=c->d[0]; if(native_bus_write32((struct t2bus *)b,0x00c00004u,v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=20u;
          if (!match16(b, 0xa180u, 0x3c04u)) return -1;
          { uint16_t v=(uint16_t)c->d[4]; c->d[6]=(c->d[6] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0xa182u, 0x3018u)) return -1;
          { uint16_t v; if(native_bus_read16(b,c->a[0],&v)!=0) return -3;
            c->a[0]=(c->a[0]+2u)&0xffffffu;
            c->d[0]=(c->d[0]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=8u;
          if (!match16(b, 0xa184u, 0x8041u)) return -1;
          { uint16_t x=(uint16_t)c->d[1], y=(uint16_t)c->d[0],r=(uint16_t)(x | y);
            c->d[1]=(c->d[1]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0xa186u, 0x33c0u)) return -1;
          if (!match32(b, 0xa188u, 0x00c00000u)) return -1;
          { uint16_t v=(uint16_t)c->d[0];
            if (native_bus_write16((struct t2bus *)b,0x00c00000u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0xa18cu, 0x51ceu)) return -1;
          { uint16_t count = (uint16_t)(c->d[6] - 1u);
            c->d[6] = (c->d[6] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00a182u : 0x00a190u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00a168u:
        {
          if (!match16(b, 0xa168u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xa16au, 0x3002u)) return -1;
          { uint16_t v=(uint16_t)c->d[2]; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0xa16cu, 0xe588u)) return -1;
          { uint32_t x=c->d[0],r=x<<2;
            uint16_t carry=(uint16_t)((x>>30)&1u);
            c->d[0]=r;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x80000000u)?8u:0u)|(r==0u?4u:0u)|(carry?17u:0u));
          }
          c->cycles+=12u;
          if (!match16(b, 0xa16eu, 0x3002u)) return -1;
          { uint16_t v=(uint16_t)c->d[2]; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0xa170u, 0x0240u)) return -1;
          if (!match16(b, 0xa172u, 0x3ffeu)) return -1;
          { uint16_t v=(uint16_t)c->d[0] & 0x3ffeu; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0xa174u, 0x0040u)) return -1;
          if(!match16(b,0xa176u,0x4000u))return -1;
          {uint16_t v=(uint16_t)(c->d[0]|0x4000u);
           c->d[0]=(c->d[0]&0xffff0000u)|v;
           c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=8u;
          if (!match16(b, 0xa178u, 0x4840u)) return -1;
          c->d[0]=(c->d[0]<<16)|(c->d[0]>>16);
          c->sr=(uint16_t)((c->sr&0xfff0u)|((c->d[0]&0x80000000u)?8u:0u)|(c->d[0]==0u?4u:0u));
          c->cycles+=4u;
          if (!match16(b, 0xa17au, 0x23c0u)) return -1;
          { uint32_t v=c->d[0]; if(native_bus_write32((struct t2bus *)b,0x00c00004u,v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=20u;
          if (!match16(b, 0xa180u, 0x3c04u)) return -1;
          { uint16_t v=(uint16_t)c->d[4]; c->d[6]=(c->d[6] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0xa182u, 0x3018u)) return -1;
          { uint16_t v; if(native_bus_read16(b,c->a[0],&v)!=0) return -3;
            c->a[0]=(c->a[0]+2u)&0xffffffu;
            c->d[0]=(c->d[0]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=8u;
          if (!match16(b, 0xa184u, 0x8041u)) return -1;
          { uint16_t x=(uint16_t)c->d[1], y=(uint16_t)c->d[0],r=(uint16_t)(x | y);
            c->d[1]=(c->d[1]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0xa186u, 0x33c0u)) return -1;
          if (!match32(b, 0xa188u, 0x00c00000u)) return -1;
          { uint16_t v=(uint16_t)c->d[0];
            if (native_bus_write16((struct t2bus *)b,0x00c00000u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0xa18cu, 0x51ceu)) return -1;
          { uint16_t count = (uint16_t)(c->d[6] - 1u);
            c->d[6] = (c->d[6] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00a182u : 0x00a190u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00a182u:
        {
          if (!match16(b, 0xa182u, 0x3018u)) return -1;
          { uint16_t v; if(native_bus_read16(b,c->a[0],&v)!=0) return -3;
            c->a[0]=(c->a[0]+2u)&0xffffffu;
            c->d[0]=(c->d[0]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=8u;
          if (!match16(b, 0xa184u, 0x8041u)) return -1;
          { uint16_t x=(uint16_t)c->d[1], y=(uint16_t)c->d[0],r=(uint16_t)(x | y);
            c->d[1]=(c->d[1]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0xa186u, 0x33c0u)) return -1;
          if (!match32(b, 0xa188u, 0x00c00000u)) return -1;
          { uint16_t v=(uint16_t)c->d[0];
            if (native_bus_write16((struct t2bus *)b,0x00c00000u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0xa18cu, 0x51ceu)) return -1;
          { uint16_t count = (uint16_t)(c->d[6] - 1u);
            c->d[6] = (c->d[6] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00a182u : 0x00a190u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00a190u:
        {
          if (!match16(b, 0xa190u, 0x0642u)) return -1;
          { uint32_t x=c->d[2]&65535u,y=0x0080u,r=(x+y)&65535u;
            c->d[2]=(c->d[2]&0xffff0000u)|r;
            uint16_t carry=(x+y)>65535u,ov=((~(x^y))&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?17u:0u));
          }
          c->cycles+=8u;
          if (!match16(b, 0xa194u, 0xd0c3u)) return -1;
          c->a[0]=(c->a[0]+(int16_t)(c->d[3]&65535u))&0xffffffu;
          c->cycles+=8u;
          if (!match16(b, 0xa196u, 0x51cdu)) return -1;
          { uint16_t count = (uint16_t)(c->d[5] - 1u);
            c->d[5] = (c->d[5] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00a168u : 0x00a19au;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00a19au:
        {
          if (!match16(b, 0xa19au, 0x4a39u)) return -1;
          if (!match32(b, 0xa19cu, 0x00ff0008u)) return -1;
          { uint8_t value;
            if (native_bus_read8(b, 0x00ff0008u, &value) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((value & 0x80u) ? 8u : 0u) | (value == 0u ? 4u : 0u));
          }
          c->cycles += 12u;
          if (!match16(b, 0xa1a0u, 0x6700u)) return -1;
          if (!match16(b, 0xa1a2u, 0x0014u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x00a1b6u : 0x00a1a4u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00a1a4u:
        {
          if (!match16(b, 0xa1a4u, 0x08f9u)) return -1;
          { uint8_t v; if(native_bus_read8(b,0x00ff010du,&v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&~4u)|((v&(1u<<5))?0u:4u));
            if(native_bus_write8((struct t2bus *)b,0x00ff010du,(uint8_t)(v|(1u<<5)))!=0)return -3; }
          c->cycles+=20u;
          if (!match16(b, 0xa1acu, 0x33f9u)) return -1;
          if (!match32(b, 0xa1aeu, 0x00ff010cu) || !match32(b, 0xa1b2u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0xa1b6u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00a1b6u:
        {
          if (!match16(b, 0xa1b6u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00a264u:
        {
          if (!match16(b, 0xa264u, 0x7e0fu)) return -1;
          c->d[7] = (uint32_t)(int32_t)(15);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[7] & 0x80000000u) ? 8u : 0u) | (c->d[7] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xa266u, 0x7c0fu)) return -1;
          c->d[6] = (uint32_t)(int32_t)(15);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[6] & 0x80000000u) ? 8u : 0u) | (c->d[6] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xa268u, 0x3418u)) return -1;
          { uint16_t v; if(native_bus_read16(b,c->a[0],&v)!=0) return -3;
            c->a[0]=(c->a[0]+2u)&0xffffffu;
            c->d[2]=(c->d[2]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=8u;
          if (!match16(b, 0xa26au, 0xc441u)) return -1;
          { uint16_t x=(uint16_t)c->d[1], y=(uint16_t)c->d[2],r=(uint16_t)(x & y);
            c->d[1]=(c->d[1]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0xa26cu, 0xd440u)) return -1;
          { uint32_t x = c->d[0] & 65535u, y = c->d[2] & 65535u, r = (x+y) & 65535u;
            uint16_t flags = (uint16_t)(((r & 0x8000u) ? 8u : 0u) | ((r == 0u) ? 4u : 0u) | (((~(x ^ y) & (r ^ y)) & 0x8000u) ? 2u : 0u) | ((x+y > 65535u) ? 17u : 0u));
            c->d[2] = (c->d[2] & 0xffff0000u) | r;
            c->sr = (uint16_t)((c->sr & 0xffe0u) | flags);
          }
          c->cycles += 4u;
          if (!match16(b, 0xa26eu, 0x45f9u)) return -1;
          if (!match32(b, 0xa270u, 0x0000bb7au)) return -1;
          c->a[2] = 0x0000bb7au;
          c->cycles += 12u;
          if (!match16(b, 0xa274u, 0x0802u)) return -1;
          c->sr=(uint16_t)((c->sr&~4u)|((c->d[2]&(1u<<12))?0u:4u));
          c->cycles+=10u;
          if (!match16(b, 0xa278u, 0x6700u)) return -1;
          if (!match16(b, 0xa27au, 0x0006u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x00a280u : 0x00a27cu;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00a27cu:
        {
          if (!match16(b, 0xa27cu, 0xd4fcu)) return -1;
          c->a[2]=(c->a[2]+(int16_t)0x0010u)&0xffffffu;
          c->cycles+=8u;
          if (!match16(b, 0xa280u, 0x0802u)) return -1;
          c->sr=(uint16_t)((c->sr&~4u)|((c->d[2]&(1u<<11))?0u:4u));
          c->cycles+=10u;
          if (!match16(b, 0xa284u, 0x6700u)) return -1;
          if (!match16(b, 0xa286u, 0x0004u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x00a28au : 0x00a288u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00a280u:
        {
          if (!match16(b, 0xa280u, 0x0802u)) return -1;
          c->sr=(uint16_t)((c->sr&~4u)|((c->d[2]&(1u<<11))?0u:4u));
          c->cycles+=10u;
          if (!match16(b, 0xa284u, 0x6700u)) return -1;
          if (!match16(b, 0xa286u, 0x0004u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x00a28au : 0x00a288u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00a2acu:
        {
          if (!match16(b, 0xa2acu, 0x2079u)) return -1;
          if (!match32(b, 0xa2aeu, 0x00ff019au)) return -1;
          if (native_bus_read32(b, 0x00ff019au, &c->a[0]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0xa2b2u, 0x2248u)) return -1;
          c->a[1]=c->a[0];
          c->cycles+=4u;
          if (!match16(b, 0xa2b4u, 0xd2fcu)) return -1;
          c->a[1]=(c->a[1]+(int16_t)0x1000u)&0xffffffu;
          c->cycles+=8u;
          if (!match16(b, 0xa2b8u, 0x2449u)) return -1;
          c->a[2]=c->a[1];
          c->cycles+=4u;
          if (!match16(b, 0xa2bau, 0x3e3cu)) return -1;
          if (!match16(b, 0xa2bcu, 0x00ffu)) return -1;
          c->d[7] = (c->d[7] & 0xffff0000u) | 0x00ffu;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00ffu & 0x8000u) ? 8u : 0u) | (0x00ffu == 0u ? 4u : 0u));
          c->cycles += 8u;
          c->pc = 0x00a2beu;
          return 0;
        }
      case 0x00a2eeu:
        {
          if (!match16(b, 0xa2eeu, 0x08b9u)) return -1;
          if (!match16(b, 0xa2f0u, 0x0005u) || !match32(b, 0xa2f2u, 0x00ff010du)) return -1;
          if (native_bus_read8(b, 0x00ff010du, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 5)) ? 0u : 4u));
          if (native_bus_write8((struct t2bus *)b, 0x00ff010du, (uint8_t)(byte_value & ~(1u << 5))) != 0) return -3;
          c->cycles += 16u;
          if (!match16(b, 0xa2f6u, 0x33f9u)) return -1;
          if (!match32(b, 0xa2f8u, 0x00ff010cu) || !match32(b, 0xa2fcu, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0xa300u, 0x33fcu)) return -1;
          if (!match16(b, 0xa302u, 0x8c81u) || !match32(b, 0xa304u, 0x00ff0122u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0122u, 0x8c81u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x8c81u & 0x8000u) ? 8u : 0u) | (0x8c81u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xa308u, 0x33f9u)) return -1;
          if (!match32(b, 0xa30au, 0x00ff0122u) || !match32(b, 0xa30eu, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0122u, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0xa312u, 0x41f9u)) return -1;
          if (!match32(b, 0xa314u, 0x000ac8e0u)) return -1;
          c->a[0] = 0x000ac8e0u;
          c->cycles += 12u;
          if (!match16(b, 0xa318u, 0x2279u)) return -1;
          if (!match32(b, 0xa31au, 0x00ff019au)) return -1;
          if (native_bus_read32(b, 0x00ff019au, &c->a[1]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0xa31eu, 0x2628u)) return -1;
          if(!match16(b,0xa320u,0x0004u))return -1;
          {uint32_t v,addr=(c->a[0]+(int16_t)0x0004u)&0xffffffu; if(native_bus_read32(b,addr,&v))return -3; c->d[3]=v; c->sr=(c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=16u;
          if (!match16(b, 0xa322u, 0x6100u)) return -1;
          if (!match16(b, 0xa324u, 0x3c3au)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00a326u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00df5eu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00a326u:
        {
          if (!match16(b, 0xa326u, 0x23fcu)) return -1;
          if (!match32(b, 0xa328u, 0x40000000u) || !match32(b, 0xa32cu, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0x40000000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=00a326 addr=00c00004 value=40000000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x40000000u & 0x80000000u) ? 8u : 0u) | (0x40000000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0xa330u, 0x2079u)) return -1;
          if (!match32(b, 0xa332u, 0x00ff019au)) return -1;
          if (native_bus_read32(b, 0x00ff019au, &c->a[0]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0xa336u, 0xd0fcu)) return -1;
          c->a[0]=(c->a[0]+(int16_t)0x0020u)&0xffffffu;
          c->cycles+=8u;
          if (!match16(b, 0xa33au, 0x3003u)) return -1;
          { uint16_t v=(uint16_t)c->d[3]; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0xa33cu, 0xe448u)) return -1;
          { uint16_t old=(uint16_t)c->d[0],r=(uint16_t)(old>>2);
            uint16_t carry=(old>>1)&1u;
            c->d[0]=(c->d[0]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xffe0u)|(r==0u?4u:0u)|(carry?17u:0u));
            c->cycles+=10u;
          }
          if (!match16(b, 0xa33eu, 0x5340u)) return -1;
          {uint32_t dst=c->d[0]&65535u,src=1u,r=(dst-src)&65535u;
           c->d[0]=(c->d[0]&0xffff0000u)|r;
           uint16_t cy=(dst<src),ov=((dst^src)&(dst^r)&32768u)!=0u;
           c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(cy?17u:0u));}
          c->cycles+=4u;
          if (!match16(b, 0xa340u, 0x4eb8u)) return -1;
          if (!match16(b, 0xa342u, 0x4a00u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00a344u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004a00u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00a344u:
        {
          if (!match16(b, 0xa344u, 0x33fcu)) return -1;
          if (!match16(b, 0xa346u, 0xffffu) || !match32(b, 0xa348u, 0x00ff01dau)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff01dau, 0xffffu) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xffffu & 0x8000u) ? 8u : 0u) | (0xffffu == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xa34cu, 0x33fcu)) return -1;
          if (!match16(b, 0xa34eu, 0xffffu) || !match32(b, 0xa350u, 0x00ff01c6u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff01c6u, 0xffffu) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xffffu & 0x8000u) ? 8u : 0u) | (0xffffu == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xa354u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xa356u, 0x6100u)) return -1;
          if (!match16(b, 0xa358u, 0xa6f8u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00a35au) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004a50u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00a35au:
        {
          if (!match16(b, 0xa35au, 0x6100u)) return -1;
          if (!match16(b, 0xa35cu, 0xa710u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00a35eu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004a6cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00a35eu:
        {
          if (!match16(b, 0xa35eu, 0x08f9u)) return -1;
          { uint8_t v; if(native_bus_read8(b,0x00ff010du,&v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&~4u)|((v&(1u<<5))?0u:4u));
            if(native_bus_write8((struct t2bus *)b,0x00ff010du,(uint8_t)(v|(1u<<5)))!=0)return -3; }
          c->cycles+=20u;
          if (!match16(b, 0xa366u, 0x33f9u)) return -1;
          if (!match32(b, 0xa368u, 0x00ff010cu) || !match32(b, 0xa36cu, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0xa370u, 0x303cu)) return -1;
          if (!match16(b, 0xa372u, 0x00fbu)) return -1;
          c->d[0] = (c->d[0] & 0xffff0000u) | 0x00fbu;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00fbu & 0x8000u) ? 8u : 0u) | (0x00fbu == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0xa374u, 0x6100u)) return -1;
          if (!match16(b, 0xa376u, 0xf026u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00a378u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00939cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00a378u:
        {
          if (!match16(b, 0xa378u, 0x6100u)) return -1;
          if (!match16(b, 0xa37au, 0xfd60u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00a37cu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a0dau;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00a37cu:
        {
          if (!match16(b, 0xa37cu, 0x41f9u)) return -1;
          if (!match32(b, 0xa37eu, 0x000ac8c0u)) return -1;
          c->a[0] = 0x000ac8c0u;
          c->cycles += 12u;
          if (!match16(b, 0xa382u, 0x7001u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(1);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xa384u, 0x6100u)) return -1;
          if (!match16(b, 0xa386u, 0x14feu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00a388u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00b884u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00a388u:
        {
          if (!match16(b, 0xa388u, 0x41f9u)) return -1;
          if (!match32(b, 0xa38au, 0x000fd4d4u)) return -1;
          c->a[0] = 0x000fd4d4u;
          c->cycles += 12u;
          if (!match16(b, 0xa38eu, 0x6100u)) return -1;
          if (!match16(b, 0xa390u, 0xf628u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00a392u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0099b8u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00a392u:
        {
          if (!match16(b, 0xa392u, 0x6100u)) return -1;
          if (!match16(b, 0xa394u, 0xfd50u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00a396u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a0e4u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00a396u:
        {
          if (!match16(b, 0xa396u, 0x3039u)) return -1;
          if (!match32(b, 0xa398u, 0x00ff0244u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0244u, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0xa39cu, 0xd040u)) return -1;
          { uint32_t x = c->d[0] & 65535u, y = c->d[0] & 65535u, r = (x+y) & 65535u;
            uint16_t flags = (uint16_t)(((r & 0x8000u) ? 8u : 0u) | ((r == 0u) ? 4u : 0u) | (((~(x ^ y) & (r ^ y)) & 0x8000u) ? 2u : 0u) | ((x+y > 65535u) ? 17u : 0u));
            c->d[0] = (c->d[0] & 0xffff0000u) | r;
            c->sr = (uint16_t)((c->sr & 0xffe0u) | flags);
          }
          c->cycles += 4u;
          if (!match16(b, 0xa39eu, 0x6100u)) return -1;
          if (!match16(b, 0xa3a0u, 0xfd7eu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00a3a2u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a11eu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00a3a2u:
        {
          if (!match16(b, 0xa3a2u, 0x33fcu)) return -1;
          if (!match16(b, 0xa3a4u, 0x0000u) || !match32(b, 0xa3a6u, 0x00ff01d2u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff01d2u, 0x0000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xa3aau, 0x41f9u)) return -1;
          if (!match32(b, 0xa3acu, 0x000fd474u)) return -1;
          c->a[0] = 0x000fd474u;
          c->cycles += 12u;
          if (!match16(b, 0xa3b0u, 0x6100u)) return -1;
          if (!match16(b, 0xa3b2u, 0xf606u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00a3b4u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0099b8u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00a3b4u:
        {
          if (!match16(b, 0xa3b4u, 0x6100u)) return -1;
          if (!match16(b, 0xa3b6u, 0xfd2eu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00a3b8u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a0e4u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00a3b8u:
        {
          if (!match16(b, 0xa3b8u, 0x08b9u)) return -1;
          if (!match16(b, 0xa3bau, 0x0005u) || !match32(b, 0xa3bcu, 0x00ff010du)) return -1;
          if (native_bus_read8(b, 0x00ff010du, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 5)) ? 0u : 4u));
          if (native_bus_write8((struct t2bus *)b, 0x00ff010du, (uint8_t)(byte_value & ~(1u << 5))) != 0) return -3;
          c->cycles += 16u;
          if (!match16(b, 0xa3c0u, 0x33f9u)) return -1;
          if (!match32(b, 0xa3c2u, 0x00ff010cu) || !match32(b, 0xa3c6u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0xa3cau, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xa3ccu, 0x6100u)) return -1;
          if (!match16(b, 0xa3ceu, 0xa682u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00a3d0u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004a50u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00a3d0u:
        {
          if (!match16(b, 0xa3d0u, 0x6100u)) return -1;
          if (!match16(b, 0xa3d2u, 0xa69au)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00a3d4u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004a6cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00a3d4u:
        {
          if (!match16(b, 0xa3d4u, 0x33fcu)) return -1;
          if (!match16(b, 0xa3d6u, 0x8c00u) || !match32(b, 0xa3d8u, 0x00ff0122u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0122u, 0x8c00u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x8c00u & 0x8000u) ? 8u : 0u) | (0x8c00u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xa3dcu, 0x33f9u)) return -1;
          if (!match32(b, 0xa3deu, 0x00ff0122u) || !match32(b, 0xa3e2u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0122u, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0xa3e6u, 0x08f9u)) return -1;
          { uint8_t v; if(native_bus_read8(b,0x00ff010du,&v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&~4u)|((v&(1u<<5))?0u:4u));
            if(native_bus_write8((struct t2bus *)b,0x00ff010du,(uint8_t)(v|(1u<<5)))!=0)return -3; }
          c->cycles+=20u;
          if (!match16(b, 0xa3eeu, 0x33f9u)) return -1;
          if (!match32(b, 0xa3f0u, 0x00ff010cu) || !match32(b, 0xa3f4u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0xa3f8u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00a488u:
        {
          if (!match16(b, 0xa488u, 0x4a79u)) return -1;
          if (!match32(b, 0xa48au, 0x00ff0282u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff0282u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0xa48eu, 0x6700u)) return -1;
          if (!match16(b, 0xa490u, 0x0066u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x00a4f6u : 0x00a492u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00a492u:
        {
          if (!match16(b, 0xa492u, 0x3039u)) return -1;
          if (!match32(b, 0xa494u, 0x00c00008u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00c00008u, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0xa498u, 0x0c40u)) return -1;
          if(!match16(b,0xa49au,0xc000u))return -1;
          {uint32_t x=c->d[0]&65535u,y=0xc000u,r=(x-y)&65535u; c->sr=(c->sr&0xfff0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u)|(((x^y)&(x^r)&0x8000u)?2u:0u)|(x<y?1u:0u);}
          c->cycles+=8u;
          if (!match16(b, 0xa49cu, 0x6500u)) return -1;
          if (!match16(b, 0xa49eu, 0x0008u)) return -1;
          c->pc = ((c->sr & 1u)) ? 0x00a4a6u : 0x00a4a0u;
          c->cycles += ((c->sr & 1u)) ? 10u : 8u;
          return 0;
        }
      case 0x00a4a0u:
        {
          if (!match16(b, 0xa4a0u, 0x0c40u)) return -1;
          if(!match16(b,0xa4a2u,0xf500u))return -1;
          {uint32_t x=c->d[0]&65535u,y=0xf500u,r=(x-y)&65535u; c->sr=(c->sr&0xfff0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u)|(((x^y)&(x^r)&0x8000u)?2u:0u)|(x<y?1u:0u);}
          c->cycles+=8u;
          if (!match16(b, 0xa4a4u, 0x65ecu)) return -1;
          c->pc = ((c->sr & 1u)) ? 0x00a492u : 0x00a4a6u;
          c->cycles += ((c->sr & 1u)) ? 10u : 8u;
          return 0;
        }
      case 0x00a4a6u:
        {
          if (!match16(b, 0xa4a6u, 0x43f9u)) return -1;
          if (!match32(b, 0xa4a8u, 0x00ff0398u)) return -1;
          c->a[1] = 0x00ff0398u;
          c->cycles += 12u;
          if (!match16(b, 0xa4acu, 0x3439u)) return -1;
          if (!match32(b, 0xa4aeu, 0x00ff029cu)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff029cu, &val) != 0) return -3;
            c->d[2] = (c->d[2] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0xa4b2u, 0x45f9u)) return -1;
          if (!match32(b, 0xa4b4u, 0x00ff0318u)) return -1;
          c->a[2] = 0x00ff0318u;
          c->cycles += 12u;
          if (!match16(b, 0xa4b8u, 0x7a07u)) return -1;
          c->d[5] = (uint32_t)(int32_t)(7);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[5] & 0x80000000u) ? 8u : 0u) | (c->d[5] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xa4bau, 0x3219u)) return -1;
          { uint16_t v; if(native_bus_read16(b,c->a[1],&v)!=0) return -3;
            c->a[1]=(c->a[1]+2u)&0xffffffu;
            c->d[1]=(c->d[1]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=8u;
          if (!match16(b, 0xa4bcu, 0x3801u)) return -1;
          { uint16_t v=(uint16_t)c->d[1]; c->d[4]=(c->d[4] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0xa4beu, 0x0244u)) return -1;
          if (!match16(b, 0xa4c0u, 0x000fu)) return -1;
          { uint16_t v=(uint16_t)c->d[4] & 0x000fu; c->d[4]=(c->d[4] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0xa4c2u, 0xc8c2u)) return -1;
          c->d[4] = (uint32_t)((c->d[4] & 0xffffu) * (c->d[2] & 0xffffu));
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[4] & 0x80000000u) ? 8u : 0u) | (c->d[4] == 0u ? 4u : 0u));
          c->cycles += 70u;
          if (!match16(b, 0xa4c4u, 0xe84cu)) return -1;
          { uint16_t old=(uint16_t)c->d[4],r=(uint16_t)(old>>4);
            uint16_t carry=(old>>3)&1u;
            c->d[4]=(c->d[4]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xffe0u)|(r==0u?4u:0u)|(carry?17u:0u));
            c->cycles+=14u;
          }
          if (!match16(b, 0xa4c6u, 0x0241u)) return -1;
          if (!match16(b, 0xa4c8u, 0x0ff0u)) return -1;
          { uint16_t v=(uint16_t)c->d[1] & 0x0ff0u; c->d[1]=(c->d[1] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0xa4cau, 0x8841u)) return -1;
          { uint16_t x=(uint16_t)c->d[1], y=(uint16_t)c->d[4],r=(uint16_t)(x | y);
            c->d[1]=(c->d[1]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0xa4ccu, 0x34c4u)) return -1;
          { uint16_t v=(uint16_t)c->d[4];
            if(native_bus_write16((struct t2bus *)b,c->a[2],v)!=0)return -3;
            c->a[2]=(c->a[2]+2u)&0xffffffu;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u));
          }
          c->cycles+=8u;
          if (!match16(b, 0xa4ceu, 0x51cdu)) return -1;
          { uint16_t count = (uint16_t)(c->d[5] - 1u);
            c->d[5] = (c->d[5] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00a4bau : 0x00a4d2u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00a4bau:
        {
          if (!match16(b, 0xa4bau, 0x3219u)) return -1;
          { uint16_t v; if(native_bus_read16(b,c->a[1],&v)!=0) return -3;
            c->a[1]=(c->a[1]+2u)&0xffffffu;
            c->d[1]=(c->d[1]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=8u;
          if (!match16(b, 0xa4bcu, 0x3801u)) return -1;
          { uint16_t v=(uint16_t)c->d[1]; c->d[4]=(c->d[4] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0xa4beu, 0x0244u)) return -1;
          if (!match16(b, 0xa4c0u, 0x000fu)) return -1;
          { uint16_t v=(uint16_t)c->d[4] & 0x000fu; c->d[4]=(c->d[4] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0xa4c2u, 0xc8c2u)) return -1;
          c->d[4] = (uint32_t)((c->d[4] & 0xffffu) * (c->d[2] & 0xffffu));
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[4] & 0x80000000u) ? 8u : 0u) | (c->d[4] == 0u ? 4u : 0u));
          c->cycles += 70u;
          if (!match16(b, 0xa4c4u, 0xe84cu)) return -1;
          { uint16_t old=(uint16_t)c->d[4],r=(uint16_t)(old>>4);
            uint16_t carry=(old>>3)&1u;
            c->d[4]=(c->d[4]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xffe0u)|(r==0u?4u:0u)|(carry?17u:0u));
            c->cycles+=14u;
          }
          if (!match16(b, 0xa4c6u, 0x0241u)) return -1;
          if (!match16(b, 0xa4c8u, 0x0ff0u)) return -1;
          { uint16_t v=(uint16_t)c->d[1] & 0x0ff0u; c->d[1]=(c->d[1] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0xa4cau, 0x8841u)) return -1;
          { uint16_t x=(uint16_t)c->d[1], y=(uint16_t)c->d[4],r=(uint16_t)(x | y);
            c->d[1]=(c->d[1]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0xa4ccu, 0x34c4u)) return -1;
          { uint16_t v=(uint16_t)c->d[4];
            if(native_bus_write16((struct t2bus *)b,c->a[2],v)!=0)return -3;
            c->a[2]=(c->a[2]+2u)&0xffffffu;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u));
          }
          c->cycles+=8u;
          if (!match16(b, 0xa4ceu, 0x51cdu)) return -1;
          { uint16_t count = (uint16_t)(c->d[5] - 1u);
            c->d[5] = (c->d[5] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00a4bau : 0x00a4d2u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00a4d2u:
        {
          if (!match16(b, 0xa4d2u, 0x33fcu)) return -1;
          if (!match16(b, 0xa4d4u, 0x0001u) || !match32(b, 0xa4d6u, 0x00ff0154u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0154u, 0x0001u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0001u & 0x8000u) ? 8u : 0u) | (0x0001u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xa4dau, 0xb479u)) return -1;
          { uint16_t v; if(native_bus_read16(b,0x00ff029eu,&v)!=0)return -3;
            uint32_t x=(c->d[2]&65535u),y=v,r=(x-y)&65535u;
            uint16_t carry=x<y;
            uint16_t ov=((x^y)&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?1u:0u));
          }
          c->cycles+=16u;
          if (!match16(b, 0xa4e0u, 0x6600u)) return -1;
          if (!match16(b, 0xa4e2u, 0x0008u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x00a4eau : 0x00a4e4u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00a4e4u:
        {
          if (!match16(b, 0xa4e4u, 0x4279u)) return -1;
          if (!match32(b, 0xa4e6u, 0x00ff0282u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0282u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0xa4eau, 0xd479u)) return -1;
          { uint16_t v; if(native_bus_read16(b,0x00ff02a0u,&v)!=0)return -3;
            uint32_t x=c->d[2]&65535u,y=v,r=(x+y)&65535u;
            c->d[2]=(c->d[2]&0xffff0000u)|r;
            uint16_t carry=((x+y)>65535u)?1u:0u,ov=((~(x^y))&(x^r)&32768u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|ov|carry|(carry?16u:0u)); }
          c->cycles+=12u;
          if (!match16(b, 0xa4f0u, 0x33c2u)) return -1;
          if (!match32(b, 0xa4f2u, 0x00ff029cu)) return -1;
          { uint16_t v=(uint16_t)c->d[2];
            if (native_bus_write16((struct t2bus *)b,0x00ff029cu,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0xa4f6u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00a4eau:
        {
          if (!match16(b, 0xa4eau, 0xd479u)) return -1;
          { uint16_t v; if(native_bus_read16(b,0x00ff02a0u,&v)!=0)return -3;
            uint32_t x=c->d[2]&65535u,y=v,r=(x+y)&65535u;
            c->d[2]=(c->d[2]&0xffff0000u)|r;
            uint16_t carry=((x+y)>65535u)?1u:0u,ov=((~(x^y))&(x^r)&32768u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|ov|carry|(carry?16u:0u)); }
          c->cycles+=12u;
          if (!match16(b, 0xa4f0u, 0x33c2u)) return -1;
          if (!match32(b, 0xa4f2u, 0x00ff029cu)) return -1;
          { uint16_t v=(uint16_t)c->d[2];
            if (native_bus_write16((struct t2bus *)b,0x00ff029cu,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0xa4f6u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00a4f6u:
        {
          if (!match16(b, 0xa4f6u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00a4f8u:
        {
          if (!match16(b, 0xa4f8u, 0x41f9u)) return -1;
          if (!match32(b, 0xa4fau, 0x000ac8a0u)) return -1;
          c->a[0] = 0x000ac8a0u;
          c->cycles += 12u;
          if (!match16(b, 0xa4feu, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xa500u, 0x6100u)) return -1;
          if (!match16(b, 0xa502u, 0x1382u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00a504u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00b884u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00a504u:
        {
          if (!match16(b, 0xa504u, 0x08b9u)) return -1;
          if (!match16(b, 0xa506u, 0x0005u) || !match32(b, 0xa508u, 0x00ff010du)) return -1;
          if (native_bus_read8(b, 0x00ff010du, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 5)) ? 0u : 4u));
          if (native_bus_write8((struct t2bus *)b, 0x00ff010du, (uint8_t)(byte_value & ~(1u << 5))) != 0) return -3;
          c->cycles += 16u;
          if (!match16(b, 0xa50cu, 0x33f9u)) return -1;
          if (!match32(b, 0xa50eu, 0x00ff010cu) || !match32(b, 0xa512u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0xa516u, 0x41f9u)) return -1;
          if (!match32(b, 0xa518u, 0x000abc34u)) return -1;
          c->a[0] = 0x000abc34u;
          c->cycles += 12u;
          if (!match16(b, 0xa51cu, 0x2628u)) return -1;
          if(!match16(b,0xa51eu,0x0004u))return -1;
          {uint32_t v,addr=(c->a[0]+(int16_t)0x0004u)&0xffffffu; if(native_bus_read32(b,addr,&v))return -3; c->d[3]=v; c->sr=(c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=16u;
          if (!match16(b, 0xa520u, 0x2279u)) return -1;
          if (!match32(b, 0xa522u, 0x00ff019au)) return -1;
          if (native_bus_read32(b, 0x00ff019au, &c->a[1]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0xa526u, 0x6100u)) return -1;
          if (!match16(b, 0xa528u, 0x3a36u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00a52au) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00df5eu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00a52au:
        {
          if (!match16(b, 0xa52au, 0x23fcu)) return -1;
          if (!match32(b, 0xa52cu, 0x40000000u) || !match32(b, 0xa530u, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0x40000000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=00a52a addr=00c00004 value=40000000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x40000000u & 0x80000000u) ? 8u : 0u) | (0x40000000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0xa534u, 0x2079u)) return -1;
          if (!match32(b, 0xa536u, 0x00ff019au)) return -1;
          if (native_bus_read32(b, 0x00ff019au, &c->a[0]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0xa53au, 0x3003u)) return -1;
          { uint16_t v=(uint16_t)c->d[3]; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0xa53cu, 0xe440u)) return -1;
          {uint16_t x=(uint16_t)c->d[0],r=(uint16_t)((int16_t)x>>2),carry=(x>>1)&1u;c->d[0]=(c->d[0]&0xffff0000u)|r;c->sr=(c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(carry?17u:0u);}
          c->cycles+=10u;
          if (!match16(b, 0xa53eu, 0x5340u)) return -1;
          {uint32_t dst=c->d[0]&65535u,src=1u,r=(dst-src)&65535u;
           c->d[0]=(c->d[0]&0xffff0000u)|r;
           uint16_t cy=(dst<src),ov=((dst^src)&(dst^r)&32768u)!=0u;
           c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(cy?17u:0u));}
          c->cycles+=4u;
          if (!match16(b, 0xa540u, 0x6100u)) return -1;
          if (!match16(b, 0xa542u, 0xa4beu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00a544u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004a00u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00a544u:
        {
          if (!match16(b, 0xa544u, 0x303cu)) return -1;
          if (!match16(b, 0xa546u, 0x00ffu)) return -1;
          c->d[0] = (c->d[0] & 0xffff0000u) | 0x00ffu;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00ffu & 0x8000u) ? 8u : 0u) | (0x00ffu == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0xa548u, 0x33fcu)) return -1;
          if (!match16(b, 0xa54au, 0x0000u) || !match32(b, 0xa54cu, 0x00c00000u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00c00000u, 0x0000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xa550u, 0x51c8u)) return -1;
          { uint16_t count = (uint16_t)(c->d[0] - 1u);
            c->d[0] = (c->d[0] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00a548u : 0x00a554u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00a548u:
        {
          if (!match16(b, 0xa548u, 0x33fcu)) return -1;
          if (!match16(b, 0xa54au, 0x0000u) || !match32(b, 0xa54cu, 0x00c00000u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00c00000u, 0x0000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xa550u, 0x51c8u)) return -1;
          { uint16_t count = (uint16_t)(c->d[0] - 1u);
            c->d[0] = (c->d[0] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00a548u : 0x00a554u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00a554u:
        {
          if (!match16(b, 0xa554u, 0x207cu)) return -1;
          if (!match32(b, 0xa556u, 0x000a8c90u)) return -1;
          c->a[0] = 0x000a8c90u;
          c->cycles += 12u;
          if (!match16(b, 0xa55au, 0x2279u)) return -1;
          if (!match32(b, 0xa55cu, 0x00ff019au)) return -1;
          if (native_bus_read32(b, 0x00ff019au, &c->a[1]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0xa560u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xa562u, 0x72ffu)) return -1;
          c->d[1] = (uint32_t)(int32_t)(-1);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xa564u, 0x6100u)) return -1;
          if (!match16(b, 0xa566u, 0xfcfeu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00a568u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a264u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00a568u:
        {
          if (!match16(b, 0xa568u, 0x303cu)) return -1;
          if (!match16(b, 0xa56au, 0xe000u)) return -1;
          c->d[0] = (c->d[0] & 0xffff0000u) | 0xe000u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xe000u & 0x8000u) ? 8u : 0u) | (0xe000u == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0xa56cu, 0x0640u)) return -1;
          { uint32_t x=c->d[0]&65535u,y=0x0080u,r=(x+y)&65535u;
            c->d[0]=(c->d[0]&0xffff0000u)|r;
            uint16_t carry=(x+y)>65535u,ov=((~(x^y))&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?17u:0u));
          }
          c->cycles+=8u;
          if (!match16(b, 0xa570u, 0x2079u)) return -1;
          if (!match32(b, 0xa572u, 0x00ff019au)) return -1;
          if (native_bus_read32(b, 0x00ff019au, &c->a[0]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0xa576u, 0x323cu)) return -1;
          if (!match16(b, 0xa578u, 0x0000u)) return -1;
          c->d[1] = (c->d[1] & 0xffff0000u) | 0x0000u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0xa57au, 0x6100u)) return -1;
          if (!match16(b, 0xa57cu, 0xfbbcu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00a57eu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a138u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00a57eu:
        {
          if (!match16(b, 0xa57eu, 0x08f9u)) return -1;
          { uint8_t v; if(native_bus_read8(b,0x00ff010du,&v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&~4u)|((v&(1u<<5))?0u:4u));
            if(native_bus_write8((struct t2bus *)b,0x00ff010du,(uint8_t)(v|(1u<<5)))!=0)return -3; }
          c->cycles+=20u;
          if (!match16(b, 0xa586u, 0x33f9u)) return -1;
          if (!match32(b, 0xa588u, 0x00ff010cu) || !match32(b, 0xa58cu, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0xa590u, 0x41f9u)) return -1;
          if (!match32(b, 0xa592u, 0x000fd4b0u)) return -1;
          c->a[0] = 0x000fd4b0u;
          c->cycles += 12u;
          if (!match16(b, 0xa596u, 0x6100u)) return -1;
          if (!match16(b, 0xa598u, 0xf420u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00a59au) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0099b8u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00a59au:
        {
          if (!match16(b, 0xa59au, 0x6100u)) return -1;
          if (!match16(b, 0xa59cu, 0xfb48u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00a59eu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a0e4u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00a59eu:
        {
          if (!match16(b, 0xa59eu, 0x3039u)) return -1;
          if (!match32(b, 0xa5a0u, 0x00ff0244u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0244u, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0xa5a4u, 0xd040u)) return -1;
          { uint32_t x = c->d[0] & 65535u, y = c->d[0] & 65535u, r = (x+y) & 65535u;
            uint16_t flags = (uint16_t)(((r & 0x8000u) ? 8u : 0u) | ((r == 0u) ? 4u : 0u) | (((~(x ^ y) & (r ^ y)) & 0x8000u) ? 2u : 0u) | ((x+y > 65535u) ? 17u : 0u));
            c->d[0] = (c->d[0] & 0xffff0000u) | r;
            c->sr = (uint16_t)((c->sr & 0xffe0u) | flags);
          }
          c->cycles += 4u;
          if (!match16(b, 0xa5a6u, 0x6100u)) return -1;
          if (!match16(b, 0xa5a8u, 0xfb76u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00a5aau) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a11eu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00a5aau:
        {
          if (!match16(b, 0xa5aau, 0x41f9u)) return -1;
          if (!match32(b, 0xa5acu, 0x000fd4bcu)) return -1;
          c->a[0] = 0x000fd4bcu;
          c->cycles += 12u;
          if (!match16(b, 0xa5b0u, 0x6100u)) return -1;
          if (!match16(b, 0xa5b2u, 0xf406u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00a5b4u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0099b8u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00a5b4u:
        {
          if (!match16(b, 0xa5b4u, 0x6100u)) return -1;
          if (!match16(b, 0xa5b6u, 0xfb2eu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00a5b8u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a0e4u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00a5b8u:
        {
          if (!match16(b, 0xa5b8u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00a5bau:
        {
          if (!match16(b, 0xa5bau, 0x23fcu)) return -1;
          if (!match32(b, 0xa5bcu, 0xc0000000u) || !match32(b, 0xa5c0u, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0xc0000000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=00a5ba addr=00c00004 value=c0000000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xc0000000u & 0x80000000u) ? 8u : 0u) | (0xc0000000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0xa5c4u, 0x7e1fu)) return -1;
          c->d[7] = (uint32_t)(int32_t)(31);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[7] & 0x80000000u) ? 8u : 0u) | (c->d[7] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xa5c6u, 0x23fcu)) return -1;
          if (!match32(b, 0xa5c8u, 0x00000000u) || !match32(b, 0xa5ccu, 0x00c00000u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00000u, 0x00000000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=00a5c6 addr=00c00000 value=00000000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00000000u & 0x80000000u) ? 8u : 0u) | (0x00000000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0xa5d0u, 0x51cfu)) return -1;
          { uint16_t count = (uint16_t)(c->d[7] - 1u);
            c->d[7] = (c->d[7] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00a5c6u : 0x00a5d4u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00a5c6u:
        {
          if (!match16(b, 0xa5c6u, 0x23fcu)) return -1;
          if (!match32(b, 0xa5c8u, 0x00000000u) || !match32(b, 0xa5ccu, 0x00c00000u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00000u, 0x00000000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=00a5c6 addr=00c00000 value=00000000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00000000u & 0x80000000u) ? 8u : 0u) | (0x00000000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0xa5d0u, 0x51cfu)) return -1;
          { uint16_t count = (uint16_t)(c->d[7] - 1u);
            c->d[7] = (c->d[7] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00a5c6u : 0x00a5d4u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00a5d4u:
        {
          if (!match16(b, 0xa5d4u, 0x23fcu)) return -1;
          if (!match32(b, 0xa5d6u, 0x50000003u) || !match32(b, 0xa5dau, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0x50000003u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=00a5d4 addr=00c00004 value=50000003\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x50000003u & 0x80000000u) ? 8u : 0u) | (0x50000003u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0xa5deu, 0x23fcu)) return -1;
          if (!match32(b, 0xa5e0u, 0x00000000u) || !match32(b, 0xa5e4u, 0x00c00000u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00000u, 0x00000000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=00a5de addr=00c00000 value=00000000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00000000u & 0x80000000u) ? 8u : 0u) | (0x00000000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0xa5e8u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00a9eeu:
        {
          if (!match16(b, 0xa9eeu, 0x23cfu)) return -1;
          if (!match32(b, 0xa9f0u, 0x00ff014au)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff014au, c->a[7]) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->a[7] & 0x80000000u) ? 8u : 0u) | (c->a[7] == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xa9f4u, 0x08b9u)) return -1;
          if (!match16(b, 0xa9f6u, 0x0005u) || !match32(b, 0xa9f8u, 0x00ff010du)) return -1;
          if (native_bus_read8(b, 0x00ff010du, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 5)) ? 0u : 4u));
          if (native_bus_write8((struct t2bus *)b, 0x00ff010du, (uint8_t)(byte_value & ~(1u << 5))) != 0) return -3;
          c->cycles += 16u;
          if (!match16(b, 0xa9fcu, 0x33f9u)) return -1;
          if (!match32(b, 0xa9feu, 0x00ff010cu) || !match32(b, 0xaa02u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0xaa06u, 0x6100u)) return -1;
          if (!match16(b, 0xaa08u, 0x40ccu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00aa0au) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00ead4u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00aa0au:
        {
          if (!match16(b, 0xaa0au, 0x303cu)) return -1;
          if (!match16(b, 0xaa0cu, 0xffffu)) return -1;
          c->d[0] = (c->d[0] & 0xffff0000u) | 0xffffu;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xffffu & 0x8000u) ? 8u : 0u) | (0xffffu == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0xaa0eu, 0xc3c1u)) return -1;
          c->d[1] = (uint32_t)((int32_t)(int16_t)c->d[1] * (int32_t)(int16_t)c->d[1]);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 70u;
          if (!match16(b, 0xaa10u, 0x51c8u)) return -1;
          { uint16_t count = (uint16_t)(c->d[0] - 1u);
            c->d[0] = (c->d[0] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00aa0eu : 0x00aa14u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00aa0eu:
        {
          if (!match16(b, 0xaa0eu, 0xc3c1u)) return -1;
          c->d[1] = (uint32_t)((int32_t)(int16_t)c->d[1] * (int32_t)(int16_t)c->d[1]);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 70u;
          if (!match16(b, 0xaa10u, 0x51c8u)) return -1;
          { uint16_t count = (uint16_t)(c->d[0] - 1u);
            c->d[0] = (c->d[0] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00aa0eu : 0x00aa14u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00aa14u:
        {
          if (!match16(b, 0xaa14u, 0x08b9u)) return -1;
          if (!match16(b, 0xaa16u, 0x0005u) || !match32(b, 0xaa18u, 0x00ff010du)) return -1;
          if (native_bus_read8(b, 0x00ff010du, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 5)) ? 0u : 4u));
          if (native_bus_write8((struct t2bus *)b, 0x00ff010du, (uint8_t)(byte_value & ~(1u << 5))) != 0) return -3;
          c->cycles += 16u;
          if (!match16(b, 0xaa1cu, 0x33f9u)) return -1;
          if (!match32(b, 0xaa1eu, 0x00ff010cu) || !match32(b, 0xaa22u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0xaa26u, 0x7072u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(114);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xaa28u, 0x6100u)) return -1;
          if (!match16(b, 0xaa2au, 0x411au)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00aa2cu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00eb44u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00aa2cu:
        {
          if (!match16(b, 0xaa2cu, 0x2e79u)) return -1;
          if (!match32(b, 0xaa2eu, 0x00ff014au)) return -1;
          if (native_bus_read32(b, 0x00ff014au, &c->a[7]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0xaa32u, 0x6100u)) return -1;
          if (!match16(b, 0xaa34u, 0x36b8u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00aa36u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00e0ecu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00aa36u:
        {
          if (!match16(b, 0xaa36u, 0x3039u)) return -1;
          if (!match32(b, 0xaa38u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00c00004u, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0xaa3cu, 0x0240u)) return -1;
          if (!match16(b, 0xaa3eu, 0x0001u)) return -1;
          { uint16_t v=(uint16_t)c->d[0] & 0x0001u; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0xaa40u, 0x6700u)) return -1;
          if (!match16(b, 0xaa42u, 0x0026u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x00aa68u : 0x00aa44u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00aa44u:
        {
          if (!match16(b, 0xaa44u, 0x33fcu)) return -1;
          if (!match16(b, 0xaa46u, 0x0000u) || !match32(b, 0xaa48u, 0x00ff0240u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0240u, 0x0000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xaa4cu, 0x33fcu)) return -1;
          if (!match16(b, 0xaa4eu, 0x0032u) || !match32(b, 0xaa50u, 0x00ff0244u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0244u, 0x0032u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0032u & 0x8000u) ? 8u : 0u) | (0x0032u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xaa54u, 0x33fcu)) return -1;
          if (!match16(b, 0xaa56u, 0x0004u) || !match32(b, 0xaa58u, 0x00ff0246u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0246u, 0x0004u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0004u & 0x8000u) ? 8u : 0u) | (0x0004u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xaa5cu, 0x33fcu)) return -1;
          if (!match16(b, 0xaa5eu, 0x0001u) || !match32(b, 0xaa60u, 0x00ff0242u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0242u, 0x0001u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0001u & 0x8000u) ? 8u : 0u) | (0x0001u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xaa64u, 0x6000u)) return -1;
          if (!match16(b, 0xaa66u, 0x0022u)) return -1;
          c->pc = (1) ? 0x00aa88u : 0x00aa68u;
          c->cycles += (1) ? 10u : 8u;
          return 0;
        }
      case 0x00aa68u:
        {
          if (!match16(b, 0xaa68u, 0x33fcu)) return -1;
          if (!match16(b, 0xaa6au, 0xffffu) || !match32(b, 0xaa6cu, 0x00ff0240u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0240u, 0xffffu) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xffffu & 0x8000u) ? 8u : 0u) | (0xffffu == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xaa70u, 0x33fcu)) return -1;
          if (!match16(b, 0xaa72u, 0x003cu) || !match32(b, 0xaa74u, 0x00ff0244u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0244u, 0x003cu) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x003cu & 0x8000u) ? 8u : 0u) | (0x003cu == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xaa78u, 0x33fcu)) return -1;
          if (!match16(b, 0xaa7au, 0x0005u) || !match32(b, 0xaa7cu, 0x00ff0246u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0246u, 0x0005u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0005u & 0x8000u) ? 8u : 0u) | (0x0005u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xaa80u, 0x33fcu)) return -1;
          if (!match16(b, 0xaa82u, 0x0000u) || !match32(b, 0xaa84u, 0x00ff0242u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0242u, 0x0000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xaa88u, 0x33fcu)) return -1;
          if (!match16(b, 0xaa8au, 0x0001u) || !match32(b, 0xaa8cu, 0x00ff05ceu)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff05ceu, 0x0001u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0001u & 0x8000u) ? 8u : 0u) | (0x0001u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xaa90u, 0x33fcu)) return -1;
          if (!match16(b, 0xaa92u, 0xffffu) || !match32(b, 0xaa94u, 0x00ff05d2u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff05d2u, 0xffffu) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xffffu & 0x8000u) ? 8u : 0u) | (0xffffu == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xaa98u, 0x41f9u)) return -1;
          if (!match32(b, 0xaa9au, 0x000fd474u)) return -1;
          c->a[0] = 0x000fd474u;
          c->cycles += 12u;
          if (!match16(b, 0xaa9eu, 0x6100u)) return -1;
          if (!match16(b, 0xaaa0u, 0xef18u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00aaa2u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0099b8u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00aa88u:
        {
          if (!match16(b, 0xaa88u, 0x33fcu)) return -1;
          if (!match16(b, 0xaa8au, 0x0001u) || !match32(b, 0xaa8cu, 0x00ff05ceu)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff05ceu, 0x0001u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0001u & 0x8000u) ? 8u : 0u) | (0x0001u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xaa90u, 0x33fcu)) return -1;
          if (!match16(b, 0xaa92u, 0xffffu) || !match32(b, 0xaa94u, 0x00ff05d2u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff05d2u, 0xffffu) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xffffu & 0x8000u) ? 8u : 0u) | (0xffffu == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xaa98u, 0x41f9u)) return -1;
          if (!match32(b, 0xaa9au, 0x000fd474u)) return -1;
          c->a[0] = 0x000fd474u;
          c->cycles += 12u;
          if (!match16(b, 0xaa9eu, 0x6100u)) return -1;
          if (!match16(b, 0xaaa0u, 0xef18u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00aaa2u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0099b8u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00aaa2u:
        {
          if (!match16(b, 0xaaa2u, 0x6100u)) return -1;
          if (!match16(b, 0xaaa4u, 0xef56u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00aaa6u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0099fau;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00aaa6u:
        {
          if (!match16(b, 0xaaa6u, 0x33fcu)) return -1;
          if (!match16(b, 0xaaa8u, 0x0023u) || !match32(b, 0xaaaau, 0x00ff01c0u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff01c0u, 0x0023u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0023u & 0x8000u) ? 8u : 0u) | (0x0023u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xaaaeu, 0x23fcu)) return -1;
          if (!match32(b, 0xaab0u, 0x00ff0be4u) || !match32(b, 0xaab4u, 0x00ff019au)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff019au, 0x00ff0be4u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=00aaae addr=00ff019a value=00ff0be4\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00ff0be4u & 0x80000000u) ? 8u : 0u) | (0x00ff0be4u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0xaab8u, 0x33fcu)) return -1;
          if (!match16(b, 0xaabau, 0x9300u) || !match32(b, 0xaabcu, 0x00ff015au)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff015au, 0x9300u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x9300u & 0x8000u) ? 8u : 0u) | (0x9300u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xaac0u, 0x33fcu)) return -1;
          if (!match16(b, 0xaac2u, 0x9400u) || !match32(b, 0xaac4u, 0x00ff0158u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0158u, 0x9400u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x9400u & 0x8000u) ? 8u : 0u) | (0x9400u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xaac8u, 0x33fcu)) return -1;
          if (!match16(b, 0xaacau, 0x9500u) || !match32(b, 0xaaccu, 0x00ff0160u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0160u, 0x9500u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x9500u & 0x8000u) ? 8u : 0u) | (0x9500u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xaad0u, 0x33fcu)) return -1;
          if (!match16(b, 0xaad2u, 0x9600u) || !match32(b, 0xaad4u, 0x00ff015eu)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff015eu, 0x9600u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x9600u & 0x8000u) ? 8u : 0u) | (0x9600u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xaad8u, 0x33fcu)) return -1;
          if (!match16(b, 0xaadau, 0x9700u) || !match32(b, 0xaadcu, 0x00ff015cu)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff015cu, 0x9700u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x9700u & 0x8000u) ? 8u : 0u) | (0x9700u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xaae0u, 0x33fcu)) return -1;
          if (!match16(b, 0xaae2u, 0x0001u) || !match32(b, 0xaae4u, 0x00ff03c4u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff03c4u, 0x0001u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0001u & 0x8000u) ? 8u : 0u) | (0x0001u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xaae8u, 0x6100u)) return -1;
          if (!match16(b, 0xaaeau, 0xf096u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00aaecu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x009b80u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00aaecu:
        {
          if (!match16(b, 0xaaecu, 0x41f9u)) return -1;
          if (!match32(b, 0xaaeeu, 0x000fd474u)) return -1;
          c->a[0] = 0x000fd474u;
          c->cycles += 12u;
          if (!match16(b, 0xaaf2u, 0x6100u)) return -1;
          if (!match16(b, 0xaaf4u, 0xeec4u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00aaf6u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0099b8u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00aaf6u:
        {
          if (!match16(b, 0xaaf6u, 0x6100u)) return -1;
          if (!match16(b, 0xaaf8u, 0xef02u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00aafau) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0099fau;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00aafau:
        {
          if (!match16(b, 0xaafau, 0x7072u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(114);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xaafcu, 0x0c79u)) return -1;
          { uint16_t v; if(native_bus_read16(b,0x00ff03c4u,&v)!=0)return -3;
            uint32_t x=v,y=0x000eu,r=(x-y)&65535u;
            uint16_t carry=x<y;
            uint16_t ov=((x^y)&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?1u:0u));
          }
          c->cycles+=16u;
          if (!match16(b, 0xab04u, 0x6700u)) return -1;
          if (!match16(b, 0xab06u, 0x0004u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x00ab0au : 0x00ab08u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00ab08u:
        {
          if (!match16(b, 0xab08u, 0x7071u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(113);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xab0au, 0x0c79u)) return -1;
          { uint16_t v; if(native_bus_read16(b,0x00ff03c4u,&v)!=0)return -3;
            uint32_t x=v,y=0x0001u,r=(x-y)&65535u;
            uint16_t carry=x<y;
            uint16_t ov=((x^y)&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?1u:0u));
          }
          c->cycles+=16u;
          if (!match16(b, 0xab12u, 0x6700u)) return -1;
          if (!match16(b, 0xab14u, 0x000cu)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x00ab20u : 0x00ab16u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00ab0au:
        {
          if (!match16(b, 0xab0au, 0x0c79u)) return -1;
          { uint16_t v; if(native_bus_read16(b,0x00ff03c4u,&v)!=0)return -3;
            uint32_t x=v,y=0x0001u,r=(x-y)&65535u;
            uint16_t carry=x<y;
            uint16_t ov=((x^y)&(x^r)&32768u)!=0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?1u:0u));
          }
          c->cycles+=16u;
          if (!match16(b, 0xab12u, 0x6700u)) return -1;
          if (!match16(b, 0xab14u, 0x000cu)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x00ab20u : 0x00ab16u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00ab16u:
        {
          if (!match16(b, 0xab16u, 0x33c0u)) return -1;
          if (!match32(b, 0xab18u, 0x00ff03c2u)) return -1;
          { uint16_t v=(uint16_t)c->d[0];
            if (native_bus_write16((struct t2bus *)b,0x00ff03c2u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0xab1cu, 0x6100u)) return -1;
          if (!match16(b, 0xab1eu, 0x4026u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00ab20u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00eb44u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00ab20u:
        {
          if (!match16(b, 0xab20u, 0x33fcu)) return -1;
          if (!match16(b, 0xab22u, 0x0000u) || !match32(b, 0xab24u, 0x00ff0216u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0216u, 0x0000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xab28u, 0x3f39u)) return -1;
          if(!match32(b,0xab2au,0x00ff03c4u))return -1;
          {uint16_t v;if(native_bus_read16(b,0x00ff03c4u,&v)!=0)return -3;
           c->a[7]=(c->a[7]-2u)&0xffffffu;
           if(native_bus_write16((struct t2bus *)b,c->a[7],v)!=0)return -3;
           c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=20u;
          if (!match16(b, 0xab2eu, 0x6100u)) return -1;
          if (!match16(b, 0xab30u, 0xa78au)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00ab32u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0052bau;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00ab32u:
        {
          if (!match16(b, 0xab32u, 0x33dfu)) return -1;
          if(!match32(b,0xab34u,0x00ff03c4u))return -1;
          {uint16_t v;
           if(native_bus_read16(b,c->a[7],&v)!=0)return -3;
           c->a[7]=(c->a[7]+2u)&0xffffffu;
           if(native_bus_write16((struct t2bus *)b,0x00ff03c4u,v)!=0)return -3;
           c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=20u;
          if (!match16(b, 0xab38u, 0x33fcu)) return -1;
          if (!match16(b, 0xab3au, 0xffffu) || !match32(b, 0xab3cu, 0x00ff0216u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff0216u, 0xffffu) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xffffu & 0x8000u) ? 8u : 0u) | (0xffffu == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xab40u, 0x08b9u)) return -1;
          if (!match16(b, 0xab42u, 0x0005u) || !match32(b, 0xab44u, 0x00ff010du)) return -1;
          if (native_bus_read8(b, 0x00ff010du, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 5)) ? 0u : 4u));
          if (native_bus_write8((struct t2bus *)b, 0x00ff010du, (uint8_t)(byte_value & ~(1u << 5))) != 0) return -3;
          c->cycles += 16u;
          if (!match16(b, 0xab48u, 0x33f9u)) return -1;
          if (!match32(b, 0xab4au, 0x00ff010cu) || !match32(b, 0xab4eu, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0xab52u, 0x7074u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(116);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xab54u, 0x33c0u)) return -1;
          if (!match32(b, 0xab56u, 0x00ff03c2u)) return -1;
          { uint16_t v=(uint16_t)c->d[0];
            if (native_bus_write16((struct t2bus *)b,0x00ff03c2u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0xab5au, 0x6100u)) return -1;
          if (!match16(b, 0xab5cu, 0x3fe8u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00ab5eu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00eb44u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00ab5eu:
        {
          if (!match16(b, 0xab5eu, 0x23fcu)) return -1;
          if (!match32(b, 0xab60u, 0x00ff0be4u) || !match32(b, 0xab64u, 0x00ff019au)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff019au, 0x00ff0be4u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=00ab5e addr=00ff019a value=00ff0be4\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00ff0be4u & 0x80000000u) ? 8u : 0u) | (0x00ff0be4u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0xab68u, 0x33fcu)) return -1;
          if (!match16(b, 0xab6au, 0x0020u) || !match32(b, 0xab6cu, 0x00ff01a6u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff01a6u, 0x0020u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0020u & 0x8000u) ? 8u : 0u) | (0x0020u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xab70u, 0x6100u)) return -1;
          if (!match16(b, 0xab72u, 0x35a2u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00ab74u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00e114u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00ab74u:
        {
          if (!match16(b, 0xab74u, 0x6100u)) return -1;
          if (!match16(b, 0xab76u, 0xdb9cu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00ab78u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x008712u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00ab78u:
        {
          if (!match16(b, 0xab78u, 0x33fcu)) return -1;
          if (!match16(b, 0xab7au, 0x00b0u) || !match32(b, 0xab7cu, 0x00ff062cu)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff062cu, 0x00b0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00b0u & 0x8000u) ? 8u : 0u) | (0x00b0u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xab80u, 0x23fcu)) return -1;
          if (!match32(b, 0xab82u, 0xffffffffu) || !match32(b, 0xab86u, 0x00ff0278u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff0278u, 0xffffffffu) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=00ab80 addr=00ff0278 value=ffffffff\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xffffffffu & 0x80000000u) ? 8u : 0u) | (0xffffffffu == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0xab8au, 0x33fcu)) return -1;
          if (!match16(b, 0xab8cu, 0x0000u) || !match32(b, 0xab8eu, 0x00ff01d2u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff01d2u, 0x0000u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000u & 0x8000u) ? 8u : 0u) | (0x0000u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xab92u, 0x08b9u)) return -1;
          if (!match16(b, 0xab94u, 0x0005u) || !match32(b, 0xab96u, 0x00ff010du)) return -1;
          if (native_bus_read8(b, 0x00ff010du, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 5)) ? 0u : 4u));
          if (native_bus_write8((struct t2bus *)b, 0x00ff010du, (uint8_t)(byte_value & ~(1u << 5))) != 0) return -3;
          c->cycles += 16u;
          if (!match16(b, 0xab9au, 0x33f9u)) return -1;
          if (!match32(b, 0xab9cu, 0x00ff010cu) || !match32(b, 0xaba0u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0xaba4u, 0x23fcu)) return -1;
          if (!match32(b, 0xaba6u, 0x0000aef2u) || !match32(b, 0xabaau, 0x00ff0138u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff0138u, 0x0000aef2u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=00aba4 addr=00ff0138 value=0000aef2\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0000aef2u & 0x80000000u) ? 8u : 0u) | (0x0000aef2u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0xabaeu, 0x3039u)) return -1;
          if (!match32(b, 0xabb0u, 0x00ff03c4u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff03c4u, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0xabb4u, 0x5279u)) return -1;
          if (!match32(b,0xabb6u,0x00ff03c4u)) return -1;
          { uint16_t dst,src=1u,result; if (native_bus_read16(b,0x00ff03c4u,&dst)!=0) return -3;
            result=(uint16_t)(dst + src);
            if (native_bus_write16((struct t2bus *)b,0x00ff03c4u,result)!=0) return -3;
            uint16_t carry=(uint32_t)dst+src>0xffffu?1u:0u;
            uint16_t overflow=((~(dst^src))&(dst^result)&0x8000u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((result&0x8000u)?8u:0u)|(result==0u?4u:0u)|overflow|carry|(carry?16u:0u));
          }
          c->cycles += 20u;
          if (!match16(b, 0xabbau, 0xe248u)) return -1;
          { uint16_t old=(uint16_t)c->d[0],r=(uint16_t)(old>>1);
            uint16_t carry=(old>>0)&1u;
            c->d[0]=(c->d[0]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xffe0u)|(r==0u?4u:0u)|(carry?17u:0u));
            c->cycles+=8u;
          }
          if (!match16(b, 0xabbcu, 0xc0fcu)) return -1;
          if(!match16(b,0xabbeu,0x0010u))return -1;
          {uint32_t r=(c->d[0]&65535u)*0x0010u; c->d[0]=r; c->sr=(c->sr&0xfff0u)|((r&0x80000000u)?8u:0u)|(r==0u?4u:0u);}
          c->cycles+=70u;
          if (!match16(b, 0xabc0u, 0x41f9u)) return -1;
          if (!match32(b, 0xabc2u, 0x0000dee6u)) return -1;
          c->a[0] = 0x0000dee6u;
          c->cycles += 12u;
          if (!match16(b, 0xabc6u, 0xd0c0u)) return -1;
          c->a[0]=(c->a[0]+(int16_t)(c->d[0]&65535u))&0xffffffu;
          c->cycles+=8u;
          if (!match16(b, 0xabc8u, 0x23d8u)) return -1;
          { uint32_t v; if(native_bus_read32(b,c->a[0],&v)!=0)return -3;
            c->a[0]=(c->a[0]+4u)&0xffffffu;
            if(native_bus_write32((struct t2bus *)b,0x00ff05deu,v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=28u;
          if (!match16(b, 0xabceu, 0x23d8u)) return -1;
          { uint32_t v; if(native_bus_read32(b,c->a[0],&v)!=0)return -3;
            c->a[0]=(c->a[0]+4u)&0xffffffu;
            if(native_bus_write32((struct t2bus *)b,0x00ff05e2u,v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=28u;
          if (!match16(b, 0xabd4u, 0x33d8u)) return -1;
          {uint16_t v;if(native_bus_read16(b,c->a[0],&v))return -3;c->a[0]=(c->a[0]+2u)&0xffffffu;if(native_bus_write16((struct t2bus *)b,0xff0604u,v))return -3;c->sr=(c->sr&0xfff0u)|((v&32768u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=20u;
          if (!match16(b, 0xabdau, 0x3039u)) return -1;
          if (!match32(b, 0xabdcu, 0x00ff0604u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0604u, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0xabe0u, 0x5240u)) return -1;
          { uint16_t dst=(uint16_t)c->d[0],r=(uint16_t)(dst+1u);
            c->d[0]=(c->d[0]&0xffff0000u)|r;
            uint16_t carry=(dst==0xffffu)?1u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u)|(dst==0x7fffu?2u:0u)|carry|(carry?16u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0xabe2u, 0x0240u)) return -1;
          if (!match16(b, 0xabe4u, 0x000fu)) return -1;
          { uint16_t v=(uint16_t)c->d[0] & 0x000fu; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0xabe6u, 0x33c0u)) return -1;
          if (!match32(b, 0xabe8u, 0x00ff0646u)) return -1;
          { uint16_t v=(uint16_t)c->d[0];
            if (native_bus_write16((struct t2bus *)b,0x00ff0646u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0xabecu, 0x33d8u)) return -1;
          {uint16_t v;if(native_bus_read16(b,c->a[0],&v))return -3;c->a[0]=(c->a[0]+2u)&0xffffffu;if(native_bus_write16((struct t2bus *)b,0xff0610u,v))return -3;c->sr=(c->sr&0xfff0u)|((v&32768u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=20u;
          if (!match16(b, 0xabf2u, 0x33d8u)) return -1;
          {uint16_t v;if(native_bus_read16(b,c->a[0],&v))return -3;c->a[0]=(c->a[0]+2u)&0xffffffu;if(native_bus_write16((struct t2bus *)b,0xff0676u,v))return -3;c->sr=(c->sr&0xfff0u)|((v&32768u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=20u;
          if (!match16(b, 0xabf8u, 0x33d8u)) return -1;
          {uint16_t v;if(native_bus_read16(b,c->a[0],&v))return -3;c->a[0]=(c->a[0]+2u)&0xffffffu;if(native_bus_write16((struct t2bus *)b,0xff06b6u,v))return -3;c->sr=(c->sr&0xfff0u)|((v&32768u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=20u;
          if (!match16(b, 0xabfeu, 0x23d8u)) return -1;
          { uint32_t v; if(native_bus_read32(b,c->a[0],&v)!=0)return -3;
            c->a[0]=(c->a[0]+4u)&0xffffffu;
            if(native_bus_write32((struct t2bus *)b,0x00ff06acu,v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=28u;
          if (!match16(b, 0xac04u, 0x23d8u)) return -1;
          { uint32_t v; if(native_bus_read32(b,c->a[0],&v)!=0)return -3;
            c->a[0]=(c->a[0]+4u)&0xffffffu;
            if(native_bus_write32((struct t2bus *)b,0x00ff06b0u,v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=28u;
          if (!match16(b, 0xac0au, 0x6100u)) return -1;
          if (!match16(b, 0xac0cu, 0x15e6u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00ac0eu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00c1f2u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00ac0eu:
        {
          if (!match16(b, 0xac0eu, 0x33fcu)) return -1;
          if (!match16(b, 0xac10u, 0x0004u) || !match32(b, 0xac12u, 0x00ff06b4u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff06b4u, 0x0004u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0004u & 0x8000u) ? 8u : 0u) | (0x0004u == 0u ? 4u : 0u));
          c->cycles += 20u;
          if (!match16(b, 0xac16u, 0x4df9u)) return -1;
          if (!match32(b, 0xac18u, 0x00ff06b8u)) return -1;
          c->a[6] = 0x00ff06b8u;
          c->cycles += 12u;
          if (!match16(b, 0xac1cu, 0x7e04u)) return -1;
          c->d[7] = (uint32_t)(int32_t)(4);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[7] & 0x80000000u) ? 8u : 0u) | (c->d[7] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xac1eu, 0x7020u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(32);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xac20u, 0x7201u)) return -1;
          c->d[1] = (uint32_t)(int32_t)(1);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xac22u, 0x7401u)) return -1;
          c->d[2] = (uint32_t)(int32_t)(1);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[2] & 0x80000000u) ? 8u : 0u) | (c->d[2] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xac24u, 0x0c47u)) return -1;
          if(!match16(b,0xac26u,0x0001u))return -1;
          {uint32_t x=c->d[7]&65535u,y=0x0001u,r=(x-y)&65535u; c->sr=(c->sr&0xfff0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u)|(((x^y)&(x^r)&0x8000u)?2u:0u)|(x<y?1u:0u);}
          c->cycles+=8u;
          if (!match16(b, 0xac28u, 0x6e00u)) return -1;
          if (!match16(b,0xac2au,0x000au)) return -1;
          c->pc=((!(c->sr & 4u) && (!!(c->sr & 8u)==!!(c->sr & 2u))))?0x00ac34u:0x00ac2cu;
          c->cycles+=((!(c->sr & 4u) && (!!(c->sr & 8u)==!!(c->sr & 2u))))?10u:8u;
          return 0;
        }
      case 0x00ac2cu:
        {
          if (!match16(b, 0xac2cu, 0x3239u)) return -1;
          if (!match32(b, 0xac2eu, 0x00ff06b6u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff06b6u, &val) != 0) return -3;
            c->d[1] = (c->d[1] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0xac32u, 0x7400u)) return -1;
          c->d[2] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[2] & 0x80000000u) ? 8u : 0u) | (c->d[2] == 0u ? 4u : 0u));
          c->cycles += 4u;
          c->pc = 0x00ac34u;
          return 0;
        }
      case 0x00b20eu:
        {
          if (!match16(b, 0xb20eu, 0x5347u)) return -1;
          {uint32_t dst=c->d[7]&65535u,src=1u,r=(dst-src)&65535u;
           c->d[7]=(c->d[7]&0xffff0000u)|r;
           uint16_t cy=(dst<src),ov=((dst^src)&(dst^r)&32768u)!=0u;
           c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(cy?17u:0u));}
          c->cycles+=4u;
          if (!match16(b, 0xb210u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          c->pc = 0x00b212u;
          return 0;
        }
      case 0x00b884u:
        {
          if (!match16(b, 0xb884u, 0x48e7u)) return -1;
          if (!match16(b, 0xb886u, 0xc0c0u)) return -1;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->a[1]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->a[0]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[1]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[0]) != 0) return -3;
          c->cycles += 40u;
          if (!match16(b, 0xb888u, 0x3200u)) return -1;
          { uint16_t v=(uint16_t)c->d[0]; c->d[1]=(c->d[1] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0xb88au, 0xeb49u)) return -1;
          { unsigned count=c->d[5]&63u,i;uint32_t v=c->d[1]&65535u;uint16_t carry=0;
            for(i=0;i<count;i++){carry=(v>>15)&1u;v=(v<<1)&65535u;}
            c->d[1]=(c->d[1]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&(count?0xffe0u:0xfff0u))|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)|(count&&carry?17u:0u)); c->cycles+=6u+2u*count; }
          if (!match16(b, 0xb88cu, 0x43f9u)) return -1;
          if (!match32(b, 0xb88eu, 0x00ff0328u)) return -1;
          c->a[1] = 0x00ff0328u;
          c->cycles += 12u;
          if (!match16(b, 0xb892u, 0xd2c1u)) return -1;
          c->a[1]=(c->a[1]+(int16_t)(c->d[1]&65535u))&0xffffffu;
          c->cycles+=8u;
          if (!match16(b, 0xb894u, 0x7007u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(7);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xb896u, 0x22d8u)) return -1;
          {uint32_t v;if(native_bus_read32(b,c->a[0],&v))return -3;c->a[0]=(c->a[0]+4u)&0xffffffu;if(native_bus_write32((struct t2bus *)b,c->a[1],v))return -3;c->a[1]=(c->a[1]+4u)&0xffffffu;c->sr=(c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=20u;
          if (!match16(b, 0xb898u, 0x51c8u)) return -1;
          { uint16_t count = (uint16_t)(c->d[0] - 1u);
            c->d[0] = (c->d[0] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00b896u : 0x00b89cu;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00b896u:
        {
          if (!match16(b, 0xb896u, 0x22d8u)) return -1;
          {uint32_t v;if(native_bus_read32(b,c->a[0],&v))return -3;c->a[0]=(c->a[0]+4u)&0xffffffu;if(native_bus_write32((struct t2bus *)b,c->a[1],v))return -3;c->a[1]=(c->a[1]+4u)&0xffffffu;c->sr=(c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=20u;
          if (!match16(b, 0xb898u, 0x51c8u)) return -1;
          { uint16_t count = (uint16_t)(c->d[0] - 1u);
            c->d[0] = (c->d[0] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00b896u : 0x00b89cu;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00b89cu:
        {
          if (!match16(b, 0xb89cu, 0x4cdfu)) return -1;
          if (!match16(b, 0xb89eu, 0x0303u)) return -1;
          { uint32_t addr = c->a[7]; uint32_t val; uint16_t word; unsigned idx;
            for (idx = 0; idx < 16u; ++idx)
              {
                if (!(0x0303u & (1u << idx))) continue;
                if (native_bus_read32(b, addr, &val) != 0) return -3;
                if (idx < 8u) c->d[idx] = val;
                else c->a[idx - 8u] = val;
                addr = (addr + 4u) & 0xffffffu;
              }
            c->a[7] = addr; /* postincrement wins if base An is in mask */
          }
          c->cycles += 40u;
          if (!match16(b, 0xb8a0u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00bcb6u:
        {
          if (!match16(b, 0xbcb6u, 0x23fcu)) return -1;
          if (!match32(b, 0xbcb8u, 0x40000010u) || !match32(b, 0xbcbcu, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0x40000010u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=00bcb6 addr=00c00004 value=40000010\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x40000010u & 0x80000000u) ? 8u : 0u) | (0x40000010u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0xbcc0u, 0x3039u)) return -1;
          if (!match32(b, 0xbcc2u, 0x00ff016au)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff016au, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0xbcc6u, 0x0240u)) return -1;
          if (!match16(b, 0xbcc8u, 0x00ffu)) return -1;
          { uint16_t v=(uint16_t)c->d[0] & 0x00ffu; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0xbccau, 0x33c0u)) return -1;
          if (!match32(b, 0xbcccu, 0x00c00000u)) return -1;
          { uint16_t v=(uint16_t)c->d[0];
            if (native_bus_write16((struct t2bus *)b,0x00c00000u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0xbcd0u, 0x33c0u)) return -1;
          if (!match32(b, 0xbcd2u, 0x00c00000u)) return -1;
          { uint16_t v=(uint16_t)c->d[0];
            if (native_bus_write16((struct t2bus *)b,0x00c00000u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0xbcd6u, 0x23fcu)) return -1;
          if (!match32(b, 0xbcd8u, 0x70000003u) || !match32(b, 0xbcdcu, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0x70000003u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=00bcd6 addr=00c00004 value=70000003\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x70000003u & 0x80000000u) ? 8u : 0u) | (0x70000003u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0xbce0u, 0x3039u)) return -1;
          if (!match32(b, 0xbce2u, 0x00ff0168u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0168u, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0xbce6u, 0x4440u)) return -1;
          { uint32_t x=c->d[0]&65535u,r=(-x)&65535u;
            c->d[0]=(c->d[0]&0xffff0000u)|r;
            uint16_t carry=x!=0u?1u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(x==32768u?2u:0u)|carry|(carry?16u:0u)); }
          c->cycles+=4u;
          if (!match16(b, 0xbce8u, 0x0240u)) return -1;
          if (!match16(b, 0xbceau, 0x01ffu)) return -1;
          { uint16_t v=(uint16_t)c->d[0] & 0x01ffu; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0xbcecu, 0x33c0u)) return -1;
          if (!match32(b, 0xbceeu, 0x00c00000u)) return -1;
          { uint16_t v=(uint16_t)c->d[0];
            if (native_bus_write16((struct t2bus *)b,0x00c00000u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0xbcf2u, 0x33c0u)) return -1;
          if (!match32(b, 0xbcf4u, 0x00c00000u)) return -1;
          { uint16_t v=(uint16_t)c->d[0];
            if (native_bus_write16((struct t2bus *)b,0x00c00000u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0xbcf8u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00c1f2u:
        {
          if (!match16(b, 0xc1f2u, 0x2039u)) return -1;
          { uint32_t v; if(native_bus_read32(b,0x00ff05e2u,&v)!=0)return -3;
            c->d[0]=v;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=16u;
          if (!match16(b, 0xc1f8u, 0x2200u)) return -1;
          c->d[1]=c->d[0];
          c->sr=(uint16_t)((c->sr&0xfff0u)|((c->d[1]&0x80000000u)?8u:0u)|(c->d[1]==0u?4u:0u));
          c->cycles+=4u;
          c->pc = 0x00c1fau;
          return 0;
        }
      case 0x00df5eu:
        {
          if (!match16(b, 0xdf5eu, 0x48e7u)) return -1;
          if (!match16(b, 0xdf60u, 0xfffcu)) return -1;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->a[5]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->a[4]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->a[3]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->a[2]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->a[1]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->a[0]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[7]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[6]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[5]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[4]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[3]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[2]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[1]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[0]) != 0) return -3;
          c->cycles += 120u;
          if (!match16(b, 0xdf62u, 0x4fefu)) return -1;
          c->a[7]=(c->a[7]+(int16_t)0xfe80u)&0xffffffu;
          c->cycles+=8u;
          if (!match16(b, 0xdf66u, 0x244fu)) return -1;
          c->a[2]=c->a[7];
          c->cycles+=4u;
          if (!match16(b, 0xdf68u, 0x5848u)) return -1;
          c->a[0] += 4u;
          c->cycles += 8u;
          if (!match16(b, 0xdf6au, 0x6100u)) return -1;
          if (!match16(b, 0xdf6cu, 0x00ecu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00df6eu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00e058u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00df6eu:
        {
          if (!match16(b, 0xdf6eu, 0x47e8u)) return -1;
          if(!match16(b,0xdf70u,0x000au))return -1;
          c->a[3]=(c->a[0]+(int16_t)0x000au)&0xffffffu;
          c->cycles+=8u;
          if (!match16(b, 0xdf72u, 0x2849u)) return -1;
          c->a[4]=c->a[1];
          c->cycles+=4u;
          c->pc = 0x00df74u;
          return 0;
        }
      case 0x00e058u:
        {
          if (!match16(b, 0xe058u, 0x7203u)) return -1;
          c->d[1] = (uint32_t)(int32_t)(3);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xe05au, 0xe188u)) return -1;
          { uint32_t x=c->d[0],r=x<<8;
            uint16_t carry=(uint16_t)((x>>24)&1u);
            c->d[0]=r;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x80000000u)?8u:0u)|(r==0u?4u:0u)|(carry?17u:0u));
          }
          c->cycles+=24u;
          if (!match16(b, 0xe05cu, 0x1018u)) return -1;
          if (native_bus_read8(b, c->a[0], &byte_value) != 0) return -3;
          c->a[0] = (c->a[0] + 1u) & 0xffffffu;
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 128u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0xe05eu, 0x51c9u)) return -1;
          { uint16_t count = (uint16_t)(c->d[1] - 1u);
            c->d[1] = (c->d[1] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00e05au : 0x00e062u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00e05au:
        {
          if (!match16(b, 0xe05au, 0xe188u)) return -1;
          { uint32_t x=c->d[0],r=x<<8;
            uint16_t carry=(uint16_t)((x>>24)&1u);
            c->d[0]=r;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x80000000u)?8u:0u)|(r==0u?4u:0u)|(carry?17u:0u));
          }
          c->cycles+=24u;
          if (!match16(b, 0xe05cu, 0x1018u)) return -1;
          if (native_bus_read8(b, c->a[0], &byte_value) != 0) return -3;
          c->a[0] = (c->a[0] + 1u) & 0xffffffu;
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 128u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0xe05eu, 0x51c9u)) return -1;
          { uint16_t count = (uint16_t)(c->d[1] - 1u);
            c->d[1] = (c->d[1] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00e05au : 0x00e062u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00e062u:
        {
          if (!match16(b, 0xe062u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00e0ecu:
        {
          if (!match16(b, 0xe0ecu, 0x41f9u)) return -1;
          if (!match32(b, 0xe0eeu, 0x00ff0150u)) return -1;
          c->a[0] = 0x00ff0150u;
          c->cycles += 12u;
          if (!match16(b, 0xe0f2u, 0x303cu)) return -1;
          if (!match16(b, 0xe0f4u, 0x048du)) return -1;
          c->d[0] = (c->d[0] & 0xffff0000u) | 0x048du;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x048du & 0x8000u) ? 8u : 0u) | (0x048du == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0xe0f6u, 0x10fcu)) return -1;
          if (!match16(b, 0xe0f8u, 0x0000u)) return -1;
          if (native_bus_write8((struct t2bus *)b, c->a[0] & 0xffffffu, 0x00u) != 0)
            { printf("T2GEN V0.71 WRITE_FAULT: PC=00e0f6 opcode=10fc EA=A0 addr=%06lx size=B value=00 D0=%08lx A0=%08lx A4=%08lx A7=%06lx SR=%04x\n", (unsigned long)(c->a[0] & 0xffffffu), (unsigned long)c->d[0], (unsigned long)c->a[0], (unsigned long)c->a[4], (unsigned long)c->a[7], (unsigned)c->sr); return -3; }
          c->a[0] = (c->a[0] + 1u) & 0xffffffu;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0xe0fau, 0x51c8u)) return -1;
          { uint16_t count = (uint16_t)(c->d[0] - 1u);
            c->d[0] = (c->d[0] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00e0f6u : 0x00e0feu;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00e0f6u:
        {
          if (!match16(b, 0xe0f6u, 0x10fcu)) return -1;
          if (!match16(b, 0xe0f8u, 0x0000u)) return -1;
          if (native_bus_write8((struct t2bus *)b, c->a[0] & 0xffffffu, 0x00u) != 0)
            { printf("T2GEN V0.71 WRITE_FAULT: PC=00e0f6 opcode=10fc EA=A0 addr=%06lx size=B value=00 D0=%08lx A0=%08lx A4=%08lx A7=%06lx SR=%04x\n", (unsigned long)(c->a[0] & 0xffffffu), (unsigned long)c->d[0], (unsigned long)c->a[0], (unsigned long)c->a[4], (unsigned long)c->a[7], (unsigned)c->sr); return -3; }
          c->a[0] = (c->a[0] + 1u) & 0xffffffu;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0xe0fau, 0x51c8u)) return -1;
          { uint16_t count = (uint16_t)(c->d[0] - 1u);
            c->d[0] = (c->d[0] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00e0f6u : 0x00e0feu;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00e0feu:
        {
          if (!match16(b, 0xe0feu, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00e100u:
        {
          if (!match16(b, 0xe100u, 0x41f9u)) return -1;
          if (!match32(b, 0xe102u, 0x00ff05deu)) return -1;
          c->a[0] = 0x00ff05deu;
          c->cycles += 12u;
          if (!match16(b, 0xe106u, 0x303cu)) return -1;
          if (!match16(b, 0xe108u, 0x57fbu)) return -1;
          c->d[0] = (c->d[0] & 0xffff0000u) | 0x57fbu;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x57fbu & 0x8000u) ? 8u : 0u) | (0x57fbu == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0xe10au, 0x30fcu)) return -1;
          if(native_bus_write16((struct t2bus *)b,c->a[0],0x0000u))return -3;
          c->a[0]=(c->a[0]+2u)&0xffffffu;
          c->sr=(c->sr&0xfff0u)|0u|4u;
          c->cycles+=12u;
          if (!match16(b, 0xe10eu, 0x51c8u)) return -1;
          { uint16_t count = (uint16_t)(c->d[0] - 1u);
            c->d[0] = (c->d[0] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00e10au : 0x00e112u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00e10au:
        {
          if (!match16(b, 0xe10au, 0x30fcu)) return -1;
          if(native_bus_write16((struct t2bus *)b,c->a[0],0x0000u))return -3;
          c->a[0]=(c->a[0]+2u)&0xffffffu;
          c->sr=(c->sr&0xfff0u)|0u|4u;
          c->cycles+=12u;
          if (!match16(b, 0xe10eu, 0x51c8u)) return -1;
          { uint16_t count = (uint16_t)(c->d[0] - 1u);
            c->d[0] = (c->d[0] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00e10au : 0x00e112u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00e112u:
        {
          if (!match16(b, 0xe112u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00e114u:
        {
          if (!match16(b, 0xe114u, 0x41f9u)) return -1;
          if (!match32(b, 0xe116u, 0x00ff05deu)) return -1;
          c->a[0] = 0x00ff05deu;
          c->cycles += 12u;
          if (!match16(b, 0xe11au, 0x303cu)) return -1;
          if (!match16(b, 0xe11cu, 0x0605u)) return -1;
          c->d[0] = (c->d[0] & 0xffff0000u) | 0x0605u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0605u & 0x8000u) ? 8u : 0u) | (0x0605u == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0xe11eu, 0x10fcu)) return -1;
          if (!match16(b, 0xe120u, 0x0000u)) return -1;
          if (native_bus_write8((struct t2bus *)b, c->a[0] & 0xffffffu, 0x00u) != 0)
            { printf("T2GEN V0.71 WRITE_FAULT: PC=00e11e opcode=10fc EA=A0 addr=%06lx size=B value=00 D0=%08lx A0=%08lx A4=%08lx A7=%06lx SR=%04x\n", (unsigned long)(c->a[0] & 0xffffffu), (unsigned long)c->d[0], (unsigned long)c->a[0], (unsigned long)c->a[4], (unsigned long)c->a[7], (unsigned)c->sr); return -3; }
          c->a[0] = (c->a[0] + 1u) & 0xffffffu;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0xe122u, 0x51c8u)) return -1;
          { uint16_t count = (uint16_t)(c->d[0] - 1u);
            c->d[0] = (c->d[0] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00e11eu : 0x00e126u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00e11eu:
        {
          if (!match16(b, 0xe11eu, 0x10fcu)) return -1;
          if (!match16(b, 0xe120u, 0x0000u)) return -1;
          if (native_bus_write8((struct t2bus *)b, c->a[0] & 0xffffffu, 0x00u) != 0)
            { printf("T2GEN V0.71 WRITE_FAULT: PC=00e11e opcode=10fc EA=A0 addr=%06lx size=B value=00 D0=%08lx A0=%08lx A4=%08lx A7=%06lx SR=%04x\n", (unsigned long)(c->a[0] & 0xffffffu), (unsigned long)c->d[0], (unsigned long)c->a[0], (unsigned long)c->a[4], (unsigned long)c->a[7], (unsigned)c->sr); return -3; }
          c->a[0] = (c->a[0] + 1u) & 0xffffffu;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0xe122u, 0x51c8u)) return -1;
          { uint16_t count = (uint16_t)(c->d[0] - 1u);
            c->d[0] = (c->d[0] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00e11eu : 0x00e126u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00e126u:
        {
          if (!match16(b, 0xe126u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00e128u:
        {
          if (!match16(b, 0xe128u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xe12au, 0x4eb8u)) return -1;
          if (!match16(b, 0xe12cu, 0x4a50u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00e12eu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004a50u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00e12eu:
        {
          if (!match16(b, 0xe12eu, 0x4eb8u)) return -1;
          if (!match16(b, 0xe130u, 0x4a6cu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00e132u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004a6cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00e132u:
        {
          if (!match16(b, 0xe132u, 0x23fcu)) return -1;
          if (!match32(b, 0xe134u, 0x40000000u) || !match32(b, 0xe138u, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0x40000000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=00e132 addr=00c00004 value=40000000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x40000000u & 0x80000000u) ? 8u : 0u) | (0x40000000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0xe13cu, 0x303cu)) return -1;
          if (!match16(b, 0xe13eu, 0x0187u)) return -1;
          c->d[0] = (c->d[0] & 0xffff0000u) | 0x0187u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0187u & 0x8000u) ? 8u : 0u) | (0x0187u == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0xe140u, 0x41fau)) return -1;
          if (!match16(b, 0xe142u, 0x0198u)) return -1;
          c->a[0] = 0x00e2dau;
          c->cycles += 8u;
          if (!match16(b, 0xe144u, 0x4eb8u)) return -1;
          if (!match16(b, 0xe146u, 0x4a00u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00e148u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004a00u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00e148u:
        {
          if (!match16(b, 0xe148u, 0x700au)) return -1;
          c->d[0] = (uint32_t)(int32_t)(10);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xe14au, 0x720au)) return -1;
          c->d[1] = (uint32_t)(int32_t)(10);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xe14cu, 0x740cu)) return -1;
          c->d[2] = (uint32_t)(int32_t)(12);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[2] & 0x80000000u) ? 8u : 0u) | (c->d[2] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xe14eu, 0x7604u)) return -1;
          c->d[3] = (uint32_t)(int32_t)(4);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[3] & 0x80000000u) ? 8u : 0u) | (c->d[3] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xe150u, 0x7801u)) return -1;
          c->d[4] = (uint32_t)(int32_t)(1);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[4] & 0x80000000u) ? 8u : 0u) | (c->d[4] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xe152u, 0x3a3cu)) return -1;
          if (!match16(b, 0xe154u, 0xe000u)) return -1;
          c->d[5] = (c->d[5] & 0xffff0000u) | 0xe000u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xe000u & 0x8000u) ? 8u : 0u) | (0xe000u == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0xe156u, 0x6100u)) return -1;
          if (!match16(b, 0xe158u, 0x0130u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00e15au) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00e288u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00e15au:
        {
          if (!match16(b, 0xe15au, 0x41fau)) return -1;
          if (!match16(b, 0xe15cu, 0x00e4u)) return -1;
          c->a[0] = 0x00e240u;
          c->cycles += 8u;
          if (!match16(b, 0xe15eu, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xe160u, 0x6100u)) return -1;
          if (!match16(b, 0xe162u, 0xd722u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00e164u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00b884u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00e164u:
        {
          if (!match16(b, 0xe164u, 0x08f9u)) return -1;
          { uint8_t v; if(native_bus_read8(b,0x00ff010du,&v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&~4u)|((v&(1u<<5))?0u:4u));
            if(native_bus_write8((struct t2bus *)b,0x00ff010du,(uint8_t)(v|(1u<<5)))!=0)return -3; }
          c->cycles+=20u;
          if (!match16(b, 0xe16cu, 0x33f9u)) return -1;
          if (!match32(b, 0xe16eu, 0x00ff010cu) || !match32(b, 0xe172u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0xe176u, 0x41f9u)) return -1;
          if (!match32(b, 0xe178u, 0x000fd4b0u)) return -1;
          c->a[0] = 0x000fd4b0u;
          c->cycles += 12u;
          if (!match16(b, 0xe17cu, 0x6100u)) return -1;
          if (!match16(b, 0xe17eu, 0xb83au)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00e180u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0099b8u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00e180u:
        {
          if (!match16(b, 0xe180u, 0x6100u)) return -1;
          if (!match16(b, 0xe182u, 0xbf62u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00e184u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a0e4u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00e184u:
        {
          if (!match16(b, 0xe184u, 0x303cu)) return -1;
          if (!match16(b, 0xe186u, 0x001eu)) return -1;
          c->d[0] = (c->d[0] & 0xffff0000u) | 0x001eu;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x001eu & 0x8000u) ? 8u : 0u) | (0x001eu == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0xe188u, 0x6100u)) return -1;
          if (!match16(b, 0xe18au, 0xbf94u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00e18cu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a11eu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00e18cu:
        {
          if (!match16(b, 0xe18cu, 0x2479u)) return -1;
          if (!match32(b, 0xe18eu, 0x00ff019au)) return -1;
          if (native_bus_read32(b, 0x00ff019au, &c->a[2]) != 0) return -3;
          c->cycles += 20u;
          if (!match16(b, 0xe192u, 0x421au)) return -1;
          if(native_bus_write8((struct t2bus *)b,c->a[2],0u))return -3;
          c->a[2]=(c->a[2]+1u)&0xffffffu;
          c->sr=(c->sr&0xfff0u)|4u; c->cycles+=12u;
          if (!match16(b, 0xe194u, 0x7026u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(38);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xe196u, 0x7209u)) return -1;
          c->d[1] = (uint32_t)(int32_t)(9);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xe198u, 0x14c0u)) return -1;
          {uint8_t v=(uint8_t)c->d[0];if(native_bus_write8((struct t2bus *)b,c->a[2],v))return -3;c->a[2]=(c->a[2]+1u)&0xffffffu;c->sr=(c->sr&0xfff0u)|((v&128u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=8u;
          if (!match16(b, 0xe19au, 0x5540u)) return -1;
          {uint32_t dst=c->d[0]&65535u,src=2u,r=(dst-src)&65535u;
           c->d[0]=(c->d[0]&0xffff0000u)|r;
           uint16_t cy=(dst<src),ov=((dst^src)&(dst^r)&32768u)!=0u;
           c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(cy?17u:0u));}
          c->cycles+=4u;
          if (!match16(b, 0xe19cu, 0x51c9u)) return -1;
          { uint16_t count = (uint16_t)(c->d[1] - 1u);
            c->d[1] = (c->d[1] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00e198u : 0x00e1a0u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00e198u:
        {
          if (!match16(b, 0xe198u, 0x14c0u)) return -1;
          {uint8_t v=(uint8_t)c->d[0];if(native_bus_write8((struct t2bus *)b,c->a[2],v))return -3;c->a[2]=(c->a[2]+1u)&0xffffffu;c->sr=(c->sr&0xfff0u)|((v&128u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=8u;
          if (!match16(b, 0xe19au, 0x5540u)) return -1;
          {uint32_t dst=c->d[0]&65535u,src=2u,r=(dst-src)&65535u;
           c->d[0]=(c->d[0]&0xffff0000u)|r;
           uint16_t cy=(dst<src),ov=((dst^src)&(dst^r)&32768u)!=0u;
           c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(cy?17u:0u));}
          c->cycles+=4u;
          if (!match16(b, 0xe19cu, 0x51c9u)) return -1;
          { uint16_t count = (uint16_t)(c->d[1] - 1u);
            c->d[1] = (c->d[1] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00e198u : 0x00e1a0u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00e1a0u:
        {
          if (!match16(b, 0xe1a0u, 0x5a4au)) return -1;
          c->a[2] += 5u;
          c->cycles += 8u;
          if (!match16(b, 0xe1a2u, 0x47fau)) return -1;
          if (!match16(b, 0xe1a4u, 0x00bcu)) return -1;
          c->a[3] = 0x00e260u;
          c->cycles += 8u;
          if (!match16(b, 0xe1a6u, 0x7e13u)) return -1;
          c->d[7] = (uint32_t)(int32_t)(19);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[7] & 0x80000000u) ? 8u : 0u) | (c->d[7] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xe1a8u, 0x7200u)) return -1;
          c->d[1] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xe1aau, 0x7002u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(2);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xe1acu, 0x6100u)) return -1;
          if (!match16(b, 0xe1aeu, 0xbf70u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00e1b0u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a11eu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00e1aau:
        {
          if (!match16(b, 0xe1aau, 0x7002u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(2);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xe1acu, 0x6100u)) return -1;
          if (!match16(b, 0xe1aeu, 0xbf70u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00e1b0u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a11eu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00e1b0u:
        {
          if (!match16(b, 0xe1b0u, 0x08b9u)) return -1;
          if (!match16(b, 0xe1b2u, 0x0005u) || !match32(b, 0xe1b4u, 0x00ff010du)) return -1;
          if (native_bus_read8(b, 0x00ff010du, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 5)) ? 0u : 4u));
          if (native_bus_write8((struct t2bus *)b, 0x00ff010du, (uint8_t)(byte_value & ~(1u << 5))) != 0) return -3;
          c->cycles += 16u;
          if (!match16(b, 0xe1b8u, 0x33f9u)) return -1;
          if (!match32(b, 0xe1bau, 0x00ff010cu) || !match32(b, 0xe1beu, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0xe1c2u, 0x4a79u)) return -1;
          if (!match32(b, 0xe1c4u, 0x00ff0242u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff0242u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0xe1c8u, 0x6700u)) return -1;
          if (!match16(b, 0xe1cau, 0x0016u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x00e1e0u : 0x00e1ccu;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00e1ccu:
        {
          if (!match16(b, 0xe1ccu, 0x3039u)) return -1;
          if (!match32(b, 0xe1ceu, 0x00c00008u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00c00008u, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0xe1d2u, 0x0c40u)) return -1;
          if(!match16(b,0xe1d4u,0xc000u))return -1;
          {uint32_t x=c->d[0]&65535u,y=0xc000u,r=(x-y)&65535u; c->sr=(c->sr&0xfff0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u)|(((x^y)&(x^r)&0x8000u)?2u:0u)|(x<y?1u:0u);}
          c->cycles+=8u;
          if (!match16(b, 0xe1d6u, 0x6500u)) return -1;
          if (!match16(b, 0xe1d8u, 0x0008u)) return -1;
          c->pc = ((c->sr & 1u)) ? 0x00e1e0u : 0x00e1dau;
          c->cycles += ((c->sr & 1u)) ? 10u : 8u;
          return 0;
        }
      case 0x00e1dau:
        {
          if (!match16(b, 0xe1dau, 0x0c40u)) return -1;
          if(!match16(b,0xe1dcu,0xf000u))return -1;
          {uint32_t x=c->d[0]&65535u,y=0xf000u,r=(x-y)&65535u; c->sr=(c->sr&0xfff0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u)|(((x^y)&(x^r)&0x8000u)?2u:0u)|(x<y?1u:0u);}
          c->cycles+=8u;
          if (!match16(b, 0xe1deu, 0x65ecu)) return -1;
          c->pc = ((c->sr & 1u)) ? 0x00e1ccu : 0x00e1e0u;
          c->cycles += ((c->sr & 1u)) ? 10u : 8u;
          return 0;
        }
      case 0x00e1e0u:
        {
          if (!match16(b, 0xe1e0u, 0x23fcu)) return -1;
          if (!match32(b, 0xe1e2u, 0xc0040000u) || !match32(b, 0xe1e6u, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0xc0040000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=00e1e0 addr=00c00004 value=c0040000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0xc0040000u & 0x80000000u) ? 8u : 0u) | (0xc0040000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0xe1eau, 0x70f0u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(-16);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xe1ecu, 0x7c0au)) return -1;
          c->d[6] = (uint32_t)(int32_t)(10);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[6] & 0x80000000u) ? 8u : 0u) | (c->d[6] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xe1eeu, 0x1232u)) return -1;
          if(!match16(b,0xe1f0u,0x0000u))return -1;
          if(native_bus_read8(b,(c->a[2]+((uint32_t)(int32_t)(int16_t)c->d[0])+(uint32_t)(0))&0xffffffu,&byte_value)!=0)return -3;
          c->d[1]=(c->d[1]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&128u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=14u;
          if (!match16(b, 0xe1f2u, 0x5401u)) return -1;
          { uint32_t dst=c->d[1]&255u,src=2u,r=(dst+src)&255u;
            c->d[1]=(c->d[1]&0xffffff00u)|r;
            uint16_t cy=((dst+src)>255u)?1u:0u;
            uint16_t ov=((~(dst^src)&(dst^r)&128u)!=0u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&128u)?8u:0u)|(r==0u?4u:0u)|ov|cy|(cy?16u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0xe1f4u, 0x0c01u)) return -1;
          if (!match16(b, 0xe1f6u, 0x0028u)) return -1;
          { uint8_t dst=(uint8_t)c->d[1], src=0x28u, result=(uint8_t)(dst-src);
            uint16_t n=(result&0x80u)?8u:0u, z=(result==0u)?4u:0u;
            uint16_t v=((dst^src)&(dst^result)&0x80u)?2u:0u;
            uint16_t carry=(dst<src)?1u:0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|n|z|v|carry);
          }
          c->cycles += 8u;
          if (!match16(b, 0xe1f8u, 0x6602u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x00e1fcu : 0x00e1fau;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00e1eeu:
        {
          if (!match16(b, 0xe1eeu, 0x1232u)) return -1;
          if(!match16(b,0xe1f0u,0x0000u))return -1;
          if(native_bus_read8(b,(c->a[2]+((uint32_t)(int32_t)(int16_t)c->d[0])+(uint32_t)(0))&0xffffffu,&byte_value)!=0)return -3;
          c->d[1]=(c->d[1]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&128u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=14u;
          if (!match16(b, 0xe1f2u, 0x5401u)) return -1;
          { uint32_t dst=c->d[1]&255u,src=2u,r=(dst+src)&255u;
            c->d[1]=(c->d[1]&0xffffff00u)|r;
            uint16_t cy=((dst+src)>255u)?1u:0u;
            uint16_t ov=((~(dst^src)&(dst^r)&128u)!=0u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&128u)?8u:0u)|(r==0u?4u:0u)|ov|cy|(cy?16u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0xe1f4u, 0x0c01u)) return -1;
          if (!match16(b, 0xe1f6u, 0x0028u)) return -1;
          { uint8_t dst=(uint8_t)c->d[1], src=0x28u, result=(uint8_t)(dst-src);
            uint16_t n=(result&0x80u)?8u:0u, z=(result==0u)?4u:0u;
            uint16_t v=((dst^src)&(dst^result)&0x80u)?2u:0u;
            uint16_t carry=(dst<src)?1u:0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|n|z|v|carry);
          }
          c->cycles += 8u;
          if (!match16(b, 0xe1f8u, 0x6602u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x00e1fcu : 0x00e1fau;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00e1f2u:
        {
          if (!match16(b, 0xe1f2u, 0x5401u)) return -1;
          { uint32_t dst=c->d[1]&255u,src=2u,r=(dst+src)&255u;
            c->d[1]=(c->d[1]&0xffffff00u)|r;
            uint16_t cy=((dst+src)>255u)?1u:0u;
            uint16_t ov=((~(dst^src)&(dst^r)&128u)!=0u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&128u)?8u:0u)|(r==0u?4u:0u)|ov|cy|(cy?16u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0xe1f4u, 0x0c01u)) return -1;
          if (!match16(b, 0xe1f6u, 0x0028u)) return -1;
          { uint8_t dst=(uint8_t)c->d[1], src=0x28u, result=(uint8_t)(dst-src);
            uint16_t n=(result&0x80u)?8u:0u, z=(result==0u)?4u:0u;
            uint16_t v=((dst^src)&(dst^result)&0x80u)?2u:0u;
            uint16_t carry=(dst<src)?1u:0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|n|z|v|carry);
          }
          c->cycles += 8u;
          if (!match16(b, 0xe1f8u, 0x6602u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x00e1fcu : 0x00e1fau;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00e1fau:
        {
          if (!match16(b, 0xe1fau, 0x4201u)) return -1;
          c->d[1] &= 0xffffff00u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 4u;
          if (!match16(b, 0xe1fcu, 0x1581u)) return -1;
          if (!match16(b,0xe1feu,0x0000u)) return -1;
          { uint32_t ea=(uint32_t)(c->a[2]+((int32_t)(int16_t)(c->d[0]&0xffffu))+(0));
            byte_value=(uint8_t)c->d[1];
            if (native_bus_write8((struct t2bus *)b,ea&0xffffffu,byte_value)!=0) return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          }
          c->cycles+=18u;
          if (!match16(b, 0xe200u, 0x5200u)) return -1;
          { uint32_t dst=c->d[0]&255u,src=1u,r=(dst+src)&255u;
            c->d[0]=(c->d[0]&0xffffff00u)|r;
            uint16_t cy=((dst+src)>255u)?1u:0u;
            uint16_t ov=((~(dst^src)&(dst^r)&128u)!=0u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&128u)?8u:0u)|(r==0u?4u:0u)|ov|cy|(cy?16u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0xe202u, 0x33f3u)) return -1;
          if (!match16(b,0xe204u,0x1000u)||!match32(b,0xe206u,0x00c00000u)) return -1;
          { uint32_t ea=(c->a[3]+((int32_t)(int16_t)(c->d[1]&0xffffu))+(0))&0xffffffu; uint16_t val;
            if (native_bus_read16(b,ea,&val)!=0) return -3;
            if (native_bus_write16((struct t2bus *)b,0x00c00000u,val)!=0) return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((val&0x8000u)?8u:0u)|(val==0u?4u:0u));
          }
          c->cycles+=26u;
          if (!match16(b, 0xe20au, 0x51ceu)) return -1;
          { uint16_t count = (uint16_t)(c->d[6] - 1u);
            c->d[6] = (c->d[6] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00e1eeu : 0x00e20eu;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00e1fcu:
        {
          if (!match16(b, 0xe1fcu, 0x1581u)) return -1;
          if (!match16(b,0xe1feu,0x0000u)) return -1;
          { uint32_t ea=(uint32_t)(c->a[2]+((int32_t)(int16_t)(c->d[0]&0xffffu))+(0));
            byte_value=(uint8_t)c->d[1];
            if (native_bus_write8((struct t2bus *)b,ea&0xffffffu,byte_value)!=0) return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          }
          c->cycles+=18u;
          if (!match16(b, 0xe200u, 0x5200u)) return -1;
          { uint32_t dst=c->d[0]&255u,src=1u,r=(dst+src)&255u;
            c->d[0]=(c->d[0]&0xffffff00u)|r;
            uint16_t cy=((dst+src)>255u)?1u:0u;
            uint16_t ov=((~(dst^src)&(dst^r)&128u)!=0u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&128u)?8u:0u)|(r==0u?4u:0u)|ov|cy|(cy?16u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0xe202u, 0x33f3u)) return -1;
          if (!match16(b,0xe204u,0x1000u)||!match32(b,0xe206u,0x00c00000u)) return -1;
          { uint32_t ea=(c->a[3]+((int32_t)(int16_t)(c->d[1]&0xffffu))+(0))&0xffffffu; uint16_t val;
            if (native_bus_read16(b,ea,&val)!=0) return -3;
            if (native_bus_write16((struct t2bus *)b,0x00c00000u,val)!=0) return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((val&0x8000u)?8u:0u)|(val==0u?4u:0u));
          }
          c->cycles+=26u;
          if (!match16(b, 0xe20au, 0x51ceu)) return -1;
          { uint16_t count = (uint16_t)(c->d[6] - 1u);
            c->d[6] = (c->d[6] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00e1eeu : 0x00e20eu;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00e202u:
        {
          if (!match16(b, 0xe202u, 0x33f3u)) return -1;
          if (!match16(b,0xe204u,0x1000u)||!match32(b,0xe206u,0x00c00000u)) return -1;
          { uint32_t ea=(c->a[3]+((int32_t)(int16_t)(c->d[1]&0xffffu))+(0))&0xffffffu; uint16_t val;
            if (native_bus_read16(b,ea,&val)!=0) return -3;
            if (native_bus_write16((struct t2bus *)b,0x00c00000u,val)!=0) return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((val&0x8000u)?8u:0u)|(val==0u?4u:0u));
          }
          c->cycles+=26u;
          if (!match16(b, 0xe20au, 0x51ceu)) return -1;
          { uint16_t count = (uint16_t)(c->d[6] - 1u);
            c->d[6] = (c->d[6] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00e1eeu : 0x00e20eu;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00e20eu:
        {
          if (!match16(b, 0xe20eu, 0x08f9u)) return -1;
          { uint8_t v; if(native_bus_read8(b,0x00ff010du,&v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&~4u)|((v&(1u<<5))?0u:4u));
            if(native_bus_write8((struct t2bus *)b,0x00ff010du,(uint8_t)(v|(1u<<5)))!=0)return -3; }
          c->cycles+=20u;
          if (!match16(b, 0xe216u, 0x33f9u)) return -1;
          if (!match32(b, 0xe218u, 0x00ff010cu) || !match32(b, 0xe21cu, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0xe220u, 0x51cfu)) return -1;
          { uint16_t count = (uint16_t)(c->d[7] - 1u);
            c->d[7] = (c->d[7] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00e1aau : 0x00e224u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00e224u:
        {
          if (!match16(b, 0xe224u, 0x3039u)) return -1;
          if (!match32(b, 0xe226u, 0x00ff0244u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff0244u, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0xe22au, 0xe248u)) return -1;
          { uint16_t old=(uint16_t)c->d[0],r=(uint16_t)(old>>1);
            uint16_t carry=(old>>0)&1u;
            c->d[0]=(c->d[0]&0xffff0000u)|r;
            c->sr=(uint16_t)((c->sr&0xffe0u)|(r==0u?4u:0u)|(carry?17u:0u));
            c->cycles+=8u;
          }
          if (!match16(b, 0xe22cu, 0x4ebau)) return -1;
          if (!match16(b, 0xe22eu, 0xbef0u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00e230u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a11eu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00e22cu:
        {
          if (!match16(b, 0xe22cu, 0x4ebau)) return -1;
          if (!match16(b, 0xe22eu, 0xbef0u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00e230u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a11eu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00e230u:
        {
          if (!match16(b, 0xe230u, 0x41f9u)) return -1;
          if (!match32(b, 0xe232u, 0x000fd4bcu)) return -1;
          c->a[0] = 0x000fd4bcu;
          c->cycles += 12u;
          if (!match16(b, 0xe236u, 0x6100u)) return -1;
          if (!match16(b, 0xe238u, 0xb780u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00e23au) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0099b8u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00e23au:
        {
          if (!match16(b, 0xe23au, 0x6100u)) return -1;
          if (!match16(b, 0xe23cu, 0xbea8u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00e23eu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a0e4u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00e23eu:
        {
          if (!match16(b, 0xe23eu, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00e288u:
        {
          if (!match16(b, 0xe288u, 0xd040u)) return -1;
          { uint32_t x = c->d[0] & 65535u, y = c->d[0] & 65535u, r = (x+y) & 65535u;
            uint16_t flags = (uint16_t)(((r & 0x8000u) ? 8u : 0u) | ((r == 0u) ? 4u : 0u) | (((~(x ^ y) & (r ^ y)) & 0x8000u) ? 2u : 0u) | ((x+y > 65535u) ? 17u : 0u));
            c->d[0] = (c->d[0] & 0xffff0000u) | r;
            c->sr = (uint16_t)((c->sr & 0xffe0u) | flags);
          }
          c->cycles += 4u;
          if (!match16(b, 0xe28au, 0x3e3cu)) return -1;
          if (!match16(b, 0xe28cu, 0x0040u)) return -1;
          c->d[7] = (c->d[7] & 0xffff0000u) | 0x0040u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0040u & 0x8000u) ? 8u : 0u) | (0x0040u == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0xe28eu, 0xde47u)) return -1;
          { uint32_t x = c->d[7] & 65535u, y = c->d[7] & 65535u, r = (x+y) & 65535u;
            uint16_t flags = (uint16_t)(((r & 0x8000u) ? 8u : 0u) | ((r == 0u) ? 4u : 0u) | (((~(x ^ y) & (r ^ y)) & 0x8000u) ? 2u : 0u) | ((x+y > 65535u) ? 17u : 0u));
            c->d[7] = (c->d[7] & 0xffff0000u) | r;
            c->sr = (uint16_t)((c->sr & 0xffe0u) | flags);
          }
          c->cycles += 4u;
          if (!match16(b, 0xe290u, 0xc2c7u)) return -1;
          c->d[1] = (uint32_t)((c->d[1] & 0xffffu) * (c->d[7] & 0xffffu));
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 70u;
          if (!match16(b, 0xe292u, 0xd041u)) return -1;
          { uint32_t x = c->d[1] & 65535u, y = c->d[0] & 65535u, r = (x+y) & 65535u;
            uint16_t flags = (uint16_t)(((r & 0x8000u) ? 8u : 0u) | ((r == 0u) ? 4u : 0u) | (((~(x ^ y) & (r ^ y)) & 0x8000u) ? 2u : 0u) | ((x+y > 65535u) ? 17u : 0u));
            c->d[0] = (c->d[0] & 0xffff0000u) | r;
            c->sr = (uint16_t)((c->sr & 0xffe0u) | flags);
          }
          c->cycles += 4u;
          if (!match16(b, 0xe294u, 0xd045u)) return -1;
          { uint32_t x = c->d[5] & 65535u, y = c->d[0] & 65535u, r = (x+y) & 65535u;
            uint16_t flags = (uint16_t)(((r & 0x8000u) ? 8u : 0u) | ((r == 0u) ? 4u : 0u) | (((~(x ^ y) & (r ^ y)) & 0x8000u) ? 2u : 0u) | ((x+y > 65535u) ? 17u : 0u));
            c->d[0] = (c->d[0] & 0xffff0000u) | r;
            c->sr = (uint16_t)((c->sr & 0xffe0u) | flags);
          }
          c->cycles += 4u;
          if (!match16(b, 0xe296u, 0x3204u)) return -1;
          { uint16_t v=(uint16_t)c->d[4]; c->d[1]=(c->d[1] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0xe298u, 0x3c03u)) return -1;
          { uint16_t v=(uint16_t)c->d[3]; c->d[6]=(c->d[6] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0xe29au, 0x5346u)) return -1;
          {uint32_t dst=c->d[6]&65535u,src=1u,r=(dst-src)&65535u;
           c->d[6]=(c->d[6]&0xffff0000u)|r;
           uint16_t cy=(dst<src),ov=((dst^src)&(dst^r)&32768u)!=0u;
           c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(cy?17u:0u));}
          c->cycles+=4u;
          if (!match16(b, 0xe29cu, 0x5342u)) return -1;
          {uint32_t dst=c->d[2]&65535u,src=1u,r=(dst-src)&65535u;
           c->d[2]=(c->d[2]&0xffff0000u)|r;
           uint16_t cy=(dst<src),ov=((dst^src)&(dst^r)&32768u)!=0u;
           c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(cy?17u:0u));}
          c->cycles+=4u;
          if (!match16(b, 0xe29eu, 0x3a02u)) return -1;
          { uint16_t v=(uint16_t)c->d[2]; c->d[5]=(c->d[5] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0xe2a0u, 0x48e7u)) return -1;
          if (!match16(b, 0xe2a2u, 0xc000u)) return -1;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[1]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[0]) != 0) return -3;
          c->cycles += 24u;
          if (!match16(b, 0xe2a4u, 0x3200u)) return -1;
          { uint16_t v=(uint16_t)c->d[0]; c->d[1]=(c->d[1] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0xe2a6u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xe2a8u, 0x3001u)) return -1;
          { uint16_t v=(uint16_t)c->d[1]; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0xe2aau, 0xe588u)) return -1;
          { uint32_t x=c->d[0],r=x<<2;
            uint16_t carry=(uint16_t)((x>>30)&1u);
            c->d[0]=r;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x80000000u)?8u:0u)|(r==0u?4u:0u)|(carry?17u:0u));
          }
          c->cycles+=12u;
          if (!match16(b, 0xe2acu, 0x3001u)) return -1;
          { uint16_t v=(uint16_t)c->d[1]; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0xe2aeu, 0x0240u)) return -1;
          if (!match16(b, 0xe2b0u, 0x3ffeu)) return -1;
          { uint16_t v=(uint16_t)c->d[0] & 0x3ffeu; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0xe2b2u, 0x0040u)) return -1;
          if(!match16(b,0xe2b4u,0x4000u))return -1;
          {uint16_t v=(uint16_t)(c->d[0]|0x4000u);
           c->d[0]=(c->d[0]&0xffff0000u)|v;
           c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=8u;
          if (!match16(b, 0xe2b6u, 0x4840u)) return -1;
          c->d[0]=(c->d[0]<<16)|(c->d[0]>>16);
          c->sr=(uint16_t)((c->sr&0xfff0u)|((c->d[0]&0x80000000u)?8u:0u)|(c->d[0]==0u?4u:0u));
          c->cycles+=4u;
          if (!match16(b, 0xe2b8u, 0x23c0u)) return -1;
          { uint32_t v=c->d[0]; if(native_bus_write32((struct t2bus *)b,0x00c00004u,v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=20u;
          if (!match16(b, 0xe2beu, 0x4cdfu)) return -1;
          if (!match16(b, 0xe2c0u, 0x0003u)) return -1;
          { uint32_t addr = c->a[7]; uint32_t val; uint16_t word; unsigned idx;
            for (idx = 0; idx < 16u; ++idx)
              {
                if (!(0x0003u & (1u << idx))) continue;
                if (native_bus_read32(b, addr, &val) != 0) return -3;
                if (idx < 8u) c->d[idx] = val;
                else c->a[idx - 8u] = val;
                addr = (addr + 4u) & 0xffffffu;
              }
            c->a[7] = addr; /* postincrement wins if base An is in mask */
          }
          c->cycles += 24u;
          if (!match16(b, 0xe2c2u, 0xd047u)) return -1;
          { uint32_t x = c->d[7] & 65535u, y = c->d[0] & 65535u, r = (x+y) & 65535u;
            uint16_t flags = (uint16_t)(((r & 0x8000u) ? 8u : 0u) | ((r == 0u) ? 4u : 0u) | (((~(x ^ y) & (r ^ y)) & 0x8000u) ? 2u : 0u) | ((x+y > 65535u) ? 17u : 0u));
            c->d[0] = (c->d[0] & 0xffff0000u) | r;
            c->sr = (uint16_t)((c->sr & 0xffe0u) | flags);
          }
          c->cycles += 4u;
          if (!match16(b, 0xe2c4u, 0x33c1u)) return -1;
          if (!match32(b, 0xe2c6u, 0x00c00000u)) return -1;
          { uint16_t v=(uint16_t)c->d[1];
            if (native_bus_write16((struct t2bus *)b,0x00c00000u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0xe2cau, 0xd243u)) return -1;
          { uint32_t x = c->d[3] & 65535u, y = c->d[1] & 65535u, r = (x+y) & 65535u;
            uint16_t flags = (uint16_t)(((r & 0x8000u) ? 8u : 0u) | ((r == 0u) ? 4u : 0u) | (((~(x ^ y) & (r ^ y)) & 0x8000u) ? 2u : 0u) | ((x+y > 65535u) ? 17u : 0u));
            c->d[1] = (c->d[1] & 0xffff0000u) | r;
            c->sr = (uint16_t)((c->sr & 0xffe0u) | flags);
          }
          c->cycles += 4u;
          if (!match16(b, 0xe2ccu, 0x51cdu)) return -1;
          { uint16_t count = (uint16_t)(c->d[5] - 1u);
            c->d[5] = (c->d[5] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00e2c4u : 0x00e2d0u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00e29eu:
        {
          if (!match16(b, 0xe29eu, 0x3a02u)) return -1;
          { uint16_t v=(uint16_t)c->d[2]; c->d[5]=(c->d[5] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0xe2a0u, 0x48e7u)) return -1;
          if (!match16(b, 0xe2a2u, 0xc000u)) return -1;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[1]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[0]) != 0) return -3;
          c->cycles += 24u;
          if (!match16(b, 0xe2a4u, 0x3200u)) return -1;
          { uint16_t v=(uint16_t)c->d[0]; c->d[1]=(c->d[1] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0xe2a6u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xe2a8u, 0x3001u)) return -1;
          { uint16_t v=(uint16_t)c->d[1]; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0xe2aau, 0xe588u)) return -1;
          { uint32_t x=c->d[0],r=x<<2;
            uint16_t carry=(uint16_t)((x>>30)&1u);
            c->d[0]=r;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x80000000u)?8u:0u)|(r==0u?4u:0u)|(carry?17u:0u));
          }
          c->cycles+=12u;
          if (!match16(b, 0xe2acu, 0x3001u)) return -1;
          { uint16_t v=(uint16_t)c->d[1]; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0xe2aeu, 0x0240u)) return -1;
          if (!match16(b, 0xe2b0u, 0x3ffeu)) return -1;
          { uint16_t v=(uint16_t)c->d[0] & 0x3ffeu; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0xe2b2u, 0x0040u)) return -1;
          if(!match16(b,0xe2b4u,0x4000u))return -1;
          {uint16_t v=(uint16_t)(c->d[0]|0x4000u);
           c->d[0]=(c->d[0]&0xffff0000u)|v;
           c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=8u;
          if (!match16(b, 0xe2b6u, 0x4840u)) return -1;
          c->d[0]=(c->d[0]<<16)|(c->d[0]>>16);
          c->sr=(uint16_t)((c->sr&0xfff0u)|((c->d[0]&0x80000000u)?8u:0u)|(c->d[0]==0u?4u:0u));
          c->cycles+=4u;
          if (!match16(b, 0xe2b8u, 0x23c0u)) return -1;
          { uint32_t v=c->d[0]; if(native_bus_write32((struct t2bus *)b,0x00c00004u,v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=20u;
          if (!match16(b, 0xe2beu, 0x4cdfu)) return -1;
          if (!match16(b, 0xe2c0u, 0x0003u)) return -1;
          { uint32_t addr = c->a[7]; uint32_t val; uint16_t word; unsigned idx;
            for (idx = 0; idx < 16u; ++idx)
              {
                if (!(0x0003u & (1u << idx))) continue;
                if (native_bus_read32(b, addr, &val) != 0) return -3;
                if (idx < 8u) c->d[idx] = val;
                else c->a[idx - 8u] = val;
                addr = (addr + 4u) & 0xffffffu;
              }
            c->a[7] = addr; /* postincrement wins if base An is in mask */
          }
          c->cycles += 24u;
          if (!match16(b, 0xe2c2u, 0xd047u)) return -1;
          { uint32_t x = c->d[7] & 65535u, y = c->d[0] & 65535u, r = (x+y) & 65535u;
            uint16_t flags = (uint16_t)(((r & 0x8000u) ? 8u : 0u) | ((r == 0u) ? 4u : 0u) | (((~(x ^ y) & (r ^ y)) & 0x8000u) ? 2u : 0u) | ((x+y > 65535u) ? 17u : 0u));
            c->d[0] = (c->d[0] & 0xffff0000u) | r;
            c->sr = (uint16_t)((c->sr & 0xffe0u) | flags);
          }
          c->cycles += 4u;
          if (!match16(b, 0xe2c4u, 0x33c1u)) return -1;
          if (!match32(b, 0xe2c6u, 0x00c00000u)) return -1;
          { uint16_t v=(uint16_t)c->d[1];
            if (native_bus_write16((struct t2bus *)b,0x00c00000u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0xe2cau, 0xd243u)) return -1;
          { uint32_t x = c->d[3] & 65535u, y = c->d[1] & 65535u, r = (x+y) & 65535u;
            uint16_t flags = (uint16_t)(((r & 0x8000u) ? 8u : 0u) | ((r == 0u) ? 4u : 0u) | (((~(x ^ y) & (r ^ y)) & 0x8000u) ? 2u : 0u) | ((x+y > 65535u) ? 17u : 0u));
            c->d[1] = (c->d[1] & 0xffff0000u) | r;
            c->sr = (uint16_t)((c->sr & 0xffe0u) | flags);
          }
          c->cycles += 4u;
          if (!match16(b, 0xe2ccu, 0x51cdu)) return -1;
          { uint16_t count = (uint16_t)(c->d[5] - 1u);
            c->d[5] = (c->d[5] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00e2c4u : 0x00e2d0u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00e2c4u:
        {
          if (!match16(b, 0xe2c4u, 0x33c1u)) return -1;
          if (!match32(b, 0xe2c6u, 0x00c00000u)) return -1;
          { uint16_t v=(uint16_t)c->d[1];
            if (native_bus_write16((struct t2bus *)b,0x00c00000u,v)!=0) return -3;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u)?8u:0u) | (v==0u?4u:0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0xe2cau, 0xd243u)) return -1;
          { uint32_t x = c->d[3] & 65535u, y = c->d[1] & 65535u, r = (x+y) & 65535u;
            uint16_t flags = (uint16_t)(((r & 0x8000u) ? 8u : 0u) | ((r == 0u) ? 4u : 0u) | (((~(x ^ y) & (r ^ y)) & 0x8000u) ? 2u : 0u) | ((x+y > 65535u) ? 17u : 0u));
            c->d[1] = (c->d[1] & 0xffff0000u) | r;
            c->sr = (uint16_t)((c->sr & 0xffe0u) | flags);
          }
          c->cycles += 4u;
          if (!match16(b, 0xe2ccu, 0x51cdu)) return -1;
          { uint16_t count = (uint16_t)(c->d[5] - 1u);
            c->d[5] = (c->d[5] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00e2c4u : 0x00e2d0u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00e2d0u:
        {
          if (!match16(b, 0xe2d0u, 0x5244u)) return -1;
          { uint16_t dst=(uint16_t)c->d[4],r=(uint16_t)(dst+1u);
            c->d[4]=(c->d[4]&0xffff0000u)|r;
            uint16_t carry=(dst==0xffffu)?1u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u)|(dst==0x7fffu?2u:0u)|carry|(carry?16u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0xe2d2u, 0x3204u)) return -1;
          { uint16_t v=(uint16_t)c->d[4]; c->d[1]=(c->d[1] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 4u;
          if (!match16(b, 0xe2d4u, 0x51ceu)) return -1;
          { uint16_t count = (uint16_t)(c->d[6] - 1u);
            c->d[6] = (c->d[6] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00e29eu : 0x00e2d8u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00e2d8u:
        {
          if (!match16(b, 0xe2d8u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00e90eu:
        {
          if (!match16(b, 0xe90eu, 0x41f9u)) return -1;
          if (!match32(b, 0xe910u, 0x000176e1u)) return -1;
          c->a[0] = 0x000176e1u;
          c->cycles += 12u;
          if (!match16(b, 0xe914u, 0x3039u)) return -1;
          if (!match32(b, 0xe916u, 0x00ff03c4u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff03c4u, &val) != 0) return -3;
            c->d[0] = (c->d[0] & 0xffff0000u) | val;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 16u;
          if (!match16(b, 0xe91au, 0x1030u)) return -1;
          if(!match16(b,0xe91cu,0x0000u))return -1;
          if(native_bus_read8(b,(c->a[0]+((uint32_t)(int32_t)(int16_t)c->d[0])+(uint32_t)(0))&0xffffffu,&byte_value)!=0)return -3;
          c->d[0]=(c->d[0]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&128u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=14u;
          if (!match16(b, 0xe91eu, 0x13c0u)) return -1;
          if (!match32(b,0xe920u,0x00ff2767u)) return -1;
          byte_value=(uint8_t)c->d[0];
          if (native_bus_write8((struct t2bus *)b,0x00ff2767u,byte_value)!=0) return -3;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0xe924u, 0x0c00u)) return -1;
          if (!match16(b, 0xe926u, 0x0002u)) return -1;
          { uint8_t dst=(uint8_t)c->d[0], src=0x02u, result=(uint8_t)(dst-src);
            uint16_t n=(result&0x80u)?8u:0u, z=(result==0u)?4u:0u;
            uint16_t v=((dst^src)&(dst^result)&0x80u)?2u:0u;
            uint16_t carry=(dst<src)?1u:0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|n|z|v|carry);
          }
          c->cycles += 8u;
          if (!match16(b, 0xe928u, 0x6600u)) return -1;
          if (!match16(b, 0xe92au, 0x0038u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x00e962u : 0x00e92cu;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00e92cu:
        {
          if (!match16(b, 0xe92cu, 0x41f9u)) return -1;
          if (!match32(b, 0xe92eu, 0x00ff0b68u)) return -1;
          c->a[0] = 0x00ff0b68u;
          c->cycles += 12u;
          if (!match16(b, 0xe932u, 0x610au)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00e934u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00e93eu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00e934u:
        {
          if (!match16(b, 0xe934u, 0x41f9u)) return -1;
          if (!match32(b, 0xe936u, 0x00ff0b79u)) return -1;
          c->a[0] = 0x00ff0b79u;
          c->cycles += 12u;
          if (!match16(b, 0xe93au, 0x6102u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00e93cu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00e93eu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00e93cu:
        {
          if (!match16(b, 0xe93cu, 0x6024u)) return -1;
          c->pc = (1) ? 0x00e962u : 0x00e93eu;
          c->cycles += (1) ? 10u : 8u;
          return 0;
        }
      case 0x00e962u:
        {
          if (!match16(b, 0xe962u, 0x41f9u)) return -1;
          if (!match32(b, 0xe964u, 0x0001783cu)) return -1;
          c->a[0] = 0x0001783cu;
          c->cycles += 12u;
          if (!match16(b, 0xe968u, 0xc0fcu)) return -1;
          if(!match16(b,0xe96au,0x0006u))return -1;
          {uint32_t r=(c->d[0]&65535u)*0x0006u; c->d[0]=r; c->sr=(c->sr&0xfff0u)|((r&0x80000000u)?8u:0u)|(r==0u?4u:0u);}
          c->cycles+=70u;
          if (!match16(b, 0xe96cu, 0x23f0u)) return -1;
          {uint32_t ea=(c->a[0]+((int32_t)(int16_t)(c->d[0]&65535u))+(int8_t)0x00u)&0xffffffu,v;if(native_bus_read32(b,ea,&v)||native_bus_write32((struct t2bus *)b,0xff26aau,v))return -3;c->sr=(c->sr&0xfff0u)|((v&0x80000000u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=28u;
          c->pc = 0x00e974u;
          return 0;
        }
      case 0x00ead4u:
        {
          if (!match16(b, 0xead4u, 0x48e7u)) return -1;
          if (!match16(b, 0xead6u, 0xa1f0u)) return -1;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->a[3]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->a[2]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->a[1]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->a[0]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[7]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[2]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[0]) != 0) return -3;
          c->cycles += 64u;
          if (!match16(b, 0xead8u, 0x207cu)) return -1;
          if (!match32(b, 0xeadau, 0x00a00000u)) return -1;
          c->a[0] = 0x00a00000u;
          c->cycles += 12u;
          if (!match16(b, 0xeadeu, 0x227cu)) return -1;
          if (!match32(b, 0xeae0u, 0x00a11100u)) return -1;
          c->a[1] = 0x00a11100u;
          c->cycles += 12u;
          if (!match16(b, 0xeae4u, 0x247cu)) return -1;
          if (!match32(b, 0xeae6u, 0x00a11200u)) return -1;
          c->a[2] = 0x00a11200u;
          c->cycles += 12u;
          if (!match16(b, 0xeaeau, 0x47f9u)) return -1;
          if (!match32(b, 0xeaecu, 0x0005017fu)) return -1;
          c->a[3] = 0x0005017fu;
          c->cycles += 12u;
          if (!match16(b, 0xeaf0u, 0x3e3cu)) return -1;
          if (!match16(b, 0xeaf2u, 0x0100u)) return -1;
          c->d[7] = (c->d[7] & 0xffff0000u) | 0x0100u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0100u & 0x8000u) ? 8u : 0u) | (0x0100u == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0xeaf4u, 0x7000u)) return -1;
          c->d[0] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[0] & 0x80000000u) ? 8u : 0u) | (c->d[0] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xeaf6u, 0x3287u)) return -1;
          if (native_bus_write16((struct t2bus *)b, c->a[1], (uint16_t)c->d[7]) != 0) { printf("T2GEN V0.57 WRITE16_STOP: pc=00eaf6 addr=%06lx\n", (unsigned long)c->a[1]); return -3; }
          c->cycles += 8u;
          if (!match16(b, 0xeaf8u, 0x3487u)) return -1;
          if (native_bus_write16((struct t2bus *)b, c->a[2], (uint16_t)c->d[7]) != 0) { printf("T2GEN V0.57 WRITE16_STOP: pc=00eaf8 addr=%06lx\n", (unsigned long)c->a[2]); return -3; }
          c->cycles += 8u;
          if (!match16(b, 0xeafau, 0x0111u)) return -1;
          if (native_bus_read8(b, c->a[1], &byte_value) != 0) { printf("T2GEN V0.57 BTST_READ_STOP: pc=00eafa addr=%06lx\n", (unsigned long)c->a[1]); return -3; }
          { uint8_t bit = (uint8_t)(c->d[0] & 7u);
            c->sr = (uint16_t)((c->sr & (uint16_t)~4u) | ((byte_value & (1u << bit)) ? 0u : 4u));
            if (c->a[1] == 0xa11100u) printf("T2GEN V0.57 BUSREQ_POLL: pc=00eafa value=%02x bit=%u z=%u\n", (unsigned)byte_value, (unsigned)bit, (unsigned)((c->sr & 4u) != 0u));
          }
          c->cycles += 8u;
          if (!match16(b, 0xeafcu, 0x66fcu)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x00eafau : 0x00eafeu;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00eafau:
        {
          if (!match16(b, 0xeafau, 0x0111u)) return -1;
          if (native_bus_read8(b, c->a[1], &byte_value) != 0) { printf("T2GEN V0.57 BTST_READ_STOP: pc=00eafa addr=%06lx\n", (unsigned long)c->a[1]); return -3; }
          { uint8_t bit = (uint8_t)(c->d[0] & 7u);
            c->sr = (uint16_t)((c->sr & (uint16_t)~4u) | ((byte_value & (1u << bit)) ? 0u : 4u));
            if (c->a[1] == 0xa11100u) printf("T2GEN V0.57 BUSREQ_POLL: pc=00eafa value=%02x bit=%u z=%u\n", (unsigned)byte_value, (unsigned)bit, (unsigned)((c->sr & 4u) != 0u));
          }
          c->cycles += 8u;
          if (!match16(b, 0xeafcu, 0x66fcu)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x00eafau : 0x00eafeu;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00eafeu:
        {
          if (!match16(b, 0xeafeu, 0x343cu)) return -1;
          if (!match16(b, 0xeb00u, 0x15f3u)) return -1;
          c->d[2] = (c->d[2] & 0xffff0000u) | 0x15f3u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x15f3u & 0x8000u) ? 8u : 0u) | (0x15f3u == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0xeb02u, 0x10dbu)) return -1;
          { uint32_t source = c->a[3], dest = c->a[0];
            if (native_bus_read8(b, source, &byte_value) != 0) { printf("T2GEN V0.57 COPY_READ_STOP: pc=00eb02 addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write8((struct t2bus *)b, dest, byte_value) != 0) { printf("T2GEN V0.57 COPY_WRITE_STOP: pc=00eb02 addr=%06lx\n", (unsigned long)dest); return -3; }
            c->a[3] = (source + 1u) & 0xffffffu;
            c->a[0] = (dest + 1u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 128u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          }
          c->cycles += 12u;
          if (!match16(b, 0xeb04u, 0x51cau)) return -1;
          { uint16_t count = (uint16_t)(c->d[2] - 1u);
            c->d[2] = (c->d[2] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00eb02u : 0x00eb08u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00eb02u:
        {
          if (!match16(b, 0xeb02u, 0x10dbu)) return -1;
          { uint32_t source = c->a[3], dest = c->a[0];
            if (native_bus_read8(b, source, &byte_value) != 0) { printf("T2GEN V0.57 COPY_READ_STOP: pc=00eb02 addr=%06lx\n", (unsigned long)source); return -3; }
            if (native_bus_write8((struct t2bus *)b, dest, byte_value) != 0) { printf("T2GEN V0.57 COPY_WRITE_STOP: pc=00eb02 addr=%06lx\n", (unsigned long)dest); return -3; }
            c->a[3] = (source + 1u) & 0xffffffu;
            c->a[0] = (dest + 1u) & 0xffffffu;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 128u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          }
          c->cycles += 12u;
          if (!match16(b, 0xeb04u, 0x51cau)) return -1;
          { uint16_t count = (uint16_t)(c->d[2] - 1u);
            c->d[2] = (c->d[2] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00eb02u : 0x00eb08u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00eb08u:
        {
          if (!match16(b, 0xeb08u, 0x4239u)) return -1;
          if (!match32(b, 0xeb0au, 0x00a01f20u)) return -1;
          if (native_bus_write8((struct t2bus *)b, 0x00a01f20u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0xeb0eu, 0x4239u)) return -1;
          if (!match32(b, 0xeb10u, 0x00a01f21u)) return -1;
          if (native_bus_write8((struct t2bus *)b, 0x00a01f21u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0xeb14u, 0x3480u)) return -1;
          if (native_bus_write16((struct t2bus *)b, c->a[2], (uint16_t)c->d[0]) != 0) { printf("T2GEN V0.57 WRITE16_STOP: pc=00eb14 addr=%06lx\n", (unsigned long)c->a[2]); return -3; }
          c->cycles += 8u;
          if (!match16(b, 0xeb16u, 0x3280u)) return -1;
          if (native_bus_write16((struct t2bus *)b, c->a[1], (uint16_t)c->d[0]) != 0) { printf("T2GEN V0.57 WRITE16_STOP: pc=00eb16 addr=%06lx\n", (unsigned long)c->a[1]); return -3; }
          c->cycles += 8u;
          if (!match16(b, 0xeb18u, 0x3487u)) return -1;
          if (native_bus_write16((struct t2bus *)b, c->a[2], (uint16_t)c->d[7]) != 0) { printf("T2GEN V0.57 WRITE16_STOP: pc=00eb18 addr=%06lx\n", (unsigned long)c->a[2]); return -3; }
          c->cycles += 8u;
          if (!match16(b, 0xeb1au, 0x4cdfu)) return -1;
          if (!match16(b, 0xeb1cu, 0x0f85u)) return -1;
          { uint32_t addr = c->a[7]; uint32_t val; uint16_t word; unsigned idx;
            for (idx = 0; idx < 16u; ++idx)
              {
                if (!(0x0f85u & (1u << idx))) continue;
                if (native_bus_read32(b, addr, &val) != 0) return -3;
                if (idx < 8u) c->d[idx] = val;
                else c->a[idx - 8u] = val;
                addr = (addr + 4u) & 0xffffffu;
              }
            c->a[7] = addr; /* postincrement wins if base An is in mask */
          }
          c->cycles += 64u;
          if (!match16(b, 0xeb1eu, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00eb20u:
        {
          if (!match16(b, 0xeb20u, 0x2f08u)) return -1;
          c->a[7]=(c->a[7]-4u)&0xffffffu;
          if (native_bus_write32((struct t2bus *)b,c->a[7],c->a[0])!=0) return -3;
          c->cycles += 12u;
          if (!match16(b, 0xeb22u, 0x207cu)) return -1;
          if (!match32(b, 0xeb24u, 0x00a11100u)) return -1;
          c->a[0] = 0x00a11100u;
          c->cycles += 12u;
          if (!match16(b, 0xeb28u, 0x30bcu)) return -1;
          if (!match16(b,0xeb2au,0x0100u)) return -1;
          if (native_bus_write16((struct t2bus *)b,c->a[0],0x0100u)!=0) return -3;
          c->sr=(uint16_t)((c->sr&0xfff0u)|0u|0u);
          c->cycles += 12u;
          if (!match16(b, 0xeb2cu, 0x0810u)) return -1;
          if (!match16(b,0xeb2eu,0x0000u)) return -1;
          if (native_bus_read8(b,c->a[0],&byte_value)!=0) return -3;
          c->sr=(uint16_t)((c->sr&~4u)|((byte_value&(1u<<0))?0u:4u));
          c->cycles += 12u;
          if (!match16(b, 0xeb30u, 0x66fau)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x00eb2cu : 0x00eb32u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00eb2cu:
        {
          if (!match16(b, 0xeb2cu, 0x0810u)) return -1;
          if (!match16(b,0xeb2eu,0x0000u)) return -1;
          if (native_bus_read8(b,c->a[0],&byte_value)!=0) return -3;
          c->sr=(uint16_t)((c->sr&~4u)|((byte_value&(1u<<0))?0u:4u));
          c->cycles += 12u;
          if (!match16(b, 0xeb30u, 0x66fau)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x00eb2cu : 0x00eb32u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00eb32u:
        {
          if (!match16(b, 0xeb32u, 0x205fu)) return -1;
          { uint32_t value; if (native_bus_read32(b,c->a[7],&value)!=0) return -3;
            c->a[0]=value&0xffffffu; c->a[7]=(c->a[7]+4u)&0xffffffu;
          }
          c->cycles += 12u;
          if (!match16(b, 0xeb34u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00eb36u:
        {
          if (!match16(b, 0xeb36u, 0x2f08u)) return -1;
          c->a[7]=(c->a[7]-4u)&0xffffffu;
          if (native_bus_write32((struct t2bus *)b,c->a[7],c->a[0])!=0) return -3;
          c->cycles += 12u;
          if (!match16(b, 0xeb38u, 0x207cu)) return -1;
          if (!match32(b, 0xeb3au, 0x00a11100u)) return -1;
          c->a[0] = 0x00a11100u;
          c->cycles += 12u;
          if (!match16(b, 0xeb3eu, 0x4250u)) return -1;
          if (native_bus_write16((struct t2bus *)b,c->a[0],0u)!=0) return -3;
          c->sr=(uint16_t)((c->sr&0xfff0u)|4u);
          c->cycles += 12u;
          if (!match16(b, 0xeb40u, 0x205fu)) return -1;
          { uint32_t value; if (native_bus_read32(b,c->a[7],&value)!=0) return -3;
            c->a[0]=value&0xffffffu; c->a[7]=(c->a[7]+4u)&0xffffffu;
          }
          c->cycles += 12u;
          if (!match16(b, 0xeb42u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00eb44u:
        {
          if (!match16(b, 0xeb44u, 0x0c00u)) return -1;
          if (!match16(b, 0xeb46u, 0x0070u)) return -1;
          { uint8_t dst=(uint8_t)c->d[0], src=0x70u, result=(uint8_t)(dst-src);
            uint16_t n=(result&0x80u)?8u:0u, z=(result==0u)?4u:0u;
            uint16_t v=((dst^src)&(dst^result)&0x80u)?2u:0u;
            uint16_t carry=(dst<src)?1u:0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|n|z|v|carry);
          }
          c->cycles += 8u;
          if (!match16(b, 0xeb48u, 0x651au)) return -1;
          c->pc = ((c->sr & 1u)) ? 0x00eb64u : 0x00eb4au;
          c->cycles += ((c->sr & 1u)) ? 10u : 8u;
          return 0;
        }
      case 0x00eb4au:
        {
          if (!match16(b, 0xeb4au, 0x0c00u)) return -1;
          if (!match16(b, 0xeb4cu, 0x0079u)) return -1;
          { uint8_t dst=(uint8_t)c->d[0], src=0x79u, result=(uint8_t)(dst-src);
            uint16_t n=(result&0x80u)?8u:0u, z=(result==0u)?4u:0u;
            uint16_t v=((dst^src)&(dst^result)&0x80u)?2u:0u;
            uint16_t carry=(dst<src)?1u:0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|n|z|v|carry);
          }
          c->cycles += 8u;
          if (!match16(b, 0xeb4eu, 0x6414u)) return -1;
          c->pc = (!(c->sr & 1u)) ? 0x00eb64u : 0x00eb50u;
          c->cycles += (!(c->sr & 1u)) ? 10u : 8u;
          return 0;
        }
      case 0x00eb4eu:
        {
          if (!match16(b, 0xeb4eu, 0x6414u)) return -1;
          c->pc = (!(c->sr & 1u)) ? 0x00eb64u : 0x00eb50u;
          c->cycles += (!(c->sr & 1u)) ? 10u : 8u;
          return 0;
        }
      case 0x00eb50u:
        {
          if (!match16(b, 0xeb50u, 0x3f00u)) return -1;
          c->a[7]=(c->a[7]-2u)&0xffffffu;
          if (native_bus_write16((struct t2bus *)b,c->a[7],(uint16_t)c->d[0]) != 0) return -3;
          { uint16_t v=(uint16_t)c->d[0]; c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles += 8u;
          if (!match16(b, 0xeb52u, 0x303cu)) return -1;
          if (!match16(b, 0xeb54u, 0x006du)) return -1;
          c->d[0] = (c->d[0] & 0xffff0000u) | 0x006du;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x006du & 0x8000u) ? 8u : 0u) | (0x006du == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0xeb56u, 0x6100u)) return -1;
          if (!match16(b, 0xeb58u, 0x000cu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00eb5au) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00eb64u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00eb5au:
        {
          if (!match16(b, 0xeb5au, 0x303cu)) return -1;
          if (!match16(b, 0xeb5cu, 0x6000u)) return -1;
          c->d[0] = (c->d[0] & 0xffff0000u) | 0x6000u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x6000u & 0x8000u) ? 8u : 0u) | (0x6000u == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0xeb5eu, 0x5340u)) return -1;
          {uint32_t dst=c->d[0]&65535u,src=1u,r=(dst-src)&65535u;
           c->d[0]=(c->d[0]&0xffff0000u)|r;
           uint16_t cy=(dst<src),ov=((dst^src)&(dst^r)&32768u)!=0u;
           c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(cy?17u:0u));}
          c->cycles+=4u;
          if (!match16(b, 0xeb60u, 0x66fcu)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x00eb5eu : 0x00eb62u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00eb5eu:
        {
          if (!match16(b, 0xeb5eu, 0x5340u)) return -1;
          {uint32_t dst=c->d[0]&65535u,src=1u,r=(dst-src)&65535u;
           c->d[0]=(c->d[0]&0xffff0000u)|r;
           uint16_t cy=(dst<src),ov=((dst^src)&(dst^r)&32768u)!=0u;
           c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(cy?17u:0u));}
          c->cycles+=4u;
          if (!match16(b, 0xeb60u, 0x66fcu)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x00eb5eu : 0x00eb62u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00eb62u:
        {
          if (!match16(b, 0xeb62u, 0x301fu)) return -1;
          { uint16_t v; if(native_bus_read16(b,c->a[7],&v)!=0) return -3;
            c->a[7]=(c->a[7]+2u)&0xffffffu;
            c->d[0]=(c->d[0]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=8u;
          if (!match16(b, 0xeb64u, 0x08b9u)) return -1;
          if (!match16(b, 0xeb66u, 0x0005u) || !match32(b, 0xeb68u, 0x00ff010du)) return -1;
          if (native_bus_read8(b, 0x00ff010du, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 5)) ? 0u : 4u));
          if (native_bus_write8((struct t2bus *)b, 0x00ff010du, (uint8_t)(byte_value & ~(1u << 5))) != 0) return -3;
          c->cycles += 16u;
          if (!match16(b, 0xeb6cu, 0x56f9u)) return -1;
          if (!match32(b, 0xeb6eu, 0x00ff0008u)) return -1;
          if (native_bus_write8((struct t2bus *)b, 0x00ff0008u, (c->sr & 4u) ? 0u : 0xffu) != 0) return -3;
          c->cycles += 16u;
          if (!match16(b, 0xeb72u, 0x33f9u)) return -1;
          if (!match32(b, 0xeb74u, 0x00ff010cu) || !match32(b, 0xeb78u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0xeb7cu, 0x48e7u)) return -1;
          if (!match16(b, 0xeb7eu, 0xe080u)) return -1;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->a[0]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[2]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[1]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[0]) != 0) return -3;
          c->cycles += 40u;
          if (!match16(b, 0xeb80u, 0x619eu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00eb82u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00eb20u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00eb64u:
        {
          if (!match16(b, 0xeb64u, 0x08b9u)) return -1;
          if (!match16(b, 0xeb66u, 0x0005u) || !match32(b, 0xeb68u, 0x00ff010du)) return -1;
          if (native_bus_read8(b, 0x00ff010du, &byte_value) != 0) return -3;
          c->sr = (uint16_t)((c->sr & ~4u) | ((byte_value & (1u << 5)) ? 0u : 4u));
          if (native_bus_write8((struct t2bus *)b, 0x00ff010du, (uint8_t)(byte_value & ~(1u << 5))) != 0) return -3;
          c->cycles += 16u;
          if (!match16(b, 0xeb6cu, 0x56f9u)) return -1;
          if (!match32(b, 0xeb6eu, 0x00ff0008u)) return -1;
          if (native_bus_write8((struct t2bus *)b, 0x00ff0008u, (c->sr & 4u) ? 0u : 0xffu) != 0) return -3;
          c->cycles += 16u;
          if (!match16(b, 0xeb72u, 0x33f9u)) return -1;
          if (!match32(b, 0xeb74u, 0x00ff010cu) || !match32(b, 0xeb78u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0xeb7cu, 0x48e7u)) return -1;
          if (!match16(b, 0xeb7eu, 0xe080u)) return -1;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->a[0]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[2]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[1]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[0]) != 0) return -3;
          c->cycles += 40u;
          if (!match16(b, 0xeb80u, 0x619eu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00eb82u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00eb20u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00eb6cu:
        {
          if (!match16(b, 0xeb6cu, 0x56f9u)) return -1;
          if (!match32(b, 0xeb6eu, 0x00ff0008u)) return -1;
          if (native_bus_write8((struct t2bus *)b, 0x00ff0008u, (c->sr & 4u) ? 0u : 0xffu) != 0) return -3;
          c->cycles += 16u;
          if (!match16(b, 0xeb72u, 0x33f9u)) return -1;
          if (!match32(b, 0xeb74u, 0x00ff010cu) || !match32(b, 0xeb78u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0xeb7cu, 0x48e7u)) return -1;
          if (!match16(b, 0xeb7eu, 0xe080u)) return -1;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->a[0]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[2]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[1]) != 0) return -3;
          c->a[7] = (c->a[7] - 4u) & 0xffffffu;
          if (native_bus_write32((struct t2bus *)b, c->a[7], c->d[0]) != 0) return -3;
          c->cycles += 40u;
          if (!match16(b, 0xeb80u, 0x619eu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00eb82u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00eb20u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00eb82u:
        {
          if (!match16(b, 0xeb82u, 0x7200u)) return -1;
          c->d[1] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80000000u) ? 8u : 0u) | (c->d[1] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xeb84u, 0x1239u)) return -1;
          if (!match32(b,0xeb86u,0x00a01f21u)) return -1;
          if (native_bus_read8(b,0x00a01f21u,&byte_value)!=0) return -3;
          c->d[1]=(c->d[1]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0xeb8au, 0x2401u)) return -1;
          c->d[2]=c->d[1];
          c->sr=(uint16_t)((c->sr&0xfff0u)|((c->d[2]&0x80000000u)?8u:0u)|(c->d[2]==0u?4u:0u));
          c->cycles+=4u;
          if (!match16(b, 0xeb8cu, 0x0682u)) return -1;
          if (!match32(b,0xeb8eu,0x00a01f10u)) return -1;
          { uint32_t dst=c->d[2],src=0x00a01f10u,r=dst+src;
            c->d[2]=r;
            uint16_t carry=(r<dst)?1u:0u;
            uint16_t ov=((~(dst^src)&(dst^r)&0x80000000u)!=0u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x80000000u)?8u:0u)|(r==0u?4u:0u)|ov|carry|(carry?16u:0u));
          }
          c->cycles+=16u;
          if (!match16(b, 0xeb92u, 0x2042u)) return -1;
          c->a[0] = c->d[2];
          c->cycles += 4u;
          if (!match16(b, 0xeb94u, 0x1080u)) return -1;
          byte_value=(uint8_t)c->d[0];
          if (native_bus_write8((struct t2bus *)b,c->a[0],byte_value)!=0) return -3;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=8u;
          if (!match16(b, 0xeb96u, 0x5241u)) return -1;
          { uint16_t dst=(uint16_t)c->d[1],r=(uint16_t)(dst+1u);
            c->d[1]=(c->d[1]&0xffff0000u)|r;
            uint16_t carry=(dst==0xffffu)?1u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u)|(dst==0x7fffu?2u:0u)|carry|(carry?16u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0xeb98u, 0x0201u)) return -1;
          if (!match16(b, 0xeb9au, 0x000fu)) return -1;
          c->d[1] = (c->d[1] & 0xffffff00u) | ((c->d[1] & 255u) & 0x0fu);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80u) ? 8u : 0u) | ((c->d[1] & 255u) == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0xeb9cu, 0x13c1u)) return -1;
          if (!match32(b,0xeb9eu,0x00a01f21u)) return -1;
          byte_value=(uint8_t)c->d[1];
          if (native_bus_write8((struct t2bus *)b,0x00a01f21u,byte_value)!=0) return -3;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0xeba2u, 0x6192u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00eba4u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00eb36u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00eb84u:
        {
          if (!match16(b, 0xeb84u, 0x1239u)) return -1;
          if (!match32(b,0xeb86u,0x00a01f21u)) return -1;
          if (native_bus_read8(b,0x00a01f21u,&byte_value)!=0) return -3;
          c->d[1]=(c->d[1]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0xeb8au, 0x2401u)) return -1;
          c->d[2]=c->d[1];
          c->sr=(uint16_t)((c->sr&0xfff0u)|((c->d[2]&0x80000000u)?8u:0u)|(c->d[2]==0u?4u:0u));
          c->cycles+=4u;
          if (!match16(b, 0xeb8cu, 0x0682u)) return -1;
          if (!match32(b,0xeb8eu,0x00a01f10u)) return -1;
          { uint32_t dst=c->d[2],src=0x00a01f10u,r=dst+src;
            c->d[2]=r;
            uint16_t carry=(r<dst)?1u:0u;
            uint16_t ov=((~(dst^src)&(dst^r)&0x80000000u)!=0u)?2u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x80000000u)?8u:0u)|(r==0u?4u:0u)|ov|carry|(carry?16u:0u));
          }
          c->cycles+=16u;
          if (!match16(b, 0xeb92u, 0x2042u)) return -1;
          c->a[0] = c->d[2];
          c->cycles += 4u;
          if (!match16(b, 0xeb94u, 0x1080u)) return -1;
          byte_value=(uint8_t)c->d[0];
          if (native_bus_write8((struct t2bus *)b,c->a[0],byte_value)!=0) return -3;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=8u;
          if (!match16(b, 0xeb96u, 0x5241u)) return -1;
          { uint16_t dst=(uint16_t)c->d[1],r=(uint16_t)(dst+1u);
            c->d[1]=(c->d[1]&0xffff0000u)|r;
            uint16_t carry=(dst==0xffffu)?1u:0u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&0x8000u)?8u:0u)|(r==0u?4u:0u)|(dst==0x7fffu?2u:0u)|carry|(carry?16u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0xeb98u, 0x0201u)) return -1;
          if (!match16(b, 0xeb9au, 0x000fu)) return -1;
          c->d[1] = (c->d[1] & 0xffffff00u) | ((c->d[1] & 255u) & 0x0fu);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[1] & 0x80u) ? 8u : 0u) | ((c->d[1] & 255u) == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0xeb9cu, 0x13c1u)) return -1;
          if (!match32(b,0xeb9eu,0x00a01f21u)) return -1;
          byte_value=(uint8_t)c->d[1];
          if (native_bus_write8((struct t2bus *)b,0x00a01f21u,byte_value)!=0) return -3;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0xeba2u, 0x6192u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00eba4u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00eb36u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00eba4u:
        {
          if (!match16(b, 0xeba4u, 0x4cdfu)) return -1;
          if (!match16(b, 0xeba6u, 0x0107u)) return -1;
          { uint32_t addr = c->a[7]; uint32_t val; uint16_t word; unsigned idx;
            for (idx = 0; idx < 16u; ++idx)
              {
                if (!(0x0107u & (1u << idx))) continue;
                if (native_bus_read32(b, addr, &val) != 0) return -3;
                if (idx < 8u) c->d[idx] = val;
                else c->a[idx - 8u] = val;
                addr = (addr + 4u) & 0xffffffu;
              }
            c->a[7] = addr; /* postincrement wins if base An is in mask */
          }
          c->cycles += 40u;
          if (!match16(b, 0xeba8u, 0x4a39u)) return -1;
          if (!match32(b, 0xebaau, 0x00ff0008u)) return -1;
          { uint8_t value;
            if (native_bus_read8(b, 0x00ff0008u, &value) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((value & 0x80u) ? 8u : 0u) | (value == 0u ? 4u : 0u));
          }
          c->cycles += 12u;
          if (!match16(b, 0xebaeu, 0x6700u)) return -1;
          if (!match16(b, 0xebb0u, 0x0014u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x00ebc4u : 0x00ebb2u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00ebb2u:
        {
          if (!match16(b, 0xebb2u, 0x08f9u)) return -1;
          { uint8_t v; if(native_bus_read8(b,0x00ff010du,&v)!=0)return -3;
            c->sr=(uint16_t)((c->sr&~4u)|((v&(1u<<5))?0u:4u));
            if(native_bus_write8((struct t2bus *)b,0x00ff010du,(uint8_t)(v|(1u<<5)))!=0)return -3; }
          c->cycles+=20u;
          if (!match16(b, 0xebbau, 0x33f9u)) return -1;
          if (!match32(b, 0xebbcu, 0x00ff010cu) || !match32(b, 0xebc0u, 0x00c00004u)) return -1;
          { uint16_t val; if (native_bus_read16(b, 0x00ff010cu, &val) != 0) return -3;
            if (native_bus_write16((struct t2bus *)b, 0x00c00004u, val) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((val & 0x8000u) ? 8u : 0u) | (val == 0u ? 4u : 0u));
          }
          c->cycles += 28u;
          if (!match16(b, 0xebc4u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00ebc4u:
        {
          if (!match16(b, 0xebc4u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x00ebc6u:
        {
          if (!match16(b, 0xebc6u, 0x4239u)) return -1;
          if (!match32(b, 0xebc8u, 0x00ff26c4u)) return -1;
          if (native_bus_write8((struct t2bus *)b, 0x00ff26c4u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          c->pc = 0x00ebccu;
          return 0;
        }
      case 0x00ee7eu:
        {
          if (!match16(b, 0xee7eu, 0x4239u)) return -1;
          if (!match32(b, 0xee80u, 0x00ff28cfu)) return -1;
          if (native_bus_write8((struct t2bus *)b, 0x00ff28cfu, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          if (!match16(b, 0xee84u, 0x6100u)) return -1;
          if (!match16(b, 0xee86u, 0x44ccu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00ee88u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x013352u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00ee88u:
        {
          if (!match16(b, 0xee88u, 0x6100u)) return -1;
          if (!match16(b, 0xee8au, 0x3a92u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00ee8cu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x01291cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00ee8cu:
        {
          if (!match16(b, 0xee8cu, 0x4bf9u)) return -1;
          if (!match32(b, 0xee8eu, 0x00ff2bbbu)) return -1;
          c->a[5] = 0x00ff2bbbu;
          c->cycles += 12u;
          if (!match16(b, 0xee92u, 0x6100u)) return -1;
          if (!match16(b, 0xee94u, 0xfd32u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00ee96u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00ebc6u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00ee96u:
        {
          if (!match16(b, 0xee96u, 0x1039u)) return -1;
          if (!match32(b, 0xee98u, 0x00ff272au)) return -1;
          if (native_bus_read8(b, 0x00ff272au, &byte_value) != 0) return -3;
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 0x80u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 16u;
          if (!match16(b, 0xee9cu, 0x1239u)) return -1;
          if (!match32(b,0xee9eu,0x00ff272du)) return -1;
          if (native_bus_read8(b,0x00ff272du,&byte_value)!=0) return -3;
          c->d[1]=(c->d[1]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0xeea2u, 0x1639u)) return -1;
          if (!match32(b,0xeea4u,0x00ff2bbfu)) return -1;
          if (native_bus_read8(b,0x00ff2bbfu,&byte_value)!=0) return -3;
          c->d[3]=(c->d[3]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0xeea8u, 0xe14au)) return -1;
          { unsigned count=c->d[0]&63u,i;uint32_t v=c->d[2]&65535u;uint16_t carry=0;
            for(i=0;i<count;i++){carry=(v>>15)&1u;v=(v<<1)&65535u;}
            c->d[2]=(c->d[2]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&(count?0xffe0u:0xfff0u))|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)|(count&&carry?17u:0u)); c->cycles+=6u+2u*count; }
          if (!match16(b, 0xeeaau, 0x1639u)) return -1;
          if (!match32(b,0xeeacu,0x00ff2bbeu)) return -1;
          if (native_bus_read8(b,0x00ff2bbeu,&byte_value)!=0) return -3;
          c->d[3]=(c->d[3]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0xeeb0u, 0x1439u)) return -1;
          if (!match32(b,0xeeb2u,0x00ff2749u)) return -1;
          if (native_bus_read8(b,0x00ff2749u,&byte_value)!=0) return -3;
          c->d[2]=(c->d[2]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0xeeb6u, 0x1639u)) return -1;
          if (!match32(b,0xeeb8u,0x00ff2b02u)) return -1;
          if (native_bus_read8(b,0x00ff2b02u,&byte_value)!=0) return -3;
          c->d[3]=(c->d[3]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0xeebcu, 0xe14bu)) return -1;
          { unsigned count=c->d[0]&63u,i;uint32_t v=c->d[3]&65535u;uint16_t carry=0;
            for(i=0;i<count;i++){carry=(v>>15)&1u;v=(v<<1)&65535u;}
            c->d[3]=(c->d[3]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&(count?0xffe0u:0xfff0u))|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)|(count&&carry?17u:0u)); c->cycles+=6u+2u*count; }
          if (!match16(b, 0xeebeu, 0x1639u)) return -1;
          if (!match32(b,0xeec0u,0x00ff2b01u)) return -1;
          if (native_bus_read8(b,0x00ff2b01u,&byte_value)!=0) return -3;
          c->d[3]=(c->d[3]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0xeec4u, 0x1639u)) return -1;
          if (!match32(b,0xeec6u,0x00ff3797u)) return -1;
          if (native_bus_read8(b,0x00ff3797u,&byte_value)!=0) return -3;
          c->d[3]=(c->d[3]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0xeecau, 0xe14bu)) return -1;
          { unsigned count=c->d[0]&63u,i;uint32_t v=c->d[3]&65535u;uint16_t carry=0;
            for(i=0;i<count;i++){carry=(v>>15)&1u;v=(v<<1)&65535u;}
            c->d[3]=(c->d[3]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&(count?0xffe0u:0xfff0u))|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)|(count&&carry?17u:0u)); c->cycles+=6u+2u*count; }
          if (!match16(b, 0xeeccu, 0x1639u)) return -1;
          if (!match32(b,0xeeceu,0x00ff3796u)) return -1;
          if (native_bus_read8(b,0x00ff3796u,&byte_value)!=0) return -3;
          c->d[3]=(c->d[3]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0xeed2u, 0x1039u)) return -1;
          if (!match32(b, 0xeed4u, 0x00ff2bbeu)) return -1;
          if (native_bus_read8(b, 0x00ff2bbeu, &byte_value) != 0) return -3;
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 0x80u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 16u;
          if (!match16(b, 0xeed8u, 0x6100u)) return -1;
          if (!match16(b, 0xeedau, 0x245eu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00eedcu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x011338u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00eedcu:
        {
          if (!match16(b, 0xeedcu, 0x13f9u)) return -1;
          {uint8_t v;if(native_bus_read8(b,0xff26a0u,&v)||native_bus_write8((struct t2bus *)b,0xff26a1u,v))return -3;c->sr=(c->sr&0xfff0u)|((v&128u)?8u:0u)|(v==0u?4u:0u);}
          c->cycles+=28u;
          if (!match16(b, 0xeee6u, 0x7a00u)) return -1;
          c->d[5] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[5] & 0x80000000u) ? 8u : 0u) | (c->d[5] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xeee8u, 0x4bf9u)) return -1;
          if (!match32(b, 0xeeeau, 0x00ff3775u)) return -1;
          c->a[5] = 0x00ff3775u;
          c->cycles += 12u;
          if (!match16(b, 0xeeeeu, 0x1a39u)) return -1;
          if (!match32(b,0xeef0u,0x00ff274bu)) return -1;
          if (native_bus_read8(b,0x00ff274bu,&byte_value)!=0) return -3;
          c->d[5]=(c->d[5]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0xeef4u, 0x671au)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x00ef10u : 0x00eef6u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x00eef6u:
        {
          if (!match16(b, 0xeef6u, 0x5345u)) return -1;
          {uint32_t dst=c->d[5]&65535u,src=1u,r=(dst-src)&65535u;
           c->d[5]=(c->d[5]&0xffff0000u)|r;
           uint16_t cy=(dst<src),ov=((dst^src)&(dst^r)&32768u)!=0u;
           c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(cy?17u:0u));}
          c->cycles+=4u;
          if (!match16(b, 0xeef8u, 0x3f05u)) return -1;
          c->a[7]=(c->a[7]-2u)&0xffffffu;
          if (native_bus_write16((struct t2bus *)b,c->a[7],(uint16_t)c->d[5]) != 0) return -3;
          { uint16_t v=(uint16_t)c->d[5]; c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles += 8u;
          if (!match16(b, 0xeefau, 0x6100u)) return -1;
          if (!match16(b, 0xeefcu, 0x23d4u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00eefeu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0112d0u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00eef8u:
        {
          if (!match16(b, 0xeef8u, 0x3f05u)) return -1;
          c->a[7]=(c->a[7]-2u)&0xffffffu;
          if (native_bus_write16((struct t2bus *)b,c->a[7],(uint16_t)c->d[5]) != 0) return -3;
          { uint16_t v=(uint16_t)c->d[5]; c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles += 8u;
          if (!match16(b, 0xeefau, 0x6100u)) return -1;
          if (!match16(b, 0xeefcu, 0x23d4u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00eefeu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0112d0u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00eefeu:
        {
          if (!match16(b, 0xeefeu, 0x6100u)) return -1;
          if (!match16(b, 0xef00u, 0x02e0u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00ef02u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00f1e0u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00ef02u:
        {
          if (!match16(b, 0xef02u, 0x6100u)) return -1;
          if (!match16(b, 0xef04u, 0x097cu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00ef06u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00f880u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00ef06u:
        {
          if (!match16(b, 0xef06u, 0x3a1fu)) return -1;
          { uint16_t v; if(native_bus_read16(b,c->a[7],&v)!=0) return -3;
            c->a[7]=(c->a[7]+2u)&0xffffffu;
            c->d[5]=(c->d[5]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=8u;
          if (!match16(b, 0xef08u, 0xdafcu)) return -1;
          c->a[5]=(c->a[5]+(int16_t)0x004bu)&0xffffffu;
          c->cycles+=8u;
          if (!match16(b, 0xef0cu, 0x51cdu)) return -1;
          { uint16_t count = (uint16_t)(c->d[5] - 1u);
            c->d[5] = (c->d[5] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00eef8u : 0x00ef10u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00ef10u:
        {
          if (!match16(b, 0xef10u, 0x7a00u)) return -1;
          c->d[5] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[5] & 0x80000000u) ? 8u : 0u) | (c->d[5] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0xef12u, 0x4bf9u)) return -1;
          if (!match32(b, 0xef14u, 0x00ff2bbbu)) return -1;
          c->a[5] = 0x00ff2bbbu;
          c->cycles += 12u;
          if (!match16(b, 0xef18u, 0x1a39u)) return -1;
          if (!match32(b,0xef1au,0x00ff2749u)) return -1;
          if (native_bus_read8(b,0x00ff2749u,&byte_value)!=0) return -3;
          c->d[5]=(c->d[5]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0xef1eu, 0x5345u)) return -1;
          {uint32_t dst=c->d[5]&65535u,src=1u,r=(dst-src)&65535u;
           c->d[5]=(c->d[5]&0xffff0000u)|r;
           uint16_t cy=(dst<src),ov=((dst^src)&(dst^r)&32768u)!=0u;
           c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(cy?17u:0u));}
          c->cycles+=4u;
          if (!match16(b, 0xef20u, 0x3f05u)) return -1;
          c->a[7]=(c->a[7]-2u)&0xffffffu;
          if (native_bus_write16((struct t2bus *)b,c->a[7],(uint16_t)c->d[5]) != 0) return -3;
          { uint16_t v=(uint16_t)c->d[5]; c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles += 8u;
          if (!match16(b, 0xef22u, 0x6100u)) return -1;
          if (!match16(b, 0xef24u, 0x02bcu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00ef26u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00f1e0u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00ef20u:
        {
          if (!match16(b, 0xef20u, 0x3f05u)) return -1;
          c->a[7]=(c->a[7]-2u)&0xffffffu;
          if (native_bus_write16((struct t2bus *)b,c->a[7],(uint16_t)c->d[5]) != 0) return -3;
          { uint16_t v=(uint16_t)c->d[5]; c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles += 8u;
          if (!match16(b, 0xef22u, 0x6100u)) return -1;
          if (!match16(b, 0xef24u, 0x02bcu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00ef26u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00f1e0u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00ef26u:
        {
          if (!match16(b, 0xef26u, 0x6100u)) return -1;
          if (!match16(b, 0xef28u, 0x1516u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00ef2au) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x01043eu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00ef2au:
        {
          if (!match16(b, 0xef2au, 0x6100u)) return -1;
          if (!match16(b, 0xef2cu, 0x0094u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00ef2eu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00efc0u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00ef2eu:
        {
          if (!match16(b, 0xef2eu, 0x6100u)) return -1;
          if (!match16(b, 0xef30u, 0x23a0u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00ef32u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0112d0u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00ef32u:
        {
          if (!match16(b, 0xef32u, 0x6100u)) return -1;
          if (!match16(b, 0xef34u, 0x094cu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00ef36u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00f880u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00ef36u:
        {
          if (!match16(b, 0xef36u, 0x6100u)) return -1;
          if (!match16(b, 0xef38u, 0x1c56u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00ef3au) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x010b8eu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00ef3au:
        {
          if (!match16(b, 0xef3au, 0x3a1fu)) return -1;
          { uint16_t v; if(native_bus_read16(b,c->a[7],&v)!=0) return -3;
            c->a[7]=(c->a[7]+2u)&0xffffffu;
            c->d[5]=(c->d[5]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&0xfff0u)|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)); }
          c->cycles+=8u;
          if (!match16(b, 0xef3cu, 0xdafcu)) return -1;
          c->a[5]=(c->a[5]+(int16_t)0x004bu)&0xffffffu;
          c->cycles+=8u;
          if (!match16(b, 0xef40u, 0x51cdu)) return -1;
          { uint16_t count = (uint16_t)(c->d[5] - 1u);
            c->d[5] = (c->d[5] & 0xffff0000u) | count;
            c->pc = (count != 0xffffu) ? 0x00ef20u : 0x00ef44u;
            c->cycles += (count != 0xffffu) ? 10u : 14u;
          }
          return 0;
        }
      case 0x00ef44u:
        {
          if (!match16(b, 0xef44u, 0x6100u)) return -1;
          if (!match16(b, 0xef46u, 0x4398u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00ef48u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0132deu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00ef48u:
        {
          if (!match16(b, 0xef48u, 0x6100u)) return -1;
          if (!match16(b, 0xef4au, 0x44b6u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x00ef4cu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x013400u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x00efc0u:
        {
          if (!match16(b, 0xefc0u, 0x6002u)) return -1;
          c->pc = (1) ? 0x00efc4u : 0x00efc2u;
          c->cycles += (1) ? 10u : 8u;
          return 0;
        }
      case 0x00f1e0u:
        {
          if (!match16(b, 0xf1e0u, 0x4239u)) return -1;
          if (!match32(b, 0xf1e2u, 0x00ff26b9u)) return -1;
          if (native_bus_write8((struct t2bus *)b, 0x00ff26b9u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          c->pc = 0x00f1e6u;
          return 0;
        }
      case 0x01043eu:
        {
          if (!match16(b, 0x1043eu, 0x4a39u)) return -1;
          if (!match32(b, 0x10440u, 0x00ff2729u)) return -1;
          { uint8_t value;
            if (native_bus_read8(b, 0x00ff2729u, &value) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((value & 0x80u) ? 8u : 0u) | (value == 0u ? 4u : 0u));
          }
          c->cycles += 12u;
          if (!match16(b, 0x10444u, 0x662eu)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x010474u : 0x010446u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x010474u:
        {
          if (!match16(b, 0x10474u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x010b8eu:
        {
          if (!match16(b, 0x10b8eu, 0x4279u)) return -1;
          if (!match32(b, 0x10b90u, 0x00ff2702u)) return -1;
          if (native_bus_write16((struct t2bus *)b, 0x00ff2702u, 0u) != 0) return -3;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | 4u);
          c->cycles += 12u;
          c->pc = 0x010b94u;
          return 0;
        }
      case 0x011338u:
        {
          if (!match16(b, 0x11338u, 0x4bf9u)) return -1;
          if (!match32(b, 0x1133au, 0x00ff2bbbu)) return -1;
          c->a[5] = 0x00ff2bbbu;
          c->cycles += 12u;
          if (!match16(b, 0x1133eu, 0x1a39u)) return -1;
          if (!match32(b,0x11340u,0x00ff2749u)) return -1;
          if (native_bus_read8(b,0x00ff2749u,&byte_value)!=0) return -3;
          c->d[5]=(c->d[5]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0x11344u, 0x6100u)) return -1;
          if (!match16(b, 0x11346u, 0x0016u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x011348u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x01135cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x011348u:
        {
          if (!match16(b, 0x11348u, 0x1a39u)) return -1;
          if (!match32(b,0x1134au,0x00ff274bu)) return -1;
          if (native_bus_read8(b,0x00ff274bu,&byte_value)!=0) return -3;
          c->d[5]=(c->d[5]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0x1134eu, 0x6700u)) return -1;
          if (!match16(b, 0x11350u, 0x000au)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x01135au : 0x011352u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x011352u:
        {
          if (!match16(b, 0x11352u, 0x4bf9u)) return -1;
          if (!match32(b, 0x11354u, 0x00ff3775u)) return -1;
          c->a[5] = 0x00ff3775u;
          c->cycles += 12u;
          if (!match16(b, 0x11358u, 0x602au)) return -1;
          c->pc = (1) ? 0x011384u : 0x01135au;
          c->cycles += (1) ? 10u : 8u;
          return 0;
        }
      case 0x01135au:
        {
          if (!match16(b, 0x1135au, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x01135cu:
        {
          if (!match16(b, 0x1135cu, 0x5305u)) return -1;
          { uint32_t x=c->d[5]&255u,r=(x-1u)&255u;
            c->d[5]=(c->d[5]&0xffffff00u)|r;
            uint16_t carry=x==0u;
            uint16_t ov=x==128u;
            c->sr=(uint16_t)((c->sr&0xffe0u)|((r&128u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(carry?17u:0u));
          }
          c->cycles+=4u;
          if (!match16(b, 0x1135eu, 0x0245u)) return -1;
          if (!match16(b, 0x11360u, 0x00ffu)) return -1;
          { uint16_t v=(uint16_t)c->d[5] & 0x00ffu; c->d[5]=(c->d[5] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x11362u, 0x103cu)) return -1;
          byte_value=0xffu;
          c->d[0]=(c->d[0]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&128u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=8u;
          c->pc = 0x011366u;
          return 0;
        }
      case 0x01291cu:
        {
          if (!match16(b, 0x1291cu, 0x203cu)) return -1;
          if (!match32(b, 0x1291eu, 0x0004d631u)) return -1;
          c->d[0] = 0x0004d631u;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x0004d631u & 0x80000000u) ? 8u : 0u) | (0x0004d631u == 0u ? 4u : 0u));
          c->cycles += 12u;
          if (!match16(b, 0x12922u, 0x1039u)) return -1;
          if (!match32(b, 0x12924u, 0x00ff2735u)) return -1;
          if (native_bus_read8(b, 0x00ff2735u, &byte_value) != 0) return -3;
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 0x80u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 16u;
          if (!match16(b, 0x12928u, 0xe148u)) return -1;
          { unsigned count=c->d[0]&63u,i;uint32_t v=c->d[0]&65535u;uint16_t carry=0;
            for(i=0;i<count;i++){carry=(v>>15)&1u;v=(v<<1)&65535u;}
            c->d[0]=(c->d[0]&0xffff0000u)|v;
            c->sr=(uint16_t)((c->sr&(count?0xffe0u:0xfff0u))|((v&0x8000u)?8u:0u)|(v==0u?4u:0u)|(count&&carry?17u:0u)); c->cycles+=6u+2u*count; }
          if (!match16(b, 0x1292au, 0x1039u)) return -1;
          if (!match32(b, 0x1292cu, 0x00ff2734u)) return -1;
          if (native_bus_read8(b, 0x00ff2734u, &byte_value) != 0) return -3;
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 0x80u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 16u;
          if (!match16(b, 0x12930u, 0x2840u)) return -1;
          c->a[4] = c->d[0];
          c->cycles += 4u;
          if (!match16(b, 0x12932u, 0x4eb9u)) return -1;
          if (!match32(b, 0x12934u, 0x00012952u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x012938u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x012952u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x012938u:
        {
          if (!match16(b, 0x12938u, 0x0c00u)) return -1;
          if (!match16(b, 0x1293au, 0x0001u)) return -1;
          { uint8_t dst=(uint8_t)c->d[0], src=0x01u, result=(uint8_t)(dst-src);
            uint16_t n=(result&0x80u)?8u:0u, z=(result==0u)?4u:0u;
            uint16_t v=((dst^src)&(dst^result)&0x80u)?2u:0u;
            uint16_t carry=(dst<src)?1u:0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|n|z|v|carry);
          }
          c->cycles += 8u;
          if (!match16(b, 0x1293cu, 0x6600u)) return -1;
          if (!match16(b, 0x1293eu, 0x0012u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x012950u : 0x012940u;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x012950u:
        {
          if (!match16(b, 0x12950u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x012952u:
        {
          if (!match16(b, 0x12952u, 0x101cu)) return -1;
          if (native_bus_read8(b, c->a[4], &byte_value) != 0) return -3;
          c->a[4] = (c->a[4] + 1u) & 0xffffffu;
          c->d[0] = (c->d[0] & 0xffffff00u) | byte_value;
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((byte_value & 128u) ? 8u : 0u) | (byte_value == 0u ? 4u : 0u));
          c->cycles += 8u;
          if (!match16(b, 0x12954u, 0x1200u)) return -1;
          byte_value=(uint8_t)c->d[0];
          c->d[1]=(c->d[1]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=4u;
          if (!match16(b, 0x12956u, 0x6700u)) return -1;
          if (!match16(b, 0x12958u, 0x001eu)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x012976u : 0x01295au;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x01295au:
        {
          if (!match16(b, 0x1295au, 0x0c00u)) return -1;
          if (!match16(b, 0x1295cu, 0x0001u)) return -1;
          { uint8_t dst=(uint8_t)c->d[0], src=0x01u, result=(uint8_t)(dst-src);
            uint16_t n=(result&0x80u)?8u:0u, z=(result==0u)?4u:0u;
            uint16_t v=((dst^src)&(dst^result)&0x80u)?2u:0u;
            uint16_t carry=(dst<src)?1u:0u;
            c->sr=(uint16_t)((c->sr&0xfff0u)|n|z|v|carry);
          }
          c->cycles += 8u;
          if (!match16(b, 0x1295eu, 0x6700u)) return -1;
          if (!match16(b, 0x12960u, 0x0016u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x012976u : 0x012962u;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x012962u:
        {
          if (!match16(b, 0x12962u, 0x0240u)) return -1;
          if (!match16(b, 0x12964u, 0x00ffu)) return -1;
          { uint16_t v=(uint16_t)c->d[0] & 0x00ffu; c->d[0]=(c->d[0] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x12966u, 0xd040u)) return -1;
          { uint32_t x = c->d[0] & 65535u, y = c->d[0] & 65535u, r = (x+y) & 65535u;
            uint16_t flags = (uint16_t)(((r & 0x8000u) ? 8u : 0u) | ((r == 0u) ? 4u : 0u) | (((~(x ^ y) & (r ^ y)) & 0x8000u) ? 2u : 0u) | ((x+y > 65535u) ? 17u : 0u));
            c->d[0] = (c->d[0] & 0xffff0000u) | r;
            c->sr = (uint16_t)((c->sr & 0xffe0u) | flags);
          }
          c->cycles += 4u;
          if (!match16(b, 0x12968u, 0x41fau)) return -1;
          if (!match16(b, 0x1296au, 0x000eu)) return -1;
          c->a[0] = 0x012978u;
          c->cycles += 8u;
          c->pc = 0x01296cu;
          return 0;
        }
      case 0x012976u:
        {
          if (!match16(b, 0x12976u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x0132deu:
        {
          if (!match16(b, 0x132deu, 0x4bf9u)) return -1;
          if (!match32(b, 0x132e0u, 0x00ff2bbbu)) return -1;
          c->a[5] = 0x00ff2bbbu;
          c->cycles += 12u;
          if (!match16(b, 0x132e4u, 0x1a39u)) return -1;
          if (!match32(b,0x132e6u,0x00ff2749u)) return -1;
          if (native_bus_read8(b,0x00ff2749u,&byte_value)!=0) return -3;
          c->d[5]=(c->d[5]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0x132eau, 0x6700u)) return -1;
          if (!match16(b, 0x132ecu, 0x0064u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x013350u : 0x0132eeu;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x0132eeu:
        {
          if (!match16(b, 0x132eeu, 0x0245u)) return -1;
          if (!match16(b, 0x132f0u, 0x00ffu)) return -1;
          { uint16_t v=(uint16_t)c->d[5] & 0x00ffu; c->d[5]=(c->d[5] & 0xffff0000u) | v;
            c->sr=(uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u)); }
          c->cycles += 8u;
          if (!match16(b, 0x132f2u, 0x5345u)) return -1;
          {uint32_t dst=c->d[5]&65535u,src=1u,r=(dst-src)&65535u;
           c->d[5]=(c->d[5]&0xffff0000u)|r;
           uint16_t cy=(dst<src),ov=((dst^src)&(dst^r)&32768u)!=0u;
           c->sr=(uint16_t)((c->sr&0xffe0u)|((r&32768u)?8u:0u)|(r==0u?4u:0u)|(ov?2u:0u)|(cy?17u:0u));}
          c->cycles+=4u;
          c->pc = 0x0132f4u;
          return 0;
        }
      case 0x013350u:
        {
          if (!match16(b, 0x13350u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x013352u:
        {
          if (!match16(b, 0x13352u, 0x7a00u)) return -1;
          c->d[5] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[5] & 0x80000000u) ? 8u : 0u) | (c->d[5] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x13354u, 0x1a39u)) return -1;
          if (!match32(b,0x13356u,0x00ff274fu)) return -1;
          if (native_bus_read8(b,0x00ff274fu,&byte_value)!=0) return -3;
          c->d[5]=(c->d[5]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0x1335au, 0x6600u)) return -1;
          if (!match16(b, 0x1335cu, 0x0004u)) return -1;
          c->pc = (!(c->sr & 4u)) ? 0x013360u : 0x01335eu;
          c->cycles += (!(c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x01335eu:
        {
          if (!match16(b, 0x1335eu, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x013360u:
        {
          if (!match16(b, 0x13360u, 0x4bf9u)) return -1;
          if (!match32(b, 0x13362u, 0x00ff3ad7u)) return -1;
          c->a[5] = 0x00ff3ad7u;
          c->cycles += 12u;
          c->pc = 0x013366u;
          return 0;
        }
      case 0x013400u:
        {
          if (!match16(b, 0x13400u, 0x7a00u)) return -1;
          c->d[5] = (uint32_t)(int32_t)(0);
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((c->d[5] & 0x80000000u) ? 8u : 0u) | (c->d[5] == 0u ? 4u : 0u));
          c->cycles += 4u;
          if (!match16(b, 0x13402u, 0x1a39u)) return -1;
          if (!match32(b,0x13404u,0x00ff274fu)) return -1;
          if (native_bus_read8(b,0x00ff274fu,&byte_value)!=0) return -3;
          c->d[5]=(c->d[5]&0xffffff00u)|byte_value;
          c->sr=(uint16_t)((c->sr&0xfff0u)|((byte_value&0x80u)?8u:0u)|(byte_value==0u?4u:0u));
          c->cycles+=16u;
          if (!match16(b, 0x13408u, 0x6700u)) return -1;
          if (!match16(b, 0x1340au, 0x00b0u)) return -1;
          c->pc = ((c->sr & 4u)) ? 0x0134bau : 0x01340cu;
          c->cycles += ((c->sr & 4u)) ? 10u : 8u;
          return 0;
        }
      case 0x01340cu:
        {
          if (!match16(b, 0x1340cu, 0x4bf9u)) return -1;
          if (!match32(b, 0x1340eu, 0x00ff3ad7u)) return -1;
          c->a[5] = 0x00ff3ad7u;
          c->cycles += 12u;
          c->pc = 0x013412u;
          return 0;
        }
      case 0x0134bau:
        {
          if (!match16(b, 0x134bau, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      case 0x0ffe6eu:
        {
          if (!match16(b, 0xffe6eu, 0x23fcu)) return -1;
          if (!match32(b, 0xffe70u, 0x00000000u) || !match32(b, 0xffe74u, 0x00ff013eu)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00ff013eu, 0x00000000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=0ffe6e addr=00ff013e value=00000000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00000000u & 0x80000000u) ? 8u : 0u) | (0x00000000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0xffe78u, 0x4a79u)) return -1;
          if (!match32(b, 0xffe7au, 0x00ff0000u)) return -1;
          { uint16_t v;
            if (native_bus_read16(b, 0x00ff0000u, &v) != 0) return -3;
            c->sr = (uint16_t)((c->sr & 0xfff0u) | ((v & 0x8000u) ? 8u : 0u) | (v == 0u ? 4u : 0u));
            c->cycles += 16u;
          }
          if (!match16(b, 0xffe7eu, 0x6a00u)) return -1;
          if (!match16(b, 0xffe80u, 0x0006u)) return -1;
          c->pc = (c->sr & 8u) ? 0x0ffe82u : 0x0ffe86u;
          c->cycles += 10u;
          return 0;
        }
      case 0x0ffe82u:
        {
          if (!match16(b, 0xffe82u, 0x4ef8u)) return -1;
          if (!match16(b, 0xffe84u, 0x4f48u)) return -1;
          c->pc = 0x004f48u;
          c->cycles += 10u;
          return 0;
        }
      case 0x0ffe86u:
        {
          if (!match16(b, 0xffe86u, 0x4eb9u)) return -1;
          if (!match32(b, 0xffe88u, 0x000ffe96u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0ffe8cu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x0ffe96u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0ffe8cu:
        {
          if (!match16(b, 0xffe8cu, 0x4eb9u)) return -1;
          if (!match32(b, 0xffe8eu, 0x0000a9eeu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0ffe92u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a9eeu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0ffe92u:
        {
          if (!match16(b, 0xffe92u, 0x4ef8u)) return -1;
          if (!match16(b, 0xffe94u, 0x524eu)) return -1;
          c->pc = 0x00524eu;
          c->cycles += 10u;
          return 0;
        }
      case 0x0ffe96u:
        {
          if (!match16(b, 0xffe96u, 0x46fcu)) return -1;
          if (!match16(b, 0xffe98u, 0x2700u)) return -1;
          if (!(c->sr & 0x2000u)) return -3;
          c->sr = 0x2700u;
          c->cycles += 12u;
          if (!match16(b, 0xffe9au, 0x23fcu)) return -1;
          if (!match32(b, 0xffe9cu, 0x00ff0000u) || !match32(b, 0xffea0u, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0x00ff0000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=0ffe9a addr=00c00004 value=00ff0000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00ff0000u & 0x80000000u) ? 8u : 0u) | (0x00ff0000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0xffea4u, 0x23fcu)) return -1;
          if (!match32(b, 0xffea6u, 0x00ff0000u) || !match32(b, 0xffeaau, 0x00c00004u)) return -1;
          if (native_bus_write32((struct t2bus *)b, 0x00c00004u, 0x00ff0000u) != 0)
            { printf("T2GEN V0.67 WRITE32_STOP: pc=0ffea4 addr=00c00004 value=00ff0000\n"); return -3; }
          c->sr = (uint16_t)((c->sr & 0xfff0u) | ((0x00ff0000u & 0x80000000u) ? 8u : 0u) | (0x00ff0000u == 0u ? 4u : 0u));
          c->cycles += 28u;
          if (!match16(b, 0xffeaeu, 0x4eb9u)) return -1;
          if (!match32(b, 0xffeb0u, 0x0000a5bau)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0ffeb4u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x00a5bau;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0ffeb4u:
        {
          if (!match16(b, 0xffeb4u, 0x4eb8u)) return -1;
          if (!match16(b, 0xffeb6u, 0x4a28u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0ffeb8u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004a28u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0ffeb8u:
        {
          if (!match16(b, 0xffeb8u, 0x4eb8u)) return -1;
          if (!match16(b, 0xffebau, 0x4a3cu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0ffebcu) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004a3cu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0ffebcu:
        {
          if (!match16(b, 0xffebcu, 0x4eb8u)) return -1;
          if (!match16(b, 0xffebeu, 0x4aa0u)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0ffec0u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004aa0u;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0ffec0u:
        {
          if (!match16(b, 0xffec0u, 0x4eb8u)) return -1;
          if (!match16(b, 0xffec2u, 0x4d3eu)) return -1;
          { uint32_t new_sp = (c->a[7] - 4u) & 0xffffffu;
            if (native_bus_write32((struct t2bus *)b, new_sp, 0x0ffec4u) != 0) return -3;
            c->a[7] = new_sp; c->pc = 0x004d3eu;
            c->cycles += 18u;
          }
          return 0;
        }
      case 0x0ffec4u:
        {
          if (!match16(b, 0xffec4u, 0x4e75u)) return -1;
          { uint32_t return_pc;
            if (native_bus_read32(b, c->a[7], &return_pc) != 0) return -3;
            c->a[7] = (c->a[7] + 4u) & 0xffffffu;
            c->pc = return_pc & 0xffffffu;
            c->cycles += 16u;
          }
          return 0;
        }
      default: return -2;
    }
}
