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
#include "t2gen_vdp_frame59.h"

struct t2cpu { uint32_t d[8], a[8], pc, usp; uint16_t sr; uint32_t cycles; uint32_t next_vblank; uint32_t irq6_count; };
struct t2vdp { uint16_t status; uint16_t regs[24]; uint8_t vram[65536]; uint8_t cram[128]; uint8_t vsram[80]; uint32_t status_reads; uint32_t ctrl_writes; uint32_t data_writes; uint32_t data_reads; uint32_t vram_writes; uint32_t cram_writes; uint32_t vsram_writes; uint32_t nonzero_writes; uint32_t address; uint8_t code; uint8_t pending; uint16_t first_control; };
struct t2bus { const uint8_t *rom; size_t len; uint8_t *ram; struct t2vdp *vdp; uint8_t io_data[3], io_ctrl[3], io_tx[3], io_rx[3], io_serial_ctrl[3]; uint32_t io_writes; uint8_t z80_ram[8192]; uint8_t z80_busreq, z80_reset_released; uint32_t z80_busreq_writes, z80_busreq_reads, z80_reset_writes, z80_ram_reads, z80_ram_writes, z80_ram_byte_writes; uint32_t psg_writes; uint8_t psg_last; };
/* Minimal deterministic VDP model, NOT a cycle-accurate video implementation.
 * 0x3400: FIFO empty + hardware status bits. VBlank is approximated by
 * a 262-scanline virtual frame, advanced on status reads (diagnostic only).
 */
static uint16_t genesis_vdp_status(struct t2vdp *v)
{
  uint32_t phase = v->status_reads++ % 262u;
  return (uint16_t)(0x3400u | ((phase >= 224u) ? 0x0008u : 0u));
}
static int genesis_vdp_read16(struct t2bus *b, uint32_t addr, uint16_t *value)
{
  uint32_t port = addr & 0x1eu;
  if (!b->vdp || (addr & 1u) || addr < 0xc00000u || addr > 0xc0001eu) return -1;
  if (port == 0x04u || port == 0x06u)
    {
      *value = genesis_vdp_status(b->vdp);
      b->vdp->pending = 0;
      return 0;
    }
  if (port == 0x00u || port == 0x02u)
    {
      /* VRAM reads only, until CRAM/VSRAM command handling is validated. */
      if ((b->vdp->code & 0x0fu) != 0x00u) return -1;
      uint32_t a = b->vdp->address & 0xffffu;
      *value = (uint16_t)(((uint16_t)b->vdp->vram[a] << 8) |
                           b->vdp->vram[(a + 1u) & 0xffffu]);
      b->vdp->address += b->vdp->regs[15] ? b->vdp->regs[15] : 2u;
      b->vdp->data_reads++;
      return 0;
    }
  return -1;
}
static int genesis_vdp_write16(struct t2bus *b, uint32_t addr, uint16_t value)
{
  uint32_t port = addr & 0x1eu;
  struct t2vdp *v = b->vdp;
  if (!v || (addr & 1u) || addr < 0xc00000u || addr > 0xc0001eu) return -1;
  if (port == 0x04u || port == 0x06u)
    {
      v->ctrl_writes++;
      if (!v->pending && (value & 0xc000u) == 0x8000u)
        {
          unsigned reg = (value >> 8) & 0x1fu;
          if (reg >= 24u) return -1;
          v->regs[reg] = value & 255u;
          return 0;
        }
      if (!v->pending) { v->first_control = value; v->pending = 1; return 0; }
      v->address = (uint32_t)(v->first_control & 0x3fffu) |
                   ((uint32_t)(value & 3u) << 14);
      v->code = (uint8_t)(((v->first_control >> 14) & 3u) |
                          ((value >> 2) & 0x3cu));
      v->pending = 0;
      return 0;
    }
  if (port == 0x00u || port == 0x02u)
    {
      uint8_t *mem; uint32_t size;
      switch (v->code & 0x0fu)
        {
          case 0x01: mem=v->vram; size=65536u; break;
          case 0x03: mem=v->cram; size=128u; break;
          case 0x05: mem=v->vsram; size=80u; break;
          default: return -1;
        }
      uint32_t a = v->address % size;
      mem[a] = (uint8_t)(value >> 8);
      mem[(a + 1u) % size] = (uint8_t)value;
      v->address += v->regs[15] ? v->regs[15] : 2u;
      v->data_writes++;
      if ((v->code & 0x0fu) == 1u) v->vram_writes++;
      else if ((v->code & 0x0fu) == 3u) v->cram_writes++;
      else if ((v->code & 0x0fu) == 5u) v->vsram_writes++;
      if (value != 0u) v->nonzero_writes++;
      return 0;
    }
  return -1;
}

