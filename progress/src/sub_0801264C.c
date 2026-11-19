/* sub_0801264C @ 0x0801264C (372 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w73a_0801264c_MATCHED.c (registry: mmbcc/src/w73a_0801264c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

void *Memcpy_4DFA8(void *dst, const void *src, u32 len);

u32 Vec2_SetMirrored(u8 *s, u32 a, u32 b);

u16 Check119_Minus3_Le1(u8 *s);

void ChipSlot_IncUse(u8 *s, u32 a);

void ChipSlot_Tick(u8 *s);

u32 SetBit16(u32 a, u32 b);

u32 GetField17_U8(u32 a);

u32 DecIfNonZero_18(u32 a);

u32 SetBytes_08011F68(u8 *s, u32 a);

void ChipInit_0801AB94(u8 a, u32 b, s16 c, s16 d, u32 e);

void Text_SelectBlobIdx(u32 a);

extern u8 TABLE_08223ED8[];

__attribute__((section(".text.w73a_0801264c")))
void sub_0801264C(u8 *s)
{
    u8 buf[16];
    u8 *q;
    Memcpy_4DFA8(buf, (const void *)0x080E9BE4, 15);
    q = s + 124;
    switch (s[14]) {
    case 0:
        Vec2_SetMirrored(s, 0xFFFFC400, 0);
        ChipSlot_IncUse(s, 2);
        Text_SelectBlobIdx(152);
        s[14]++;
        break;
    case 1:
        if (Check119_Minus3_Le1(s)) {
            Vec2_SetMirrored(s, 0xFFFFFA00, 0);
            ChipSlot_IncUse(s, 1);
            s[14]++;
        }
        break;
    case 2:
        if (Check119_Minus3_Le1(s)) {
            ChipSlot_IncUse(s, 18);
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
            ChipSlot_IncUse(s, 19);
            SetBit16(*(u32 *)(s + 44), 3);
            bb = buf[s[17]];
            nb = ((u32)s[35] << 28) >> 28;
            tbl = TABLE_08223ED8;
            ent = (u16 *)(tbl + *q * 4);
            a = ent[0];
            b = ent[1];
            ChipInit_0801AB94(bb, nb, (s16)(a + 0x2200), (s16)(b - 0xF00),
                          *(u32 *)(s + 44));
            s[14]++;
        }
        break;
    case 4:
        if ((u8)GetField17_U8(*(u32 *)(s + 44)) > 6) {
            ChipSlot_IncUse(s, 2);
            s[14]++;
        }
        break;
    case 5:
        if (Check119_Minus3_Le1(s)) {
            Vec2_SetMirrored(s, 0xFFFFC400, 0);
            ChipSlot_IncUse(s, 1);
            s[14]++;
        }
        break;
    case 6:
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
