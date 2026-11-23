/* identical to sub_08004E50 (matched), with its names changed by decompdecomp */
/* sub_08004DFC @ 0x08004E50 (16 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w33d_08004e50.c (registry: src/w33d_08004e50.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0800D3A0(u8 a);

void sub_08004DFC(u8 a)
{
    sub_0800D3A0(a);
}
