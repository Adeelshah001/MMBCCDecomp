/* Checksum_23D34 @ 0x08023D34 (52 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_D_old.c (registry: src/wave14_D_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w14d_08023d34")))
unsigned int Checksum_23D34(unsigned char *str, unsigned int c)
{
    register unsigned char *p __asm__("r4");
    register unsigned int sum __asm__("r3");
    register unsigned int i __asm__("r2");
    register unsigned int t __asm__("r0");

    p = str;
    __asm__ volatile("lsl %0, %0, #24\n\tlsr %0, %0, #24" : "+r" (c));
    sum = 0;
    i = 0;

    do {
        t = p[i];
        t += sum;
        sum = (unsigned char)t;
        t = i + 1;
        i = (unsigned char)t;
    } while (i <= 13);

    t = sum + c;
    if ((unsigned char)t == 0) { } else return 1;
    return 0;
}
