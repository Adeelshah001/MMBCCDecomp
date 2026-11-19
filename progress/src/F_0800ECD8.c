/* F_0800ECD8 @ 0x0800ECD8 (30 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w15c_0800ecd8.c (registry: src/w15c_0800ecd8.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

s8 Fwd_0801025c(u32 a, s8 b);

void SetByte20_Clear21to23_02005130(u8 x);

u32 F_0800ECD8(u32 a, u8 b)
{
    u32 r = (u32)(s8)Fwd_0801025c(a, (s8)b);
    if (r == 1)
    {
        SetByte20_Clear21to23_02005130(13);
        return 1;
    }
    return r;
}
