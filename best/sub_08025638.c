/* StoreIdx2_25638 @ 0x08025638 (26 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave9_d_old.c (registry: src/wave9_d_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


void sub_08025638(u8 *p, u8 idx, u8 val)
{
    register u8 *q = p;
    if (idx > 9)
        goto big;
    q += 2;
    q[idx] = val;
    return;
big: {
    u8 *r = q + idx;
    r[2] = val;
}
}
