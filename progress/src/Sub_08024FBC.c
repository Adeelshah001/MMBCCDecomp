/* Sub_08024FBC @ 0x08024FBC (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_08024fbc_MATCHED.c (registry: staging/wave34_C/w34c_08024fbc_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u16 sub_08026238();

__attribute__((section(".text.w34c_08024fbc")))
u16 Sub_08024FBC(int a, int b)
{
    u8 *p = (u8 *)0x02007090;
    u8 *q;
    __asm__ volatile("" : "+r"(p));
    q = p + 24;
    return (u16)sub_08026238(q, a, b);
}
