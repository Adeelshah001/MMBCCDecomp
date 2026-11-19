/* GetPtr_08008610 @ 0x08008610 (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x08008610: GetPtr_08008610 (24B, coordinator-verified). */
extern unsigned int g_02003674;

__attribute__((section(".text.w7g2_08008610")))
unsigned int GetPtr_08008610(unsigned char *s)
{
    if (s[11] != 0)
        return 0x02004aa0;
    return g_02003674;
}
