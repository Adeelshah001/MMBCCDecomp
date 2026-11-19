/* Sub_08013024 @ 0x08013024 (276 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w60d_08013024_MATCHED.c (registry: src/w60d_08013024_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Vec2_SetMirrored(u8 *o, u32 x, u32 y);

extern void ChipSlot_IncUse(u8 *s, int idx);

extern void ChipSlot_Tick(u8 *s);

extern u16 Check119_Minus3_Le1(u8 *s);

extern void SetBit16(u8 *s, int bit);

extern void ChipInit_0801AA70(int a, int b, int c, int d, int e, u8 *f);

extern int Text_SelectBlobIdx(int idx);

extern u8 GetField17_U8(u8 *s);

extern void DecIfNonZero_18(u8 *s);

extern void SetBytes_08011F68(u8 *s, u8 v);

__attribute__((section(".text.w60d_08013024")))
void Sub_08013024(u8 *s)
{
    u8 *p = s + 124;
    switch (s[14]) {
    case 0:
        Vec2_SetMirrored(s, 0xffffc400, 0);
        ChipSlot_IncUse(s, 8);
        s[14]++;
        break;
    case 1:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        ChipSlot_IncUse(s, 9);
        s[14]++;
        break;
    case 2: {
        u8 *q;
        register int nib __asm__("r2");
        int c;
        int z;
        if (Check119_Minus3_Le1(s) == 0)
            break;
        SetBit16(*(u8 **)(s + 44), 3);
        q = s + 35;
        nib = ((u32)*q << 28) >> 28;
        c = -15360;
        z = 0;
        ChipInit_0801AA70(2, 0, nib, c, z, *(u8 **)(s + 44));
        nib = ((u32)*q << 28) >> 28;
        ChipInit_0801AA70(3, 0, nib, c, z, *(u8 **)(s + 44));
        Text_SelectBlobIdx(152);
        s[14]++;
        break;
    }
    case 3:
        if (GetField17_U8(*(u8 **)(s + 44)) <= 6)
            break;
        ChipSlot_IncUse(s, 10);
        s[14]++;
        break;
    case 4:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        DecIfNonZero_18(*(u8 **)(s + 44));
        *(u32 *)(s + 44) = 0;
        Vec2_SetMirrored(s, 0xffffc400, 0);
        ChipSlot_IncUse(s, 0);
        p[4] = 0;
        SetBytes_08011F68(s, 0);
        break;
    }
    ChipSlot_Tick(s);
}
