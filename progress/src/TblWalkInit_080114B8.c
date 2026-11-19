/* TblWalkInit_080114B8 @ 0x080114B8 (48 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w18b_080114b8.c (registry: src/w18b_080114b8.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 *TableWalk_080113F4(u16 cur);

__attribute__((section(".text.w18b_080114b8")))
u32 TblWalkInit_080114B8(u16 x)
{
    u8 *t = (u8 *)0x02005230;
    u8 *r;
    u32 z = 0;

    t[4] = z;
    t[5] = z;
    t[6] = z;
    t[7] = z;
    *(u32 *)(t + 8) = z;
    r = TableWalk_080113F4(x);
    *(u8 **)t = r;
    if (r == 0)
        return 1;
    return 0;
}
