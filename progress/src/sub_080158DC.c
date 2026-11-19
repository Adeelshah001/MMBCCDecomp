/* sub_080158DC @ 0x080158DC (364 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w194f_080158dc_MATCHED.c (registry: src/w194f_080158dc_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

u32 Vec2_SetMirrored(u8 *s, u32 a, u32 b);

u16 Check119_Minus3_Le1(u8 *s);

void ChipSlot_IncUse(u8 *s, u32 a);

void ChipSlot_Tick(u8 *s);

u32 SetBit16(u32 a, u32 b);

u32 GetField17_U8(u32 a);

u32 DecIfNonZero_18(u32 a);

u32 SetBytes_08011F68(u8 *s, u32 a);

void ChipInit_0801AB94(u8 a, u32 b, s16 c, s16 d, u32 e);

extern u8 TABLE_08223ED8[];

__attribute__((section(".text.w194f_080158dc_bppinr0_oldO2")))
void sub_080158DC(u8 *s)
{
    u8 buf[4];
    u8 *q;
    register u8 *bp __asm__("r0") = &buf[0];
    *bp = 48;
    q = s + 124;
    switch (s[14]) {
    case 0:
        Vec2_SetMirrored(s, 0xFFFFC400, 0);
        ChipSlot_IncUse(s, 2);
        s[14]++;
        break;
    case 1:
        if (Check119_Minus3_Le1(s)) {
            Vec2_SetMirrored(s, 0x1400, 0);
            ChipSlot_IncUse(s, 1);
            s[14]++;
        }
        break;
    case 2:
        if (Check119_Minus3_Le1(s)) {
            ChipSlot_IncUse(s, 15);
            s[14]++;
        }
        break;
    case 3:
        if (Check119_Minus3_Le1(s)) {
            u8 bb;
            u32 nb;
            u8 *tbl;
            u16 *ent;
            u16 a;
            u16 b;
            SetBit16(*(u32 *)(s + 44), 3);
            bb = buf[s[17]];
            nb = ((u32)s[35] << 28) >> 28;
            tbl = TABLE_08223ED8;
            ent = (u16 *)(tbl + *q * 4);
            a = ent[0];
            b = ent[1];
            ChipInit_0801AB94(bb, nb, (s16)(a + 0x2200), (s16)(b - 0xF00),
                          *(u32 *)(s + 44));
            ChipSlot_IncUse(s, 16);
            s[14]++;
        }
        break;
    case 4:
        if (Check119_Minus3_Le1(s))
            s[14]++;
        break;
    case 5:
        if ((u8)GetField17_U8(*(u32 *)(s + 44)) > 6) {
            ChipSlot_IncUse(s, 2);
            s[14]++;
        }
        break;
    case 6:
        if (Check119_Minus3_Le1(s)) {
            Vec2_SetMirrored(s, 0xFFFFC400, 0);
            ChipSlot_IncUse(s, 1);
            s[14]++;
        }
        break;
    case 7:
        if (Check119_Minus3_Le1(s)) {
            DecIfNonZero_18(*(u32 *)(s + 44));
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
