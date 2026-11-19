/* ChipSlot_InitEntry @ 0x08046CA0 (92 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave13_D_old.c (registry: src/wave13_D_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* Wave 13 worker D: 4 leaves-up matches, all old_agbcc.
 * Coordinator-verified byte-identical (clean-room rebuild + ROM diff).
 * Evidence: docs/match_notes_wave13_D.md, docs/wave13_D_results.tsv. */

__attribute__((section(".text.w13d_08046ca0")))
void ChipSlot_InitEntry(unsigned char *p, unsigned short *q, unsigned char a, unsigned char b)
{
    unsigned char r;
    short i;

    p[4] = 0;
    if (b == 0) {
        p[5] = b;
        r = 20;
    } else {
        p[5] = 0;
        r = 25;
    }
    p[3] = r;
    p[2] = r;
    p[8] = b;
    {
        unsigned short v;
        __asm__ volatile("" : "=r" (v) : "0" (0x800A));
        *(unsigned short *)(p + 6) = v;
    }
    for (i = 0; i < a + 1; i++)
        q[i] = 0;
    q[0] = 0x8000;
}
