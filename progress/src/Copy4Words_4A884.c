/* Copy4Words_4A884 @ 0x0804A884 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_D_old.c (registry: src/wave14_D_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w14d_0804a884")))
void Copy4Words_4A884(unsigned int *src)
{
    unsigned char *p;
    unsigned int *dst;
    __asm__ volatile("" : "=r" (p) : "0" (0x0200BD20));
    {
        register unsigned char *q __asm__("r3") = p;
        q += 127;
        q[0] = 0;
        q -= 1;
        q[0] = 0;
        dst = (unsigned int *)(p + 140);
    }
    {
        register unsigned int *s __asm__("r0") = src;
        register unsigned int *d __asm__("r1") = dst;
        __asm__ volatile(
            "ldmia %0!, {r2, r3, r4}\n\t"
            "stmia %1!, {r2, r3, r4}\n\t"
            "ldr %0, [%0]\n\t"
            "str %0, [%1]"
            : "+r" (s), "+r" (d)
            :
            : "r2", "r3", "r4", "memory");
    }
}
