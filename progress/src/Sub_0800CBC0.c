/* Sub_0800CBC0 @ 0x0800CBC0 (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_0800cbc0_MATCHED.c (registry: staging/wave34_C/w34c_0800cbc0_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void F_0800C268(u32 b, u16 c, int d, int e, int f);

__attribute__((section(".text.w34c_0800cbc0")))
void Sub_0800CBC0(int dummy, u32 b, u32 c)
{
    u32 bb = b;
    u16 cc = c;
    F_0800C268(bb, cc, 4, 4, 2);
}
