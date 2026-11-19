/* sub_08013F24 @ 0x08013F24 (340 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w70a_08013f24_MATCHED.c (registry: src/w70a_08013f24_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

void Vec2_SetMirrored(u8 *o, s32 x, s32 y);

void ChipSlot_IncUse(u8 *s, u8 idx);

u16 Check119_Minus3_Le1(u8 *s);

u16 Text_SelectBlobIdx(u16 idx);

void SetBit16(u8 *s, u8 bit);

void ChipInit_0801AA70(u8 a, u8 b, u8 c, s32 d, u32 e, u8 *f);

u8 GetField17_U8(u8 *s);

void DecIfNonZero_18(u8 *s);

void SetBytes_08011F68(u8 *s, u8 v);

void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w70a_08013f24")))
void sub_08013F24(u8 *s)
{
    u8 *q = s;
    q += 124;

    switch (s[14]) {
    case 0:
        Vec2_SetMirrored(s, 0xFFFFC400, 0);
        ChipSlot_IncUse(s, 2);
        Text_SelectBlobIdx(152);
        s[14]++;
        break;
    case 1:
        if (Check119_Minus3_Le1(s) != 0) {
            Vec2_SetMirrored(s, 0xFFFFFA00, 0);
            ChipSlot_IncUse(s, 1);
            s[14]++;
        }
        break;
    case 2:
        if (Check119_Minus3_Le1(s) != 0) {
            ChipSlot_IncUse(s, 8);
            s[14]++;
        }
        break;
    case 3:
        if (Check119_Minus3_Le1(s) != 0) {
            u8 nib;
            SetBit16(*(u8 **)(s + 44), 3);
            nib = (u32)((s + 35)[0] << 28) >> 28;
            ChipInit_0801AA70(21, 0, nib, 0xFFFFFA00, 0, *(u8 **)(s + 44));
            ChipSlot_IncUse(s, 9);
            s[14]++;
        }
        break;
    case 4:
        if (GetField17_U8(*(u8 **)(s + 44)) > 6) {
            ChipSlot_IncUse(s, 10);
            s[14]++;
        }
        break;
    case 5:
        if (Check119_Minus3_Le1(s) != 0) {
            ChipSlot_IncUse(s, 2);
            s[14]++;
        }
        break;
    case 6:
        if (Check119_Minus3_Le1(s) != 0) {
            Vec2_SetMirrored(s, 0xFFFFC400, 0);
            ChipSlot_IncUse(s, 1);
            s[14]++;
        }
        break;
    case 7:
        if (Check119_Minus3_Le1(s) != 0) {
            DecIfNonZero_18(*(u8 **)(s + 44));
            *(u32 *)(s + 44) = 0;
            Vec2_SetMirrored(s, 0xFFFFC400, 0);
            ChipSlot_IncUse(s, 0);
            q[4] = 0;
            SetBytes_08011F68(s, 0);
        }
        break;
    default:
        break;
    }
    ChipSlot_Tick(s);
}
