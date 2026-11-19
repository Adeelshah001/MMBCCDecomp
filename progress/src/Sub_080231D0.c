/* Sub_080231D0 @ 0x080231D0 (146 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37c_080231d0_MATCHED.c (registry: mmbcc/src/w37c_080231d0_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void ChipSlot_IncUse(u8 *s, int idx);

extern void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w37c_080231d0")))
void Sub_080231D0(u8 *s)
{
    register u8 *base __asm__("r0");
    u16 v;
    switch (s[13]) {
    case 0:
        s[13] = 1;
        ChipSlot_IncUse(s, s[17]);
        base = (u8 *)0x02004830;
        __asm__ volatile("" : "+r"(base));
        *(u32 *)(s + 80) = *(u8 *)(base + 621) << 11;
        *(u32 *)(s + 84) = *(u8 *)(base + 622) << 11;
        v = 256;
        *(u16 *)(s + 76) = v;
        *(u16 *)(s + 78) = v;
    case 1: {
        u8 ub;
        s8 b;
        u32 *tp;
        register u8 *tbase __asm__("r1");
        u8 z;
        base = (u8 *)0x02004830;
        __asm__ volatile("" : "+r"(base));
        ub = *(u8 *)(base + 620);
        b = (s8)ub;
        if (s[17] == b)
            goto tail;
        if (b < 0) {
            tbase = (u8 *)0x08226ef0;
            __asm__ volatile("" : "+r"(tbase));
            tp = (u32 *)(s[9] * 4 + (u32)tbase);
            *(u32 *)(s + 12) = 2;
            *(u32 *)(s + 20) = *(u32 *)(*(u32 *)tp + 8);
            goto tail;
        }
        z = 0;
        s[17] = ub;
        s[13] = z;
        goto tail;
    }
    default:
        goto tail;
    }
tail:
    ChipSlot_Tick(s);
}
