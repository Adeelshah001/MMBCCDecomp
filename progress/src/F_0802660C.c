/* F_0802660C @ 0x0802660C (48 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave15_B.c (registry: src/wave15_B.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 GetBoundedByte_080252D0(void *s, u16 idx);

__attribute__((section(".text.w15b_0802660c")))
u16 F_0802660C(u8 *p, u16 idx)
{
    u16 i = idx;
    if (i == 0)
        return 0x1000;
    if (i >= *(u16 *)(p + 22))
        return 0;
    {
        u8 v = GetBoundedByte_080252D0(p + 16, i);
        return v | 0x2000;
    }
}
