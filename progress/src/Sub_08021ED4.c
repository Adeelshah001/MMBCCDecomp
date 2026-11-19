/* Sub_08021ED4 @ 0x08021ED4 (104 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_08021ed4_MATCHED.c (registry: mmbcc/src/w36b_08021ed4_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

typedef struct { u32 x, y; } Pair;

extern void ChipSlot_Tick(u8 *p);

__attribute__((section(".text.w36b_08021ed4")))
void Sub_08021ED4(u8 *p)
{
    u8 *q = *(u8 **)(p + 40);
    u8 first = q[0];
    u8 state = p[13];
    switch (state) {
    case 0:
        if (first == 255) {
            p[10] &= 0xfe;
        } else {
            p[10] |= 1;
            p[13]++;
            p[18] = first;
        }
        break;
    case 1: {
        struct Pair { s16 a; s16 b; } *t;
        p[13] = 0;
        t = (struct Pair *)0x082270bc;
        *(u32 *)(p + 80) = (u32)(t[p[18]].a << 8);
        *(u32 *)(p + 84) = (u32)(t[p[18]].b << 8);
        break;
    }
    default:
        break;
    }
    ChipSlot_Tick(p);
}
