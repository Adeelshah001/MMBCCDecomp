/* SetPairZero_28874 @ 0x08028874 (12 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_e.c (registry: src/wave3_e.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x08028874 (12B, tentative): p[0] = (u8)v; p[1] = 0. */
__attribute__((section(".text.w3e_setpair0_28874")))
void SetPairZero_28874(u32 *p, u8 v)
{
    p[0] = v;
    p[1] = 0;
}
