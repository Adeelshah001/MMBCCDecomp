/* Sub_0801572C @ 0x0801572C (236 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w38a_0801572c_MATCHED.c (registry: mmcc/src/w38a_0801572c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

extern void Vec2_SetMirrored(u8 *s, int a, int b);

extern void ChipSlot_IncUse(u8 *s, int idx);

extern u16 Check119_Minus3_Le1(u8 *s);

extern void ChipInit_0801CD50(int a, int b, int c, int d, int e, int f);

extern u8 GetField17_U8(int v);

extern void DecIfNonZero_18(int v);

extern void SetBytes_08011F68(u8 *s, u8 v);

extern void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w38a_0801572c")))
void Sub_0801572C(u8 *s)
{
    u8 *p = s + 124;
    int mode = s[14];
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
    ChipSlot_IncUse(s, 11);
    goto inc2;
c1:
    if (Check119_Minus3_Le1(s) == 0)
        goto tail;
    ChipSlot_IncUse(s, 12);
    goto inc2;
c2:
    if (Check119_Minus3_Le1(s) == 0)
        goto tail;
    {
        u8 *t1 = (u8 *)0x08223E62;
        u8 *b1;
        int a0, a1;
        int nib;
        register u8 *base2 __asm__("r3");
        u8 *tb;
        int o0 = 0;
        int o1 = 2;
        int h0, h1;
        a0 = t1[s[17] * 2];
        b1 = t1 + 1;
        a1 = b1[s[17] * 2];
        nib = (int)(((u32)s[35] << 28) >> 28);
        base2 = (u8 *)0x08223ED8;
        __asm__ volatile("" : "+r"(base2));
        {
            int off = p[0] * 4;
            __asm__ volatile("add %0, %1, %2" : "=r"(tb) : "r"(off), "r"(base2));
        }
        __asm__ volatile("" : "+r"(tb));
        h0 = *(s16 *)(tb + o0);
        h1 = *(s16 *)(tb + o1);
        ChipInit_0801CD50(a0, a1, nib, h0, h1, *(u32 *)(s + 44));
    }
inc2:
    s[14]++;
    goto tail;
c3:
    if ((u8)GetField17_U8(*(u32 *)(s + 44)) <= 6)
        goto tail;
    DecIfNonZero_18(*(u32 *)(s + 44));
    *(u32 *)(s + 44) = 0;
    Vec2_SetMirrored(s, -15360, 0);
    ChipSlot_IncUse(s, 0);
    p[4] = 0;
    SetBytes_08011F68(s, 0);
tail:
    ChipSlot_Tick(s);
}
