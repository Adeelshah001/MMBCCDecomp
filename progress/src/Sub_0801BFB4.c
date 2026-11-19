/* Sub_0801BFB4 @ 0x0801BFB4 (124 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_0801bfb4_MATCHED.c (registry: mmbcc/src/w36b_0801bfb4_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Wrapper_D770(u8 *s, u32 a, u32 b);

extern void ChipSlot_IncUse(u8 *s, u32 x);

extern void sub_0800DD08(u8 *buf, u8 *s);

extern void Vec2_SetMirrored(u8 *s, u32 a, u32 b);

extern void Text_SelectBlobIdx(u32 x);

__attribute__((section(".text.w36b_0801bfb4")))
void Sub_0801BFB4(u8 *s)
{
    u8 buf[8];
    u16 v;
    int idx;
    u8 *tab;
    int x;
    Wrapper_D770(s, 2090, 0);
    ChipSlot_IncUse(s, 0);
    v = *(u16 *)0x081705b0;
    idx = (v >> 4) * 2;
    tab = (u8 *)0x020031e4;
    x = tab[idx] & 3;
    if (x > 3) x = 3;
    s[69] = (s[69] & ~13) | (x << 2);
    s[34] = 13;
    sub_0800DD08(buf, s);
    Vec2_SetMirrored(s, 0xffffec00, 0);
    Text_SelectBlobIdx(159);
}
