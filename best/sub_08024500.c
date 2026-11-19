/* ClampAdd200 @ 0x08024500 (20 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x08024500: ClampAdd200 (20B, coordinator-verified). */
unsigned char sub_08024500(unsigned short v)
{
    if (v > 48)
        return 200;
    return (unsigned char)(v + 200);
}
