/* Sub_08006928 @ 0x08006928 (52 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_08006928_MATCHED.c (registry: staging/wave34_C/w34c_08006928_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern void sub_0800695c(u8 *p, u8 *a, s16 b, s16 c, s8 d, int e);

__attribute__((section(".text.w34c_08006928")))
void Sub_08006928(u8 *a, int b, int c, int d)
{
    u8 *aa = a;
    s16 bb = b;
    s16 cc = c;
    s8 dd = d;
    sub_0800695c((u8 *)0x0200483c, aa, bb, cc, dd, 0);
}
