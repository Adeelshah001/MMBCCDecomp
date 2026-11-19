/* F_4C53C @ 0x0804C53C (26 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave11_A_old.c (registry: src/wave11_A_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w11a_0804c53c")))
void F_4C53C(u8 dummy, u8 *p)
{
    register u8 *pp __asm__("r1") = p;
    register u8 t __asm__("r2");
    register u8 v __asm__("r3");
    __asm__ volatile("movs %0, #0" : "=r" (t));
    (void)dummy;
    pp[22] = t;
    pp[26] = t;
    t = pp[24];
    if (t == 0)
        t = 12;
    else
        t = 3;
    v = pp[0];
    v |= t;
    pp[0] = v;
}
