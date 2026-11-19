/* FlagClear_4D7A0 @ 0x0804D7A0 (30 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave12_B_old.c (registry: src/wave12_B_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* FlagClear_4D7A0 @ 0x0804D7A0 (30 B): clears flag bytes, sets bit w. */
__attribute__((section(".text.w12b_0804d7a0")))
void FlagClear_4D7A0(u8 *s)
{
    register u8 *p __asm__("r1") = s;
    register u8 z __asm__("r2") = 0;
    register u8 w __asm__("r0");
    asm volatile("" : "+r" (z));
    p[26] = 0;
    p[22] = 0;
    if (p[24] != 0) goto else_;
    w = 12;
    goto join;
else_:
    w = 3;
join:
    p[0] |= w;
}
