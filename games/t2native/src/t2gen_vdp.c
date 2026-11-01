
#include "t2gen_vdp.h"

#include <string.h>
#include <stdio.h>
/* Release build: remove high-volume VDP debug formatting and UART I/O. */
#ifndef T2GEN_VERBOSE_VDP
#define printf(...) ((void)0)
#endif

static struct t2gen_vdp_s g_vdp;
static t2gen_vdp_dma_read_t g_dma_reader;
/* V8.2 diagnostics: bounded output, no changes to emulation behavior. */
static uint32_t g_dbg_nonzero_vram;
static uint32_t g_dbg_nonzero_cram;
static uint32_t g_dbg_nonzero_vsram;
static uint32_t g_dbg_zero_data;
static uint32_t g_dbg_nonzero_data;
static uint32_t g_dbg_ignored_data;
static uint32_t g_dbg_reset_count;
static uint32_t g_dbg_dma_zero_words;
static uint32_t g_dbg_dma_nonzero_words;
static uint32_t g_dbg_data_samples;
static uint32_t g_dbg_control_samples;
/* V8.4: fill is distinct from CPU->VDP DMA and needs its own counters. */
static uint32_t g_dbg_fill_words;
static uint32_t g_dbg_fill_nonzero_bytes;
static uint32_t g_dbg_first_nonzero_logged;
static uint32_t g_dbg_first_nonzero_cram_logged;
static uint32_t g_dbg_first_nonzero_vsram_logged;

static unsigned dbg_vram_nonzero(void)
{
  unsigned n = 0;
  for (unsigned i = 0; i < T2GEN_VRAM_SIZE; i++)
    if (g_vdp.vram[i]) n++;
  return n;
}
static unsigned dbg_cram_nonzero(void)
{
  unsigned n = 0;
  for (unsigned i = 0; i < 64; i++)
    if (g_vdp.cram[i]) n++;
  return n;
}


void t2gen_vdp_set_dma_reader(t2gen_vdp_dma_read_t reader)
{
  g_dma_reader = reader;
}

static uint32_t dma_length(void)
{
  uint32_t n = (uint32_t)g_vdp.reg[19] | ((uint32_t)g_vdp.reg[20] << 8);
  return n ? n : 65536u;
}

static void dma_finish(uint32_t count)
{
  g_vdp.dma_words += count;
  g_vdp.dma_transfers++;
  g_vdp.reg[19] = 0;
  g_vdp.reg[20] = 0;
}

