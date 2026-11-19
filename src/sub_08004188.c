/* SwapPtr_08004188 @ 0x08004188 (20 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x08004188: SwapPtr (20B, coordinator-verified). */
void sub_08004188(unsigned int *p, unsigned int *q, short x, short y)
{
    int off = (y << 2) + (x << 7);
    unsigned int *r = (unsigned int *)((unsigned char *)p + off);
    unsigned int tmp = *r;
    *q = tmp;
    *r = (unsigned int)q;
}
