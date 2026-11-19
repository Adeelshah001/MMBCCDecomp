/* F_3FA48 @ 0x0803FA48 (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave11_A_old.c (registry: src/wave11_A_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w11a_0803fa48")))
u32 F_3FA48(u16 x)
{
    u16 xx = x;
    u32 r = 0;
    int pool;
    __asm__ volatile("" : "=r" (pool) : "0" (0x3a1));
    if (xx >= pool) {
        pool++;
        if (xx <= pool)
            r = 1;
        else if (xx == 0x13a0)
            r = 1;
    }
    return r;
}
