/* F_3FD9C @ 0x0803FD9C (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave11_A_old.c (registry: src/wave11_A_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w11a_0803fd9c")))
int F_3FD9C(u16 x)
{
    u16 xx = x;
    int r = 0;
    u32 p;
    __asm__ volatile("" : "=r" (p) : "0" (0x222));
    if (xx == p || xx == 0x3000)
        r = 1;
    return r;
}
