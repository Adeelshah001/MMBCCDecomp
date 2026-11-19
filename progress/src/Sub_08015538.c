/* Sub_08015538 @ 0x08015538 (268 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w60c_08015538_MATCHED.c (registry: src/w60c_08015538_MATCHED.c).
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

extern void ChipInit_0801AA70(u8 a, u8 b, u8 c, s16 d, s16 e, u8 *f);

extern u8 GetField17_U8(u8 *p);

extern void DecIfNonZero_18(u8 *p);

extern void SetBytes_08011F68(u8 *s, u8 v);

extern void ChipSlot_Tick(u8 *s);

extern const u8 Tbl_08223E52[];

extern const s16 TABLE_08223ED8[][2];

__attribute__((section(".text.w60c_08015538")))
void Sub_08015538(u8 *s)
{
    u8 *p = s;
    register u8 *q __asm__("r0");
    u8 d9arg;
    p += 124;
    switch (s[14]) {
    case 0:
        Vec2_SetMirrored(s, 0xFFFFC400, 0);
        __asm__ volatile("add r0, r5, #0");
        d9arg = 11;
        goto shared;
    case 1:
        if (Check119_Minus3_Le1(s) == 0)
            goto tail;
        q = s;
        d9arg = 12;
        goto shared;
    case 2: {
        const u8 *t;
        u8 idx;
        u8 a;
        u8 b;
        u8 nib;
        const s16 (*tblS)[2];
        const s16 *pair;
        if (Check119_Minus3_Le1(s) == 0)
            goto tail;
        t = Tbl_08223E52;
        idx = s[17];
        a = t[2 * idx];
        t++;
        b = t[2 * idx];
        nib = ((u32)s[35] << 28) >> 28;
        tblS = TABLE_08223ED8;
        pair = tblS[p[0]];
        ChipInit_0801AA70(a, b, nib, pair[0], pair[1], *(u8 **)(s + 44));
        q = s;
        d9arg = 13;
        goto shared;
    }
    case 3:
        if (Check119_Minus3_Le1(s) == 0)
            goto tail;
        q = s;
        d9arg = 0;
        /* fall through to shared */
    shared:
        ChipSlot_IncUse(q, d9arg);
        goto inc;
    inc:
        s[14]++;
        goto tail;
    case 4:
        if (GetField17_U8(*(u8 **)(s + 44)) <= 6)
            goto tail;
        DecIfNonZero_18(*(u8 **)(s + 44));
        {
            int z = 0;
            *(u32 *)(s + 44) = z;
            Vec2_SetMirrored(s, 0xFFFFC400, 0);
            ChipSlot_IncUse(s, 0);
            p[4] = z;
            SetBytes_08011F68(s, 0);
        }
        goto tail;
    default:
        goto tail;
    }
tail:
    ChipSlot_Tick(s);
}
