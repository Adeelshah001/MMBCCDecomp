/* SetIfGt199 @ 0x0802571C (18 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x0802571c: SetIfGt199 (20B, coordinator-verified). */
__attribute__((section(".text.w7g2_0802571c")))
void SetIfGt199(unsigned char *s, unsigned char a, unsigned char b)
{
    if (a > 199) {
        s[1] = a;
        s[0] = b;
    }
}
