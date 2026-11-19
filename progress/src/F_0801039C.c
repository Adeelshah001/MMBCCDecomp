/* F_0801039C @ 0x0801039C (48 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave15_B.c (registry: src/wave15_B.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Ewram5160_Init_10508(u8 v);

__attribute__((section(".text.w15b_0801039c")))
u8 F_0801039C(u8 *p, u8 b)
{
    u8 bb;
    u8 *q;
    bb = b;
    q = (u8 *)0x02005160;
    __asm__ volatile("" : "+r" (q));
    if (*q != 0)
        return 0;
    Ewram5160_Init_10508(6);
    *(u8 **)(q + 48) = p;
    *(q + 66) = bb;
    return 1;
}
