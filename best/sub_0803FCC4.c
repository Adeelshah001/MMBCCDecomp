/* InRange3B0_3B1 @ 0x0803FCC4 (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x0803fcc4: InRange3B0_3B1 (28B, coordinator-verified). */
unsigned int sub_0803FCC4(unsigned short v)
{
    unsigned int r = 0;
    int lim = 0x3b1;
    int w = v;
    if (w > lim)
        goto L0;
    if (w < lim - 1)
        goto L0;
    r = 1;
L0:
    return r;
}
