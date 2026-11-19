/* Sub_0801A568 @ 0x0801A568 (136 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36c_0801a568_MATCHED.c (registry: mmbcc/src/w36c_0801a568_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void ChipSlot_Setup(u8 *s, int a, int b);

extern void ChipSlot_IncUse(u8 *s, int a);

extern void sub_0800DD08(u32 *out, u8 *s);

extern void Vec2_SetMirrored(u8 *s, u32 a, int b);

extern void SetBit16(u32 a, int b);

extern void Text_SelectBlobIdx(int a);

__attribute__((section(".text.w36c_0801a568")))
void Sub_0801A568(u8 *s)
{
    u32 out[2];
    u8 *p;
    int c;
    int t;
    int t69;
    int m69;
    int z;
    ChipSlot_Setup(s, 593, 0);
    ChipSlot_IncUse(s, 0);
    c = *(u8 *)(0x020031e4 + (((*(u16 *)0x081705b0 >> 4) << 1))) & 3;
    __asm__ volatile("add %0, %1, #0" : "=r"(t) : "r"(c));
    if (t > 3)
        c = 3;
    p = s + 69;
    t69 = c << 2;
    m69 = s[69] & -13;
    s[69] = m69 | t69;
    p -= 35;
    z = 0;
    p[0] = 13;
    *(u32 *)(s + 88) = z;
    *(u32 *)(s + 96) = z;
    *(u32 *)(s + 92) = z;
    *(u32 *)(s + 100) = z;
    sub_0800DD08(out, s);
    Vec2_SetMirrored(s, 15360, 0);
    SetBit16(*(u32 *)(s + 44), 3);
    Text_SelectBlobIdx(159);
}
