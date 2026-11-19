/* BuildU32_4DA34 @ 0x0804DA34 (72 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_D_old.c (registry: src/wave14_D_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w14d_0804da34")))
void BuildU32_4DA34(unsigned int dummy, unsigned int *ctx)
{
    register unsigned char *s __asm__("r2");
    register unsigned int v __asm__("r4");
    register unsigned int mask __asm__("r0");
    register unsigned int sh __asm__("r3");

    s = (unsigned char *)ctx[16];

    __asm__ volatile("" : "=r" (mask) : "0" (0xFFFFFF00));
    v &= mask;
    v |= s[0];

    sh = (unsigned int)s[1] << 8;
    __asm__ volatile("" : "=r" (mask) : "0" (0xFFFF00FF));
    v &= mask;
    v |= sh;

    sh = (unsigned int)s[2] << 16;
    __asm__ volatile("" : "=r" (mask) : "0" (0xFF00FFFF));
    v &= mask;
    v |= sh;

    sh = (unsigned int)s[3] << 24;
    __asm__ volatile("" : "=r" (mask) : "0" (0x00FFFFFF));
    v &= mask;
    v |= sh;

    ctx[10] = v;
    s += 4;
    ctx[16] = (unsigned int)s;
}
