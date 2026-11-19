/* Sub_080137e4 @ 0x080137E4 (288 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w60d_080137e4_MATCHED.c (registry: src/w60d_080137e4_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

extern void Vec2_SetMirrored(u8 *o, u32 x, u32 y);

extern void ChipSlot_IncUse(u8 *s, int idx);

extern void ChipSlot_Tick(u8 *s);

extern u16 Check119_Minus3_Le1(u8 *s);

extern void ChipInit_0801EBF0(int a, int b, int c, s16 d, s16 e);

extern void ChipInit_0801AA70(int a, int b, int c, int d, int e, u8 *f);

extern u8 GetField17_U8(u8 *p);

extern void DecIfNonZero_18(u8 *s);

extern void SetBytes_08011F68(u8 *s, u8 v);

__attribute__((section(".text.w60d_080137e4")))
void Sub_080137e4(u8 *s)
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
        ChipInit_0801EBF0(36, -1, ((u32)s[35] << 28) >> 28, -15360, 0);
        ChipSlot_IncUse(s, 9);
        s[18] = 5;
        s[14]++;
        break;
    case 2: {
        int a1;
        int nib;
        register u8 *base __asm__("r3");
        int idx;
        u8 *ep;
        int off0;
        int h0;
        int off;
        int h1;
        s[18]--;
        if (s[18] != 0)
            break;
        a1 = p[10];
        nib = ((u32)s[35] << 28) >> 28;
        base = (u8 *)0x08223ed8;
        __asm__ volatile("" : "+r"(base));
        idx = p[0];
        ep = (u8 *)(idx * 4);
        __asm__ volatile("add %0, %0, %1" : "+r"(ep) : "r"(base));
        off0 = 0;
        h0 = *(s16 *)(ep + off0);
        off = 2;
        h1 = *(s16 *)(ep + off);
        ChipInit_0801AA70(20, a1, nib, h0, h1, *(u8 **)(s + 44));
        s[14]++;
        break;
    }
    case 3:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        ChipSlot_IncUse(s, 10);
        s[14]++;
        break;
    case 4:
        if (GetField17_U8(*(u8 **)(s + 44)) <= 6)
            break;
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
