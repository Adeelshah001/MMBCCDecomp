/* Sub_08014944 @ 0x08014944 (256 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w56d_08014944_MATCHED.c (registry: src/w56d_08014944_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

typedef struct { s16 a; s16 b; } T2;

extern void Vec2_SetMirrored(u8 *s, int a, int b);

extern void ChipSlot_IncUse(u8 *s, int idx);

extern u16 Check119_Minus3_Le1(u8 *s);

extern void ChipInit_0801CD50(int a, int b, int c, s16 d, s16 e, u32 f);

extern u8 GetField17_U8(u32 v);

extern void DecIfNonZero_18(u32 v);

extern void SetBytes_08011F68(u8 *s, int v);

extern void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w56d_08014944")))
void Sub_08014944(u8 *s)
{
    u8 *p = s + 124;
    u32 s44;
    switch (s[14]) {
    case 0:
        Vec2_SetMirrored(s, -15360, 0);
        ChipSlot_IncUse(s, 11);
        goto inc;
    case 1:
        if ((u16)Check119_Minus3_Le1(s) != 0) {
            int nib;
            T2 *tbl;
            T2 t;
            nib = ((unsigned)s[35] << 28) >> 28;
            tbl = (T2 *)0x08223ed8;
            __asm__ volatile("" : "+r"(tbl));
            t = tbl[p[0]];
            ChipInit_0801CD50(11, 0, nib, t.a, t.b, *(u32 *)(s + 44));
            ChipSlot_IncUse(s, 9);
            goto inc;
        }
        break;
    case 2:
        if ((u16)Check119_Minus3_Le1(s) != 0) {
            ChipSlot_IncUse(s, 10);
            goto inc;
        }
        break;
    case 3:
        if ((u16)Check119_Minus3_Le1(s) == 0)
            goto tail;
    inc:
        s[14]++;
        goto tail;
    case 4:
        if ((u8)GetField17_U8(*(u32 *)(s + 44)) > 6) {
            DecIfNonZero_18(*(u32 *)(s + 44));
            *(u32 *)(s + 44) = 0;
            Vec2_SetMirrored(s, -15360, 0);
            ChipSlot_IncUse(s, 0);
            p[4] = 0;
            SetBytes_08011F68(s, 0);
        }
        break;
    default:
        break;
    }
    goto tail;
tail:
    ChipSlot_Tick(s);
}
