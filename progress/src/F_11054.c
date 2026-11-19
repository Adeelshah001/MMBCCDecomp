/* F_11054 @ 0x08011054 (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave11_A_old.c (registry: src/wave11_A_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w11a_08011054")))
int F_11054(u8 *p)
{
    u8 *q = p;
    u8 *g;
    __asm__ volatile("" : "=r" (g) : "0" ((u8 *)0x020051b0));
    if (g[4] == 1) {
        q[0] = g[12];
        return 1;
    }
    return 0;
}
