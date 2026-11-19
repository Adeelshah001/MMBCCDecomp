/* Sub_08012274 @ 0x08012274 (280 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w60d_08012274_MATCHED.c (registry: src/w60d_08012274_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

extern void SetBit16(u8 *s, int bit);

extern void Vec2_SetMirrored(u8 *o, u32 x, u32 y);

extern void ChipSlot_IncUse(u8 *s, int idx);

extern void ChipSlot_Tick(u8 *s);

extern u16 Check119_Minus3_Le1(u8 *s);

extern void ChipInit_08017A44(int a, int b, int c, int d, int e);

extern int Text_SelectBlobIdx(int idx);

extern void DecIfNonZero_18(u8 *s);

extern void SetBytes_08011F68(u8 *s, u8 v);

__attribute__((section(".text.w60d_08012274")))
void Sub_08012274(u8 *s)
{
    u8 *p = s + 124;
    switch (s[14]) {
    case 0:
        SetBit16(*(u8 **)(s + 44), 3);
        Vec2_SetMirrored(s, 0xffffc400, 0);
        ChipSlot_IncUse(s, 11);
        s[14]++;
        break;
    case 1:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        s[14]++;
        ChipSlot_IncUse(s, 12);
        break;
    case 2: {
        int a;
        int nib;
        register u8 *base __asm__("r2");
        int idx;
        u8 *ep;
        int h0;
        int add;
        int off;
        s16 h1;
        if (Check119_Minus3_Le1(s) == 0)
            break;
        a = s[17];
        nib = ((u32)s[35] << 28) >> 28;
        base = (u8 *)0x08223ed8;
        __asm__ volatile("" : "+r"(base));
        idx = p[0];
        ep = (u8 *)(idx * 4);
        __asm__ volatile("add %0, %0, %1" : "+r"(ep) : "r"(base));
        h0 = *(u16 *)ep;
        add = h0 + -14592;
        __asm__ volatile("lsl %0, %0, #16\n\tasr %0, %0, #16" : "+r"(add));
        off = 2;
        h1 = *(s16 *)(ep + off);
        ChipInit_08017A44(a, nib, add, h1, *(u32 *)(s + 44));
        Text_SelectBlobIdx(164);
        s[18] = 6;
        s[14]++;
        break;
    }
    case 3:
        s[18]--;
        if (s[18] != 0)
            break;
        ChipSlot_IncUse(s, 13);
        s[14]++;
        break;
    case 4:
        if (Check119_Minus3_Le1(s) == 0)
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