/* Mega Drive I/O registers. Unpressed 3-button pad: inputs pulled high.
 * Only output-configured bits are driven by the data latch. This does not
 * emulate six-button timing or external peripherals. */
static int genesis_io_read8(const struct t2bus *b, uint32_t addr, uint8_t *value)
{
  unsigned port, reg;
  if (addr < 0xa10000u || addr > 0xa1001fu) return -1;
  if (!(addr & 1u)) { *value = 0; return 0; }
  if (addr == 0xa10001u) { *value = 0x80u; return 0; }
  if (addr < 0xa10003u || addr > 0xa1001fu) return -1;
  reg = (unsigned)((addr - 0xa10003u) / 6u);
  port = (unsigned)(((addr - 0xa10003u) % 6u) / 2u);
  if (reg >= 5u || port >= 3u) return -1;
  switch (reg)
    {
      case 0: *value = (uint8_t)((b->io_data[port] & b->io_ctrl[port]) |
                                (0x7fu & (uint8_t)~b->io_ctrl[port])); return 0;
      case 1: *value = b->io_ctrl[port]; return 0;
      case 2: *value = b->io_tx[port]; return 0;
      case 3: *value = b->io_rx[port]; return 0;
      case 4: *value = b->io_serial_ctrl[port]; return 0;
    }
  return -1;
}
static int genesis_io_write8(struct t2bus *b, uint32_t addr, uint8_t value)
{
  unsigned reg, port;
  if (addr < 0xa10000u || addr > 0xa1001fu) return -1;
  if (!(addr & 1u)) return 0;
  if (addr < 0xa10003u) return -1;
  reg = (unsigned)((addr - 0xa10003u) / 6u);
  port = (unsigned)(((addr - 0xa10003u) % 6u) / 2u);
  if (reg >= 5u || port >= 3u) return -1;
  switch (reg)
    {
      case 0: b->io_data[port] = value; break;
      case 1: b->io_ctrl[port] = value; break;
      case 2: b->io_tx[port] = value; break;
      case 3: b->io_rx[port] = value; break;
      case 4: b->io_serial_ctrl[port] = value; break;
    }
  if (++b->io_writes <= 24u)
    printf("T2GEN V0.96 IO_WRITE: addr=%06lx value=%02x port=%u reg=%u\n",
           (unsigned long)addr, (unsigned)value, port, reg);
  return 0;
}
static int genesis_io_read16(const struct t2bus *b, uint32_t addr, uint16_t *value)
{
  uint8_t hi, lo;
  if ((addr & 1u) || genesis_io_read8(b, addr, &hi) ||
      genesis_io_read8(b, addr + 1u, &lo)) return -1;
  *value = (uint16_t)(((uint16_t)hi << 8) | lo);
  return 0;
}
static int genesis_io_read32(const struct t2bus *b, uint32_t addr, uint32_t *value)
{
  uint16_t hi, lo;
  if (genesis_io_read16(b, addr, &hi) ||
      genesis_io_read16(b, addr + 2u, &lo)) return -1;
  *value = ((uint32_t)hi << 16) | lo;
  return 0;
}
/* Z80 control is 68000-visible word access. Bit 8 of the 68000 word
 * carries the BUSREQ/RESET signal. BUSREQ readback is active-low:
 * 0x0000 means the 68000 has been granted the Z80 bus. No Z80 CPU runs.
 * State changes are immediate in this deliberately simplified model.
 */
