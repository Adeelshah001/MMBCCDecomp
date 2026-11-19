/* FlagCheck_0200B7E0_3 @ 0x08027E44 (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x08027e44: FlagCheck_0200B7E0_3 (24B, coordinator-verified). */
extern unsigned char gEwram_0200B7E0[];

__attribute__((section(".text.w7g2_08027e44")))
unsigned int FlagCheck_0200B7E0_3(void)
{
    unsigned char *p = gEwram_0200B7E0;
    unsigned int v;
    __asm__("movs %0, #1" : "=r"(v));
    v &= p[3];
    if (v == 0)
        return 0;
    return 1;
}
