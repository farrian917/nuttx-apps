/* ======================================================================== */
/* ========================= LICENSING & COPYRIGHT ======================== */
/* ======================================================================== */
/*
 *                                  MUSASHI
 *                                Version 4.60
 *
 * A portable Motorola M680x0 processor emulation engine.
 * Copyright Karl Stenerud.  All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


/* ======================================================================== */
/* ================================= NOTES ================================ */
/* ======================================================================== */



/* ======================================================================== */
/* ================================ INCLUDES ============================== */
/* ======================================================================== */

extern void m68040_fpu_op0(void);
extern void m68040_fpu_op1(void);
extern void m68881_mmu_ops(void);
// extern unsigned char m68ki_cycles[][0x10000];
// extern void (*m68ki_instruction_jump_table[0x10000])(void); /* opcode handler jump table */
// extern void (**m68ki_instruction_jump_table)(void);
// extern unsigned char (*m68ki_cycles)[0x10000];
extern void (**m68ki_instruction_jump_table)(void);
extern unsigned char (*m68ki_cycles)[0x10000];
extern void m68ki_build_opcode_table(void);

// #include "m68kops.h"
// #include "m68kcpu.h"
#if defined(T2GEN_V010_NATIVE_CMP_EXEC) || defined(T2GEN_V011_NATIVE_SYNC_EXEC)
#include "../t2gen_native_sync.h"
#ifdef T2GEN_V012_NATIVE_BRANCH_EXEC
#ifdef T2GEN_V015_PAIRED_SYNC
static unsigned long g_t2gen_v016_paired_count[3];
static unsigned long g_t2gen_v016_paired_fallback[3];
unsigned long t2gen_v016_paired_count(unsigned int i)
{ return i < 3 ? g_t2gen_v016_paired_count[i] : 0; }
unsigned long t2gen_v016_paired_fallback(unsigned int i)
{ return i < 3 ? g_t2gen_v016_paired_fallback[i] : 0; }
#endif
#ifdef T2GEN_V018_ROUTINE_DISPATCH
static unsigned long g_t2gen_v018_followup[3];
static unsigned long g_t2gen_v018_exit[3];
unsigned long t2gen_v018_followup_count(unsigned int i)
{ return i < 3 ? g_t2gen_v018_followup[i] : 0; }
unsigned long t2gen_v018_exit_count(unsigned int i)
{ return i < 3 ? g_t2gen_v018_exit[i] : 0; }
#endif
#ifdef T2GEN_V017_NATIVE_SYNC_RTS
static unsigned long g_t2gen_v017_rts_count[3];
unsigned long t2gen_v017_rts_count(unsigned int i)
{ return i < 3 ? g_t2gen_v017_rts_count[i] : 0; }
#endif
#ifdef T2GEN_V025_NATIVE_MOVEQ
/* All 68000 MOVEQ D0..D7 immediate forms; CCR X is preserved. */
static unsigned long g_t2gen_v025_moveq_count;
static unsigned long g_t2gen_v025_moveq_negative;
static unsigned long g_t2gen_v025_moveq_zero;
unsigned long t2gen_v025_moveq_count(void) { return g_t2gen_v025_moveq_count; }
unsigned long t2gen_v025_moveq_negative(void) { return g_t2gen_v025_moveq_negative; }
unsigned long t2gen_v025_moveq_zero(void) { return g_t2gen_v025_moveq_zero; }
#endif

#ifdef T2GEN_V024_NATIVE_DBF
/* 68000 DBF (DBRA), condition always false.  Counts are diagnostic only. */
static unsigned long g_t2gen_v024_dbf_count;
static unsigned long g_t2gen_v024_dbf_taken;
static unsigned long g_t2gen_v024_dbf_expired;
unsigned long t2gen_v024_dbf_count(void) { return g_t2gen_v024_dbf_count; }
unsigned long t2gen_v024_dbf_taken(void) { return g_t2gen_v024_dbf_taken; }
unsigned long t2gen_v024_dbf_expired(void) { return g_t2gen_v024_dbf_expired; }
#endif

#ifdef T2GEN_V023_NATIVE_5670
static unsigned long g_t2gen_v023_tst;
static unsigned long g_t2gen_v023_beq;
static unsigned long g_t2gen_v023_beq_taken;
static unsigned long g_t2gen_v023_fallback[2];
unsigned long t2gen_v023_tst_count(void) { return g_t2gen_v023_tst; }
unsigned long t2gen_v023_beq_count(void) { return g_t2gen_v023_beq; }
unsigned long t2gen_v023_beq_taken(void) { return g_t2gen_v023_beq_taken; }
unsigned long t2gen_v023_fallback(unsigned int i)
{ return i < 2u ? g_t2gen_v023_fallback[i] : 0; }
#endif
#ifdef T2GEN_V020_DIRECT_BRANCH
static unsigned long g_t2gen_v020_direct[3];
static unsigned long g_t2gen_v020_fallback[3];
unsigned long t2gen_v020_direct_count(unsigned int i)
{ return i < 3 ? g_t2gen_v020_direct[i] : 0; }
unsigned long t2gen_v020_fallback_count(unsigned int i)
{ return i < 3 ? g_t2gen_v020_fallback[i] : 0; }
#endif
#ifdef T2GEN_V019_PREDECODED_SYNC
static unsigned long g_t2gen_v019_fast[3];
static unsigned long g_t2gen_v019_fallback[3];
unsigned long t2gen_v019_fast_count(unsigned int i)
{ return i < 3 ? g_t2gen_v019_fast[i] : 0; }
unsigned long t2gen_v019_fallback_count(unsigned int i)
{ return i < 3 ? g_t2gen_v019_fallback[i] : 0; }
#endif
static unsigned long g_t2gen_v012_branch_count[3];
static unsigned long g_t2gen_v012_branch_taken[3];
unsigned long t2gen_v012_branch_count(unsigned int i)
{
  return i < 3 ? g_t2gen_v012_branch_count[i] : 0;
}
unsigned long t2gen_v012_branch_taken(unsigned int i)
{
  return i < 3 ? g_t2gen_v012_branch_taken[i] : 0;
}
#endif
static unsigned long g_t2gen_v010_native_cmp_count;
#ifdef T2GEN_V011_NATIVE_SYNC_EXEC
static unsigned long g_t2gen_v011_cmp_d0_count;
static unsigned long g_t2gen_v011_tst_count;
unsigned long t2gen_v011_native_cmp_d0_count(void) { return g_t2gen_v011_cmp_d0_count; }
unsigned long t2gen_v011_native_tst_count(void) { return g_t2gen_v011_tst_count; }
#endif
unsigned long t2gen_v010_native_cmp_count(void)
{
  return g_t2gen_v010_native_cmp_count;
}
#endif


// #include "m68kfpu.c"
// #include "m68kmmu.h" // uses some functions from m68kfpu.c which are static !

#include "m68kops.h"
#include "m68kcpu.h"

/*
 * NuttX ARM headers redefine M68KI_REG_PC, M68KI_REG_SP and M68KI_REG_FP
 * as Cortex-M register numbers.
 *
 * Restore Musashi's Motorola 68000 register aliases.
 */

#undef M68KI_REG_PC
#undef M68KI_REG_SP
#undef M68KI_REG_FP

#define M68KI_REG_PC  m68ki_cpu.pc
#define M68KI_REG_SP  m68ki_cpu.dar[15]
#define M68KI_REG_FP  m68ki_cpu.fpr

#include "m68kfpu.c"
#include "m68kmmu.h"

/* ======================================================================== */
/* ================================= DATA ================================= */
/* ======================================================================== */

int  m68ki_initial_cycles;
int  m68ki_remaining_cycles = 0;                     /* Number of clocks remaining */
uint m68ki_tracing = 0;
uint m68ki_address_space;

#ifdef M68K_LOG_ENABLE
const char *const m68ki_cpu_names[] =
{
	"Invalid CPU",
	"M68000",
	"M68010",
	"M68EC020",
	"M68020",
	"M68EC030",
	"M68030",
	"M68EC040",
	"M68LC040",
	"M68040",
	"SCC68070",
};
#endif /* M68K_LOG_ENABLE */

/* The CPU core */
m68ki_cpu_core m68ki_cpu = {0};

#if M68K_EMULATE_ADDRESS_ERROR
#ifdef _BSD_SETJMP_H
sigjmp_buf m68ki_aerr_trap;
#else
jmp_buf m68ki_aerr_trap;
#endif
#endif /* M68K_EMULATE_ADDRESS_ERROR */

uint    m68ki_aerr_address;
uint    m68ki_aerr_write_mode;
uint    m68ki_aerr_fc;

jmp_buf m68ki_bus_error_jmp_buf;

/* Used by shift & rotate instructions */
const uint8 m68ki_shift_8_table[65] =
{
	0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff
};
const uint16 m68ki_shift_16_table[65] =
{
	0x0000, 0x8000, 0xc000, 0xe000, 0xf000, 0xf800, 0xfc00, 0xfe00, 0xff00,
	0xff80, 0xffc0, 0xffe0, 0xfff0, 0xfff8, 0xfffc, 0xfffe, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff
};
const uint m68ki_shift_32_table[65] =
{
	0x00000000, 0x80000000, 0xc0000000, 0xe0000000, 0xf0000000, 0xf8000000,
	0xfc000000, 0xfe000000, 0xff000000, 0xff800000, 0xffc00000, 0xffe00000,
	0xfff00000, 0xfff80000, 0xfffc0000, 0xfffe0000, 0xffff0000, 0xffff8000,
	0xffffc000, 0xffffe000, 0xfffff000, 0xfffff800, 0xfffffc00, 0xfffffe00,
	0xffffff00, 0xffffff80, 0xffffffc0, 0xffffffe0, 0xfffffff0, 0xfffffff8,
	0xfffffffc, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
	0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
	0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
	0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
	0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
	0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
};


/* Number of clock cycles to use for exception processing.
 * I used 4 for any vectors that are undocumented for processing times.
 */
