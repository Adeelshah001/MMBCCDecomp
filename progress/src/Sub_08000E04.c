/* Sub_08000E04 @ 0x08000E04 (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_08000e04_MATCHED.c (registry: staging/wave34_C/w34c_08000e04_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void ContextSwitch(u8 *p1, u8 *p2, u32 v);

__attribute__((section(".text.w34c_08000e04")))
void Sub_08000E04(u8 *s, int b)
{
    u8 *p1, *p2;
    u32 v;
    if (b == 0)
        return;
    *(u16 *)(s + 2) = b;
    s[0] = 4;
    p1 = s + 4;
    p2 = s;
    p2 += 8;
    v = *(u32 *)0x02000800;
    ContextSwitch(p1, p2, v);
}