static int genesis_z80_read16(const struct t2bus *b, uint32_t addr, uint16_t *value)
{
  if (addr == 0xa11100u)
    {
      *value = b->z80_busreq ? 0x0000u : 0x0100u;
      return 0;
    }
  if (addr == 0xa11200u)
    {
      *value = b->z80_reset_released ? 0x0100u : 0x0000u;
      return 0;
    }
  return -1;
}
static int genesis_z80_write16(struct t2bus *b, uint32_t addr, uint16_t value)
{
  if (addr == 0xa11100u)
    {
      b->z80_busreq = (value & 0x0100u) != 0u;
      b->z80_busreq_writes++;
      return 0;
    }
  if (addr == 0xa11200u)
    {
      b->z80_reset_released = (value & 0x0100u) != 0u;
      b->z80_reset_writes++;
      return 0;
    }
  return -1;
}
static int native_bus_read16(const struct t2bus *b, uint32_t addr,
                             uint16_t *value)
{
  addr &= 0xffffffu;
  if (addr & 1u) return -1;
  if (addr >= 0xa10000u && addr <= 0xa1001eu)
    {
      return genesis_io_read16(b, addr, value);
    }
  if (addr == 0xa11100u || addr == 0xa11200u)
    return genesis_z80_read16(b, addr, value);
  if (addr >= 0xa00000u && addr <= 0xa01ffeu && b->z80_busreq)
    {
      uint32_t off = addr - 0xa00000u;
      *value = ((uint16_t)b->z80_ram[off] << 8) | b->z80_ram[off + 1u];
      ((struct t2bus *)b)->z80_ram_reads++;
      return 0;
    }
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
  if (addr >= 0xc00000u && addr <= 0xc0001eu)
    return genesis_vdp_read16((struct t2bus *)b, addr, value);
  return genesis_io_read16(b, addr, value);
}
/* 68000 big-endian bus writes: RAM only; MMIO/ROM writes fail closed. */
static int native_bus_write8(struct t2bus *b, uint32_t addr, uint8_t value)
{
  addr &= 0xffffffu;
  if (addr >= 0xa10000u && addr <= 0xa1001fu)
    return genesis_io_write8(b, addr, value);
  /* Genesis PSG is an 8-bit, write-only port on the odd byte lane.
   * Silence-only stub: accept the command without inventing audio. */
  if (addr == 0xc00011u)
    {
      b->psg_writes++;
      b->psg_last = value;
      if (b->psg_writes <= 8u)
        printf("T2GEN V0.62 PSG_WRITE: count=%lu value=%02x\n",
               (unsigned long)b->psg_writes, (unsigned)value);
      return 0;
    }
  if (addr >= 0xa00000u && addr <= 0xa01fffu && b->z80_busreq)
    {
      b->z80_ram[addr - 0xa00000u] = value;
      b->z80_ram_byte_writes++;
      return 0;
    }
  if (addr >= 0xff0000u)
    {
      if (addr == 0xff0218u || addr == 0xff0219u)
        printf("T2GEN V0.92 FLAG_WRITE8: addr=%06lx value=%02x\n",
               (unsigned long)addr, (unsigned)value);
      b->ram[addr & 0xffffu] = value;
      return 0;
    }
  printf("T2GEN V0.59 WRITE_STOP: addr=%06lx value=%02x\n",
         (unsigned long)addr, value);
  return -3;
}
static int native_bus_write16(struct t2bus *b, uint32_t addr, uint16_t value)
{
  addr &= 0xffffffu;
  if (addr & 1u) return -3;
  if (addr >= 0xa10000u && addr <= 0xa1001eu)
    {
      if (genesis_io_write8(b, addr, (uint8_t)(value >> 8)) != 0 ||
          genesis_io_write8(b, addr + 1u, (uint8_t)value) != 0)
        return -3;
      return 0;
    }
  if (addr == 0xa11100u || addr == 0xa11200u)
    return genesis_z80_write16(b, addr, value);
  if (addr >= 0xa00000u && addr <= 0xa01ffeu && b->z80_busreq)
    {
      uint32_t off = addr - 0xa00000u;
      b->z80_ram[off] = (uint8_t)(value >> 8);
      b->z80_ram[off + 1u] = (uint8_t)value;
      b->z80_ram_writes++;
      return 0;
    }
  if (addr >= 0xc00000u && addr <= 0xc0001eu)
    return genesis_vdp_write16(b, addr, value);
  if (addr >= 0xff0000u && addr <= 0xfffffeu)
    {
      if (addr == 0xff0218u)
        printf("T2GEN V0.92 FLAG_WRITE16: value=%04x\n", (unsigned)value);
      b->ram[addr & 0xffffu] = (uint8_t)(value >> 8);
      b->ram[(addr + 1u) & 0xffffu] = (uint8_t)value;
      return 0;
    }
  return -3;
}
static int native_bus_write32(struct t2bus *b, uint32_t addr, uint32_t value)
{
  addr &= 0xffffffu;
  if (addr & 1u) return -3;
  /* 68000 longword access to VDP control/data port is two ordered
   * 16-bit transfers to the SAME port, not addr and addr+2.
   * This is essential for VDP 32-bit command words. */
  if (addr >= 0xc00000u && addr <= 0xc0001eu)
    {
      uint32_t port = addr & 0x1eu;
      if (port != 0x00u && port != 0x02u &&
          port != 0x04u && port != 0x06u) return -3;
      if (genesis_vdp_write16(b, addr, (uint16_t)(value >> 16)) != 0)
        return -3;
      if (genesis_vdp_write16(b, addr, (uint16_t)value) != 0)
        return -3;
      return 0;
    }
  /* Check the complete destination before changing any bytes. */
  if (addr < 0xff0000u || addr > 0xfffffcu)
    {
      printf("T2GEN V0.59 WRITE32_STOP: addr=%06lx\n", (unsigned long)addr);
      return -3;
    }
  if (addr == 0xff0230u || addr == 0xff0234u || addr == 0xff0238u)
    printf("T2GEN V1.01 PTR_WRITE32: addr=%06lx value=%08lx\n", (unsigned long)addr, (unsigned long)value);
  if (addr == 0xff0138u)
    printf("T2GEN V0.94 CALLBACK_WRITE: FF0138=%06lx\n", (unsigned long)(value & 0xffffffu));
  for (unsigned i = 0; i < 4u; ++i)
    if (native_bus_write8(b, addr + i, (uint8_t)(value >> (24u - 8u*i))))
      return -3;
  return 0;
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

  if (genesis_io_read32(b, 0xa10008u, &io_value) != 0) return -3;
  c->sr = (uint16_t)((c->sr & 0xfff0u) |
                       ((io_value & 0x80000000u) ? 8u : 0u) |
                       ((io_value == 0u) ? 4u : 0u));
  c->cycles += 20u;
  printf("T2GEN V0.59 AOT: pc=000200 TST.L ($A10008).L value=%08lx sr=%04x\n",
         (unsigned long)io_value, c->sr);

  /* BNE.S +6: branch target 0x20E; fallthrough 0x208. */
  c->pc = (c->sr & 4u) ? 0x208u : 0x20eu;
  c->cycles += (c->sr & 4u) ? 8u : 10u;
  printf("T2GEN V0.59 AOT: pc=000206 BNE.S +6 -> %06lx\n",
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
  /* BUSREQ readback: upper byte carries active-low bus-grant bit. */
  if (addr == 0xa11100u)
    {
      *value = b->z80_busreq ? 0x00u : 0x01u;
      ((struct t2bus *)b)->z80_busreq_reads++;
      return 0;
    }
  if (addr == 0xa11200u)
    {
      *value = b->z80_reset_released ? 0x01u : 0x00u;
      return 0;
    }
  if (addr >= 0xa00000u && addr <= 0xa01fffu && b->z80_busreq)
    {
      *value = b->z80_ram[addr - 0xa00000u];
      ((struct t2bus *)b)->z80_ram_reads++;
      return 0;
    }
  if (addr >= 0xff0000u)
    {
      *value = b->ram[addr & 0xffffu];
      return 0;
    }
  return genesis_io_read8(b, addr, value);
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

#ifndef T2GEN_NATIVE_BLOCK_BUDGET
#define T2GEN_NATIVE_BLOCK_BUDGET 1000000u
#endif

static int native_dispatch(struct t2cpu *c, struct t2bus *b)
{
  unsigned wait_a0da = 0;
  const uint32_t frame_cycles = 127840u; /* nominal NTSC 68000 cycles/frame */
  unsigned steps;
  uint32_t trace_pc[16] = {0};
  unsigned trace_pos = 0;
  for (steps = 0; steps < T2GEN_NATIVE_BLOCK_BUDGET; steps++)
    {
      /* V0.93: deliver IRQ6 at an emulated frame boundary. No RAM flag
       * shortcuts. 68000 format-0 exception frame: SR at SP, PC at SP+2.
       * Keep the saved supervisor stack separate from USP on mode changes.
       */
      if (c->next_vblank == 0u) c->next_vblank = frame_cycles;
      if (c->cycles >= c->next_vblank)
        {
          c->next_vblank += frame_cycles;
          if ((b->vdp->regs[1] & 0x20u) && ((c->sr >> 8) & 7u) < 6u)
            {
              uint32_t vector = 0, old_pc = c->pc;
              uint16_t old_sr = c->sr;
              uint32_t old_sp = c->a[7];
              if (native_bus_read32(b, 0x78u, &vector) != 0 ||
                  (vector & 1u) || vector >= b->len)
                { printf("T2GEN V0.93 IRQ6_BAD_VECTOR: %06lx\n", (unsigned long)vector); return -3; }
              if (!(old_sr & 0x2000u))
                { c->a[7] = c->usp; c->usp = old_sp; }
              c->a[7] = (c->a[7] - 6u) & 0xffffffu;
              if (native_bus_write16(b, c->a[7], old_sr) ||
                  native_bus_write32(b, c->a[7] + 2u, old_pc)) return -3;
              c->sr = (uint16_t)((old_sr | 0x2000u) & ~0x0700u);
              c->sr |= 0x0600u;
              c->pc = vector & 0xffffffu;
              c->cycles += 44u;
              c->irq6_count++;
              printf("T2GEN V0.93 IRQ6_ENTER: count=%lu from=%06lx handler=%06lx SR=%04x SP=%06lx\n",
                     (unsigned long)c->irq6_count, (unsigned long)old_pc,
                     (unsigned long)c->pc, (unsigned)c->sr, (unsigned long)c->a[7]);
            }
        }
      uint32_t previous = c->pc;
      /* V0.98: inspect indexed pointer tables and potential RAM code. */
      if (previous == 0x009420u || previous == 0x009448u ||
          (previous >= 0xff0000u && previous <= 0xffffffu))
        {
          uint32_t ptr_a = 0, ptr_b = 0, ram_ptr = 0, saved_ptr = 0;
          uint32_t index = ((uint32_t)(int32_t)(int16_t)(c->d[0] & 0xffffu));
          uint32_t ea_a = (0x009166u + index) & 0xffffffu;
          uint32_t ea_b = (0x00913au + index) & 0xffffffu;
          unsigned i;
          (void)native_bus_read32(b, ea_a, &ptr_a);
          (void)native_bus_read32(b, ea_b, &ptr_b);
          (void)native_bus_read32(b, 0xff023cu, &ram_ptr);
          (void)native_bus_read32(b, 0xff0238u, &saved_ptr);
          printf("T2GEN V0.98 INDEX_TRACE: pc=%06lx D0=%08lx A0=%06lx A1=%06lx EA1=%06lx ROM1=%08lx EA2=%06lx ROM2=%08lx FF0238=%08lx FF023C=%08lx\n",
                 (unsigned long)previous, (unsigned long)c->d[0],
                 (unsigned long)(c->a[0] & 0xffffffu),
                 (unsigned long)(c->a[1] & 0xffffffu),
                 (unsigned long)ea_a, (unsigned long)ptr_a,
                 (unsigned long)ea_b, (unsigned long)ptr_b,
                 (unsigned long)saved_ptr, (unsigned long)ram_ptr);
          if (previous >= 0xff0000u)
            {
              printf("T2GEN V0.98 RAM_TARGET: pc=%06lx bytes=",
                     (unsigned long)previous);
              for (i = 0; i < 32u; i++)
                printf("%02x", (unsigned)b->ram[(previous + i) & 0xffffu]);
              printf("\nT2GEN V0.98 RAM_CONTEXT: FF0620=");
              for (i = 0; i < 48u; i++)
                printf("%02x", (unsigned)b->ram[(0x0620u + i) & 0xffffu]);
              printf("\n");
            }
        }
      /* V0.92: diagnose the actual RAM wait without inventing VBlank IRQs. */
      if (previous == 0x00a0dau)
        {
          uint16_t flag = 0, other = 0;
          if (native_bus_read16(b, 0x00ff0218u, &flag) ||
              native_bus_read16(b, 0x00ff0222u, &other))
            return -3;
          if (wait_a0da == 0u)
            {
              uint32_t vec4 = 0, vec6 = 0;
              (void)native_bus_read32(b, 0x00000070u, &vec4);
              (void)native_bus_read32(b, 0x00000078u, &vec6);
              printf("T2GEN V0.92 WAIT_ENTER: pc=%06lx FF0218=%04x FF0222=%04x SR=%04x cycles=%lu VDPreg1=%02x VDPstatus_reads=%lu IRQ4vector=%06lx IRQ6vector=%06lx\n",
                     (unsigned long)previous, flag, other, c->sr,
                     (unsigned long)c->cycles, (unsigned)b->vdp->regs[1],
                     (unsigned long)b->vdp->status_reads,
                     (unsigned long)(vec4 & 0xffffffu),
                     (unsigned long)(vec6 & 0xffffffu));
            }
          if (++wait_a0da >= 4096u && flag != 0u)
            {
              printf("T2GEN V0.92 WAIT_STALL: pc=%06lx FF0218=%04x FF0222=%04x SR=%04x iterations=%u cycles=%lu (no synthetic IRQ or RAM flag modification)\n",
                     (unsigned long)previous, flag, other, c->sr,
                     wait_a0da, (unsigned long)c->cycles);
              return 0;
            }
        }
      else
        {
          wait_a0da = 0u;
        }
      trace_pc[trace_pos++ & 15u] = previous;
      uint32_t previous_cycles = c->cycles;
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
                printf("T2GEN V0.71 AOT_STOP: PC=%06lx D0=%08lx D1=%08lx A0=%08lx A1=%08lx SR=%04x cycles=%lu\n", (unsigned long)c->pc, (unsigned long)c->d[0], (unsigned long)c->d[1], (unsigned long)c->a[0], (unsigned long)c->a[1], (unsigned)c->sr, (unsigned long)c->cycles);
                printf("T2GEN V0.71 STACK: A7=%06lx\n", (unsigned long)c->a[7]);
                { unsigned ti;
                  printf("T2GEN V0.77 TRACE16:");
                  for (ti = 0; ti < 16u; ti++)
                    printf(" %06lx", (unsigned long)trace_pc[(trace_pos + ti) & 15u]);
                  printf("\n");
                }
                printf("T2GEN V0.60 DISPATCH_STOP: untranslated pc=%06lx\n",
                       (unsigned long)c->pc);
                return 0;
              }
            break;
        }
      if (rc != 0)
        {
          printf("T2GEN V0.60 DISPATCH_STOP: block failure pc=%06lx rc=%d\n",
                 (unsigned long)previous, rc);
          return rc;
        }
      if (c->pc == previous && c->cycles == previous_cycles)
        {
          printf("T2GEN V0.60 DISPATCH_STOP: no progress pc=%06lx\n",
                 (unsigned long)c->pc);
          return -1;
        }
    }
  printf("T2GEN V0.78 DISPATCH_STOP: block budget exhausted steps=%lu pc=%06lx D0=%08lx D1=%08lx SR=%04x A7=%06lx cycles=%lu\n",
         (unsigned long)steps, (unsigned long)c->pc,
         (unsigned long)c->d[0], (unsigned long)c->d[1],
         (unsigned)c->sr, (unsigned long)c->a[7],
         (unsigned long)c->cycles);
  { unsigned ti;
    printf("T2GEN V0.78 TRACE16:");
    for (ti = 0; ti < 16u; ti++)
      printf(" %06lx", (unsigned long)trace_pc[(trace_pos + ti) & 15u]);
    printf("\n");
  }
  return 0;
}