static void dma_start(void)
{
  uint32_t n = dma_length();
  uint8_t mode = g_vdp.reg[23] >> 6;
  uint32_t src = (uint32_t)g_vdp.reg[21] |
                 ((uint32_t)g_vdp.reg[22] << 8) |
                 ((uint32_t)(g_vdp.reg[23] & 0x7f) << 16);
  uint32_t i;
  unsigned before_vram = 0;
  unsigned before_cram = 0;
  printf("T2GEN V8.2 DMA BEGIN mode=%u len=%lu src_word=%06lX dst=%04X code=%02X inc=%u vram_nz=%u cram_nz=%u\n",
         (unsigned)mode, (unsigned long)n, (unsigned long)src,
         (unsigned)g_vdp.addr, (unsigned)g_vdp.code,
         (unsigned)g_vdp.reg[15], before_vram, before_cram);

  if (mode == 2)
    {
      printf("T2GEN V8.4 DMA FILL armed length=%lu destination=%04X increment=%u\n",
             (unsigned long)n, (unsigned)g_vdp.addr, (unsigned)g_vdp.reg[15]);
      g_vdp.dma_fill_pending = true;
      return;
    }
  if (mode == 3 && (g_vdp.code & 0x0f) == 1)
    {
      for (i = 0; i < n; i++)
        {
          g_vdp.vram[g_vdp.addr] = g_vdp.vram[(uint16_t)src];
          src = (uint16_t)(src + 1);
          g_vdp.addr += g_vdp.reg[15];
        }
      g_vdp.reg[21] = src & 0xff;
      g_vdp.reg[22] = (src >> 8) & 0xff;
      dma_finish(n);
      return;
    }
  if (mode <= 1 && g_dma_reader)
    {
      for (i = 0; i < n; i++)
        {
          uint16_t word = g_dma_reader((src << 1) & 0xffffffu);
          if (word) g_dbg_dma_nonzero_words++;
          else g_dbg_dma_zero_words++;
          if (i < 8u)
            printf("T2GEN V8.2 DMA WORD[%lu] src=%06lX dst=%04X val=%04X\n",
                   (unsigned long)i, (unsigned long)((src << 1) & 0xffffffu),
                   (unsigned)g_vdp.addr, (unsigned)word);
          uint16_t addr = g_vdp.addr;
          switch (g_vdp.code & 0x0f)
            {
              case 1:
                g_vdp.vram[addr] = word >> 8;
                g_vdp.vram[(uint16_t)(addr + 1)] = word;
                break;
              case 3:
                g_vdp.cram[(addr >> 1) & 63] = word;
                break;
              case 5:
                if (((addr >> 1) & 63) < 40)
                  g_vdp.vsram[(addr >> 1) & 63] = word;
                break;
              default:
                g_vdp.dma_unsupported++;
                return;
            }
          src = (src + 1) & 0x7fffffu;
          g_vdp.addr += g_vdp.reg[15];
        }
      g_vdp.reg[21] = src & 0xff;
      g_vdp.reg[22] = (src >> 8) & 0xff;
      g_vdp.reg[23] = (g_vdp.reg[23] & 0x80) | ((src >> 16) & 0x7f);
      printf("T2GEN V8.2 DMA END vram_nz=%u cram_nz=%u src_end=%06lX dst_end=%04X zero_words=%lu nonzero_words=%lu\n",
             dbg_vram_nonzero(), dbg_cram_nonzero(),
             (unsigned long)src, (unsigned)g_vdp.addr,
             (unsigned long)g_dbg_dma_zero_words,
             (unsigned long)g_dbg_dma_nonzero_words);
      dma_finish(n);
      return;
    }
  g_vdp.dma_unsupported++;
}


void t2gen_vdp_reset(void)
{
  printf("T2GEN V8.2 RESET #%lu before: vram_nz=%u cram_nz=%u datawrites=%lu\n",
         (unsigned long)++g_dbg_reset_count, dbg_vram_nonzero(),
         dbg_cram_nonzero(), (unsigned long)g_vdp.data_writes);
  memset(&g_vdp, 0, sizeof(g_vdp));
  g_vdp.reg[15] = 2;
  g_vdp.status = 0x3400;
}

void t2gen_vdp_write_control(uint16_t value)
{
  if (g_dbg_control_samples++ < 24u)
    printf("T2GEN V8.2 CTRL[%lu] value=%04X pending=%u addr=%04X code=%02X\n",
           (unsigned long)(g_dbg_control_samples - 1), (unsigned)value,
           (unsigned)g_vdp.command_pending, (unsigned)g_vdp.addr,
           (unsigned)g_vdp.code);
  if (!g_vdp.command_pending &&
      (value & 0xc000) == 0x8000)
    {
      uint8_t reg = (value >> 8) & 0x1f;

      if (reg < 24)
        {
          g_vdp.reg[reg] = value & 0xff;
          g_vdp.register_writes++;
        }

      return;
    }

  if (!g_vdp.command_pending)
    {
      g_vdp.command = value;
      g_vdp.command_pending = true;
    }
  else
    {
      g_vdp.addr =
        (g_vdp.command & 0x3fff) |
        ((value & 0x0003) << 14);

      g_vdp.code =
        ((g_vdp.command >> 14) & 0x03) |
        ((value >> 2) & 0x3c);

      g_vdp.command_pending = false;
      if ((g_vdp.code & 0x20) && (g_vdp.reg[1] & 0x10))
        dma_start();
    }
}

