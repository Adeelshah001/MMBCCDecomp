/* Sub_08004EF4 @ 0x08004EF4 (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_08004ef4_MATCHED.c (registry: staging/wave34_C/w34c_08004ef4_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void sub_0800D420(int);

extern void Fwd_0800d55c(void);

extern void Sub_08020EA4(u8 *p1, u8 *p2, int n);

__attribute__((section(".text.w34c_08004ef4")))
void Sub_08004EF4(void)
{
    sub_0800D420(1);
    Fwd_0800d55c();
    Sub_08020EA4((u8 *)0x02004ff0, (u8 *)0x02006700, 18);
}
