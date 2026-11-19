/* MaxAssign_17 @ 0x08017478 (14 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x08017478: MaxAssign_17 (16B, coordinator-verified). */
void sub_08017478(unsigned char *s, unsigned char v)
{
    if (s[17] < v)
        s[17] = v;
}
