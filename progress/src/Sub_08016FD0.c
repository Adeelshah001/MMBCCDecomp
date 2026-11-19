/* Sub_08016FD0 @ 0x08016FD0 (48 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_08016fd0_MATCHED.c (registry: staging/wave34_C/w34c_08016fd0_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern void sub_08004398(u32 a, int b, u32 c, int d, s16 e);

__attribute__((section(".text.w34c_08016fd0")))
void Sub_08016FD0(u32 a, u32 b, int c)
{
    u32 aa = a;
    u32 bb = b;
    s16 cc = c;
    sub_08004398(aa, 1, bb, 136, cc);
    *(u32 *)0x020053c0 = aa;
    *(u32 *)0x02000838 = bb;
}