void t2gen_vdp_write_data(uint16_t value)
{
  uint16_t addr = g_vdp.addr;
  g_vdp.data_writes++;
  if (value) g_dbg_nonzero_data++;
  else g_dbg_zero_data++;
  if (g_dbg_data_samples++ < 16u)
    printf("T2GEN V8.2 DATA[%lu] val=%04X addr=%04X code=%02X inc=%u fill=%u\n",
           (unsigned long)(g_dbg_data_samples - 1), (unsigned)value,
           (unsigned)addr, (unsigned)g_vdp.code,
           (unsigned)g_vdp.reg[15], (unsigned)g_vdp.dma_fill_pending);

  if (g_vdp.dma_fill_pending)
    {
      uint32_t i, n = dma_length();
      /* Approximate MD DMA fill: first byte at address, then high byte
       * to successive VRAM locations. Not cycle-accurate. */
      g_vdp.vram[addr] = (uint8_t)value;
      printf("T2GEN V8.4 DMA FILL execute length=%lu seed=%04X start=%04X inc=%u\n",
             (unsigned long)n, (unsigned)value, (unsigned)addr,
             (unsigned)g_vdp.reg[15]);
      g_dbg_fill_words += n;
      if ((value & 0xffu) != 0u) g_dbg_fill_nonzero_bytes++;
      if ((value >> 8) != 0u) g_dbg_fill_nonzero_bytes += n;
      for (i = 0; i < n; i++)
        {
          g_vdp.vram[(uint16_t)(g_vdp.addr + 1)] = value >> 8;
          g_vdp.addr += g_vdp.reg[15];
        }
      g_vdp.dma_fill_pending = false;
      printf("T2GEN V8.4 DMA FILL done end=%04X vram_nonzero=%u\n",
             (unsigned)g_vdp.addr, dbg_vram_nonzero());
      dma_finish(n);
      return;
    }

  switch (g_vdp.code & 0x0f)
    {
      case 0x01: /* VRAM write */
        if (value)
          {
            g_dbg_nonzero_vram++;
            if (!g_dbg_first_nonzero_logged++)
              printf("T2GEN V8.4 FIRST VRAM DATA: addr=%04X value=%04X code=%02X inc=%u\n",
                     (unsigned)addr, (unsigned)value, (unsigned)g_vdp.code,
                     (unsigned)g_vdp.reg[15]);
          }
        g_vdp.vram[addr] = value >> 8;
        g_vdp.vram[(uint16_t)(addr + 1)] = value;
        break;

      case 0x03: /* CRAM write */
        if (value)
          {
            g_dbg_nonzero_cram++;
            if (!g_dbg_first_nonzero_cram_logged++)
              printf("T2GEN V8.4 FIRST CRAM DATA: addr=%04X value=%04X code=%02X\n",
                     (unsigned)addr, (unsigned)value, (unsigned)g_vdp.code);
          }
        g_vdp.cram[(addr >> 1) & 63] = value;
        break;

      case 0x05: /* VSRAM write */
        if (value)
          {
            g_dbg_nonzero_vsram++;
            if (!g_dbg_first_nonzero_vsram_logged++)
              printf("T2GEN V8.4 FIRST VSRAM DATA: addr=%04X value=%04X code=%02X\n",
                     (unsigned)addr, (unsigned)value, (unsigned)g_vdp.code);
          }
        if (((addr >> 1) & 63) < 40)
          {
            g_vdp.vsram[(addr >> 1) & 63] = value;
          }
        break;
      default:
        g_dbg_ignored_data++;
        break;
    }

  g_vdp.addr += g_vdp.reg[15];
  g_vdp.command_pending = false;
}

uint16_t t2gen_vdp_read_control(void)
{
  g_vdp.command_pending = false;
  g_vdp.status_reads++;
  return g_vdp.status;
}

