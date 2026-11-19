/* TryConsume_08040060 @ 0x08040060 (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x08040060: TryConsume (24B, coordinator-verified). */
unsigned int sub_08040060(unsigned char *s, unsigned short n)
{
    unsigned int *p = (unsigned int *)(s + 32);
    if (*p >= n) {
        *p -= n;
        return 0;
    } else {
        return 1;
    }
}
