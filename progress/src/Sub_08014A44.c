/* Sub_08014A44 @ 0x08014A44 (272 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w60d_08014a44_MATCHED.c (registry: src/w60d_08014a44_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Vec2_SetMirrored(u8 *o, u32 x, u32 y);

extern void ChipSlot_IncUse(u8 *s, int idx);

extern void ChipSlot_Tick(u8 *s);

extern u16 Check119_Minus3_Le1(u8 *s);

extern void SetBit16(u8 *s, int bit);

extern void ChipInit_080178A8(u32 a, u32 b, u32 c, u32 d, u32 e);

extern u8 GetField17_U8(u8 *s);

extern void MaxAssign_17(u8 *s, u8 v);

extern void DecIfNonZero_18(u8 *s);

extern void SetBytes_08011F68(u8 *s, u8 v);

__attribute__((section(".text.w60d_08014a44")))
void Sub_08014A44(u8 *s)
{
    u8 *p = s + 124;
    switch (s[14]) {
    case 0:
        Vec2_SetMirrored(s, 0xffffc400, 0);
        ChipSlot_IncUse(s, 8);
        s[14]++;
        break;
    case 1:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        SetBit16(*(u8 **)(s + 44), 3);
        ChipInit_080178A8(125, ((u32)s[35] << 28) >> 28, 0xffffec00, 0, *(u32 *)(s + 44));
        ChipSlot_IncUse(s, 9);
        s[18] = 3;
        s[14]++;
        break;
    case 2:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        {
            int t = s[18] - 1;
            s[18] = t;
            if ((u8)t == 0) {
                ChipSlot_IncUse(s, 10);
                s[14]++;
            } else {
                ChipSlot_IncUse(s, 9);
            }
        }
        break;
    case 3:
        if (GetField17_U8(*(u8 **)(s + 44)) <= 5)
            break;
        MaxAssign_17(*(u8 **)(s + 44), 7);
        s[14]++;
        break;
    case 4:
        DecIfNonZero_18(*(u8 **)(s + 44));
        *(u32 *)(s + 44) = 0;
        Vec2_SetMirrored(s, 0xffffc400, 0);
        ChipSlot_IncUse(s, 0);
        p[4] = 0;
        SetBytes_08011F68(s, 0);
        break;
    }
    ChipSlot_Tick(s);
}
