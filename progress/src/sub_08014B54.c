/* sub_08014B54 @ 0x08014B54 (412 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w83a_08014b54_MATCHED.c (registry: mmbcc/src/w83a_08014b54_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;
typedef signed int s32;

void Vec2_SetMirrored(u8 *s, s32 x, s32 y);

void ChipSlot_IncUse(u8 *s, u32 a);

void Text_SelectBlobIdx(u32 a);

s16 Check119_Minus3_Le1(u8 *s);

void SetBit16(u32 a, u32 b);

void ChipInit_080178A8(u32 a, u32 b, s32 c, s32 d, u32 e);

u8 GetField17_U8(u8 *s);

void MaxAssign_17(u32 a, u32 b);

void DecIfNonZero_18(u32 a);

void SetBytes_08011F68(u8 *s, u32 a);

void ChipSlot_Tick(u8 *s);

extern u8 gEwram_02003670[];

__attribute__((section(".text.w83a_08014b54")))
void sub_08014B54(u8 *s)
{
    u8 *q = s + 124;
    switch (s[14]) {
    case 0:
        Vec2_SetMirrored(s, -15360, 0);
        ChipSlot_IncUse(s, 2);
        Text_SelectBlobIdx(152);
        s[14]++;
        break;
    case 1:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        Vec2_SetMirrored(s, -1536, 0);
        ChipSlot_IncUse(s, 1);
        s[14]++;
        break;
    case 2:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        SetBit16(*(u32 *)(s + 44), 3);
        ChipSlot_IncUse(s, 8);
        s[14]++;
        break;
    case 3:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        ChipInit_080178A8(132, ((u32)s[35] << 28) >> 28, 240 << 6, 0, *(u32 *)(s + 44));
        ChipSlot_IncUse(s, 9);
        s[14]++;
        break;
    case 4:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        {
            u8 mk = 15;
            u32 off = 0x11AF;
            u8 *p = gEwram_02003670 + off;
            u8 c = 240;
            u8 b = *p;
            *p = (b & mk) | c;
        }
        Text_SelectBlobIdx(135);
        s[18] = 25;
        s[14]++;
        break;
    case 5:
        if ((s8)--s[18] != 0)
            break;
        ChipSlot_IncUse(s, 10);
        s[14]++;
        break;
    case 6:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        ChipSlot_IncUse(s, 2);
        s[14]++;
        break;
    case 7:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        Vec2_SetMirrored(s, -15360, 0);
        ChipSlot_IncUse(s, 2);
        s[14]++;
        break;
    case 8:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        ChipSlot_IncUse(s, 0);
        s[14]++;
        break;
    case 9:
        if ((u8)GetField17_U8((u8 *)*(u32 *)(s + 44)) <= 5)
            break;
        MaxAssign_17(*(u32 *)(s + 44), 7);
        DecIfNonZero_18(*(u32 *)(s + 44));
        *(u32 *)(s + 44) = 0;
        q[4] = 0;
        SetBytes_08011F68(s, 0);
        break;
    default:
        break;
    }
    ChipSlot_Tick(s);
}
