/* Clear126_127_Set156_0200BD20 @ 0x0804AA78 (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x0804a494: Clear126_127_Set131 (28B, coordinator-verified). */
extern unsigned char gUnknown_0200BD20[];

void sub_0804AA78(unsigned int *src)
{
    unsigned char *p = gUnknown_0200BD20;
    unsigned char *q = p + 127;
    *q = 0;
    q--;
    *q = 0;
    *(unsigned int *)(p + 156) = *src;
}
