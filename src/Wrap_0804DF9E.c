/* Wrap_0804DF9E @ 0x0804DF9E (10 B, neighbor extent (no ELF size; fixed up after compile)) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_j_noiw.c (registry: ldscript BYTE (src/wave4_j_noiw.c)).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0804DD9C(void);

/* 0x0804DF9E: call sub_0804DD9C, return 0. Tentative name. */
u32 Wrap_0804DF9E(void)
{
    sub_0804DD9C();
    return 0;
}
