/* Gt199_08026700 @ 0x08026700 (16 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x08026700: Gt199_08026700 (16B, coordinator-verified). */
unsigned int sub_08026700(unsigned char v)
{
    if (v > 199)
        return 1;
    return 0;
}
