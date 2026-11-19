/* sub_08012504 @ 0x08012504 (328 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w68a_08012504_MATCHED.c (registry: src/w68a_08012504_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;
typedef signed int s32;

void Vec2_SetMirrored(u8 *o, s32 x, s32 y);

void ChipSlot_IncUse(u8 *s, u8 idx);

void ChipSlot_Tick(u8 *s);

u16 Check119_Minus3_Le1(u8 *s);

u8 GetField17_U8(u8 *s);

void SetBytes_08011F68(u8 *s, u8 v);

void DecIfNonZero_18(u8 *s);

s16 Text_SelectBlobIdx(u16 idx);

u32 *ChipInit_0801BBB4(u8 a, u8 b, s32 c, s32 d, u8 *e);

__attribute__((section(".text.w68a_08012504")))
void sub_08012504(u8 *s)
{
    u8 *e = s;
    e += 124;

    switch (s[14]) {
    case 0:
        Vec2_SetMirrored(s, 0xFFFFC400, 0);
        ChipSlot_IncUse(s, 2);
        Text_SelectBlobIdx(152);
        s[14]++;
        break;
    case 1:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        Vec2_SetMirrored(s, 0xFFFF9C00, 0);
        ChipSlot_IncUse(s, 1);
        s[14]++;
        break;
    case 2:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        ChipSlot_IncUse(s, 15);
        s[14]++;
        break;
    case 3: {
        u8 a17;
        u8 *p;
        u8 nib;
        if (Check119_Minus3_Le1(s) == 0)
            break;
        ChipSlot_IncUse(s, 16);
        Text_SelectBlobIdx(131);
        s[14]++;
        a17 = s[17];
        p = s;
        p += 35;
        nib = (u32)(p[0] << 28) >> 28;
        ChipInit_0801BBB4(a17, nib, 0xFFFFA600, 0xFFFFCD00, *(u8 **)(s + 44));
        break;
    }
    case 4:
        if (GetField17_U8(*(u8 **)(s + 44)) <= 6)
            break;
        ChipSlot_IncUse(s, 2);
        s[14]++;
        break;
    case 5:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        Vec2_SetMirrored(s, 0xFFFFC400, 0);
        ChipSlot_IncUse(s, 1);
        s[14]++;
        break;
    case 6:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        DecIfNonZero_18(*(u8 **)(s + 44));
        *(u8 **)(s + 44) = 0;
        Vec2_SetMirrored(s, 0xFFFFC400, 0);
        ChipSlot_IncUse(s, 0);
        e[4] = 0;
        SetBytes_08011F68(s, 0);
        break;
    default:
        break;
    }
    ChipSlot_Tick(s);
}