const uint8 m68ki_exception_cycle_table[5][256] =
{
	{ /* 000 */
		 40, /*  0: Reset - Initial Stack Pointer                      */
		  4, /*  1: Reset - Initial Program Counter                    */
		 50, /*  2: Bus Error                             (unemulated) */
		 50, /*  3: Address Error                         (unemulated) */
		 34, /*  4: Illegal Instruction                                */
		 38, /*  5: Divide by Zero                                     */
		 40, /*  6: CHK                                                */
		 34, /*  7: TRAPV                                              */
		 34, /*  8: Privilege Violation                                */
		 34, /*  9: Trace                                              */
		 34, /* 10: 1010                                               */
		 34, /* 11: 1111                                               */
		  4, /* 12: RESERVED                                           */
		  4, /* 13: Coprocessor Protocol Violation        (unemulated) */
		  4, /* 14: Format Error                                       */
		 44, /* 15: Uninitialized Interrupt                            */
		  4, /* 16: RESERVED                                           */
		  4, /* 17: RESERVED                                           */
		  4, /* 18: RESERVED                                           */
		  4, /* 19: RESERVED                                           */
		  4, /* 20: RESERVED                                           */
		  4, /* 21: RESERVED                                           */
		  4, /* 22: RESERVED                                           */
		  4, /* 23: RESERVED                                           */
		 44, /* 24: Spurious Interrupt                                 */
		 44, /* 25: Level 1 Interrupt Autovector                       */
		 44, /* 26: Level 2 Interrupt Autovector                       */
		 44, /* 27: Level 3 Interrupt Autovector                       */
		 44, /* 28: Level 4 Interrupt Autovector                       */
		 44, /* 29: Level 5 Interrupt Autovector                       */
		 44, /* 30: Level 6 Interrupt Autovector                       */
		 44, /* 31: Level 7 Interrupt Autovector                       */
		 34, /* 32: TRAP #0                                            */
		 34, /* 33: TRAP #1                                            */
		 34, /* 34: TRAP #2                                            */
		 34, /* 35: TRAP #3                                            */
		 34, /* 36: TRAP #4                                            */
		 34, /* 37: TRAP #5                                            */
		 34, /* 38: TRAP #6                                            */
		 34, /* 39: TRAP #7                                            */
		 34, /* 40: TRAP #8                                            */
		 34, /* 41: TRAP #9                                            */
		 34, /* 42: TRAP #10                                           */
		 34, /* 43: TRAP #11                                           */
		 34, /* 44: TRAP #12                                           */
		 34, /* 45: TRAP #13                                           */
		 34, /* 46: TRAP #14                                           */
		 34, /* 47: TRAP #15                                           */
		  4, /* 48: FP Branch or Set on Unknown Condition (unemulated) */
		  4, /* 49: FP Inexact Result                     (unemulated) */
		  4, /* 50: FP Divide by Zero                     (unemulated) */
		  4, /* 51: FP Underflow                          (unemulated) */
		  4, /* 52: FP Operand Error                      (unemulated) */
		  4, /* 53: FP Overflow                           (unemulated) */
		  4, /* 54: FP Signaling NAN                      (unemulated) */
		  4, /* 55: FP Unimplemented Data Type            (unemulated) */
		  4, /* 56: MMU Configuration Error               (unemulated) */
		  4, /* 57: MMU Illegal Operation Error           (unemulated) */
		  4, /* 58: MMU Access Level Violation Error      (unemulated) */
		  4, /* 59: RESERVED                                           */
		  4, /* 60: RESERVED                                           */
		  4, /* 61: RESERVED                                           */
		  4, /* 62: RESERVED                                           */
		  4, /* 63: RESERVED                                           */
		     /* 64-255: User Defined                                   */
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4
	},
	{ /* 010 */
		 40, /*  0: Reset - Initial Stack Pointer                      */
		  4, /*  1: Reset - Initial Program Counter                    */
		126, /*  2: Bus Error                             (unemulated) */
		126, /*  3: Address Error                         (unemulated) */
		 38, /*  4: Illegal Instruction                                */
		 44, /*  5: Divide by Zero                                     */
		 44, /*  6: CHK                                                */
		 34, /*  7: TRAPV                                              */
		 38, /*  8: Privilege Violation                                */
		 38, /*  9: Trace                                              */
		  4, /* 10: 1010                                               */
		  4, /* 11: 1111                                               */
		  4, /* 12: RESERVED                                           */
		  4, /* 13: Coprocessor Protocol Violation        (unemulated) */
		  4, /* 14: Format Error                                       */
		 44, /* 15: Uninitialized Interrupt                            */
		  4, /* 16: RESERVED                                           */
		  4, /* 17: RESERVED                                           */
		  4, /* 18: RESERVED                                           */
		  4, /* 19: RESERVED                                           */
		  4, /* 20: RESERVED                                           */
		  4, /* 21: RESERVED                                           */
		  4, /* 22: RESERVED                                           */
		  4, /* 23: RESERVED                                           */
		 46, /* 24: Spurious Interrupt                                 */
		 46, /* 25: Level 1 Interrupt Autovector                       */
		 46, /* 26: Level 2 Interrupt Autovector                       */
		 46, /* 27: Level 3 Interrupt Autovector                       */
		 46, /* 28: Level 4 Interrupt Autovector                       */
		 46, /* 29: Level 5 Interrupt Autovector                       */
		 46, /* 30: Level 6 Interrupt Autovector                       */
		 46, /* 31: Level 7 Interrupt Autovector                       */
		 38, /* 32: TRAP #0                                            */
		 38, /* 33: TRAP #1                                            */
		 38, /* 34: TRAP #2                                            */
		 38, /* 35: TRAP #3                                            */
		 38, /* 36: TRAP #4                                            */
		 38, /* 37: TRAP #5                                            */
		 38, /* 38: TRAP #6                                            */
		 38, /* 39: TRAP #7                                            */
		 38, /* 40: TRAP #8                                            */
		 38, /* 41: TRAP #9                                            */
		 38, /* 42: TRAP #10                                           */
		 38, /* 43: TRAP #11                                           */
		 38, /* 44: TRAP #12                                           */
		 38, /* 45: TRAP #13                                           */
		 38, /* 46: TRAP #14                                           */
		 38, /* 47: TRAP #15                                           */
		  4, /* 48: FP Branch or Set on Unknown Condition (unemulated) */
		  4, /* 49: FP Inexact Result                     (unemulated) */
		  4, /* 50: FP Divide by Zero                     (unemulated) */
		  4, /* 51: FP Underflow                          (unemulated) */
		  4, /* 52: FP Operand Error                      (unemulated) */
		  4, /* 53: FP Overflow                           (unemulated) */
		  4, /* 54: FP Signaling NAN                      (unemulated) */
		  4, /* 55: FP Unimplemented Data Type            (unemulated) */
		  4, /* 56: MMU Configuration Error               (unemulated) */
		  4, /* 57: MMU Illegal Operation Error           (unemulated) */
		  4, /* 58: MMU Access Level Violation Error      (unemulated) */
		  4, /* 59: RESERVED                                           */
		  4, /* 60: RESERVED                                           */
		  4, /* 61: RESERVED                                           */
		  4, /* 62: RESERVED                                           */
		  4, /* 63: RESERVED                                           */
		     /* 64-255: User Defined                                   */
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4
	},
	{ /* 020 */
		  4, /*  0: Reset - Initial Stack Pointer                      */
		  4, /*  1: Reset - Initial Program Counter                    */
		 50, /*  2: Bus Error                             (unemulated) */
		 50, /*  3: Address Error                         (unemulated) */
		 20, /*  4: Illegal Instruction                                */
		 38, /*  5: Divide by Zero                                     */
		 40, /*  6: CHK                                                */
		 20, /*  7: TRAPV                                              */
		 34, /*  8: Privilege Violation                                */
		 25, /*  9: Trace                                              */
		 20, /* 10: 1010                                               */
		 20, /* 11: 1111                                               */
		  4, /* 12: RESERVED                                           */
		  4, /* 13: Coprocessor Protocol Violation        (unemulated) */
		  4, /* 14: Format Error                                       */
		 30, /* 15: Uninitialized Interrupt                            */
		  4, /* 16: RESERVED                                           */
		  4, /* 17: RESERVED                                           */
		  4, /* 18: RESERVED                                           */
		  4, /* 19: RESERVED                                           */
		  4, /* 20: RESERVED                                           */
		  4, /* 21: RESERVED                                           */
		  4, /* 22: RESERVED                                           */
		  4, /* 23: RESERVED                                           */
		 30, /* 24: Spurious Interrupt                                 */
		 30, /* 25: Level 1 Interrupt Autovector                       */
		 30, /* 26: Level 2 Interrupt Autovector                       */
		 30, /* 27: Level 3 Interrupt Autovector                       */
		 30, /* 28: Level 4 Interrupt Autovector                       */
		 30, /* 29: Level 5 Interrupt Autovector                       */
		 30, /* 30: Level 6 Interrupt Autovector                       */
		 30, /* 31: Level 7 Interrupt Autovector                       */
		 20, /* 32: TRAP #0                                            */
		 20, /* 33: TRAP #1                                            */
		 20, /* 34: TRAP #2                                            */
		 20, /* 35: TRAP #3                                            */
		 20, /* 36: TRAP #4                                            */
		 20, /* 37: TRAP #5                                            */
		 20, /* 38: TRAP #6                                            */
		 20, /* 39: TRAP #7                                            */
		 20, /* 40: TRAP #8                                            */
		 20, /* 41: TRAP #9                                            */
		 20, /* 42: TRAP #10                                           */
		 20, /* 43: TRAP #11                                           */
		 20, /* 44: TRAP #12                                           */
		 20, /* 45: TRAP #13                                           */
		 20, /* 46: TRAP #14                                           */
		 20, /* 47: TRAP #15                                           */
		  4, /* 48: FP Branch or Set on Unknown Condition (unemulated) */
		  4, /* 49: FP Inexact Result                     (unemulated) */
		  4, /* 50: FP Divide by Zero                     (unemulated) */
		  4, /* 51: FP Underflow                          (unemulated) */
		  4, /* 52: FP Operand Error                      (unemulated) */
		  4, /* 53: FP Overflow                           (unemulated) */
		  4, /* 54: FP Signaling NAN                      (unemulated) */
		  4, /* 55: FP Unimplemented Data Type            (unemulated) */
		  4, /* 56: MMU Configuration Error               (unemulated) */
		  4, /* 57: MMU Illegal Operation Error           (unemulated) */
		  4, /* 58: MMU Access Level Violation Error      (unemulated) */
		  4, /* 59: RESERVED                                           */
		  4, /* 60: RESERVED                                           */
		  4, /* 61: RESERVED                                           */
		  4, /* 62: RESERVED                                           */
		  4, /* 63: RESERVED                                           */
		     /* 64-255: User Defined                                   */
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4
	},
	{ /* 030 - not correct */
		  4, /*  0: Reset - Initial Stack Pointer                      */
		  4, /*  1: Reset - Initial Program Counter                    */
		 50, /*  2: Bus Error                             (unemulated) */
		 50, /*  3: Address Error                         (unemulated) */
		 20, /*  4: Illegal Instruction                                */
		 38, /*  5: Divide by Zero                                     */
		 40, /*  6: CHK                                                */
		 20, /*  7: TRAPV                                              */
		 34, /*  8: Privilege Violation                                */
		 25, /*  9: Trace                                              */
		 20, /* 10: 1010                                               */
		 20, /* 11: 1111                                               */
		  4, /* 12: RESERVED                                           */
		  4, /* 13: Coprocessor Protocol Violation        (unemulated) */
		  4, /* 14: Format Error                                       */
		 30, /* 15: Uninitialized Interrupt                            */
		  4, /* 16: RESERVED                                           */
		  4, /* 17: RESERVED                                           */
		  4, /* 18: RESERVED                                           */
		  4, /* 19: RESERVED                                           */
		  4, /* 20: RESERVED                                           */
		  4, /* 21: RESERVED                                           */
		  4, /* 22: RESERVED                                           */
		  4, /* 23: RESERVED                                           */
		 30, /* 24: Spurious Interrupt                                 */
		 30, /* 25: Level 1 Interrupt Autovector                       */
		 30, /* 26: Level 2 Interrupt Autovector                       */
		 30, /* 27: Level 3 Interrupt Autovector                       */
		 30, /* 28: Level 4 Interrupt Autovector                       */
		 30, /* 29: Level 5 Interrupt Autovector                       */
		 30, /* 30: Level 6 Interrupt Autovector                       */
		 30, /* 31: Level 7 Interrupt Autovector                       */
		 20, /* 32: TRAP #0                                            */
		 20, /* 33: TRAP #1                                            */
		 20, /* 34: TRAP #2                                            */
		 20, /* 35: TRAP #3                                            */
		 20, /* 36: TRAP #4                                            */
		 20, /* 37: TRAP #5                                            */
		 20, /* 38: TRAP #6                                            */
		 20, /* 39: TRAP #7                                            */
		 20, /* 40: TRAP #8                                            */
		 20, /* 41: TRAP #9                                            */
		 20, /* 42: TRAP #10                                           */
		 20, /* 43: TRAP #11                                           */
		 20, /* 44: TRAP #12                                           */
		 20, /* 45: TRAP #13                                           */
		 20, /* 46: TRAP #14                                           */
		 20, /* 47: TRAP #15                                           */
		  4, /* 48: FP Branch or Set on Unknown Condition (unemulated) */
		  4, /* 49: FP Inexact Result                     (unemulated) */
		  4, /* 50: FP Divide by Zero                     (unemulated) */
		  4, /* 51: FP Underflow                          (unemulated) */
		  4, /* 52: FP Operand Error                      (unemulated) */
		  4, /* 53: FP Overflow                           (unemulated) */
		  4, /* 54: FP Signaling NAN                      (unemulated) */
		  4, /* 55: FP Unimplemented Data Type            (unemulated) */
		  4, /* 56: MMU Configuration Error               (unemulated) */
		  4, /* 57: MMU Illegal Operation Error           (unemulated) */
		  4, /* 58: MMU Access Level Violation Error      (unemulated) */
		  4, /* 59: RESERVED                                           */
		  4, /* 60: RESERVED                                           */
		  4, /* 61: RESERVED                                           */
		  4, /* 62: RESERVED                                           */
		  4, /* 63: RESERVED                                           */
		     /* 64-255: User Defined                                   */
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4
	},
	{ /* 040 */ // TODO: these values are not correct
		  4, /*  0: Reset - Initial Stack Pointer                      */
		  4, /*  1: Reset - Initial Program Counter                    */
		 50, /*  2: Bus Error                             (unemulated) */
		 50, /*  3: Address Error                         (unemulated) */
		 20, /*  4: Illegal Instruction                                */
		 38, /*  5: Divide by Zero                                     */
		 40, /*  6: CHK                                                */
		 20, /*  7: TRAPV                                              */
		 34, /*  8: Privilege Violation                                */
		 25, /*  9: Trace                                              */
		 20, /* 10: 1010                                               */
		 20, /* 11: 1111                                               */
		  4, /* 12: RESERVED                                           */
		  4, /* 13: Coprocessor Protocol Violation        (unemulated) */
		  4, /* 14: Format Error                                       */
		 30, /* 15: Uninitialized Interrupt                            */
		  4, /* 16: RESERVED                                           */
		  4, /* 17: RESERVED                                           */
		  4, /* 18: RESERVED                                           */
		  4, /* 19: RESERVED                                           */
		  4, /* 20: RESERVED                                           */
		  4, /* 21: RESERVED                                           */
		  4, /* 22: RESERVED                                           */
		  4, /* 23: RESERVED                                           */
		 30, /* 24: Spurious Interrupt                                 */
		 30, /* 25: Level 1 Interrupt Autovector                       */
		 30, /* 26: Level 2 Interrupt Autovector                       */
		 30, /* 27: Level 3 Interrupt Autovector                       */
		 30, /* 28: Level 4 Interrupt Autovector                       */
		 30, /* 29: Level 5 Interrupt Autovector                       */
		 30, /* 30: Level 6 Interrupt Autovector                       */
		 30, /* 31: Level 7 Interrupt Autovector                       */
		 20, /* 32: TRAP #0                                            */
		 20, /* 33: TRAP #1                                            */
		 20, /* 34: TRAP #2                                            */
		 20, /* 35: TRAP #3                                            */
		 20, /* 36: TRAP #4                                            */
		 20, /* 37: TRAP #5                                            */
		 20, /* 38: TRAP #6                                            */
		 20, /* 39: TRAP #7                                            */
		 20, /* 40: TRAP #8                                            */
		 20, /* 41: TRAP #9                                            */
		 20, /* 42: TRAP #10                                           */
		 20, /* 43: TRAP #11                                           */
		 20, /* 44: TRAP #12                                           */
		 20, /* 45: TRAP #13                                           */
		 20, /* 46: TRAP #14                                           */
		 20, /* 47: TRAP #15                                           */
		  4, /* 48: FP Branch or Set on Unknown Condition (unemulated) */
		  4, /* 49: FP Inexact Result                     (unemulated) */
		  4, /* 50: FP Divide by Zero                     (unemulated) */
		  4, /* 51: FP Underflow                          (unemulated) */
		  4, /* 52: FP Operand Error                      (unemulated) */
		  4, /* 53: FP Overflow                           (unemulated) */
		  4, /* 54: FP Signaling NAN                      (unemulated) */
		  4, /* 55: FP Unimplemented Data Type            (unemulated) */
		  4, /* 56: MMU Configuration Error               (unemulated) */
		  4, /* 57: MMU Illegal Operation Error           (unemulated) */
		  4, /* 58: MMU Access Level Violation Error      (unemulated) */
		  4, /* 59: RESERVED                                           */
		  4, /* 60: RESERVED                                           */
		  4, /* 61: RESERVED                                           */
		  4, /* 62: RESERVED                                           */
		  4, /* 63: RESERVED                                           */
		     /* 64-255: User Defined                                   */
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4
	}
};

