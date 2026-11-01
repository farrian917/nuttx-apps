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
/* V0.41: Cortex-M7 Thumb-2 native CMP.W implementation. The 68000
 * subtraction is Dn.W - memory.W. ARM's carry flag means NO borrow,
 * so it must be inverted when forming the 68000 C bit. X is preserved.
 * This executes real ARM ALU instructions, not a 68000 opcode handler.
 * No memory access or instruction timing is performed in this helper. */
static inline struct t2n_sync_result t2n_v041_arm_cmp_word(uint32_t dn,
                                                             uint16_t mem,
                                                             uint16_t old_sr)
{
#if defined(__arm__) && defined(__thumb__)
  uint32_t lhs = dn & 0xffffu;
  uint32_t rhs = (uint32_t)mem;
  uint32_t apsr;
  __asm__ volatile ("subs %[lhs], %[lhs], %[rhs]\n\tmrs %[apsr], apsr"
                    : [lhs] "+r" (lhs), [apsr] "=r" (apsr)
                    : [rhs] "r" (rhs)
                    : "cc");
  uint8_t c = (uint8_t)(old_sr & T2N_CCR_X);
  if (apsr & (1u << 30)) c |= T2N_CCR_Z;
  if ((uint16_t)lhs & 0x8000u) c |= T2N_CCR_N;
  if (!(apsr & (1u << 29))) c |= T2N_CCR_C;
  /* ARM's 32-bit V is not 68000's 16-bit V. Compute 16-bit overflow. */
  if (((((uint16_t)dn ^ mem) & ((uint16_t)dn ^ (uint16_t)lhs)) & 0x8000u) != 0)
    c |= T2N_CCR_V;
  return (struct t2n_sync_result){c, (uint8_t)((uint16_t)lhs == 0u)};
#else
  return t2n_cmp_word(dn, mem, old_sr);
#endif
}
#ifdef T2GEN_V041_ARM_CMP
#define t2n_v041_cmp_word t2n_v041_arm_cmp_word
#else
#define t2n_v041_cmp_word t2n_cmp_word
#endif
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
