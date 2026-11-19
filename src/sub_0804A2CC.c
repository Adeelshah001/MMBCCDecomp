/* G0BD10_Zero2 @ 0x0804A2CC (16 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_c.c (registry: src/wave3_c.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u16 gUnknown_0200BD10[];

void sub_0804A2CC(void)
{
    gUnknown_0200BD10[0] = 0;
    gUnknown_0200BD10[1] = 0;
}