const uint8 m68ki_ea_idx_cycle_table[64] =
{
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0, /* ..01.000 no memory indirect, base NULL             */
	 5, /* ..01..01 memory indirect,    base NULL, outer NULL */
	 7, /* ..01..10 memory indirect,    base NULL, outer 16   */
	 7, /* ..01..11 memory indirect,    base NULL, outer 32   */
	 0,  5,  7,  7,  0,  5,  7,  7,  0,  5,  7,  7,
	 2, /* ..10.000 no memory indirect, base 16               */
	 7, /* ..10..01 memory indirect,    base 16,   outer NULL */
	 9, /* ..10..10 memory indirect,    base 16,   outer 16   */
	 9, /* ..10..11 memory indirect,    base 16,   outer 32   */
	 0,  7,  9,  9,  0,  7,  9,  9,  0,  7,  9,  9,
	 6, /* ..11.000 no memory indirect, base 32               */
	11, /* ..11..01 memory indirect,    base 32,   outer NULL */
	13, /* ..11..10 memory indirect,    base 32,   outer 16   */
	13, /* ..11..11 memory indirect,    base 32,   outer 32   */
	 0, 11, 13, 13,  0, 11, 13, 13,  0, 11, 13, 13
};



/* ======================================================================== */
/* =============================== CALLBACKS ============================== */
/* ======================================================================== */

/* Default callbacks used if the callback hasn't been set yet, or if the
 * callback is set to NULL
 */

/* Interrupt acknowledge */
static int default_int_ack_callback_data;
static int default_int_ack_callback(int int_level)
{
	default_int_ack_callback_data = int_level;
	CPU_INT_LEVEL = 0;
	return M68K_INT_ACK_AUTOVECTOR;
}

/* Breakpoint acknowledge */
static unsigned int default_bkpt_ack_callback_data;
static void default_bkpt_ack_callback(unsigned int data)
{
	default_bkpt_ack_callback_data = data;
}

/* Called when a reset instruction is executed */
static void default_reset_instr_callback(void)
{
}

/* Called when a cmpi.l #v, dn instruction is executed */
static void default_cmpild_instr_callback(unsigned int val, int reg)
{
	(void)val;
	(void)reg;
}

/* Called when a rte instruction is executed */
static void default_rte_instr_callback(void)
{
}

/* Called when a tas instruction is executed */
static int default_tas_instr_callback(void)
{
	return 1; // allow writeback
}

/* Called when an illegal instruction is encountered */
static int default_illg_instr_callback(int opcode)
{
	(void)opcode;
	return 0; // not handled : exception will occur
}

/* Called when a TRAP instruction is encountered */
static int default_trap_instr_callback(int trap)
{
    (void)trap;
    return 0; // not handled : exception will occur
}

/* Called when the program counter changed by a large value */
static unsigned int default_pc_changed_callback_data;
static void default_pc_changed_callback(unsigned int new_pc)
{
	default_pc_changed_callback_data = new_pc;
}

/* Called every time there's bus activity (read/write to/from memory */
static unsigned int default_set_fc_callback_data;
static void default_set_fc_callback(unsigned int new_fc)
{
	default_set_fc_callback_data = new_fc;
}

/* Called every instruction cycle prior to execution */
static void default_instr_hook_callback(unsigned int pc)
{
	(void)pc;
}


#if M68K_EMULATE_ADDRESS_ERROR
	#include <setjmp.h>
	#ifdef _BSD_SETJMP_H
	sigjmp_buf m68ki_aerr_trap;
	#else
	jmp_buf m68ki_aerr_trap;
	#endif
#endif /* M68K_EMULATE_ADDRESS_ERROR */

/* ======================================================================== */
/* ================================= API ================================== */
/* ======================================================================== */

