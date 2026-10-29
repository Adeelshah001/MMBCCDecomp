/* MMBCCDecomp — Wave 3 batch 5, old_agbcc TU (worker E, coordinator-split).
 * MATCHED 2026-10-20.
 *
 * ConstZeroS16_2472C needs old_agbcc: main agbcc's DCE deletes the kept
 * `lsls r0,r0,#24` (or adds stack junk across ~15 probed shapes);
 * old_agbcc preserves it. Evidence: docs/match_notes_wave3_e.md.
 * Makefile rule for this file uses $(OLDAGBCC) (precedent: text.o,
 * vec2.o, entrymgr.o).
 */

typedef unsigned char u8;
typedef short s16;
typedef unsigned int u32;

/* 0x0802472C (6B, tentative): computes (u32)a << 24, tests it, returns 0
 * either way (s16 per caller sign-extension). */
__attribute__((section(".text.w3e_zero16_2472c")))
s16 ConstZeroS16_2472C(u8 a)
{
    if ((u32)a << 24)
        return 0;
    return 0;
}

/* 2-byte zero pad: ROM has 0000 after the 6 code bytes. */
__attribute__((section(".text.w3e_zero16_2472c")))
static const u8 sPad_ConstZeroS16_2472C[2] = { 0, 0 };
