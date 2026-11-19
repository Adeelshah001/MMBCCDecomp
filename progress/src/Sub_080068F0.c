/* Sub_080068F0 @ 0x080068F0 (56 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_080068f0_MATCHED.c (registry: staging/wave34_C/w34c_080068f0_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern void sub_0800695c(u8 *p, u8 *a, s16 b, s16 c, s8 d, u8 e);

__attribute__((section(".text.w34c_080068f0")))
void Sub_080068F0(u8 *a, int b, int c, int d, int e)
{
    u8 *aa = a;
    s16 bb = b;
    s16 cc = c;
    s8 dd = d;
    u8 ee = e;
    sub_0800695c((u8 *)0x02004830, aa, bb, cc, dd, ee);
}
