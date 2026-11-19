/* Sub_080174F4 @ 0x080174F4 (136 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37b_080174f4_MATCHED.c (registry: mmbcc/src/w37b_080174f4_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void ChipSlot_Setup(u8 *s, int a, int b);

extern void ChipSlot_IncUse(u8 *s, int a);

extern void Sub_0801757C(u8 *s);

__attribute__((section(".text.w37b_080174f4")))
void Sub_080174F4(u8 *s)
{
    u32 *base;
    u32 *p;
    u32 *e;
    int one;
    int c;
    int tc;
    base = (u32 *)0x082243d8;
    __asm__ volatile("" : "+r"(base));
    p = base + s[9];
    one = 1;
    *(u32 *)(s + 12) = one;
    e = *p;
    *(u32 *)(s + 20) = e[1];
    *(u32 *)(s + 108) = 0;
    s[10] = 2 | s[10] | one;
    ChipSlot_Setup(s, 512, s[16]);
    ChipSlot_IncUse(s, 0);
    s[18] = 0;
    c = *(u8 *)(0x020031e4 + (((*(u16 *)0x081705b0 >> 4) << 1))) & 3;
    tc = c;
    __asm__ volatile("" : "+r"(tc));
    if (tc > 3)
        c = 3;
    {
        u8 *q = s + 69;
        int sh = c << 2;
        int m = *q & -13;
        *q = m | sh;
    }
    s[34] = 14;
    Sub_0801757C(s);
}
