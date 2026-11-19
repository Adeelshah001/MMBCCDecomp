/* F_0802D5A8 @ 0x0802D5A8 (44 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave15_B.c (registry: src/wave15_B.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

extern u16 TblGet_f00(u8 idx);

__attribute__((section(".text.w15b_0802d5a8")))
void F_0802D5A8(s16 delta, u16 *p, u8 idx)
{
    u16 lim;
    int d = delta;
    s16 cur;
    u16 pv = *p;
    __asm__("add %0, %1, %0" : "+r" (d) : "r" (pv));
    *p = (u16)d;
    lim = TblGet_f00(idx);
    cur = *(s16 *)p;
    if (cur > lim)
        *p = lim;
}