uint16_t t2gen_vdp_read_data(void)
{
  uint16_t value = 0;

  switch (g_vdp.code & 0x0f)
    {
      case 0x00: /* VRAM read */
        value =
          ((uint16_t)g_vdp.vram[g_vdp.addr] << 8) |
          g_vdp.vram[(uint16_t)(g_vdp.addr + 1)];
        break;

      case 0x08: /* CRAM read */
        value = g_vdp.cram[(g_vdp.addr >> 1) & 63];
        break;

      case 0x04: /* VSRAM read */
        if (((g_vdp.addr >> 1) & 63) < 40)
          {
            value = g_vdp.vsram[(g_vdp.addr >> 1) & 63];
          }
        break;
    }

  g_vdp.addr += g_vdp.reg[15];
  g_vdp.command_pending = false;
  return value;
}

/* V7: coarse NTSC scanline model. This is not dot-accurate timing. */
void t2gen_vdp_set_scanline(uint16_t line)
{
  bool old_blank = (g_vdp.status & 0x0008u) != 0;
  bool new_blank = line >= 224u;
  g_vdp.scanline = line;
  if (new_blank)
    g_vdp.status |= 0x0008u;
  else
    g_vdp.status &= (uint16_t)~0x0008u;
  if (!old_blank && new_blank)
    g_vdp.vblank_entries++;
  if (line == 0u)
    g_vdp.frames++;
}

bool t2gen_vdp_irq_enabled(void)
{
  return (g_vdp.reg[1] & 0x20u) != 0u;
}

void t2gen_vdp_note_irq(void)
{
  g_vdp.irq_requests++;
}

void t2gen_vdp_dump(void)
{
  unsigned i;
  printf("T2GEN VDP registers:\n");
  for (i = 0; i < 24; i++)
    {
      printf("R%02u=%02X ", i, (unsigned)g_vdp.reg[i]);
      if ((i & 7u) == 7u)
        {
          printf("\n");
        }
    }
  printf("T2GEN VDP: regwrites=%lu datawrites=%lu DMA=%lu words=%lu unsupported=%lu fill_pending=%u\n",
         (unsigned long)g_vdp.register_writes, (unsigned long)g_vdp.data_writes,
         (unsigned long)g_vdp.dma_transfers, (unsigned long)g_vdp.dma_words,
         (unsigned long)g_vdp.dma_unsupported, (unsigned)g_vdp.dma_fill_pending);
  printf("T2GEN V7: frames=%lu scanline=%u vblank=%lu irq=%lu status_reads=%lu\n",
         (unsigned long)g_vdp.frames, (unsigned)g_vdp.scanline,
         (unsigned long)g_vdp.vblank_entries,
         (unsigned long)g_vdp.irq_requests,
         (unsigned long)g_vdp.status_reads);
  printf("T2GEN VDP: addr=%04X code=%02X status=%04X pending=%u\n",
         (unsigned)g_vdp.addr, (unsigned)g_vdp.code,
         (unsigned)g_vdp.status, (unsigned)g_vdp.command_pending);
}


const struct t2gen_vdp_s *t2gen_vdp_state(void)
{
  return &g_vdp;
}


