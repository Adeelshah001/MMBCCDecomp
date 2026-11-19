/* Setup10270_Flag14_0800ECF8 @ 0x0800ECF8 (38 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w22b_0800ecf8.c (registry: src/w22b_0800ecf8.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u32 F_08010270(u8 a, u32 b, u8 c, s8 d);

extern void SetByte20_Clear21to23_02005130(u8 x);

__attribute__((section(".text.w22b_0800ECF8")))
s8 Setup10270_Flag14_0800ECF8(u8 a, u32 b, u8 c, s8 d)
{
    s8 r = F_08010270(a, b, c, d);
    if (r == 1) {
        SetByte20_Clear21to23_02005130(14);
        return 1;
    }
    return r;
}
