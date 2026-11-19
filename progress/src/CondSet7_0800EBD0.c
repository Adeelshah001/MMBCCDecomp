/* CondSet7_0800EBD0 @ 0x0800EBD0 (30 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w16c_0800ebd0.c (registry: src/w16c_0800ebd0.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

u8 F_0801039C(u8 *p, u8 b);

void SetByte20_Clear21to23_02005130(u8 v);

__attribute__((section(".text.w16c_0800ebd0")))
u32 CondSet7_0800EBD0(u8 *p, u32 b)
{
    u32 r = (u32)(s8)F_0801039C(p, (u8)b);
    if (r != 1)
        return r;
    SetByte20_Clear21to23_02005130(7);
    return 1;
}
