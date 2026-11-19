/* Sub_08015644 @ 0x08015644 (232 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w51a_08015644_MATCHED.c (registry: src/w51a_08015644_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern void ChipSlot_IncUse(u8 *s, u8 n);

extern void ChipSlot_Tick(u8 *s);

extern void Vec2_SetMirrored(u8 *o, int x, int y);

extern short Check119_Minus3_Le1(u8 *s);

extern void SetBytes_08011F68(u8 *s, int a);

extern u8 GetField17_U8(u32 a);

extern void DecIfNonZero_18(u32 a);

extern void ChipInit_0801AA70(int a, int b, int c, int d, int e, u32 f);

extern u8 tbl_08223E60[][2];

extern s16 TABLE_08223ED8[][2];

__attribute__((section(".text.w51a_08015644")))
void Sub_08015644(u8 *s)
{
    u8 *t = s + 124;
    switch (s[14]) {
    case 0:
        ChipSlot_IncUse(s, 2);
        s[14]++;
        break;
    case 1: {
        int b0, b1, nib;
        s16 (*tp)[2];
        s16 *e;
        if (Check119_Minus3_Le1(s) == 0)
            break;
        b0 = tbl_08223E60[s[17]][0];
        b1 = tbl_08223E60[s[17]][1];
        nib = (int)(((u32)s[35] << 28) >> 28);
        tp = TABLE_08223ED8;
        e = tp[t[0]];
        ChipInit_0801AA70(b0, b1, nib, e[0], e[1], *(u32 *)(s + 44));
        s[10] &= 0xfe;
        s[14]++;
        break;
    }
    case 2:
        if (GetField17_U8(*(u32 *)(s + 44)) <= 6)
            break;
        s[10] |= 1;
        ChipSlot_IncUse(s, 1);
        s[14]++;
        break;
    case 3:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        DecIfNonZero_18(*(u32 *)(s + 44));
        *(u32 *)(s + 44) = 0;
        Vec2_SetMirrored(s, -15360, 0);
        ChipSlot_IncUse(s, 0);
        t[4] = 0;
        SetBytes_08011F68(s, 0);
        break;
    default:
        break;
    }
    ChipSlot_Tick(s);
}
