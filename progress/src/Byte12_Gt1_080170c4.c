/* Byte12_Gt1_080170c4 @ 0x080170C4 (14 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x080170c4: Byte12_Gt1 (16B, coordinator-verified). */
__attribute__((section(".text.w7g2_080170c4")))
unsigned int Byte12_Gt1_080170c4(unsigned char *s)
{
    unsigned int r = 0;
    if (s[12] > 1)
        r = 1;
    return r;
}
