/* Wrap_07818 @ 0x08007818 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_C.c (registry: src/wave14_C.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* Wrap_07818 @ 0x08007818 */
void sub_08007840(u8 *p, s8 a, s8 b, s8 c);

void sub_08007818(s8 a, s8 b, s8 c)
{
    sub_08007840((u8 *)0x0200483c, a, b, c);
}
