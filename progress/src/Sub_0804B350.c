/* Sub_0804B350 @ 0x0804B350 (46 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35b_0804b350_MATCHED.c (registry: mmbcc/src/w35b_0804b350_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern s8 Sub_08028778(u8 *p, int x);

__attribute__((section(".text.w35b_0804b350")))
int Sub_0804B350(u8 *s)
{
    s8 w = Sub_08028778(s + 1, 0);
    int t;
    if (w != 0)
        return 0;
    t = s[4];
    if (t <= 5)
    {
        *(u32 *)s = w;
        s[0] = 1;
    }
    else
    {
        *(u32 *)s = w;
        s[0] = 2;
    }
    return 0;
}
