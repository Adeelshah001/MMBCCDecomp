/* Sub_080429E0 @ 0x080429E0 (86 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36a_080429e0_MATCHED.c (registry: mmbcc/src/w36a_080429e0_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u32 sub_080242A8(u32 a, u32 b);

extern u32 Wrap_GetRomTableU16(u32 a);

extern u32 Sub_080241D0(u32 a);

extern u32 GetEnt_U16_14(u32 a);

__attribute__((section(".text.w36a_080429e0")))
u16 Sub_080429E0(void)
{
    u16 acc = 0;
    u8 i;
    u8 c;
    u8 t;
    u32 y;
    u16 r;
    for (i = 1; i <= 9; i++) {
        c = (u8)sub_080242A8(4096, i);
        if (c != 0)
            acc = (u16)(acc + Wrap_GetRomTableU16(c));
    }
    t = (u8)Sub_080241D0(4096);
    y = Wrap_GetRomTableU16(t);
    r = (u16)(y + GetEnt_U16_14(y));
    r = (u16)(r - acc);
    return r;
}
