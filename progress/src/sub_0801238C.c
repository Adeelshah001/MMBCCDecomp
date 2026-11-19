/* sub_0801238C @ 0x0801238C (376 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w74a_0801238c_MATCHED.c (registry: mmbcc/src/w74a_0801238c_MATCHED.c).
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

u32 DecIfNonZero_18(u32 a);

u32 SetBytes_08011F68(u8 *s, u32 a);

void Text_SelectBlobIdx(u32 a);

void ChipInit_0801AA70(u8 a, u8 b, u32 c, s16 d, s16 e, u32 f);

void ChipInit_0801AB94(u8 a, u32 b, s16 c, s16 d, u32 e);

void ChipInit_0801BBB4(u8 a, u32 b, s16 c, s16 d, u32 e);

extern u8 TABLE_08223D47[];

extern u8 TABLE_08223D44[];

extern u8 TABLE_08223ED8[];

__attribute__((section(".text.w74a_0801238c")))
void sub_0801238C(u8 *s)
{
    u8 *q;
    q = s + 124;
    switch (s[14]) {
    case 0:
        Vec2_SetMirrored(s, 0xFFFFC400, 0);
        ChipSlot_IncUse(s, 15);
        s[14]++;
        break;
    case 1:
        if (Check119_Minus3_Le1(s)) {
            s[14]++;
            ChipSlot_IncUse(s, 16);
            if ((u8)(s[17] - 19) <= 5) {
                u8 *bp;
                int ix;
                u8 p0, p1;
                u32 nb;
                u8 *tbl;
                u16 *ent;
                s16 a, b;
                Text_SelectBlobIdx(131);
                bp = TABLE_08223D47;
                ix = (s[17] - 19) * 2;
                p0 = bp[ix];
                bp++;
                p1 = bp[ix];
                nb = ((u32)s[35] << 28) >> 28;
                tbl = TABLE_08223ED8;
                ent = (u16 *)(tbl + *q * 4);
                a = ent[0];
                b = ent[1];
                ChipInit_0801AA70(p0, p1, nb, a, b, *(u32 *)(s + 44));
            } else if ((u8)(s[17] - 16) <= 2) {
                u8 by;
                u32 nb;
                Text_SelectBlobIdx(146);
                by = TABLE_08223D44[s[17] - 16];
                nb = ((u32)s[35] << 28) >> 28;
                ChipInit_0801AB94(by, nb, 15360, -6400, *(u32 *)(s + 44));
            } else {
                u8 sv;
                u32 nb;
                u8 *tbl;
                u16 *ent;
                u16 a, b;
                Text_SelectBlobIdx(131);
                sv = s[17];
                nb = ((u32)s[35] << 28) >> 28;
                tbl = TABLE_08223ED8;
                ent = (u16 *)(tbl + *q * 4);
                a = ent[0];
                b = ent[1];
                ChipInit_0801BBB4(sv, nb, (s16)(a - 15360),
                              (s16)(b - 11520), *(u32 *)(s + 44));
            }
        }
        break;
    case 2:
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