/* Access the internals of the CPU */
unsigned int m68k_get_reg(void* context, m68k_register_t regnum)
{
	m68ki_cpu_core* cpu = context != NULL ?(m68ki_cpu_core*)context : &m68ki_cpu;

	switch(regnum)
	{
		case M68K_REG_D0:	return cpu->dar[0];
		case M68K_REG_D1:	return cpu->dar[1];
		case M68K_REG_D2:	return cpu->dar[2];
		case M68K_REG_D3:	return cpu->dar[3];
		case M68K_REG_D4:	return cpu->dar[4];
		case M68K_REG_D5:	return cpu->dar[5];
		case M68K_REG_D6:	return cpu->dar[6];
		case M68K_REG_D7:	return cpu->dar[7];
		case M68K_REG_A0:	return cpu->dar[8];
		case M68K_REG_A1:	return cpu->dar[9];
		case M68K_REG_A2:	return cpu->dar[10];
		case M68K_REG_A3:	return cpu->dar[11];
		case M68K_REG_A4:	return cpu->dar[12];
		case M68K_REG_A5:	return cpu->dar[13];
		case M68K_REG_A6:	return cpu->dar[14];
		case M68K_REG_A7:	return cpu->dar[15];
		case M68K_REG_PC:	return MASK_OUT_ABOVE_32(cpu->pc);
		case M68K_REG_SR:	return	cpu->t1_flag						|
									cpu->t0_flag						|
									(cpu->s_flag << 11)					|
									(cpu->m_flag << 11)					|
									cpu->int_mask						|
									((cpu->x_flag & XFLAG_SET) >> 4)	|
									((cpu->n_flag & NFLAG_SET) >> 4)	|
									((!cpu->not_z_flag) << 2)			|
									((cpu->v_flag & VFLAG_SET) >> 6)	|
									((cpu->c_flag & CFLAG_SET) >> 8);
		case M68K_REG_SP:	return cpu->dar[15];
		case M68K_REG_USP:	return cpu->s_flag ? cpu->sp[0] : cpu->dar[15];
		case M68K_REG_ISP:	return cpu->s_flag && !cpu->m_flag ? cpu->dar[15] : cpu->sp[4];
		case M68K_REG_MSP:	return cpu->s_flag && cpu->m_flag ? cpu->dar[15] : cpu->sp[6];
		case M68K_REG_SFC:	return cpu->sfc;
		case M68K_REG_DFC:	return cpu->dfc;
		case M68K_REG_VBR:	return cpu->vbr;
		case M68K_REG_CACR:	return cpu->cacr;
		case M68K_REG_CAAR:	return cpu->caar;
		case M68K_REG_PREF_ADDR:	return cpu->pref_addr;
		case M68K_REG_PREF_DATA:	return cpu->pref_data;
		case M68K_REG_PPC:	return MASK_OUT_ABOVE_32(cpu->ppc);
		case M68K_REG_IR:	return cpu->ir;
		case M68K_REG_CPU_TYPE:
			switch(cpu->cpu_type)
			{
				case CPU_TYPE_000:		return (unsigned int)M68K_CPU_TYPE_68000;
				case CPU_TYPE_010:		return (unsigned int)M68K_CPU_TYPE_68010;
				case CPU_TYPE_EC020:	return (unsigned int)M68K_CPU_TYPE_68EC020;
				case CPU_TYPE_020:		return (unsigned int)M68K_CPU_TYPE_68020;
				case CPU_TYPE_040:		return (unsigned int)M68K_CPU_TYPE_68040;
			}
			return M68K_CPU_TYPE_INVALID;
		default:			return 0;
	}
	return 0;
}

void m68k_set_reg(m68k_register_t regnum, unsigned int value)
{
	switch(regnum)
	{
		case M68K_REG_D0:	REG_D[0] = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_D1:	REG_D[1] = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_D2:	REG_D[2] = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_D3:	REG_D[3] = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_D4:	REG_D[4] = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_D5:	REG_D[5] = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_D6:	REG_D[6] = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_D7:	REG_D[7] = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_A0:	REG_A[0] = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_A1:	REG_A[1] = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_A2:	REG_A[2] = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_A3:	REG_A[3] = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_A4:	REG_A[4] = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_A5:	REG_A[5] = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_A6:	REG_A[6] = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_A7:	REG_A[7] = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_PC:	m68ki_jump(MASK_OUT_ABOVE_32(value)); return;
		case M68K_REG_SR:	m68ki_set_sr_noint_nosp(value); return;
		case M68K_REG_SP:	M68KI_REG_SP = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_USP:	if(FLAG_S)
								REG_USP = MASK_OUT_ABOVE_32(value);
							else
								M68KI_REG_SP = MASK_OUT_ABOVE_32(value);
							return;
		case M68K_REG_ISP:	if(FLAG_S && !FLAG_M)
								M68KI_REG_SP = MASK_OUT_ABOVE_32(value);
							else
								REG_ISP = MASK_OUT_ABOVE_32(value);
							return;
		case M68K_REG_MSP:	if(FLAG_S && FLAG_M)
								M68KI_REG_SP = MASK_OUT_ABOVE_32(value);
							else
								REG_MSP = MASK_OUT_ABOVE_32(value);
							return;
		case M68K_REG_VBR:	REG_VBR = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_SFC:	REG_SFC = value & 7; return;
		case M68K_REG_DFC:	REG_DFC = value & 7; return;
		case M68K_REG_CACR:	REG_CACR = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_CAAR:	REG_CAAR = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_PPC:	REG_PPC = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_IR:	REG_IR = MASK_OUT_ABOVE_16(value); return;
		case M68K_REG_CPU_TYPE: m68k_set_cpu_type(value); return;
		default:			return;
	}
}

/* Set the callbacks */
void m68k_set_int_ack_callback(int  (*callback)(int int_level))
{
	CALLBACK_INT_ACK = callback ? callback : default_int_ack_callback;
}

void m68k_set_bkpt_ack_callback(void  (*callback)(unsigned int data))
{
	CALLBACK_BKPT_ACK = callback ? callback : default_bkpt_ack_callback;
}

void m68k_set_reset_instr_callback(void  (*callback)(void))
{
	CALLBACK_RESET_INSTR = callback ? callback : default_reset_instr_callback;
}

void m68k_set_cmpild_instr_callback(void  (*callback)(unsigned int, int))
{
	CALLBACK_CMPILD_INSTR = callback ? callback : default_cmpild_instr_callback;
}

void m68k_set_rte_instr_callback(void  (*callback)(void))
{
	CALLBACK_RTE_INSTR = callback ? callback : default_rte_instr_callback;
}

void m68k_set_tas_instr_callback(int  (*callback)(void))
{
	CALLBACK_TAS_INSTR = callback ? callback : default_tas_instr_callback;
}

void m68k_set_illg_instr_callback(int  (*callback)(int))
{
	CALLBACK_ILLG_INSTR = callback ? callback : default_illg_instr_callback;
}

void m68k_set_trap_instr_callback(int  (*callback)(int))
{
    CALLBACK_TRAP_INSTR = callback ? callback : default_trap_instr_callback;
}

void m68k_set_pc_changed_callback(void  (*callback)(unsigned int new_pc))
{
	CALLBACK_PC_CHANGED = callback ? callback : default_pc_changed_callback;
}

void m68k_set_fc_callback(void  (*callback)(unsigned int new_fc))
{
	CALLBACK_SET_FC = callback ? callback : default_set_fc_callback;
}

void m68k_set_instr_hook_callback(void  (*callback)(unsigned int pc))
{
	CALLBACK_INSTR_HOOK = callback ? callback : default_instr_hook_callback;
}

