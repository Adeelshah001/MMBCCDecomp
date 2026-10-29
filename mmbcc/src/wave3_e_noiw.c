/* MMBCCDecomp — Wave 3 batch 5, no-interwork TU (worker E,
 * coordinator-split). MATCHED 2026-10-20.
 *
 * DivZeroStub_4DEDE needs agbcc WITHOUT -mthumb-interwork: the ROM
 * epilogue is `pop {pc}`; interwork emits `pop {r1}; bx r1`. Evidence:
 * docs/match_notes_wave3_e.md. Makefile rule for this file omits
 * -mthumb-interwork (precedent: wave3_d_noiw.o).
 *
 * NOTE: this file is NOT compiled into the build (not in SRCS_C).
 * Its 10-byte function is emitted via BYTE() in ldscript.ld
 * (.text.w3e_divzero_4dede): the ROM has `00 29` (unmatched code) right
 * after the 10 code bytes, so neither gas's c046 pad nor a 00 00 pad
 * object is correct. This file is the documented, build-verified source
 * of those 10 bytes (verified by compiling with the no-interwork rule
 * and diffing vs ROM). Re-verify with:
 *   cpp -I mmbcc/include src/wave3_e_noiw.c -o /tmp/x.i &&
 *   tools/agbcc/bin/agbcc -O2 -Wimplicit -Wparentheses -o /tmp/x.s /tmp/x.i
 */

typedef unsigned char u8;
typedef unsigned int u32;

extern void sub_0804DD9C(void);   /* .set in wave3_d_noiw.c */

/* 0x0804DEDE (8B, tentative): divide-by-zero path — sub_0804DE70 (custom
 * divmod) `beq`s here when the divisor (r1) is 0. Calls sub_0804DD9C,
 * returns 0. */
__attribute__((section(".text.w3e_divzero_4dede")))
u32 DivZeroStub_4DEDE(void)
{
    sub_0804DD9C();
    return 0;
}
