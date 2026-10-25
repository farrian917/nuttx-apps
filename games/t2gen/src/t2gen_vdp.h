
#ifndef T2GEN_VDP_H
#define T2GEN_VDP_H

#include <stdint.h>
#include <stdbool.h>

#define T2GEN_VRAM_SIZE 65536

struct t2gen_vdp_s
{
  uint8_t vram[T2GEN_VRAM_SIZE];
  /* V0.30: generation of each 32-byte pattern; writes invalidate tiles. */
  uint32_t tile_version[2048];
  uint32_t tile_reset_serial;
  uint16_t cram[64];
  uint16_t vsram[40];
  uint8_t reg[24];

  uint16_t addr;
  uint8_t code;
  uint16_t command;
  bool command_pending;
  uint16_t status;
  uint16_t read_buffer;
  bool dma_fill_pending;
  uint32_t dma_words;
  uint32_t dma_transfers;
  uint32_t dma_unsupported;
  uint32_t register_writes;
  uint32_t data_writes;
  uint16_t scanline;
  uint32_t frames;
  uint32_t vblank_entries;
  uint32_t irq_requests;
  uint32_t status_reads;
};

typedef uint16_t (*t2gen_vdp_dma_read_t)(uint32_t address);
void t2gen_vdp_set_dma_reader(t2gen_vdp_dma_read_t reader);
void t2gen_vdp_reset(void);

void t2gen_vdp_write_control(uint16_t value);
void t2gen_vdp_write_data(uint16_t value);
uint16_t t2gen_vdp_read_control(void);
uint16_t t2gen_vdp_read_data(void);
const struct t2gen_vdp_s *t2gen_vdp_state(void);
void t2gen_vdp_dump(void);
void t2gen_vdp_dump_memory(void);
void t2gen_vdp_dump_write_diagnostics(void);
void t2gen_vdp_set_scanline(uint16_t line);
bool t2gen_vdp_irq_enabled(void);
void t2gen_vdp_note_irq(void);

#endif
