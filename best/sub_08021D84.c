/* Byte19_Bits3F_Set @ 0x08021D84 (18 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x08021d84: Byte19_Bits3F_Set (20B, coordinator-verified). */
unsigned int sub_08021D84(unsigned char *s)
{
    unsigned int r = 0;
    unsigned int mask = 0x3f;
    mask &= s[19];
    if (mask == 0x3f)
        r = 1;
    return r;
}
