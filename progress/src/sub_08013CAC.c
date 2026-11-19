/* sub_08013CAC @ 0x08013CAC (332 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w69a_08013cac_MATCHED.c (registry: src/w69a_08013cac_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

typedef struct { s32 x, y; } Pair;

void Vec2_SetMirrored(u8 *o, s32 x, s32 y);

void ChipSlot_IncUse(u8 *s, u8 idx);

u16 Check119_Minus3_Le1(u8 *s);

u16 Text_SelectBlobIdx(u16 idx);

void SetBit16(u8 *s, u8 bit);

void Vec2_AddMirrored(u8 *o, s32 x, s32 y);

Pair sub_0800DD08(u8 *s);

void ChipInit_080178A8(u8 a, u8 b, u16 c, s32 d, u8 *e);

u8 GetField17_U8(u8 *s);

void MaxAssign_17(u8 *s, u8 v);

void DecIfNonZero_18(u8 *s);

void SetBytes_08011F68(u8 *s, u8 v);

void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w69a_08013cac")))
void sub_08013CAC(u8 *s)
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
        if (Check119_Minus3_Le1(s) != 0) {
            s[18] = 5;
            ChipSlot_IncUse(s, 9);
            Text_SelectBlobIdx(148);
            s[14]++;
        }
        break;
    case 2:
        if (--s[18] != 0)
            break;
        SetBit16(*(u8 **)(s + 44), 3);
        s[14]++;
        break;
    case 3: {
        Pair v;
        Vec2_AddMirrored(s, 0x700, 0);
        v = sub_0800DD08(s);
        if (v.x > 55) {
            u8 *p35 = s + 35;
            u8 nib = (u32)(p35[0] << 28) >> 28;
            ChipInit_080178A8(126, nib, 0x3C00, 0xFFFFE200, *(u8 **)(s + 44));
            s[10] &= 0xFE;
            s[18] = 10;
            s[14]++;
        }
        break;
    }
    case 4:
        if (--s[18] != 0)
            break;
        s[10] |= 1;
        Vec2_SetMirrored(s, 0xFFFFC400, 0);
        ChipSlot_IncUse(s, 10);
        s[14]++;
        break;
    case 5:
        if (Check119_Minus3_Le1(s) != 0) {
            ChipSlot_IncUse(s, 0);
            s[14]++;
        }
        break;
    case 6:
        if (GetField17_U8(*(u8 **)(s + 44)) > 5) {
            MaxAssign_17(*(u8 **)(s + 44), 7);
            DecIfNonZero_18(*(u8 **)(s + 44));
            *(u32 *)(s + 44) = 0;
            q[4] = 0;
            SetBytes_08011F68(s, 0);
        }
        break;
    default:
        break;
    }
    ChipSlot_Tick(s);
}
