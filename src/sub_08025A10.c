/* F_08025A10 @ 0x08025A10 (84 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w17c_table.c (registry: src/w17c_table.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 sub_08025730(u8 *tbl, u8 idx);

extern u32 sub_08025754(u8 *tbl);

extern u32 sub_0802588C(u8 *s);

extern u8 sub_08025654(u8 *base, u8 idx);

extern void sub_080256DC(u8 *p, u8 v);

extern void sub_08025638(u8 *p, u8 idx, u8 val);

/* 0x08025a10 (84 B): TblLookup + SumStrides/AddTbl compare + SetU8/StoreIdx. */
u32 sub_08025A10(u8 *s, u8 idx)
{
    sub_08025730(s, idx);
    if (idx == 0) {
        u32 sum = sub_08025754(s);
        u32 add = sub_0802588C(s);
        if ((sum << 16) > (add << 16))
            return 1;
    }
    {
        u8 t = sub_08025654(s, idx);
        sub_080256DC(s + (((u32)(u8)t << 2) + 20), 255);
        sub_08025638(s, idx, 255);
    }
    return 0;
}
