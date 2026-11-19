/* InRange224_230 @ 0x0803FE30 (20 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x0803fe30: InRange224_230 (20B, coordinator-verified). */
unsigned int sub_0803FE30(unsigned short v)
{
    unsigned int r = 0;
    int w = v;
    int lo = 224;
    if (w > 230)
        goto L0;
    if (w < lo)
        goto L0;
    r = 1;
L0:
    return r;
}
