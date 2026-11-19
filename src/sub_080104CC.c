/* F_080104CC @ 0x080104CC (38 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave15_B.c (registry: src/wave15_B.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0800BEE0(unsigned int a, unsigned int b);

u8 sub_080104CC(u8 x)
{
    if (*(u8 *)0x02005160 != 0)
        return 0;
    sub_0800BEE0(x, 0);
    return 1;
}
