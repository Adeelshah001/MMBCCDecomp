/* sub_08012B80 @ 0x08012B80 (424 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w194f_08012b80_MATCHED.c (registry: src/w194f_08012b80_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;
typedef signed int s32;

s16 Check119_Minus3_Le1(u8 *s);

void Vec2_SetMirrored(u8 *s, s32 x, s32 y);

void ChipSlot_IncUse(u8 *s, u32 a);

void ChipSlot_IncUse(u8 *s, u32 a);

void Text_SelectBlobIdx(u32 a);

void SetBit16(u32 a, u32 b);

void ChipInit_0801AB94(u32 a, u32 b, s32 c, s32 d, u32 e);

void MaxAssign_17(u32 a, u32 b);

void ChipInit_0801B98C(u32 a, u32 b, u32 c, s32 d, s32 e, u32 f);

void DecIfNonZero_18(u32 a);

void SetBytes_08011F68(u8 *s, u32 a);

void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w194f_08012b80_v10_alias_oldO2")))
void sub_08012B80(u8 *s)
{
    u8 *p124 = s + 124;
    switch (s[14]) {
    case 0:
        Vec2_SetMirrored(s, -15360, 0);
        ChipSlot_IncUse(s, 2);
        Text_SelectBlobIdx(152);
        break;
    case 1:
        if (Check119_Minus3_Le1(s) == 0)
            goto epi;
        Vec2_SetMirrored(s, 1024, 0);
        ChipSlot_IncUse(s, 1);
        break;
    case 2:
        if (Check119_Minus3_Le1(s) == 0)
            goto epi;
        SetBit16(*(u32 *)(s + 44), 3);
        ChipSlot_IncUse(s, 9);
        break;
    case 3:
        if (Check119_Minus3_Le1(s) == 0)
            goto epi;
        ChipInit_0801AB94(30, ((u32)s[35] << 28) >> 28, 15360, -7168, *(u32 *)(s + 44));
        ChipSlot_IncUse(s, 10);
        MaxAssign_17(*(u32 *)(s + 44), 1);
        break;
    case 4:
        if (Check119_Minus3_Le1(s) == 0)
            goto epi;
        ChipSlot_IncUse(s, 2);
        break;
    case 5:
        if (Check119_Minus3_Le1(s) == 0)
            goto epi;
        ChipInit_0801B98C(10, 0, ((u32)s[35] << 28) >> 28, -15360, -25600, *(u32 *)(s + 44));
        Vec2_SetMirrored(s, -15360, 0);
        ChipSlot_IncUse(s, 1);
        break;
    case 6:
        if (Check119_Minus3_Le1(s) == 0)
            goto epi;
        MaxAssign_17(*(u32 *)(s + 44), 8);
        ChipSlot_IncUse(s, 0);
        s[18] = 30;
        break;
    case 7:
        goto c7;
    default:
        goto epi;
    }
    s[14]++;
    goto epi;
c7:
        if ((s8)--s[18] != 0)
            goto epi;
        DecIfNonZero_18(*(u32 *)(s + 44));
        *(u32 *)(s + 44) = 0;
        Vec2_SetMirrored(s, -15360, 0);
        ChipSlot_IncUse(s, 0);
        p124[4] = 0;
        SetBytes_08011F68(s, 0);
        goto epi;
epi:
    ChipSlot_Tick(s);
}
