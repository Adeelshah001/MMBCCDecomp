/* Sub_080260A0 @ 0x080260A0 (50 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_080260a0_MATCHED.c (registry: staging/wave34_C/w34c_080260a0_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern void Sub_080256E0(u8 *p);

__attribute__((section(".text.w34c_080260a0")))
void Sub_080260A0(u8 *s)
{
    s16 i;
    for (i = 0; i <= 2; i++)
    {
        Sub_080256E0(s + i * 144);
    }
    s[432] = 0;
}
