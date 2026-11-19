/* sub_080257BC @ 0x080257BC (60 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w18b_080257bc.c (registry: src/w18b_080257bc.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 TblLookup_25730(u8 *tbl, u8 idx);

extern u16 SumStrides_25754(u8 *tbl);

extern u16 GetRomTableU16(u8 idx);

__attribute__((section(".text.w18b_080257bc")))
void sub_080257BC(u8 *p, u16 x)
{
    u8 v = TblLookup_25730(p, 0);
    u16 sum;
    u16 t;

    if (v == 0)
        v = p[1];
    sum = SumStrides_25754(p);
    if ((int)sum <= (int)GetRomTableU16(v) + (int)x)
        *(u16 *)(p + 14) = x;
}
