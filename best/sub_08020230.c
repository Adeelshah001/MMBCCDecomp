/* F_20230 @ 0x08020230 (26 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave11_A_old.c (registry: src/wave11_A_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


void sub_08020230(u8 *a, u8 *p, u8 x)
{
    u8 *q = p;
    u8 xx = x;
    a += 0x23;
    if ((*a & 15) == 0)
        q[5] = xx;
    else
        q[6] = xx;
}
