/* Sub_080241AC @ 0x080241AC (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_080241ac_MATCHED.c (registry: staging/wave34_C/w34c_080241ac_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Call3_08025464(u8 *p);

extern void Sub_08026208(u8 *q, u32 x, u32 n);

__attribute__((section(".text.w34c_080241ac")))
void Sub_080241AC(void)
{
    u8 *p = (u8 *)0x02007090;
    u8 *q;
    Call3_08025464(p);
    q = p;
    q += 24;
    Sub_08026208(q, *(u32 *)(p + 52) + 1184, 1184);
}