void t2gen_native43_probe(const uint8_t *rom, size_t len, const char *fbpath)
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
  b.vdp = (struct t2vdp *)calloc(1u, sizeof(*b.vdp));
  if (!b.ram || !b.vdp)
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
  printf("T2GEN V0.60 NATIVE_AOT: SP=%08lx PC=%06lx (no Musashi, no interpreter)\n",
         (unsigned long)sp, (unsigned long)pc);
  if (pc != 0x200u)
    {
      printf("T2GEN V0.59 STOP: unknown reset PC; no native block\n");
      goto done;
    }
  rc = native_dispatch(&c, &b);
  printf("T2GEN V0.60 NATIVE_STOP: pc=%06lx cycles=%lu rc=%d\n",
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
  if (b.vdp && fbpath && strcmp(fbpath, "none") != 0)
    {
      struct t2gen_vdp_frame59 *v = malloc(sizeof(*v));
      if (!v)
        {
          printf("T2GEN V0.59.1 VDP_SNAPSHOT: allocation failed\n");
        }
      else
        {
          memcpy(v->vram, b.vdp->vram, sizeof(v->vram));
          memcpy(v->cram, b.vdp->cram, sizeof(v->cram));
          for (unsigned r = 0; r < 24; ++r)
            v->regs[r] = (uint8_t)b.vdp->regs[r];
          { unsigned nzv=0, nzc=0, first=65536u, i;
            for (i=0;i<65536u;++i) if (v->vram[i]) {++nzv; if(first==65536u)first=i;}
            for (i=0;i<128u;++i) if (v->cram[i]) ++nzc;
            printf("T2GEN V0.61 VDP_MEMORY: vram_nonzero=%u cram_nonzero_bytes=%u first_vram=%05x\n",nzv,nzc,first);
          }
          { unsigned k; printf("T2GEN V1.10 PALETTE: reg1=%02x display_enable=%u code=%02x addr=%06lx first16=", (unsigned)b.vdp->regs[1], (unsigned)((b.vdp->regs[1]>>6)&1u), (unsigned)b.vdp->code, (unsigned long)b.vdp->address);
            for(k=0;k<32u;k++)printf("%02x",(unsigned)v->cram[k]);
            printf("\n"); }
          printf("T2GEN V0.59.1 VDP_SNAPSHOT: data_writes=%lu\n",
                 (unsigned long)b.vdp->data_writes);
          if (t2gen_vdp_frame59_render(fbpath, v) < 0)
            printf("T2GEN V0.59.1 VDP_SNAPSHOT: render failed\n");
          free(v);
        }
    }
  if (b.vdp) printf("T2GEN V0.73 VDP_CLASS: vram=%lu cram=%lu vsram=%lu nonzero_words=%lu code=%02x address=%06lx dma_reg=%02x\n",
    (unsigned long)b.vdp->vram_writes, (unsigned long)b.vdp->cram_writes,
    (unsigned long)b.vdp->vsram_writes, (unsigned long)b.vdp->nonzero_writes,
    (unsigned)b.vdp->code, (unsigned long)b.vdp->address, (unsigned)b.vdp->regs[1]);
  if (b.vdp) printf("T2GEN V0.59 VDP: status_reads=%lu ctrl_writes=%lu data_writes=%lu data_reads=%lu\n",
    (unsigned long)b.vdp->status_reads, (unsigned long)b.vdp->ctrl_writes,
    (unsigned long)b.vdp->data_writes, (unsigned long)b.vdp->data_reads);
  printf("T2GEN V0.59 Z80: busreq=%u reset_released=%u busreq_writes=%lu busreq_reads=%lu reset_writes=%lu ram_reads=%lu ram_writes=%lu\n",
         (unsigned)b.z80_busreq, (unsigned)b.z80_reset_released,
         (unsigned long)b.z80_busreq_writes, (unsigned long)b.z80_busreq_reads, (unsigned long)b.z80_reset_writes,
         (unsigned long)b.z80_ram_reads, (unsigned long)b.z80_ram_writes);
  {
    uint32_t checksum = 2166136261u;
    unsigned i;
    for (i = 0; i < sizeof(b.z80_ram); ++i)
      checksum = (checksum ^ b.z80_ram[i]) * 16777619u;
    printf("T2GEN V0.62 PSG: writes=%lu last=%02x\n",
         (unsigned long)b.psg_writes, (unsigned)b.psg_last);
  printf("T2GEN V0.59 Z80_RAM: byte_writes=%lu fnv1a=%08lx first16=",
           (unsigned long)b.z80_ram_byte_writes, (unsigned long)checksum);
    for (i = 0; i < 16u; ++i) printf("%02x", (unsigned)b.z80_ram[i]);
    printf("\n");
  }
  free(b.vdp);
  free(b.ram);
  printf("T2GEN V0.59: native probe returned\n");
}
