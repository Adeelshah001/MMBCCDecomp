/* sub_080147FC @ 0x080147FC (328 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w66a_080147fc_MATCHED.c (registry: src/w66a_080147fc_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

void Vec2_SetMirrored(u8 *o, s32 x, s32 y);

void ChipSlot_IncUse(u8 *s, u8 idx);

void ChipSlot_Tick(u8 *s);

u16 Check119_Minus3_Le1(u8 *s);

void SetBit16(u8 *s, u8 bit);

u16 Text_SelectBlobIdx(u16 idx);

u32 *ChipInit_0801B98C(u8 a, u8 b, u8 c, u16 d, u16 e, u8 *f);

u8 GetField17_U8(u8 *s);

void MaxAssign_17(u8 *s, u8 v);

void DecIfNonZero_18(u8 *s);

void SetBytes_08011F68(u8 *s, u8 v);

__attribute__((section(".text.w66a_080147fc")))
void sub_080147FC(u8 *s)
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
        ChipSlot_IncUse(s, 9);
        s[14]++;
        break;
    case 2: {
        u8 *p = s;
        u8 nib;
        if (Check119_Minus3_Le1(s) == 0)
            break;
        SetBit16(*(u8 **)(s + 44), 3);
        p += 35;
        nib = (u32)(p[0] << 28) >> 28;
        ChipInit_0801B98C(9, 0, nib, 0, 0, *(u8 **)(s + 44));
        nib = (u32)(p[0] << 28) >> 28;
        ChipInit_0801B98C(9, 1, nib, 0, 0, *(u8 **)(s + 44));
        nib = (u32)(p[0] << 28) >> 28;
        ChipInit_0801B98C(9, 2, nib, 0, 0, *(u8 **)(s + 44));
        s[10] &= 0xFE;
        Text_SelectBlobIdx(149);
        s[14]++;
        break;
    }
    case 3:
        if (GetField17_U8(*(u8 **)(s + 44)) <= 5)
            break;
        s[10] |= 1;
        ChipSlot_IncUse(s, 9);
        s[14]++;
        break;
    case 4:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        MaxAssign_17(*(u8 **)(s + 44), 7);
        s[14]++;
        break;
    case 5:
        DecIfNonZero_18(*(u8 **)(s + 44));
        *(u8 **)(s + 44) = 0;
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
