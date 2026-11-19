/* TblGet_25654 @ 0x08025654 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave9_e_old.c (registry: src/wave9_e_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


u8 sub_08025654(u8 *base, u8 idx)
{
    u8 *p;
    u8 x = idx;
    if (x > 9)
        goto L1;
    p = base + 2;
    goto L2;
L1:
    if (x > 11)
        return 0;
    x = x - 10;
    p = base + 12;
L2:
    p += x;
    return *p;
}
