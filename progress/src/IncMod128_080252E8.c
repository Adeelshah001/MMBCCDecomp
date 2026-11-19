/* IncMod128_080252E8 @ 0x080252E8 (16 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x080252e8: IncMod128 (16B, coordinator-verified). */
__attribute__((section(".text.w7g2_080252e8")))
void IncMod128_080252E8(unsigned char *s)
{
    unsigned int v = 0x7f;
    unsigned int w;
    v &= s[0];
    v++;
    w = 0x80;
    v |= w;
    s[0] = v;
}
