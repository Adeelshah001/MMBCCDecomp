/* GetEwramBD20_130 @ 0x0804A3F0 (12 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_a.c (registry: src/wave3_a.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 gEwram_0200BD20[];

/* 0x0804A3F0: return *(u8*)(0x0200BD20+130). Tentative. */
__attribute__((section(".text.w3a_getewrambd20_130")))
u8 GetEwramBD20_130(void)
{
    u8 *base = gEwram_0200BD20;
    return *(base + 130);
}
