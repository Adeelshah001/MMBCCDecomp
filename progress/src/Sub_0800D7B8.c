/* Sub_0800D7B8 @ 0x0800D7B8 (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_0800d7b8_MATCHED.c (registry: staging/wave34_C/w34c_0800d7b8_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void sub_0800D800(u8 *s, int one, u16 b, u8 c, int zero);

__attribute__((section(".text.w34c_0800d7b8")))
void Sub_0800D7B8(u8 *s, int b, int c)
{
    u16 bb = b;
    u8 cc = c;
    sub_0800D800(s, 2, bb, cc, 1);
}