/* V8.1: inspect the VDP state before drawing a snapshot. */
void t2gen_vdp_dump_memory(void)
{
  unsigned vram_nonzero = 0;
  unsigned cram_nonzero = 0;
  unsigned vsram_nonzero = 0;
  unsigned pattern_nonzero = 0;
  unsigned p;
  const uint32_t bases[2] = {
    ((uint32_t)(g_vdp.reg[4] & 7u) << 13) & 0xffffu,
    ((uint32_t)(g_vdp.reg[2] & 0x38u) << 10) & 0xffffu
  };
  const char *names[2] = {"B", "A"};

  for (unsigned i = 0; i < T2GEN_VRAM_SIZE; i++)
    {
      if (g_vdp.vram[i] != 0)
        {
          vram_nonzero++;
        }
    }
  for (unsigned i = 0; i < 64; i++)
    {
      if (g_vdp.cram[i] != 0)
        {
          cram_nonzero++;
        }
    }
  for (unsigned i = 0; i < 40; i++)
    {
      if (g_vdp.vsram[i] != 0)
        {
          vsram_nonzero++;
        }
    }
  /* Tile patterns occupy 32 bytes each. Count nonempty tiles in VRAM. */
  for (unsigned tile = 0; tile < 2048; tile++)
    {
      for (unsigned j = 0; j < 32; j++)
        {
          if (g_vdp.vram[tile * 32u + j] != 0)
            {
              pattern_nonzero++;
              break;
            }
        }
    }

  printf("T2GEN V8.1: VRAM nonzero=%u/65536 CRAM nonzero=%u/64 "
         "VSRAM nonzero=%u/40 patterns_nonzero=%u/2048\n",
         vram_nonzero, cram_nonzero, vsram_nonzero, pattern_nonzero);
  printf("T2GEN V8.1: CRAM first 16:");
  for (unsigned i = 0; i < 16; i++)
    {
      printf(" %04X", (unsigned)g_vdp.cram[i]);
    }
  printf("\n");

  for (p = 0; p < 2; p++)
    {
      unsigned nonzero_entries = 0;
      unsigned cols = 32u << (g_vdp.reg[16] & 3u);
      unsigned rows = 32u << ((g_vdp.reg[16] >> 4) & 3u);
      uint32_t base = bases[p];
      if (cols > 128u) cols = 128u;
      if (rows > 128u) rows = 128u;
      for (unsigned i = 0; i < cols * rows; i++)
        {
          uint32_t a = (base + 2u * i) & 0xffffu;
          uint16_t entry = ((uint16_t)g_vdp.vram[a] << 8) |
                           g_vdp.vram[(a + 1u) & 0xffffu];
          if (entry != 0) nonzero_entries++;
        }
      printf("T2GEN V8.1: plane %s base=%04lX entries_nonzero=%u/%u "
             "first32:", names[p], (unsigned long)base,
             nonzero_entries, cols * rows);
      for (unsigned i = 0; i < 32; i++)
        {
          printf(" %02X", (unsigned)g_vdp.vram[(base + i) & 0xffffu]);
        }
      printf("\n");
    }
}

void t2gen_vdp_dump_write_diagnostics(void)
{
  printf("T2GEN V8.2 SUMMARY: data_zero=%lu data_nonzero=%lu ignored=%lu vram_nonzero_writes=%lu cram_nonzero_writes=%lu vsram_nonzero_writes=%lu resets=%lu\n",
         (unsigned long)g_dbg_zero_data, (unsigned long)g_dbg_nonzero_data,
         (unsigned long)g_dbg_ignored_data, (unsigned long)g_dbg_nonzero_vram,
         (unsigned long)g_dbg_nonzero_cram, (unsigned long)g_dbg_nonzero_vsram,
         (unsigned long)g_dbg_reset_count);
  printf("T2GEN V8.4 SUMMARY: dma_fill_words=%lu fill_nonzero_bytes=%lu first_nonzero_vram=%lu first_nonzero_cram=%lu first_nonzero_vsram=%lu\n",
         (unsigned long)g_dbg_fill_words, (unsigned long)g_dbg_fill_nonzero_bytes,
         (unsigned long)g_dbg_first_nonzero_logged,
         (unsigned long)g_dbg_first_nonzero_cram_logged,
         (unsigned long)g_dbg_first_nonzero_vsram_logged);
  printf("T2GEN V8.2 SUMMARY: dma_zero_words=%lu dma_nonzero_words=%lu final_vram_nz=%u final_cram_nz=%u\n",
         (unsigned long)g_dbg_dma_zero_words,
         (unsigned long)g_dbg_dma_nonzero_words,
         dbg_vram_nonzero(), dbg_cram_nonzero());
}
