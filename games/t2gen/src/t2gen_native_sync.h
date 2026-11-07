/* Native ARM/C implementation of original 68000 polling comparisons. */
#ifndef T2GEN_NATIVE_SYNC_H
#define T2GEN_NATIVE_SYNC_H
#include <stdint.h>
#define T2N_CCR_C 0x01u
#define T2N_CCR_V 0x02u
#define T2N_CCR_Z 0x04u
#define T2N_CCR_N 0x08u
#define T2N_CCR_X 0x10u
struct t2n_sync_result { uint8_t ccr; uint8_t branch_taken; };
/* CMP.W <ea>,Dn calculates Dn.W - <ea>. X is preserved. */
static inline struct t2n_sync_result t2n_cmp_word(uint32_t dn,
                                                    uint16_t mem,
                                                    uint16_t old_sr)
{
  uint16_t a=(uint16_t)dn, r=(uint16_t)(a-mem);
  uint8_t c=(uint8_t)(old_sr & T2N_CCR_X);
  if (r == 0) c |= T2N_CCR_Z;
  if (r & 0x8000u) c |= T2N_CCR_N;
  if (a < mem) c |= T2N_CCR_C;
  if (((a ^ mem) & (a ^ r) & 0x8000u) != 0) c |= T2N_CCR_V;
  return (struct t2n_sync_result){c, (uint8_t)(r == 0)};
}
/* TST.W clears C,V; sets N,Z; preserves X. BNE branches if !Z. */
static inline struct t2n_sync_result t2n_tst_word(uint16_t mem,
                                                    uint16_t old_sr)
{
  uint8_t c=(uint8_t)(old_sr & T2N_CCR_X);
  if (mem == 0) c |= T2N_CCR_Z;
  if (mem & 0x8000u) c |= T2N_CCR_N;
  return (struct t2n_sync_result){c, (uint8_t)(mem != 0)};
}
#endif
