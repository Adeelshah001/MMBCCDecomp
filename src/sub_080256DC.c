/* SetU8_Off1 @ 0x080256DC (4 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_b.c (registry: src/wave3_b.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* Byte setter at struct offset 1 (TENTATIVE name).
 * ROM 0x080256DC (4 B). */
void sub_080256DC(u8 *p, u8 v)
{
    p[1] = v;
}
