/* sub_08047510 @ 0x08047510 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_D_old.c (registry: src/wave14_D_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w14d_08047510")))
void sub_08047510(unsigned char *a, unsigned int b)
{
    register unsigned char *aa __asm__("r2") = a;
    register unsigned int bb __asm__("r3") = b;
    unsigned char t = aa[4];
    signed char ss;
    if (((signed char *)aa)[4] == 0)
        return;
    aa[4] = t - 1;
    __asm__ volatile("" ::: "memory");
    ss = ((signed char *)aa)[4];
    {
        register unsigned int addr __asm__("r0");
        register unsigned int pool __asm__("r2");
        addr = ss * 2 + bb;
        __asm__ volatile("" : "=r" (pool) : "0" (0xFFFF8000));
        *(unsigned short *)addr = ss + pool;
    }
}
