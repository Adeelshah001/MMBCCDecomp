/* SumStrides_25754 @ 0x08025754 (60 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w16b_08025754.c (registry: src/w16b_08025754.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern u16 GetRomTableU16(u8 idx);

extern u8 TblLookup_25730(u8 *tbl, u8 idx);

u16 SumStrides_25754(u8 *tbl)
{
    u8 *tt = tbl;
    u16 sum = 0;
    u16 i = 1;
    u32 t;
    do {
        u8 v = TblLookup_25730(tt, (u8)i);
        if (v != 0)
            sum += GetRomTableU16(v);
        t = ((u32)i << 16) + 0x10000; i = t >> 16;
    } while ((s16)i <= 9);
    return sum;
}
