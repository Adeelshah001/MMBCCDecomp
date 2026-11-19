/* SetByte432_08026108 @ 0x08026108 (20 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x08026108: SetByte432_08026108 (20B, coordinator-verified). */
__attribute__((section(".text.w7g2_08026108")))
void SetByte432_08026108(unsigned char *s, unsigned char v)
{
    if (v > 2)
        v = 2;
    s[432] = v;
}
