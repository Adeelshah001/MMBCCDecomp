/* sub_0800EE70 @ 0x0800EE70 (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w33d_0800ee70.c (registry: src/w33d_0800ee70.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern void sub_0800BF6C(s16 a, u32 b);

__attribute__((section(".text.w33d_0800ee70")))
void sub_0800EE70(u8 a)
{
    volatile s16 *pv = (volatile s16 *)0x02005130;
    s16 *p = (s16 *)0x02005130;
    *pv = a;
    sub_0800BF6C(p[0], 255);
}
