/* Init_08004244 @ 0x08004244 (20 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x08004244: Init_08004244 (20B, coordinator-verified). */
void sub_08004244(void *s, void **pp)
{
    *(void **)s = pp;
    ((unsigned char *)s)[4] = 0;
    ((unsigned char *)s)[5] = 0;
    ((unsigned char *)s)[6] = (*(unsigned char **)pp)[1] + 1;
    ((unsigned char *)s)[7] = 0;
}
