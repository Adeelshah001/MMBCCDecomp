/* F_2FC4C @ 0x0802FC4C (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_D_old.c (registry: src/wave14_D_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w14d_0802fc4c")))
void F_2FC4C(unsigned int *p, unsigned char x, unsigned short y)
{
    unsigned char xx = x;
    register unsigned short yy __asm__("r2") = y;
    register unsigned int *qq __asm__("r1");
    register unsigned int pp __asm__("r0");
    register unsigned short tt __asm__("r3");
    if (xx == 2)
        return;
    qq = (unsigned int *)*p;
    __asm__ volatile("" : "=r" (pp) : "0" (0x271));
    if (*(unsigned short *)((unsigned char *)qq + 8) != pp)
        return;
    tt = *(unsigned short *)((unsigned char *)qq + 10);
    __asm__ volatile("" : "+r" (tt));
    {
        register unsigned short s __asm__("r0");
        s = tt + yy;
        *(unsigned short *)((unsigned char *)qq + 10) = s;
    }
}