/* Set the CPU type. */
void m68k_set_cpu_type(unsigned int cpu_type)
{
	switch(cpu_type)
	{
		case M68K_CPU_TYPE_68000:
			CPU_TYPE         = CPU_TYPE_000;
			CPU_ADDRESS_MASK = 0x00ffffff;
			CPU_SR_MASK      = 0xa71f; /* T1 -- S  -- -- I2 I1 I0 -- -- -- X  N  Z  V  C  */
			CYC_INSTRUCTION  = m68ki_cycles[0];
			CYC_EXCEPTION    = m68ki_exception_cycle_table[0];
			CYC_BCC_NOTAKE_B = -2;
			CYC_BCC_NOTAKE_W = 2;
			CYC_DBCC_F_NOEXP = -2;
			CYC_DBCC_F_EXP   = 2;
			CYC_SCC_R_TRUE   = 2;
			CYC_MOVEM_W      = 2;
			CYC_MOVEM_L      = 3;
			CYC_SHIFT        = 1;
			CYC_RESET        = 132;
			HAS_PMMU	 = 0;
			return;
		case M68K_CPU_TYPE_SCC68070:
			m68k_set_cpu_type(M68K_CPU_TYPE_68010);
			CPU_ADDRESS_MASK = 0xffffffff;
			CPU_TYPE         = CPU_TYPE_SCC070;
			return;
		case M68K_CPU_TYPE_68010:
			CPU_TYPE         = CPU_TYPE_010;
			CPU_ADDRESS_MASK = 0x00ffffff;
			CPU_SR_MASK      = 0xa71f; /* T1 -- S  -- -- I2 I1 I0 -- -- -- X  N  Z  V  C  */
			CYC_INSTRUCTION  = m68ki_cycles[1];
			CYC_EXCEPTION    = m68ki_exception_cycle_table[1];
			CYC_BCC_NOTAKE_B = -4;
			CYC_BCC_NOTAKE_W = 0;
			CYC_DBCC_F_NOEXP = 0;
			CYC_DBCC_F_EXP   = 6;
			CYC_SCC_R_TRUE   = 0;
			CYC_MOVEM_W      = 2;
			CYC_MOVEM_L      = 3;
			CYC_SHIFT        = 1;
			CYC_RESET        = 130;
			HAS_PMMU	 = 0;
			return;
		case M68K_CPU_TYPE_68EC020:
			CPU_TYPE         = CPU_TYPE_EC020;
			CPU_ADDRESS_MASK = 0x00ffffff;
			CPU_SR_MASK      = 0xf71f; /* T1 T0 S  M  -- I2 I1 I0 -- -- -- X  N  Z  V  C  */
			CYC_INSTRUCTION  = m68ki_cycles[2];
			CYC_EXCEPTION    = m68ki_exception_cycle_table[2];
			CYC_BCC_NOTAKE_B = -2;
			CYC_BCC_NOTAKE_W = 0;
			CYC_DBCC_F_NOEXP = 0;
			CYC_DBCC_F_EXP   = 4;
			CYC_SCC_R_TRUE   = 0;
			CYC_MOVEM_W      = 2;
			CYC_MOVEM_L      = 2;
			CYC_SHIFT        = 0;
			CYC_RESET        = 518;
			HAS_PMMU	 = 0;
			return;
		case M68K_CPU_TYPE_68020:
			CPU_TYPE         = CPU_TYPE_020;
			CPU_ADDRESS_MASK = 0xffffffff;
			CPU_SR_MASK      = 0xf71f; /* T1 T0 S  M  -- I2 I1 I0 -- -- -- X  N  Z  V  C  */
			CYC_INSTRUCTION  = m68ki_cycles[2];
			CYC_EXCEPTION    = m68ki_exception_cycle_table[2];
			CYC_BCC_NOTAKE_B = -2;
			CYC_BCC_NOTAKE_W = 0;
			CYC_DBCC_F_NOEXP = 0;
			CYC_DBCC_F_EXP   = 4;
			CYC_SCC_R_TRUE   = 0;
			CYC_MOVEM_W      = 2;
			CYC_MOVEM_L      = 2;
			CYC_SHIFT        = 0;
			CYC_RESET        = 518;
			HAS_PMMU	 = 0;
			return;
		case M68K_CPU_TYPE_68030:
			CPU_TYPE         = CPU_TYPE_030;
			CPU_ADDRESS_MASK = 0xffffffff;
			CPU_SR_MASK      = 0xf71f; /* T1 T0 S  M  -- I2 I1 I0 -- -- -- X  N  Z  V  C  */
			CYC_INSTRUCTION  = m68ki_cycles[3];
			CYC_EXCEPTION    = m68ki_exception_cycle_table[3];
			CYC_BCC_NOTAKE_B = -2;
			CYC_BCC_NOTAKE_W = 0;
			CYC_DBCC_F_NOEXP = 0;
			CYC_DBCC_F_EXP   = 4;
			CYC_SCC_R_TRUE   = 0;
			CYC_MOVEM_W      = 2;
			CYC_MOVEM_L      = 2;
			CYC_SHIFT        = 0;
			CYC_RESET        = 518;
			HAS_PMMU	       = 1;
			return;
		case M68K_CPU_TYPE_68EC030:
			CPU_TYPE         = CPU_TYPE_EC030;
			CPU_ADDRESS_MASK = 0xffffffff;
			CPU_SR_MASK          = 0xf71f; /* T1 T0 S  M  -- I2 I1 I0 -- -- -- X  N  Z  V  C  */
			CYC_INSTRUCTION  = m68ki_cycles[3];
			CYC_EXCEPTION    = m68ki_exception_cycle_table[3];
			CYC_BCC_NOTAKE_B = -2;
			CYC_BCC_NOTAKE_W = 0;
			CYC_DBCC_F_NOEXP = 0;
			CYC_DBCC_F_EXP   = 4;
			CYC_SCC_R_TRUE   = 0;
			CYC_MOVEM_W      = 2;
			CYC_MOVEM_L      = 2;
			CYC_SHIFT        = 0;
			CYC_RESET        = 518;
			HAS_PMMU	       = 0;		/* EC030 lacks the PMMU and is effectively a die-shrink 68020 */
			return;
		case M68K_CPU_TYPE_68040:		// TODO: these values are not correct
			CPU_TYPE         = CPU_TYPE_040;
			CPU_ADDRESS_MASK = 0xffffffff;
			CPU_SR_MASK      = 0xf71f; /* T1 T0 S  M  -- I2 I1 I0 -- -- -- X  N  Z  V  C  */
			CYC_INSTRUCTION  = m68ki_cycles[4];
			CYC_EXCEPTION    = m68ki_exception_cycle_table[4];
			CYC_BCC_NOTAKE_B = -2;
			CYC_BCC_NOTAKE_W = 0;
			CYC_DBCC_F_NOEXP = 0;
			CYC_DBCC_F_EXP   = 4;
			CYC_SCC_R_TRUE   = 0;
			CYC_MOVEM_W      = 2;
			CYC_MOVEM_L      = 2;
			CYC_SHIFT        = 0;
			CYC_RESET        = 518;
			HAS_PMMU	 = 1;
			return;
		case M68K_CPU_TYPE_68EC040: // Just a 68040 without pmmu apparently...
			CPU_TYPE         = CPU_TYPE_EC040;
			CPU_ADDRESS_MASK = 0xffffffff;
			CPU_SR_MASK      = 0xf71f; /* T1 T0 S  M  -- I2 I1 I0 -- -- -- X  N  Z  V  C  */
			CYC_INSTRUCTION  = m68ki_cycles[4];
			CYC_EXCEPTION    = m68ki_exception_cycle_table[4];
			CYC_BCC_NOTAKE_B = -2;
			CYC_BCC_NOTAKE_W = 0;
			CYC_DBCC_F_NOEXP = 0;
			CYC_DBCC_F_EXP   = 4;
			CYC_SCC_R_TRUE   = 0;
			CYC_MOVEM_W      = 2;
			CYC_MOVEM_L      = 2;
			CYC_SHIFT        = 0;
			CYC_RESET        = 518;
			HAS_PMMU	 = 0;
			return;
		case M68K_CPU_TYPE_68LC040:
			CPU_TYPE         = CPU_TYPE_LC040;
			m68ki_cpu.sr_mask          = 0xf71f; /* T1 T0 S  M  -- I2 I1 I0 -- -- -- X  N  Z  V  C  */
			m68ki_cpu.cyc_instruction  = m68ki_cycles[4];
			m68ki_cpu.cyc_exception    = m68ki_exception_cycle_table[4];
			m68ki_cpu.cyc_bcc_notake_b = -2;
			m68ki_cpu.cyc_bcc_notake_w = 0;
			m68ki_cpu.cyc_dbcc_f_noexp = 0;
			m68ki_cpu.cyc_dbcc_f_exp   = 4;
			m68ki_cpu.cyc_scc_r_true   = 0;
			m68ki_cpu.cyc_movem_w      = 2;
			m68ki_cpu.cyc_movem_l      = 2;
			m68ki_cpu.cyc_shift        = 0;
			m68ki_cpu.cyc_reset        = 518;
			HAS_PMMU	       = 1;
			return;
	}
}

#ifdef T2GEN_V021_OPCODE_PROFILE
/* Fixed-capacity opcode histogram: 2048 slots x 8 bytes = 16 KiB.
 * No allocation, no IO, no timing changes. Profiling is opt-in and adds
 * substantial overhead; compare performance with this option OFF.
 * The first opcode of a slot is stored with an explicit occupied bit so
 * opcode 0x0000 is counted correctly. Linear probing resolves collisions. */
#define T2GEN_V021_SLOTS 2048u
static struct { unsigned long count; unsigned short opcode; unsigned short used; }
    g_t2gen_v021_hist[T2GEN_V021_SLOTS];
static unsigned long g_t2gen_v021_groups[16];
static unsigned long g_t2gen_v021_total;
static unsigned long g_t2gen_v021_overflow;
static void t2gen_v021_record(unsigned int opcode)
{
    unsigned int slot = (opcode * 40503u) & (T2GEN_V021_SLOTS - 1u);
    unsigned int n;
    g_t2gen_v021_total++;
    g_t2gen_v021_groups[(opcode >> 12) & 15u]++;
    for (n = 0; n < T2GEN_V021_SLOTS; n++)
    {
        if (!g_t2gen_v021_hist[slot].used)
        {
            g_t2gen_v021_hist[slot].used = 1;
            g_t2gen_v021_hist[slot].opcode = (unsigned short)opcode;
            g_t2gen_v021_hist[slot].count = 1;
            return;
        }
        if (g_t2gen_v021_hist[slot].opcode == opcode)
        {
            g_t2gen_v021_hist[slot].count++;
            return;
        }
        slot = (slot + 1u) & (T2GEN_V021_SLOTS - 1u);
    }
    g_t2gen_v021_overflow++;
}
unsigned long t2gen_v021_total(void) { return g_t2gen_v021_total; }
unsigned long t2gen_v021_overflow(void) { return g_t2gen_v021_overflow; }
unsigned long t2gen_v021_group(unsigned int i)
{ return i < 16u ? g_t2gen_v021_groups[i] : 0; }
/* Rank without sorting or changing the histogram. Report 24 hot opcodes. */
unsigned int t2gen_v021_top(unsigned int rank, unsigned int *opcode,
                           unsigned long *count)
{
    unsigned long ceiling = ~0ul;
    unsigned int ceiling_opcode = 0x10000u;
    unsigned int r, i, found = 0;
    for (r = 0; r <= rank; r++)
    {
        unsigned long best = 0;
        unsigned int best_opcode = 0x10000u;
        for (i = 0; i < T2GEN_V021_SLOTS; i++)
        {
            unsigned long c = g_t2gen_v021_hist[i].count;
            unsigned int op = g_t2gen_v021_hist[i].opcode;
            if (!g_t2gen_v021_hist[i].used ||
                c > ceiling || (c == ceiling && op >= ceiling_opcode))
                continue;
            if (c > best || (c == best && op < best_opcode))
            { best = c; best_opcode = op; }
        }
        if (best_opcode == 0x10000u) return 0;
        ceiling = best;
        ceiling_opcode = best_opcode;
        found = 1;
    }
    if (found) { *opcode = ceiling_opcode; *count = ceiling; }
    return found;
}
#endif /* T2GEN_V021_OPCODE_PROFILE */

#ifdef T2GEN_V022_PC_PROFILE
/* Profile only four high-frequency opcode forms. PC is the address of the
 * instruction just fetched, not the post-fetch PC. This is a diagnostic,
 * never part of instruction execution or cycle accounting. */
#define T2GEN_V022_SLOTS 4096u
static struct { unsigned long pc, count; unsigned short opcode, used; }
    g_t2gen_v022_hist[T2GEN_V022_SLOTS];
