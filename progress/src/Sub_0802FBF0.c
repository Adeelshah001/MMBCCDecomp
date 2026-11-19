/* Sub_0802FBF0 @ 0x0802FBF0 (56 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36e_0802fbf0_MATCHED.c (registry: mmbcc/src/w36e_0802fbf0_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w36e_0802fbf0")))
void Sub_0802FBF0(u8 *pp)
{
    register u8 *ppc __asm__("r2") = pp;
    u8 *p1 = ppc + (197 << 1);
    u8 *q;
    u8 v;
    v = *p1;
    if (v <= 99)
        *p1 = v + 5;
    __asm__ volatile("" : "+r"(ppc));
    ppc = ppc + 0x18B;
    v = *ppc;
    if (v <= 99)
        *ppc = v + 5;
    q = (u8 *)0x02005168;
    q[12] = *p1;
    q += 20;
    q[12] = *ppc;
}
