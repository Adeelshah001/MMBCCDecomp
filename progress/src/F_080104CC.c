/* F_080104CC @ 0x080104CC (38 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave15_B.c (registry: src/wave15_B.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void SyncObjFlagBits_BEE0(unsigned int a, unsigned int b);

__attribute__((section(".text.w15b_080104cc")))
u8 F_080104CC(u8 x)
{
    if (*(u8 *)0x02005160 != 0)
        return 0;
    SyncObjFlagBits_BEE0(x, 0);
    return 1;
}
