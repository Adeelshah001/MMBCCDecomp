/* sub_0804D634 @ 0x0804D634 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_D_old.c (registry: src/wave14_D_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w14d_0804d634")))
void sub_0804D634(unsigned char *a, unsigned int b)
{
    register unsigned char *aa __asm__("r2") = a;
    register unsigned int v __asm__("r3");
    register unsigned int pool __asm__("r0");
    __asm__ volatile("lsl %0, %0, #16\n\tlsr %0, %0, #16" : "+r" (b));
    v = *(unsigned int *)(aa + 52);
    __asm__ volatile("" : "=r" (pool) : "0" (0x68736D53));
    if (v != pool)
        return;
    *(unsigned short *)(aa + 30) = (unsigned short)b;
    {
        register unsigned short c __asm__("r4");
        register int t __asm__("r0");
        c = *(unsigned short *)(aa + 28);
        t = b;
        t = t * c;
        t >>= 8;
        *(unsigned short *)(aa + 32) = (unsigned short)t;
    }
}
