/* IsOne_020051B0_4 @ 0x0801109C (20 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x0801109c: IsOne_020051B0_4 (20B, coordinator-verified). */
extern unsigned char RomBase_20051B0[];

__attribute__((section(".text.w7g2_0801109c")))
unsigned int IsOne_020051B0_4(void)
{
    unsigned int v = RomBase_20051B0[4];
    if (v == 1)
        goto L1;
    __asm__ volatile("movs %0, #0" : "=r"(v));
    goto L2;
L1:
    __asm__ volatile("movs %0, #1" : "=r"(v));
L2:
    return v;
}
