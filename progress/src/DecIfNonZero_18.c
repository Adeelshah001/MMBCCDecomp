/* DecIfNonZero_18 @ 0x08017464 (14 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x08017464: DecIfNonZero_18 (16B, coordinator-verified). */
__attribute__((section(".text.w7g2_08017464")))
void DecIfNonZero_18(unsigned char *s)
{
    if (s[18] != 0)
        s[18]--;
}
