/* F_0802476C @ 0x0802476C (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave15_B.c (registry: src/wave15_B.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_08025578(u8 *p, u8 a, u8 b);

void sub_0802476C(u8 a, u8 b)
{
    sub_08025578((u8 *)0x02007090, a, b);
}
