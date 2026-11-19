/* Sub_08013280 @ 0x08013280 (232 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w50d_08013280_MATCHED.c (registry: src/w50d_08013280_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void ChipSlot_IncUse(u8 *s, u8 n);

extern void ChipSlot_Tick(u8 *s);

extern void Vec2_SetMirrored(u8 *o, int x, int y);

extern short Check119_Minus3_Le1(u8 *s);

extern void SetBytes_08011F68(u8 *s, int a);

extern void SetBit16(u32 a, int b);

extern u8 GetField17_U8(u32 a);

extern void MaxAssign_17(u32 a, int b);

extern void DecIfNonZero_18(u32 a);

extern void ChipInit_080178A8(int a, int b, int c, int d, u32 e);

__attribute__((section(".text.w50d_08013280")))
void Sub_08013280(u8 *s)
{
    u8 *t = s + 124;
    switch (s[14]) {
    case 0:
        Vec2_SetMirrored(s, -15360, 0);
        ChipSlot_IncUse(s, 8);
        s[14]++;
        break;
    case 1:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        ChipSlot_IncUse(s, 9);
        s[14]++;
        break;
    case 2:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        SetBit16(*(u32 *)(s + 44), 3);
        ChipInit_080178A8(133, (int)(((u32)s[35] << 28) >> 28), 0x3c00, 0, *(u32 *)(s + 44));
        ChipSlot_IncUse(s, 10);
        s[14]++;
        break;
    case 3:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        ChipSlot_IncUse(s, 9);
        s[14]++;
        break;
    case 4:
        if (GetField17_U8(*(u32 *)(s + 44)) <= 5)
            break;
        MaxAssign_17(*(u32 *)(s + 44), 7);
        DecIfNonZero_18(*(u32 *)(s + 44));
        *(u32 *)(s + 44) = 0;
        Vec2_SetMirrored(s, -15360, 0);
        ChipSlot_IncUse(s, 0);
        t[4] = 0;
        SetBytes_08011F68(s, 0);
        break;
    default:
        break;
    }
    ChipSlot_Tick(s);
}
