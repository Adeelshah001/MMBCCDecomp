/* F_EE50 @ 0x0800EE50 (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave11_A_old.c (registry: src/wave11_A_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w11a_0800ee50")))
void F_EE50(void)
{
    register u8 *pp __asm__("r0");
    register u8 *qq __asm__("r2");
    u8 v, r;
    __asm__ volatile("" : "=r" (pp) : "0" ((u8 *)0x02005160));
    qq = pp;
    qq += 0x44;
    v = *qq + 1;
    r = 0;
    if (v <= 1)
        r = 1;
    *qq = r;
}
