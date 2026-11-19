/* StoreTwoHalves_030BC @ 0x080030BC (6 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_e.c (registry: src/wave3_e.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x080030BC (6B, tentative): stores two halfwords at p+8 / p+10. */
void sub_080030BC(u16 *p, u16 a, u16 b)
{
    p[4] = a;
    p[5] = b;
}