static unsigned long g_t2gen_v022_total, g_t2gen_v022_overflow;
static unsigned long g_t2gen_v022_opcode_total[4];
static void t2gen_v022_record(unsigned long pc, unsigned int op)
{
    unsigned int kind, slot, n;
    switch (op)
    {
      case 0x4a79: kind = 0; break;
      case 0x67f8: kind = 1; break;
      case 0x51c8: kind = 2; break;
      case 0x51cf: kind = 3; break;
      default: return;
    }
    g_t2gen_v022_total++;
    g_t2gen_v022_opcode_total[kind]++;
    slot = ((unsigned int)(pc >> 1) * 2654435761u) & (T2GEN_V022_SLOTS - 1u);
    for (n = 0; n < T2GEN_V022_SLOTS; n++)
    {
        if (!g_t2gen_v022_hist[slot].used)
        {
            g_t2gen_v022_hist[slot].used = 1;
            g_t2gen_v022_hist[slot].pc = pc;
            g_t2gen_v022_hist[slot].opcode = (unsigned short)op;
            g_t2gen_v022_hist[slot].count = 1;
            return;
        }
        if (g_t2gen_v022_hist[slot].pc == pc &&
            g_t2gen_v022_hist[slot].opcode == op)
        {
            g_t2gen_v022_hist[slot].count++;
            return;
        }
        slot = (slot + 1u) & (T2GEN_V022_SLOTS - 1u);
    }
    g_t2gen_v022_overflow++;
}
unsigned long t2gen_v022_total(void) { return g_t2gen_v022_total; }
unsigned long t2gen_v022_overflow(void) { return g_t2gen_v022_overflow; }
unsigned long t2gen_v022_opcode_count(unsigned int kind)
{ return kind < 4u ? g_t2gen_v022_opcode_total[kind] : 0; }
/* Deterministic descending count, ascending PC and opcode tie-break. */
unsigned int t2gen_v022_top(unsigned int rank, unsigned long *pc,
                           unsigned int *opcode, unsigned long *count)
{
    unsigned long ceiling = ~0ul, ceiling_pc = ~0ul;
    unsigned int ceiling_op = 0x10000u, r, i;
    for (r = 0; r <= rank; r++)
    {
        unsigned long best = 0, best_pc = ~0ul;
        unsigned int best_op = 0x10000u;
        for (i = 0; i < T2GEN_V022_SLOTS; i++)
        {
            unsigned long c = g_t2gen_v022_hist[i].count;
            unsigned long a = g_t2gen_v022_hist[i].pc;
            unsigned int op = g_t2gen_v022_hist[i].opcode;
            if (!g_t2gen_v022_hist[i].used ||
                c > ceiling ||
                (c == ceiling && (a < ceiling_pc ||
                 (a == ceiling_pc && op <= ceiling_op)))) continue;
            if (c > best || (c == best &&
                (a < best_pc || (a == best_pc && op < best_op))))
            { best = c; best_pc = a; best_op = op; }
        }
        if (best_op == 0x10000u) return 0;
        ceiling = best; ceiling_pc = best_pc; ceiling_op = best_op;
    }
    *pc = ceiling_pc; *opcode = ceiling_op; *count = ceiling;
    return 1;
}
#endif /* T2GEN_V022_PC_PROFILE */

