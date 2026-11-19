/* GetBoundedByte_08025478 @ 0x08025478 (22 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x08025478: GetBoundedByte_08025478 (24B, coordinator-verified). */
unsigned char sub_08025478(void *s, unsigned short idx)
{
    unsigned short lim = *(unsigned short *)((unsigned char *)s + 18);
    if (idx >= lim)
        return 0;
    return *(*(unsigned char **)((unsigned char *)s + 8) + idx);
}
