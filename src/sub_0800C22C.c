/* Sub_0800C22C @ 0x0800C22C (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_0800c22c_MATCHED.c (registry: staging/wave34_C/w34c_0800c22c_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0800E068();

void sub_0800C22C(u8 a)
{
    int b = a;
    u8 *p = (u8 *)0x02004f40;
    p[26] = 1;
    sub_0800E068(p + 32, (u8)b);
}
