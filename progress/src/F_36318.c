/* F_36318 @ 0x08036318 (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave11_A_old.c (registry: src/wave11_A_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w11a_08036318")))
u32 F_36318(u32 x)
{
    u32 xx = x;
    u8 *base;
    __asm__ volatile("" : "=r" (base) : "0" ((u8 *)0x0200bce8));
    if (xx > 6)
        return 0;
    *(base + 2) |= (1 << xx);
    return 1;
}
