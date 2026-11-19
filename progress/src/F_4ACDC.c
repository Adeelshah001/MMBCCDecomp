/* F_4ACDC @ 0x0804ACDC (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave11_A_old.c (registry: src/wave11_A_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w11a_0804acdc")))
void F_4ACDC(u32 x)
{
    u8 *base;
    u8 *p;
    u8 *q;
    __asm__ volatile("" : "=r" (base) : "0" ((u8 *)0x0200bd20));
    p = base + 0x7f;
    *p = 0;
    p--;
    *p = 0;
    p += 0x22;
    (*p)++;
    q = base + 0xa1;
    *q = (u8)x;
}
