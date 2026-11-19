/* Sub_08036374 @ 0x08036374 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_08036374_MATCHED.c (registry: staging/wave34_C/w34c_08036374_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_080363EC(u8 *p);

extern int sub_0803643C(s8 x, int y, int z);

int sub_08036374(int x)
{
    u8 *p = (u8 *)0x0200bce8;
    int xx = x;
    s8 ss;
    sub_080363EC(p);
    ss = xx;
    p[1] = sub_0803643C(ss, 0, 0);
    return 1;
}
