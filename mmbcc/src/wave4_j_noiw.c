/* MMBCCDecomp — Wave 4 batch J, no-interwork TU (worker J).
 * MATCHED 2026-10-20.
 *
 * agbcc emits `pop {pc}` epilogues only WITHOUT -mthumb-interwork.
 * Precedent: mmbcc/src/wave3_d_noiw.c (DivZeroStub), wave3_e_noiw.c.
 * Suggested Makefile rule (coordinator): build this file WITHOUT
 * -mthumb-interwork, like $(BUILD)/wave3_d_noiw.o.
 *
 * 0x0804DF9E Wrap_0804DF9E (8 B): push {lr}; bl sub_0804DD9C;
 *   movs r0,#0; pop {pc}. Wrapper around the `mov pc,lr` stub at
 *   0x0804DD9C. 8 code bytes; the assembler pads the section with a
 *   2-byte nop which the ROM does not have (next function at 0x0804DFA8
 *   follows immediately) — strip like GetIndexedU8 (wave3_a).
 */

typedef unsigned char u8;
typedef unsigned int u32;

extern void sub_0804DD9C(void);

/* 0x0804DF9E: call sub_0804DD9C, return 0. Tentative name. */
__attribute__((section(".text.w4j_wrap_0804df9e")))
u32 Wrap_0804DF9E(void)
{
    sub_0804DD9C();
    return 0;
}

/* sub_0804DD9C is defined in mmbcc/src/wave3_d_noiw.c (landed); the
   extern declaration above suffices. */