/* Execute some instructions until we use up num_cycles clock cycles */
/* ASG: removed per-instruction interrupt checks */
int m68k_execute(int num_cycles)
{
	/* eat up any reset cycles */
	if (RESET_CYCLES) {
	    int rc = RESET_CYCLES;
	    RESET_CYCLES = 0;
	    num_cycles -= rc;
	    if (num_cycles <= 0)
		return rc;
	}

	/* Set our pool of clock cycles available */
	SET_CYCLES(num_cycles);
	m68ki_initial_cycles = num_cycles;

	/* See if interrupts came in */
	m68ki_check_interrupts();

	/* Make sure we're not stopped */
	if(!CPU_STOPPED)
	{
		/* Return point if we had an address error */
		m68ki_set_address_error_trap(); /* auto-disable (see m68kcpu.h) */

		m68ki_check_bus_error_trap();

		/* Main loop.  Keep going until we run out of clock cycles */
		do
		{
			int i;
#ifdef T2GEN_V018_ROUTINE_DISPATCH
            /* A continuation uses this same instruction prologue and
             * cycle/trace epilogue, not an atomic busy-wait shortcut. */
            int t2n_v018_continuation = 0;
            unsigned int t2n_v018_which = 0;
t2n_v018_next_instruction:
#endif
			/* Set tracing accodring to T1. (T0 is done inside instruction) */
			m68ki_trace_t1(); /* auto-disable (see m68kcpu.h) */

			/* Set the address space for reads */
			m68ki_use_data_space(); /* auto-disable (see m68kcpu.h) */

			/* Call external hook to peek at CPU */
			m68ki_instr_hook(M68KI_REG_PC); /* auto-disable (see m68kcpu.h) */

			/* Record previous program counter */
			REG_PPC = M68KI_REG_PC;

			/* Record previous D/A register state (in case of bus error) */
			for (i = 15; i >= 0; i--){
				REG_DA_SAVE[i] = REG_DA[i];
			}

			/* Read an instruction and call its handler */
			REG_IR = m68ki_read_imm_16();
#ifdef T2GEN_V021_OPCODE_PROFILE
            t2gen_v021_record(REG_IR);
#endif
#ifdef T2GEN_V022_PC_PROFILE
            t2gen_v022_record(REG_PPC, REG_IR);
#endif
#ifdef T2GEN_V016_SWITCH_DISPATCH
            /* One PPC switch, with exact opcode and operand validation.
             * All other cases execute the original Musashi handler. */
            {
                int native_done = 0;
#ifdef T2GEN_V019_PREDECODED_SYNC
                /* ROM-specific predecoded branch entry points.  No
                 * speculative instruction execution: the opcode was just
                 * fetched normally, and is checked before execution.
                 * The standard per-instruction prologue and epilogue run.
                 * A changed opcode falls through to Musashi's dispatcher. */
                unsigned int fast_which;
                unsigned int fast_expected;
                if (REG_PPC == 0x0000a134u)
                    fast_which = 0u;
                else if (REG_PPC == 0x00006126u)
                    fast_which = 1u;
                else if (REG_PPC == 0x0000a0eau)
                    fast_which = 2u;
                else
                    fast_which = 3u;
                if (fast_which < 3u)
                {
                    fast_expected = fast_which == 2u ? 0x66f8u : 0x67f8u;
                    if (REG_IR == fast_expected)
                    {
                        int taken = fast_which == 2u ? COND_NE() : COND_EQ();
                        g_t2gen_v019_fast[fast_which]++;
                        g_t2gen_v012_branch_count[fast_which]++;
                        if (taken)
                        {
                            g_t2gen_v012_branch_taken[fast_which]++;
                            m68ki_trace_t0();
                            m68ki_branch_8(MASK_OUT_ABOVE_8(REG_IR));
                        }
                        else
                            USE_CYCLES(CYC_BCC_NOTAKE_B);
                        native_done = 1;
                    }
                    else
                        g_t2gen_v019_fallback[fast_which]++;
                }
#endif
#ifdef T2GEN_V018_ROUTINE_DISPATCH
                /* The immediately following branch/RTS is dispatched
                 * directly. Still validate the actual fetched opcode. */
                if (t2n_v018_continuation)
                {
                    if (REG_PPC == 0x0000a134u || REG_PPC == 0x00006126u ||
                        REG_PPC == 0x0000a0eau)
                    {
                        unsigned int expected = t2n_v018_which == 2u ? 0x66f8u : 0x67f8u;
                        if (REG_IR == expected)
                        {
                            int taken = t2n_v018_which == 2u ? COND_NE() : COND_EQ();
                            g_t2gen_v012_branch_count[t2n_v018_which]++;
                            if (taken)
                            {
                                g_t2gen_v012_branch_taken[t2n_v018_which]++;
                                m68ki_trace_t0();
                                m68ki_branch_8(MASK_OUT_ABOVE_8(REG_IR));
                            }
                            else
                                USE_CYCLES(CYC_BCC_NOTAKE_B);
                            native_done = 1;
                        }
                    }
#ifdef T2GEN_V017_NATIVE_SYNC_RTS
                    else if (REG_IR == 0x4e75u &&
                             (REG_PPC == 0x0000a136u || REG_PPC == 0x00006128u ||
                              REG_PPC == 0x0000a0ecu))
                    {
                        m68ki_trace_t0();
                        m68ki_jump(m68ki_pull_32());
                        g_t2gen_v017_rts_count[t2n_v018_which]++;
                        native_done = 1;
                    }
#endif
                    if (!native_done)
                        g_t2gen_v018_exit[t2n_v018_which]++;
                }
                if (!native_done)
#endif
#ifdef T2GEN_V025_NATIVE_MOVEQ
                /* Opcode table mask matches Musashi's MOVEQ entry exactly.
                 * Do not touch X; preserve Musashi's internal Z convention
                 * (FLAG_Z holds the actual result, zero means Z set).
                 * CYC_INSTRUCTION[REG_IR] remains charged by outer loop. */
                if (!native_done && (REG_IR & 0xf100u) == 0x7000u)
                {
                    uint res = MAKE_INT_8(MASK_OUT_ABOVE_8(REG_IR));
                    REG_D[(REG_IR >> 9) & 7u] = res;
                    FLAG_N = NFLAG_32(res);
                    FLAG_Z = res;
                    FLAG_V = VFLAG_CLEAR;
                    FLAG_C = CFLAG_CLEAR;
                    g_t2gen_v025_moveq_count++;
                    if (res & 0x80000000u) g_t2gen_v025_moveq_negative++;
                    if (res == 0u) g_t2gen_v025_moveq_zero++;
                    native_done = 1;
                }
#endif
                if (!native_done)
#ifdef T2GEN_V024_NATIVE_DBF
                /* DBF Dn,<disp16>: all eight D registers, original 68000
                 * semantics, no CCR modifications.  The extension word is
                 * fetched ONLY on the taken path, matching Musashi exactly.
                 * Keep one instruction per outer dispatch iteration so
                 * tracing, interrupts and cycle accounting are unchanged. */
                if (!native_done && (REG_IR & 0xfff8u) == 0x51c8u)
                {
                    uint *r_dst = &REG_D[REG_IR & 7u];
                    uint res = MASK_OUT_ABOVE_16(*r_dst - 1u);
                    *r_dst = MASK_OUT_BELOW_16(*r_dst) | res;
                    g_t2gen_v024_dbf_count++;
                    if (res != 0xffffu)
                    {
                        uint offset = m68ki_read_imm_16();
                        M68KI_REG_PC -= 2u;
                        m68ki_trace_t0();
                        m68ki_branch_16(offset);
                        USE_CYCLES(CYC_DBCC_F_NOEXP);
                        g_t2gen_v024_dbf_taken++;
                    }
                    else
                    {
                        M68KI_REG_PC += 2u;
                        USE_CYCLES(CYC_DBCC_F_EXP);
                        g_t2gen_v024_dbf_expired++;
                    }
                    native_done = 1;
                }
#endif
                if (!native_done)
                switch (REG_PPC)
                {
#ifdef T2GEN_V023_NATIVE_5670
                case 0x00005670u:
                    if (REG_IR == 0x4a79u)
                    {
                        uint addr = m68ki_read_imm_32();
                        if (addr == 0x00ff03b0u)
                        {
                            uint16_t w = (uint16_t)m68ki_read_16(addr);
                            struct t2n_sync_result r = t2n_tst_word(w, m68ki_get_sr());
                            m68ki_set_ccr(r.ccr);
                            g_t2gen_v023_tst++;
                        }
                        else
                        {
                            /* The extension words have already been consumed.
                             * Match existing native dispatch mismatch policy. */
                            REG_IR = 0x4afcu;
                            m68ki_instruction_jump_table[REG_IR]();
                            g_t2gen_v023_fallback[0]++;
                        }
                        native_done = 1;
                    }
                    else g_t2gen_v023_fallback[0]++;
                    break;
                case 0x00005676u:
                    if (REG_IR == 0x67f8u)
                    {
                        g_t2gen_v023_beq++;
                        if (COND_EQ())
                        {
                            g_t2gen_v023_beq_taken++;
                            m68ki_trace_t0();
                            m68ki_branch_8(0xf8u);
                        }
                        else USE_CYCLES(CYC_BCC_NOTAKE_B);
                        native_done = 1;
                    }
                    else g_t2gen_v023_fallback[1]++;
                    break;
#endif
                case 0x0000a12eu:
                    if (REG_IR == 0xb279u)
                    {
                        uint addr = m68ki_read_imm_32();
                        if (addr == 0x00ff03b0u)
                        {
                            uint16_t w = (uint16_t)m68ki_read_16(addr);
                            struct t2n_sync_result r = t2n_cmp_word(REG_D[1], w, m68ki_get_sr());
                            m68ki_set_ccr(r.ccr);
                            g_t2gen_v010_native_cmp_count++;
                        }
                        else
                        {
                            REG_IR = 0x4afcu;
                            m68ki_instruction_jump_table[REG_IR]();
                        }
                        native_done = 1;
                    }
                    break;
                case 0x00006120u:
                    if (REG_IR == 0xb079u)
                    {
                        uint addr = m68ki_read_imm_32();
                        if (addr == 0x00ff03b0u)
                        {
                            uint16_t w = (uint16_t)m68ki_read_16(addr);
                            struct t2n_sync_result r = t2n_cmp_word(REG_D[0], w, m68ki_get_sr());
                            m68ki_set_ccr(r.ccr);
                            g_t2gen_v011_cmp_d0_count++;
                        }
                        else
                        {
                            REG_IR = 0x4afcu;
                            m68ki_instruction_jump_table[REG_IR]();
                        }
                        native_done = 1;
                    }
                    break;
                case 0x0000a0e4u:
                    if (REG_IR == 0x4a79u)
                    {
                        uint addr = m68ki_read_imm_32();
                        if (addr == 0x00ff0222u)
                        {
                            uint16_t w = (uint16_t)m68ki_read_16(addr);
                            struct t2n_sync_result r = t2n_tst_word(w, m68ki_get_sr());
                            m68ki_set_ccr(r.ccr);
                            g_t2gen_v011_tst_count++;
                        }
                        else
                        {
                            REG_IR = 0x4afcu;
                            m68ki_instruction_jump_table[REG_IR]();
                        }
                        native_done = 1;
                    }
                    break;
#ifdef T2GEN_V020_DIRECT_BRANCH
                /* V0.20: direct, site-specific branch handlers.
                 * No second PPC classification or which-index computation.
                 * Fallback is the original Musashi jump-table dispatch. */
                case 0x0000a134u:
                    if (REG_IR == 0x67f8u)
                    {
                        g_t2gen_v020_direct[0]++;
                        g_t2gen_v012_branch_count[0]++;
                        if (COND_EQ())
                        {
                            g_t2gen_v012_branch_taken[0]++;
                            m68ki_trace_t0();
                            m68ki_branch_8(0xf8u);
                        }
                        else USE_CYCLES(CYC_BCC_NOTAKE_B);
                        native_done = 1;
                    }
                    else g_t2gen_v020_fallback[0]++;
                    break;
                case 0x00006126u:
                    if (REG_IR == 0x67f8u)
                    {
                        g_t2gen_v020_direct[1]++;
                        g_t2gen_v012_branch_count[1]++;
                        if (COND_EQ())
                        {
                            g_t2gen_v012_branch_taken[1]++;
                            m68ki_trace_t0();
                            m68ki_branch_8(0xf8u);
                        }
                        else USE_CYCLES(CYC_BCC_NOTAKE_B);
                        native_done = 1;
                    }
                    else g_t2gen_v020_fallback[1]++;
                    break;
                case 0x0000a0eau:
                    if (REG_IR == 0x66f8u)
                    {
                        g_t2gen_v020_direct[2]++;
                        g_t2gen_v012_branch_count[2]++;
                        if (COND_NE())
                        {
                            g_t2gen_v012_branch_taken[2]++;
                            m68ki_trace_t0();
                            m68ki_branch_8(0xf8u);
                        }
                        else USE_CYCLES(CYC_BCC_NOTAKE_B);
                        native_done = 1;
                    }
                    else g_t2gen_v020_fallback[2]++;
                    break;
#else
                case 0x0000a134u:
                case 0x00006126u:
                case 0x0000a0eau:
                    {
                        unsigned int which = REG_PPC == 0x0000a134u ? 0u :
                                             REG_PPC == 0x00006126u ? 1u : 2u;
                        unsigned int expected = which == 2u ? 0x66f8u : 0x67f8u;
                        if (REG_IR == expected)
                        {
                            int taken = which == 2u ? COND_NE() : COND_EQ();
                            g_t2gen_v012_branch_count[which]++;
                            if (taken)
                            {
                                g_t2gen_v012_branch_taken[which]++;
                                m68ki_trace_t0();
                                m68ki_branch_8(MASK_OUT_ABOVE_8(REG_IR));
                            }
                            else
                            {
                                USE_CYCLES(CYC_BCC_NOTAKE_B);
                            }
                            native_done = 1;
                        }
                    }
                    break;
#endif /* T2GEN_V020_DIRECT_BRANCH */
#ifdef T2GEN_V017_NATIVE_SYNC_RTS
                case 0x0000a136u:
                case 0x00006128u:
                case 0x0000a0ecu:
                    if (REG_IR == 0x4e75u)
                    {
                        unsigned int which = REG_PPC == 0x0000a136u ? 0u :
                                             REG_PPC == 0x00006128u ? 1u : 2u;
                        /* Exact Musashi RTS semantics: T0 trace, pop long,
                         * then jump. Generic outer dispatch still charges
                         * CYC_INSTRUCTION[0x4e75]. No polling is skipped. */
                        m68ki_trace_t0();
                        m68ki_jump(m68ki_pull_32());
                        g_t2gen_v017_rts_count[which]++;
                        native_done = 1;
                    }
                    break;
#endif
                default:
                    break;
                }
                if (!native_done)
                    m68ki_instruction_jump_table[REG_IR]();
            }
#else
#if defined(T2GEN_V010_NATIVE_CMP_EXEC) || defined(T2GEN_V011_NATIVE_SYNC_EXEC)
			/* The ROM bytes at A12E are B2 79 00 FF 03 B0:
			 * CMP.W ($00FF03B0).L,D1. Intercept only this exact
			 * instruction; consume its extension words and use the
			 * normal data-space bus callback. The next BEQ remains
			 * a genuine Musashi instruction, preserving interrupt
			 * opportunities at instruction boundaries. */
			if (REG_PPC == 0x0000a12eu && REG_IR == 0xb279u)
			{
				uint addr = m68ki_read_imm_32();
				if (addr == 0x00ff03b0u)
				{
					uint16_t w = (uint16_t)m68ki_read_16(addr);
					struct t2n_sync_result r = t2n_cmp_word(REG_D[1], w, m68ki_get_sr());
					m68ki_set_ccr(r.ccr);
					g_t2gen_v010_native_cmp_count++;
				}
				else
				{
					/* Unexpected ROM modification: do not silently
					 * execute an instruction with a wrong address. */
					REG_IR = 0x4afcu; /* ILLEGAL opcode */
					m68ki_instruction_jump_table[REG_IR]();
				}
			}
#ifdef T2GEN_V011_NATIVE_SYNC_EXEC
            else if (REG_PPC == 0x00006120u && REG_IR == 0xb079u)
            {
                uint addr = m68ki_read_imm_32();
                if (addr == 0x00ff03b0u)
                {
                    uint16_t w = (uint16_t)m68ki_read_16(addr);
                    struct t2n_sync_result r = t2n_cmp_word(REG_D[0], w, m68ki_get_sr());
                    m68ki_set_ccr(r.ccr);
                    g_t2gen_v011_cmp_d0_count++;
                }
                else
                {
                    REG_IR = 0x4afcu;
                    m68ki_instruction_jump_table[REG_IR]();
                }
            }
            else if (REG_PPC == 0x0000a0e4u && REG_IR == 0x4a79u)
            {
                uint addr = m68ki_read_imm_32();
                if (addr == 0x00ff0222u)
                {
                    uint16_t w = (uint16_t)m68ki_read_16(addr);
                    struct t2n_sync_result r = t2n_tst_word(w, m68ki_get_sr());
                    m68ki_set_ccr(r.ccr);
                    g_t2gen_v011_tst_count++;
                }
                else
                {
                    REG_IR = 0x4afcu;
                    m68ki_instruction_jump_table[REG_IR]();
                }
            }
#endif
#ifdef T2GEN_V012_NATIVE_BRANCH_EXEC
            else if ((REG_PPC == 0x0000a134u && REG_IR == 0x67f8u) ||
                     (REG_PPC == 0x00006126u && REG_IR == 0x67f8u) ||
                     (REG_PPC == 0x0000a0eau && REG_IR == 0x66f8u))
            {
                /* Identical semantics to Musashi m68k_op_beq_8 / bne_8:
                 * taken: trace T0 and signed 8-bit PC displacement;
                 * not taken: additional BCC_NOTAKE_B cycles.
                 * The outer dispatcher still charges CYC_INSTRUCTION[IR].
                 * Each branch remains an individual instruction, so
                 * interrupts/trace boundaries are unchanged. */
                unsigned int which = REG_PPC == 0x0000a134u ? 0u :
                                     REG_PPC == 0x00006126u ? 1u : 2u;
                int taken = which == 2u ? COND_NE() : COND_EQ();
                g_t2gen_v012_branch_count[which]++;
                if (taken)
                {
                    g_t2gen_v012_branch_taken[which]++;
                    m68ki_trace_t0();
                    m68ki_branch_8(MASK_OUT_ABOVE_8(REG_IR));
                }
                else
                {
                    USE_CYCLES(CYC_BCC_NOTAKE_B);
                }
            }
#endif
			else
#endif
			{
				m68ki_instruction_jump_table[REG_IR]();
			}
#endif /* T2GEN_V016_SWITCH_DISPATCH */
			USE_CYCLES(CYC_INSTRUCTION[REG_IR]);

#ifdef T2GEN_V015_PAIRED_SYNC
            /* Optional fast path: consume the immediately following branch
             * in this same C dispatch iteration. Crucially, it still gets
             * its own opcode fetch, PPC, register snapshot, instruction
             * cycle debit, and trace exception boundary. The branch must
             * never execute when the slice is already exhausted. */
            if (GET_CYCLES() > 0 &&
                ((REG_PPC == 0x0000a12eu && REG_IR == 0xb279u && M68KI_REG_PC == 0x0000a134u) ||
                 (REG_PPC == 0x00006120u && REG_IR == 0xb079u && M68KI_REG_PC == 0x00006126u) ||
                 (REG_PPC == 0x0000a0e4u && REG_IR == 0x4a79u && M68KI_REG_PC == 0x0000a0eau)))
            {
                unsigned int which = M68KI_REG_PC == 0x0000a134u ? 0u :
                                     M68KI_REG_PC == 0x00006126u ? 1u : 2u;
                unsigned int expected = which == 2u ? 0x66f8u : 0x67f8u;
                int j;
                /* Finish the CMP/TST instruction before starting BEQ/BNE. */
                m68ki_exception_if_trace();
                m68ki_trace_t1();
                m68ki_use_data_space();
                m68ki_instr_hook(M68KI_REG_PC);
                REG_PPC = M68KI_REG_PC;
                for (j = 15; j >= 0; j--)
                    REG_DA_SAVE[j] = REG_DA[j];
                REG_IR = m68ki_read_imm_16();
                if (REG_IR == expected)
                {
                    g_t2gen_v016_paired_count[which]++;
                    int taken = which == 2u ? COND_NE() : COND_EQ();
                    g_t2gen_v012_branch_count[which]++;
                    if (taken)
                    {
                        g_t2gen_v012_branch_taken[which]++;
                        m68ki_trace_t0();
                        m68ki_branch_8(MASK_OUT_ABOVE_8(REG_IR));
                    }
                    else
                        USE_CYCLES(CYC_BCC_NOTAKE_B);
                }
                else
                {
                    g_t2gen_v016_paired_fallback[which]++;
                    /* Modified ROM: fall back to Musashi's opcode table. */
                    m68ki_instruction_jump_table[REG_IR]();
                }
                USE_CYCLES(CYC_INSTRUCTION[REG_IR]);
            }
#endif

			/* Trace m68k_exception, if necessary */
			m68ki_exception_if_trace(); /* auto-disable (see m68kcpu.h) */
#ifdef T2GEN_V018_ROUTINE_DISPATCH
            /* Continue only when the next PC is another translated
             * instruction of the same original ROM routine. The check
             * happens AFTER trace handling, which can change PC. */
            if (GET_CYCLES() > 0)
            {
                unsigned int next = M68KI_REG_PC;
                unsigned int which = 3u;
                if (next == 0x0000a134u || next == 0x0000a136u)
                    which = 0u;
                else if (next == 0x00006126u || next == 0x00006128u)
                    which = 1u;
                else if (next == 0x0000a0eau || next == 0x0000a0ecu)
                    which = 2u;
                if (which < 3u)
                {
                    t2n_v018_continuation = 1;
                    t2n_v018_which = which;
                    g_t2gen_v018_followup[which]++;
                    goto t2n_v018_next_instruction;
                }
            }
#endif
		} while(GET_CYCLES() > 0);

		/* set previous PC to current PC for the next entry into the loop */
		REG_PPC = M68KI_REG_PC;
	}
	else
		SET_CYCLES(0);

	/* return how many clocks we used */
	return m68ki_initial_cycles - GET_CYCLES();
}


