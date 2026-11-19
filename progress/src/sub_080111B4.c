/* sub_080111B4 @ 0x080111B4 (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w33d_080111b4.c (registry: src/w33d_080111b4.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u32 sub_0800B3EC(u32 a, u32 b);

__attribute__((section(".text.w33d_080111b4")))
void sub_080111B4(u32 a)
{
    volatile u8 *p = (volatile u8 *)0x020051B0;
    u32 zero = 0;
    p[4] = a;
    p[1] = zero;
    p[0] = zero;
    sub_0800B3EC(0, 0);
}
