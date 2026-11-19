/* Eq2260000 @ 0x0803FEF8 (20 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x0803fef8: Eq2260000 (20B, coordinator-verified). */
__attribute__((section(".text.w7g2_0803fef8")))
unsigned int Eq2260000(unsigned short v)
{
    unsigned int x = (unsigned int)v << 16;
    unsigned int r = 0;
    if (x == 0x02260000)
        r = 1;
    return r;
}
