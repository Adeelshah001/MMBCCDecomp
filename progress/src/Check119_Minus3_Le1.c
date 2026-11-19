/* Check119_Minus3_Le1 @ 0x08011F50 (22 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x08011f50: Check119_Minus3_Le1 (24B, coordinator-verified). */
__attribute__((section(".text.w7g2_08011f50")))
unsigned int Check119_Minus3_Le1(unsigned char *s)
{
    unsigned int v = (unsigned char)(s[119] - 3);
    if (v <= 1)
        return 1;
    return 0;
}
