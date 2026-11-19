/* F_4C610 @ 0x0804C610 (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave11_A_old.c (registry: src/wave11_A_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w11a_0804c610")))
void F_4C610(u8 *p, u16 x)
{
    u8 *q = p;
    u16 xx = x;
    register u32 vv __asm__("r3") = *(u32 *)(q + 52);
    u32 pv;
    __asm__ volatile("" : "=r" (pv) : "0" (0x68736d53));
    if (vv == pv) {
        register u32 c100 __asm__("r0");
        *(u16 *)(q + 38) = xx;
        *(u16 *)(q + 36) = xx;
        __asm__ volatile("" : "=r" (c100) : "0" (0x100));
        *(u16 *)(q + 40) = (u16)c100;
    }
}
