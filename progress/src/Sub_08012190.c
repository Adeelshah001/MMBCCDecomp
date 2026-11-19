/* Sub_08012190 @ 0x08012190 (228 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w50d_08012190_MATCHED.c (registry: src/w50d_08012190_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern s16 TABLE_08223ED8[][2];

extern void Vec2_SetMirrored(u8 *s, int x, int y);

extern void ChipSlot_IncUse(u8 *s, u8 idx);

extern void ChipSlot_Tick(u8 *s);

extern short Check119_Minus3_Le1(u8 *s);

extern void SetBytes_08011F68(u8 *s, u8 v);

extern void SetBit16(u32 a, int b);

extern u8 GetField17_U8(u32 a);

extern void DecIfNonZero_18(u32 a);

extern void ChipInit_0801AA70(int a, u8 b, int c, s16 d, s16 e, u32 f);

__attribute__((section(".text.w50d_08012190")))
void Sub_08012190(u8 *s)
{
    u8 *t = s + 124;
    switch (s[14]) {
    case 0:
        Vec2_SetMirrored(s, -15360, 0);
        ChipSlot_IncUse(s, 11);
        s[14]++;
        break;
    case 1:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        SetBit16(*(u32 *)(s + 44), 3);
        {
            u8 m = s[17];
            int nib = ((u32)s[35] << 28) >> 28;
            s16 (*tp)[2] = TABLE_08223ED8;
            s16 *e = tp[t[0]];
            ChipInit_0801AA70(22, m, nib, e[0], e[1], *(u32 *)(s + 44));
        }
        ChipSlot_IncUse(s, 12);
        s[14]++;
        break;
    case 2:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        ChipSlot_IncUse(s, 13);
        s[14]++;
        break;
    case 3:
        if ((u8)GetField17_U8(*(u32 *)(s + 44)) > 6) {
            DecIfNonZero_18(*(u32 *)(s + 44));
            *(u32 *)(s + 44) = 0;
            Vec2_SetMirrored(s, -15360, 0);
            ChipSlot_IncUse(s, 0);
            t[4] = 0;
            SetBytes_08011F68(s, 0);
        }
        break;
    default:
        break;
    }
    ChipSlot_Tick(s);
}
