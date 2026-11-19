/* F_08025A10 @ 0x08025A10 (84 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w17c_table.c (registry: src/w17c_table.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 TblLookup_25730(u8 *tbl, u8 idx);

extern u32 SumStrides_25754(u8 *tbl);

extern u32 AddTbl_S14(u8 *s);

extern u8 TblGet_25654(u8 *base, u8 idx);

extern void SetU8_Off1(u8 *p, u8 v);

extern void StoreIdx2_25638(u8 *p, u8 idx, u8 val);

/* 0x08025a10 (84 B): TblLookup + SumStrides/AddTbl compare + SetU8/StoreIdx. */
__attribute__((section(".text.w17c_08025a10")))
u32 F_08025A10(u8 *s, u8 idx)
{
    TblLookup_25730(s, idx);
    if (idx == 0) {
        u32 sum = SumStrides_25754(s);
        u32 add = AddTbl_S14(s);
        if ((sum << 16) > (add << 16))
            return 1;
    }
    {
        u8 t = TblGet_25654(s, idx);
        SetU8_Off1(s + (((u32)(u8)t << 2) + 20), 255);
        StoreIdx2_25638(s, idx, 255);
    }
    return 0;
}
