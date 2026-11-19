/* sub_080146C0 @ 0x080146C0 (316 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w68c_080146c0_MATCHED.c (registry: src/w68c_080146c0_MATCHED.c).
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

void PalModeSet_4DFC(u8 a);

u16 Text_SelectBlobIdx(u16 idx);

void ChipInit_080178A8(u32 a, u32 b, u32 c, u32 d, u8 *e);

u8 TestBit16(u8 *s, u8 bit);

u8 GetField17_U8(u8 *s);

void MaxAssign_17(u8 *s, u8 v);

void DecIfNonZero_18(u8 *s);

void SetBytes_08011F68(u8 *s, u8 v);

extern u8 gEwram_02003670[];

__attribute__((section(".text.w68c_080146c0")))
void sub_080146C0(u8 *s)
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
        SetBit16(*(u8 **)(s + 44), 3);
        PalModeSet_4DFC(2);
        Text_SelectBlobIdx(149);
        s[18] = 10;
        ChipSlot_IncUse(s, 9);
        s[14]++;
        break;
    case 2: {
        u8 *p = s;
        u8 nib;
        u8 m;
        int f;
        u8 b;
        if (--s[18] != 0)
            break;
        p += 35;
        nib = (u32)(p[0] << 28) >> 28;
        ChipInit_080178A8(130, nib, 0xFFFFEC00, 0, *(u8 **)(s + 44));
        if (TestBit16(*(u8 **)(s + 44), 0) != 0) {
            s[14]++;
            break;
        }
        m = 15;
        b = gEwram_02003670[0x11AF];
        f = 0xF0;
        gEwram_02003670[0x11AF] = (b & m) | f;
        s[14]++;
        break;
    }
    case 3:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        ChipSlot_IncUse(s, 10);
        s[14]++;
        break;
    case 4:
        if (GetField17_U8(*(u8 **)(s + 44)) <= 5)
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
