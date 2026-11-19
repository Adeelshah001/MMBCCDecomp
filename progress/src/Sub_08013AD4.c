/* Sub_08013AD4 @ 0x08013AD4 (220 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w38a_08013ad4_MATCHED.c (registry: mmcc/src/w38a_08013ad4_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

extern void Vec2_SetMirrored(u8 *o, s32 x, s32 y);

extern u16 Check119_Minus3_Le1(u8 *s);

extern void SetBit16(u8 *s, int bit);

extern void ChipInit_0801AA70(int a, int b, int c, int d, int e, u8 *f);

extern u8 GetField17_U8(u8 *p);

extern void DecIfNonZero_18(u8 *s);

extern void ChipSlot_IncUse(u8 *s, int idx);

extern void SetBytes_08011F68(u8 *s, u8 v);

extern void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w38a_08013ad4")))
void Sub_08013AD4(u8 *s)
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
    SetBit16(*(u8 **)(s + 44), 3);
    ChipInit_0801AA70(18, 0, ((u32)s[35] << 28) >> 28, -11520, -8960,
        *(u8 **)(s + 44));
    ChipSlot_IncUse(s, 9);
    s[14]++;
    goto tail;
c2:
    if (Check119_Minus3_Le1(s) == 0)
        goto tail;
    ChipSlot_IncUse(s, 10);
    s[14]++;
    goto tail;
c3:
    if ((u8)GetField17_U8(*(u8 **)(s + 44)) <= 6)
        goto tail;
    DecIfNonZero_18(*(u8 **)(s + 44));
    *(u8 **)(s + 44) = 0;
    Vec2_SetMirrored(s, -15360, 0);
    ChipSlot_IncUse(s, 0);
    p[4] = 0;
    SetBytes_08011F68(s, 0);
    goto tail;
tail:
    ChipSlot_Tick(s);
}
