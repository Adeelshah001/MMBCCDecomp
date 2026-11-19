/* Sub_0800777C @ 0x0800777C (26 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_0800777c_MATCHED.c (registry: staging/wave34_C/w34c_0800777c_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_08007798();

void sub_0800777C(u8 a, u8 b, u8 c)
{
    sub_08007798(a, b, 11, c);
}
