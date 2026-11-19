/* Sub_0804C780 @ 0x0804C780 (52 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35b_0804c780_MATCHED.c (registry: mmbcc/src/w35b_0804c780_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Sub_0804CECC(u32 x);

__attribute__((section(".text.w35b_0804c780")))
void Sub_0804C780(int idx)
{
    u32 sh = (u32)idx << 16;
    register u32 *tbl1 __asm__("r2") = (u32 *)0x08106d7c;
    register u32 *tbl2 __asm__("r1") = (u32 *)0x08106dd0;
    u32 t;
    u16 v;
    u32 base;
    u32 v2;
    u32 v3;
    u32 v4;
    __asm__ volatile("" : "+r"(tbl1));
    __asm__ volatile("" : "+r"(tbl2));
    t = (sh >> 13) + (u32)tbl2;
    v = *(u16 *)(t + 4);
    base = (v * 3) * 4;
    base += (u32)tbl1;
    v2 = *(u32 *)base;
    v3 = *(u32 *)v2;
    v4 = *(u32 *)t;
    if (v3 == v4)
        Sub_0804CECC(v2);
}
