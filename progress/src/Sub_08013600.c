/* Sub_08013600 @ 0x08013600 (264 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w60c_08013600_MATCHED.c (registry: src/w60c_08013600_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;
typedef signed int s32;

extern void Vec2_SetMirrored(u8 *s, s32 x, s32 y);

extern void ChipSlot_IncUse(u8 *s, u8 idx);

extern s16 Check119_Minus3_Le1(u8 *s);

extern void SetBit16(u8 *p, u8 bit);

extern u32 *ChipInit_080178A8(u8 a, u8 b, s16 c, s16 d, u8 *e);

extern u8 GetField17_U8(u8 *p);

extern void MaxAssign_17(u8 *p, u8 v);

extern void DecIfNonZero_18(u8 *p);

extern void SetBytes_08011F68(u8 *s, u8 v);

extern void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w60c_08013600")))
void Sub_08013600(u8 *s)
{
    u8 *p = s;
    p += 124;
    switch (s[14]) {
    case 0:
        Vec2_SetMirrored(s, 0xFFFFC400, 0);
        ChipSlot_IncUse(s, 8);
        goto inc;
    case 1:
        if (Check119_Minus3_Le1(s) == 0)
            goto tail;
        ChipSlot_IncUse(s, 9);
        goto inc;
    case 2:
        if (Check119_Minus3_Le1(s) == 0)
            goto tail;
        ChipSlot_IncUse(s, 10);
        goto inc;
    case 3:
        if (Check119_Minus3_Le1(s) == 0)
            goto tail;
        SetBit16(*(u8 **)(s + 44), 3);
        ChipInit_080178A8(85, ((u32)s[35] << 28) >> 28, -5120, 0, *(u8 **)(s + 44));
        goto inc;
    case 4:
        if (GetField17_U8(*(u8 **)(s + 44)) <= 5)
            goto tail;
        MaxAssign_17(*(u8 **)(s + 44), 7);
        goto inc;
    inc:
        s[14]++;
        goto tail;
    case 5:
        DecIfNonZero_18(*(u8 **)(s + 44));
        {
        int z = 0;
        *(u32 *)(s + 44) = z;
        Vec2_SetMirrored(s, 0xFFFFC400, 0);
        ChipSlot_IncUse(s, 0);
        p[4] = z;
        SetBytes_08011F68(s, 0);
        goto tail;
    }
    default:
        goto tail;
    }
tail:
    ChipSlot_Tick(s);
}
