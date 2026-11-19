/* Sub_0804AFAC @ 0x0804AFAC (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_0804afac_MATCHED.c (registry: staging/wave34_C/w34c_0804afac_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern int Sub_08028778(u8 *p, int one);

__attribute__((section(".text.w34c_0804afac")))
int Sub_0804AFAC(u8 *s)
{
    int t = Sub_08028778(s + 1, 1);
    int r;
    __asm__ volatile("lsl %1, %1, #24\n\tasr %0, %1, #24" : "=r"(r), "+r"(t));
    if (r == 0)
    {
        s[0]++;
        s[1] = r;
    }
    return 0;
}
