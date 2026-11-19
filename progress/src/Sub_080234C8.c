/* Sub_080234C8 @ 0x080234C8 (208 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w38c_080234c8_MATCHED.c (registry: mmbcc/src/w38c_080234c8_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

extern void ChipSlot_Setup(u8 *s, int a, int b);

extern void ChipSlot_IncUse(u8 *s, int v);

extern void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w38c_080234c8")))
void Sub_080234C8(u8 *s)
{
    u8 *p = *(u8 **)(s + 40);
    register int g1 __asm__("r3");
    g1 = 1;
    __asm__ volatile("ldrsb %0, [%1, %0]" : "+r"(g1) : "r"(p));
    if (g1 != 1 ||
        *(u16 *)(p + 2) != *(s32 *)(s + 88) ||
        (s8)p[4] != *(s32 *)(s + 96) ||
        (s8)p[5] != *(s32 *)(s + 100) ||
        (p[7] & 4) != 0) {
        s[13] = 0;
        s[14] = 0;
        s[10] &= 254;
    } else if (s[14] == 0) {
        int idx;
        u16 *tbl;
        register int one __asm__("r0");
        one = 1;
        s[14] = g1;
        s[10] |= one;
        tbl = (u16 *)0x082271d4;
        __asm__ volatile("" : "+r"(tbl));
        ChipSlot_Setup(s, 3 | tbl[s[17]], 0);
        ChipSlot_IncUse(s, 1);
        idx = *(u8 *)(((*(u16 *)0x081705b0 >> 4) << 1) +
            0x020031e4) & 3;
        if (idx > 3)
            idx = 3;
        {
            u8 *q = s + 69;
            int sh = idx << 2;
            int nm = -13;
            *q = (*q & nm) | sh;
        }
        s[34] = 1;
        *(s32 *)(s + 80) = (*(s32 *)(s + 96) << 11) + (160 << 5);
        *(s32 *)(s + 84) = *(s32 *)(s + 100) << 11;
    }
    ChipSlot_Tick(s);
}
