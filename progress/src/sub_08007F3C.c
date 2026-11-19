/* sub_08007F3C @ 0x08007F3C (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w33d_08007f3c.c (registry: src/w33d_08007f3c.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void sub_08007F54(u16 a, s8 b, s8 c, u32 d);

__attribute__((section(".text.w33d_08007f3c")))
void sub_08007F3C(u16 a, s8 b, s8 c)
{
    sub_08007F54(a, b, c, 0);
}
