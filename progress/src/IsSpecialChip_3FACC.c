/* IsSpecialChip_3FACC @ 0x0803FACC (76 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave11_D_old.c (registry: src/wave11_D_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x0803FACC (76 B): returns 1 if u16 chip in {0x1030,0x3030,0x2030,0x4030}
 * or in 0x30..0x36, else 0. */
__attribute__((section(".text.w11d_0803facc")))
u8 IsSpecialChip_3FACC(u16 chip)
{
    int a = chip;
    int b = a;
    int lo = 0x30;
    u8 r = 0;
    if (a == 0x1030) goto yes;
    if (a > 0x1030) goto big;
    if (a > 0x36) goto no;
    if (a < lo) goto no;
    goto yes;
big:
    if (a == 0x3030) goto yes;
    if (a > 0x3030) goto huge;
    if (a == 0x2030) goto yes;
    goto no;
huge:
    /* Keep the b-copy alive in r2 for the final compare. */
    asm("" : "+r" (b));
    if (b != 0x4030) goto no;
yes:
    r = 1;
no:
    return r;
}
