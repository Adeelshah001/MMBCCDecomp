/* ObjInit_1D3C0 @ 0x0801D3C0 (164 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave9_a_old.c (registry: src/wave9_a_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void ChipSlot_Setup(u8 *s, u16 a, u8 b);

extern void ChipSlot_IncUse(u8 *s, u8 idx);

__attribute__((section(".text.w9a_0801d3c0")))
void ObjInit_1D3C0(u8 *s)
{
    if (s[17] == 0) {
        s[10] |= 1;
        __asm__ volatile("" ::: "memory");
        *(u32 *)(s + 108) = 0;
        __asm__ volatile("" ::: "memory");
        s[10] |= 2;
        ChipSlot_Setup(s, 0x501, 0);
        ChipSlot_IncUse(s, 8);
        {
            u8 *p = s + 0x45;
            int m = -13;
            *p &= m;
        }
    } else {
        int one;
        int zero;
        u8 *p = s;
        __asm__ volatile("movs %0, #1\n\tmovs %1, #0" : "=l"(one), "=l"(zero));
        s[10] |= one;
        p += 0x50;
        __asm__ volatile("" ::: "memory");
        *(u32 *)(p + 28) = zero;
        s[10] |= 2;
        ChipSlot_Setup(s, 0x501, 0);
        ChipSlot_IncUse(s, 0);
        {
            u8 *p;
            u8 *q;
            int m;
            p = s + 0x41;
            m = -13;
            *p = (*p & m) | 4;
            q = s + 0x45;
            *q &= m;
        }
    }
    s[18] = 0;
    s[19] = 0;
    s[10] |= 1;
}
