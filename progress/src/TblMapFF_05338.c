/* TblMapFF_05338 @ 0x08005338 (104 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_D_old.c (registry: src/wave14_D_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* Wave 14 worker D: blocked revisits, old_agbcc.
 * Coordinator-verified byte-identical (clean-room rebuild + ROM diff).
 * Evidence: docs/match_notes_wave14_D.md, docs/wave14_D_results.tsv. */

__attribute__((section(".text.w14d_08005338")))
void TblMapFF_05338(unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
    register unsigned char *tbl __asm__("r2");
    volatile unsigned short *out;
    __asm__ volatile("" : "=r" (tbl) : "0" (0x02003670));

    if (a == 0xFF) a = tbl[0x11B0];
    if (b == 0xFF) b = tbl[0x11B1];
    if (c == 0xFF) c = tbl[0x11B2];
    if (d == 0xFF) {
        register unsigned int off __asm__("r3");
        register unsigned char *p __asm__("r0");
        __asm__ volatile("" : "=r" (off) : "0" (0x11B3));
        p = tbl + off;
        d = *p;
    }

    out = (volatile unsigned short *)0x02003230;
    {
        register unsigned short v __asm__("r3");
        v = d;
        v |= c << 8;
        out[2] = v;
    }
    out[4] = b | (a << 8);
}
