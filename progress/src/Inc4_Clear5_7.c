/* Inc4_Clear5_7 @ 0x080112BC (16 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x080112bc: Inc4_Clear5_7 (16B, coordinator-verified). */
__attribute__((section(".text.w7g2_080112bc")))
void Inc4_Clear5_7(unsigned char *s)
{
    unsigned int v = s[4] + 1;
    unsigned int z = 0;
    s[4] = v;
    s[5] = z;
    s[6] = z;
    s[7] = z;
}
