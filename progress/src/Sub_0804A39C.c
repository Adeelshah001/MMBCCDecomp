/* Sub_0804A39C @ 0x0804A39C (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_0804a39c_MATCHED.c (registry: staging/wave34_C/w34c_0804a39c_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void sub_08000F28(void);

__attribute__((section(".text.w34c_0804a39c")))
void Sub_0804A39C(void)
{
    u8 *p = (u8 *)0x0200bd20;
    volatile u16 *q;
    u16 t, v, one;
    sub_08000F28();
    q = (volatile u16 *)0x02002ee0;
    t = q[1];
    one = 1;
    v = q[1];
    v = 0;
    q[1] = one | t;
    *(u32 *)(p + 120) = v;
}
