/* Sub_0800C48C @ 0x0800C48C (38 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_0800c48c_MATCHED.c (registry: staging/wave34_C/w34c_0800c48c_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Sub_08005274(int x, int y, int z);

extern void Sub_0800E144();

__attribute__((section(".text.w34c_0800c48c")))
void Sub_0800C48C(u8 *s, int x)
{
    int xx = x;
    if (xx == 0)
        return;
    Sub_08005274(xx, 0, 1);
    if (s[26] == 0)
        return;
    Sub_0800E144(s + 32);
}
