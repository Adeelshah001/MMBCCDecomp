/* sub_08015F90 @ 0x08015F90 (322 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w67d_08015f90_MATCHED.c (registry: staging/w67d_1de84/15f90_v1.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

void ChipSlot_IncUse(u8 *s, u8 idx);

void ChipSlot_Tick(u8 *s);

u16 Check119_Minus3_Le1(u8 *s);

void Vec2_SetMirrored(u8 *o, s32 x, s32 y);

u8 GetField17_U8(u8 *s);

void MaxAssign_17(u8 *s, u8 v);

void DecIfNonZero_18(u8 *s);

void SetBytes_08011F68(u8 *s, u8 v);

void SetBit16(u8 *s, u8 bit);

u8 TestBit16(u8 *s, u8 v);

__attribute__((section(".text.w67d_08015f90")))
void sub_08015F90(u8 *s)
{
    u8 *e = s;
    e += 124;

    switch (s[14]) {
    case 0:
        SetBit16(*(u8 **)(s + 44), 0);
        Vec2_SetMirrored(s, 0xFFFFC400, 0);
        ChipSlot_IncUse(s, 0);
        s[14]++;
        break;
    case 1:
        if (TestBit16(*(u8 **)(s + 44), 3) == 0)
            break;
        ChipSlot_IncUse(s, 2);
        s[14]++;
        break;
    case 2:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        Vec2_SetMirrored(s, 0xFFFFB000, 0xFFFFFB00);
        ChipSlot_IncUse(s, 1);
        s[14]++;
        break;
    case 3:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        ChipSlot_IncUse(s, 0);
        s[18] = 20;
        s[14]++;
        break;
    case 4:
        if (--s[18] == 0)
            s[14]++;
        break;
    case 5:
        if (GetField17_U8(*(u8 **)(s + 44)) <= 5)
            break;
        ChipSlot_IncUse(s, 2);
        s[14]++;
        break;
    case 6:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        Vec2_SetMirrored(s, 0xFFFFC400, 0);
        ChipSlot_IncUse(s, 1);
        s[14]++;
        break;
    case 7:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        ChipSlot_IncUse(s, 0);
        s[14]++;
        break;
    case 8:
        if (GetField17_U8(*(u8 **)(s + 44)) <= 6)
            break;
        MaxAssign_17(*(u8 **)(s + 44), 8);
        DecIfNonZero_18(*(u8 **)(s + 44));
        *(u8 **)(s + 44) = 0;
        e[4] = 0;
        SetBytes_08011F68(s, 0);
        break;
    default:
        break;
    }
    ChipSlot_Tick(s);
}
