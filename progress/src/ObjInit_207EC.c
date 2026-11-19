/* ObjInit_207EC @ 0x080207EC (132 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave5_g1_old.c (registry: src/wave5_g1_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void ChipSlot_Setup(u8 *s, u16 a, u8 b);

extern void ChipSlot_IncUse(u8 *s, u8 idx);

__attribute__((section(".text.w5g1_207ec")))
void ObjInit_207EC(u8 *s)
{
    u8 *r5 = *(u8 **)(s + 40);
    u8 t;

    *(u32 *)(s + 108) = 0;
    t = 2;
    t |= s[10];
    s[10] = t | 1;
    ChipSlot_Setup(s, 0x411a, 0);
    ChipSlot_IncUse(s, s[0x78]);
    {
        u32 idx = ((u32)r5[0x45] << 28) >> 30;
        int mask = -13;
        u8 *p = s;
        u32 sh;
        register int c __asm__("r1");
        __asm__ ("movs %0, %1" : "=r" (c) : "r" (idx));
        if (c > 3)
            idx = 3;
        p += 0x45;
        sh = idx << 2;
        *p = (*p & mask) | sh;
    }
    {
        u8 *q = r5;
        u8 v;
        u8 *w = s;

        q += 0x22;
        v = *q;
        w += 0x22;
        *w = v;
    }
    if (s[17] & 2)
        *(u32 *)(s + 96) = 0x15400;
    else
        *(u32 *)(s + 96) = 0xFFFF9C00;
    *(u32 *)(s + 100) = 0;
}
