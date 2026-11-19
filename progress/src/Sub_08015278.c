/* Sub_08015278 @ 0x08015278 (256 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w39c_08015278_MATCHED.c (registry: mmbcc/src/w39c_08015278_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

extern void SetBit16(int v, int bit);

extern void Vec2_SetMirrored(u8 *s, int a, int b);

extern void ChipSlot_IncUse(u8 *s, int idx);

extern u16 Check119_Minus3_Le1(u8 *s);

extern void ChipInit_08017A44(int a, int b, int c, int d, int e);

extern void Text_SelectBlobIdx(int idx);

extern void DecIfNonZero_18(int v);

extern void SetBytes_08011F68(u8 *s, int v);

extern void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w39c_08015278")))
void Sub_08015278(u8 *s)
{
    u8 *p = s + 124;
    if (s[14] == 1)
        goto c1;
    if (s[14] > 1)
        goto gt1;
    if (s[14] == 0)
        goto c0;
    goto tail;
gt1:
    if (s[14] == 2)
        goto c2;
    if (s[14] == 3)
        goto c3;
    goto tail;
c0:
    SetBit16(*(u32 *)(s + 44), 3);
    Vec2_SetMirrored(s, -15360, 0);
    ChipSlot_IncUse(s, 11);
    s[14]++;
    goto tail;
c1:
    if (Check119_Minus3_Le1(s)) {
        s[14]++;
        ChipSlot_IncUse(s, 12);
    }
    goto tail;
c2:
    if (Check119_Minus3_Le1(s)) {
        int nib;
        int h0;
        int h1;
        int add;
        s[14]++;
        ChipSlot_IncUse(s, 13);
        nib = (int)(((u32)s[35] << 28) >> 28);
        {
            register u8 *base __asm__("r2");
            register u8 *tbp __asm__("r0");
            base = (u8 *)0x08223ED8;
            __asm__ volatile("" : "+r"(base));
            tbp = (u8 *)(p[0] * 4);
            __asm__ volatile("add %0, %0, %1" : "+r"(tbp) : "r"(base));
            h0 = *(u16 *)tbp;
            add = h0 + -14592;
            __asm__ volatile("lsl %0, %0, #16\n\tasr %0, %0, #16" : "+r"(add));
            h1 = *(s16 *)(tbp + 2);
            ChipInit_08017A44(4, nib, add, h1, *(u32 *)(s + 44));
        }
        Text_SelectBlobIdx(164);
    }
    goto tail;
c3:
    if (Check119_Minus3_Le1(s)) {
        DecIfNonZero_18(*(u32 *)(s + 44));
        *(u32 *)(s + 44) = 0;
        Vec2_SetMirrored(s, -15360, 0);
        ChipSlot_IncUse(s, 0);
        p[4] = 0;
        SetBytes_08011F68(s, 0);
    }
tail:
    ChipSlot_Tick(s);
}
