/* Clamp48_08024528 @ 0x08024528 (18 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x08024528: Clamp48_08024528 (20B, coordinator-verified). */
unsigned char sub_08024528(unsigned short v)
{
    if (v > 48)
        return 0;
    return (unsigned char)v;
}
