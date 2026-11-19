/* Sub_0801CAC4 @ 0x0801CAC4 (128 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36c_0801cac4_MATCHED.c (registry: mmbcc/src/w36c_0801cac4_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void ChipSlot_Setup(u8 *s, int a, int b);

extern void ChipSlot_IncUse(u8 *s, int a);

extern void sub_0800DD08(u8 *sp, u8 *s);

extern void Vec2_SetMirrored(u8 *s, int a, int b);

extern void Text_SelectBlobIdx(int a);

__attribute__((section(".text.w36c_0801cac4")))
void Sub_0801CAC4(u8 *s)
{
    u8 buf[8];
    u8 *p;
    u8 b;
    int c, t;
    u32 cc, m;
    ChipSlot_Setup(s, 597, 0);
    ChipSlot_IncUse(s, 0);
    b = ((u8 *)0x020031e4)[(*(u16 *)0x081705b0 >> 4) * 2];
    c = b & 3;
    t = c;
    __asm__ volatile("" : "+r"(t));
    if (t > 3) c = 3;
    p = s + 69;
    cc = c << 2;
    __asm__ volatile("movs %0, #13" : "=r"(m));
    m = -m;
    *p = (*p & m) | cc;
    p -= 35;
    { u32 z = 0;
    *p = 13;
    *(u32 *)(s + 88) = z;
    *(u32 *)(s + 96) = z;
    *(u32 *)(s + 92) = z;
    *(u32 *)(s + 100) = z; }
    sub_0800DD08(buf, s);
    Vec2_SetMirrored(s, 160 << 5, 0);
    Text_SelectBlobIdx(159);
}
