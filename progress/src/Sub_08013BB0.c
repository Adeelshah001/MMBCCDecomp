/* Sub_08013BB0 @ 0x08013BB0 (252 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w55d_08013bb0_MATCHED.c (registry: src/w55d_08013bb0_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

extern void Vec2_SetMirrored(u8 *o, s32 x, s32 y);

extern u16 Check119_Minus3_Le1(u8 *s);

extern void ChipInit_0801EBF0(int a, int b, int c, int d, int e);

extern void SetBit16(u32 v, int bit);

extern void ChipInit_080178A8(int a, int b, int c, int d, u32 e);

extern u8 GetField17_U8(u32 v);

extern void MaxAssign_17(u32 v, int n);

extern void DecIfNonZero_18(u32 v);

extern void ChipSlot_IncUse(u8 *s, int idx);

extern void SetBytes_08011F68(u8 *s, u8 v);

extern void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w55d_08013bb0")))
void Sub_08013BB0(u8 *s)
{
    u8 *p = s + 124;
    int mode;
    mode = s[14];
    if (mode == 1)
        goto c1;
    if (mode > 1)
        goto gt1;
    if (mode == 0)
        goto c0;
    goto tail;
gt1:
    if (mode == 2)
        goto c2;
    if (mode == 3)
        goto c3;
    goto tail;
c0:
    Vec2_SetMirrored(s, -15360, 0);
    ChipSlot_IncUse(s, 8);
    s[14]++;
    goto tail;
c1:
    if (Check119_Minus3_Le1(s) == 0)
        goto tail;
    ChipInit_0801EBF0(33, -1, ((u32)s[35] << 28) >> 28, -15360, 0);
    ChipSlot_IncUse(s, 9);
    s[14]++;
    goto tail;
c2:
    if (Check119_Minus3_Le1(s) == 0)
        goto tail;
    SetBit16(*(u32 *)(s + 44), 3);
    {
        int nib = ((u32)s[35] << 28) >> 28;
        ChipInit_080178A8(86, nib, -5120, -7680, *(u32 *)(s + 44));
    }
    ChipSlot_IncUse(s, 10);
    s[14]++;
    goto tail;
c3:
    if ((u8)GetField17_U8(*(u32 *)(s + 44)) <= 5)
        goto tail;
    MaxAssign_17(*(u32 *)(s + 44), 7);
    DecIfNonZero_18(*(u32 *)(s + 44));
    *(u32 *)(s + 44) = 0;
    Vec2_SetMirrored(s, -15360, 0);
    ChipSlot_IncUse(s, 0);
    p[4] = 0;
    SetBytes_08011F68(s, 0);
    goto tail;
tail:
    ChipSlot_Tick(s);
}