int m68k_cycles_run(void)
{
	return m68ki_initial_cycles - GET_CYCLES();
}

int m68k_cycles_remaining(void)
{
	return GET_CYCLES();
}

/* Change the timeslice */
void m68k_modify_timeslice(int cycles)
{
	m68ki_initial_cycles += cycles;
	ADD_CYCLES(cycles);
}


void m68k_end_timeslice(void)
{
	m68ki_initial_cycles -= GET_CYCLES();
	SET_CYCLES(0);
}


/* ASG: rewrote so that the int_level is a mask of the IPL0/IPL1/IPL2 bits */
/* KS: Modified so that IPL* bits match with mask positions in the SR
 *     and cleaned out remenants of the interrupt controller.
 */
void m68k_set_irq(unsigned int int_level)
{
	uint old_level = CPU_INT_LEVEL;
	CPU_INT_LEVEL = int_level << 8;

	/* A transition from < 7 to 7 always interrupts (NMI) */
	/* Note: Level 7 can also level trigger like a normal IRQ */
	if(old_level != 0x0700 && CPU_INT_LEVEL == 0x0700)
		m68ki_cpu.nmi_pending = TRUE;
}

void m68k_set_virq(unsigned int level, unsigned int active)
{
	uint state = m68ki_cpu.virq_state;
	uint blevel;

	if(active)
		state |= 1 << level;
	else
		state &= ~(1 << level);
	m68ki_cpu.virq_state = state;

	for(blevel = 7; blevel > 0; blevel--)
		if(state & (1 << blevel))
			break;
	m68k_set_irq(blevel);
}

unsigned int m68k_get_virq(unsigned int level)
{
	return (m68ki_cpu.virq_state & (1 << level)) ? 1 : 0;
}

void m68k_init(void)
{
	static uint emulation_initialized = 0;

	/* The first call to this function initializes the opcode handler jump table */
	if(!emulation_initialized)
		{
		m68ki_build_opcode_table();
		emulation_initialized = 1;
	}

	m68k_set_int_ack_callback(NULL);
	m68k_set_bkpt_ack_callback(NULL);
	m68k_set_reset_instr_callback(NULL);
	m68k_set_cmpild_instr_callback(NULL);
	m68k_set_rte_instr_callback(NULL);
	m68k_set_tas_instr_callback(NULL);
	m68k_set_illg_instr_callback(NULL);
    m68k_set_trap_instr_callback(NULL);
	m68k_set_pc_changed_callback(NULL);
	m68k_set_fc_callback(NULL);
	m68k_set_instr_hook_callback(NULL);
}

/* Trigger a Bus Error exception */
void m68k_pulse_bus_error(void)
{
	m68ki_exception_bus_error();
}

/* Pulse the RESET line on the CPU */
void m68k_pulse_reset(void)
{
	/* Disable the PMMU on reset */
	m68ki_cpu.pmmu_enabled = 0;

	/* Clear all stop levels and eat up all remaining cycles */
	CPU_STOPPED = 0;
	SET_CYCLES(0);

	CPU_RUN_MODE = RUN_MODE_BERR_AERR_RESET;
	CPU_INSTR_MODE = INSTRUCTION_YES;

	/* Turn off tracing */
	FLAG_T1 = FLAG_T0 = 0;
	m68ki_clear_trace();
	/* Interrupt mask to level 7 */
	FLAG_INT_MASK = 0x0700;
	CPU_INT_LEVEL = 0;
	m68ki_cpu.virq_state = 0;
	/* Reset VBR */
	REG_VBR = 0;
	/* Go to supervisor mode */
	m68ki_set_sm_flag(SFLAG_SET | MFLAG_CLEAR);

	/* Invalidate the prefetch queue */
#if M68K_EMULATE_PREFETCH
	/* Set to arbitrary number since our first fetch is from 0 */
	CPU_PREF_ADDR = 0x1000;
#endif /* M68K_EMULATE_PREFETCH */

	/* Read the initial stack pointer and program counter */
	m68ki_jump(0);
	M68KI_REG_SP = m68ki_read_imm_32();
	M68KI_REG_PC = m68ki_read_imm_32();
	m68ki_jump(M68KI_REG_PC);

	CPU_RUN_MODE = RUN_MODE_NORMAL;

	RESET_CYCLES = CYC_EXCEPTION[EXCEPTION_RESET];
}

/* Pulse the HALT line on the CPU */
void m68k_pulse_halt(void)
{
	CPU_STOPPED |= STOP_LEVEL_HALT;
}

/* Get and set the current CPU context */
/* This is to allow for multiple CPUs */
unsigned int m68k_context_size(void)
{
	return sizeof(m68ki_cpu_core);
}

unsigned int m68k_get_context(void* dst)
{
	if(dst) *(m68ki_cpu_core*)dst = m68ki_cpu;
	return sizeof(m68ki_cpu_core);
}

void m68k_set_context(void* src)
{
	if(src) m68ki_cpu = *(m68ki_cpu_core*)src;
}

/* ======================================================================== */
/* ============================== MAME STUFF ============================== */
/* ======================================================================== */

#if M68K_COMPILE_FOR_MAME == M68K_OPT_ON

static struct {
	UINT16 sr;
	UINT8 stopped;
	UINT8 halted;
} m68k_substate;

static void m68k_prepare_substate(void)
{
	m68k_substate.sr = m68ki_get_sr();
	m68k_substate.stopped = (CPU_STOPPED & STOP_LEVEL_STOP) != 0;
	m68k_substate.halted  = (CPU_STOPPED & STOP_LEVEL_HALT) != 0;
}

static void m68k_post_load(void)
{
	m68ki_set_sr_noint_nosp(m68k_substate.sr);
	CPU_STOPPED = m68k_substate.stopped ? STOP_LEVEL_STOP : 0
		        | m68k_substate.halted  ? STOP_LEVEL_HALT : 0;
	m68ki_jump(M68KI_REG_PC);
}

void m68k_state_register(const char *type, int index)
{
	/* Note, D covers A because the dar array is common, REG_A=REG_D+8 */
	state_save_register_item_array(type, index, REG_D);
	state_save_register_item(type, index, REG_PPC);
	state_save_register_item(type, index, M68KI_REG_PC);
	state_save_register_item(type, index, REG_USP);
	state_save_register_item(type, index, REG_ISP);
	state_save_register_item(type, index, REG_MSP);
	state_save_register_item(type, index, REG_VBR);
	state_save_register_item(type, index, REG_SFC);
	state_save_register_item(type, index, REG_DFC);
	state_save_register_item(type, index, REG_CACR);
	state_save_register_item(type, index, REG_CAAR);
	state_save_register_item(type, index, m68k_substate.sr);
	state_save_register_item(type, index, CPU_INT_LEVEL);
	state_save_register_item(type, index, m68k_substate.stopped);
	state_save_register_item(type, index, m68k_substate.halted);
	state_save_register_item(type, index, CPU_PREF_ADDR);
	state_save_register_item(type, index, CPU_PREF_DATA);
	state_save_register_func_presave(m68k_prepare_substate);
	state_save_register_func_postload(m68k_post_load);
}

#endif /* M68K_COMPILE_FOR_MAME */

/* ======================================================================== */
/* ============================== END OF FILE ============================= */
/* ======================================================================== */
