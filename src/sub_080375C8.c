/* Sub_080375C8 @ 0x080375C8 (54 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35c_080375c8_MATCHED.c (registry: mmbcc/src/w35c_080375c8_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern int sub_080246A8(u8 x);

extern void sub_08006A54(int a, int b, int c, int d, int e);

extern void sub_08007C04(u8 x, int y);

extern void sub_08007CF4(int a, int b, int c);

void sub_080375C8(int a, int b)
{
    u8 x = b;
    int t = sub_080246A8(x);
    sub_08006A54(t, 20, 1, 8, 2);
    sub_08007C04(x, 1);
    sub_08007CF4(1, 20, 3);
}
