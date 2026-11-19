/* Sub_08013DF8 @ 0x08013DF8 (300 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w138a_08013df8_MATCHED.c (registry: src/w138a_08013df8_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;
typedef signed int s32;

extern void Vec2_SetMirrored(u8 *s, s32 x, s32 y);

extern void ChipSlot_IncUse(u8 *s, u8 idx);

extern void ChipSlot_Tick(u8 *s);

extern s16 Check119_Minus3_Le1(u8 *s);

extern void SetBit16(u32 a, int b);

extern u32 *ChipInit_0801AA70(int a, int b, int c, int d, int e, u8 *f);

extern u32 GetField17_U8(u32 a);

extern void MaxAssign_17(u32 a, int b);

extern void DecIfNonZero_18(u32 a);

extern void SetBytes_08011F68(u8 *s, int a);

__attribute__((section(".text.w138a_08013df8_v2")))
void Sub_08013DF8(u8 *s)
{
    u8 *q = s;
    q += 124;

    switch (s[14]) {
    case 0:
        Vec2_SetMirrored(s, 0xFFFFC400, 0);
        ChipSlot_IncUse(s, 8);
        s[14]++;
        break;
    case 1:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        SetBit16(*(u32 *)(s + 44), 3);
        {
            u8 *p = s + 35;
            ChipInit_0801AA70(30, 0, (u32)(p[0] << 28) >> 28, 0xFFFFEC00, 0xFFFFB000, *(u8 **)(s + 44));
            ChipInit_0801AA70(30, 1, (u32)(p[0] << 28) >> 28, 0xFFFFEC00, 0xFFFFB000, *(u8 **)(s + 44));
            ChipInit_0801AA70(30, 2, (u32)(p[0] << 28) >> 28, 0xFFFFEC00, 0xFFFFB000, *(u8 **)(s + 44));
        }
        ChipSlot_IncUse(s, 9);
        s[14]++;
        break;
    case 2:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        s[14]++;
        break;
    case 3:
        if ((u8)GetField17_U8(*(u32 *)(s + 44)) <= 5)
            break;
        ChipSlot_IncUse(s, 10);
        s[14]++;
        break;
    case 4:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        MaxAssign_17(*(u32 *)(s + 44), 7);
        DecIfNonZero_18(*(u32 *)(s + 44));
        *(u32 *)(s + 44) = 0;
        Vec2_SetMirrored(s, 0xFFFFC400, 0);
        ChipSlot_IncUse(s, 0);
        q[4] = 0;
        SetBytes_08011F68(s, 0);
        break;
    default:
        break;
    }
    ChipSlot_Tick(s);
}
