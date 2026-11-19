/* GetPtr_0800dcf8 @ 0x0800DCF8 (16 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x0800dcf8: GetPtr_0800DCF8 (16B, coordinator-verified). */
unsigned char *sub_0800DCF8(unsigned char *s, unsigned char b)
{
    unsigned char *t = s;
    unsigned int u = (unsigned int)b << 24;
    s += 12;
    s += *(unsigned int *)(t + 12);
    u >>= 19;
    s += u;
    return s;
}
