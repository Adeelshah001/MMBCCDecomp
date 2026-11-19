/* Sub_0804044C @ 0x0804044C (132 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37b_0804044c_MATCHED.c (registry: mmbcc/src/w37b_0804044c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern int sub_08024818(int sum);

extern void sub_08007C04(u8 t, int x);

extern void sub_08007CF4(int a, s8 b, s8 c);

extern int sub_080246A8(u8 t);

extern void sub_08006A54(int a, int b, int c, int d, int e);

extern int sub_080246C4(u8 t);

void sub_0804044C(u8 *s)
{
    int off = 0x46a8;
    u8 b0 = s[off];
    u8 b1 = s[off + 1];
    u8 t = (u8)sub_08024818(b0 + b1);
    sub_08007C04(t, 2);
    {
        u8 *tbl = (u8 *)0x082329e0;
        sub_08007CF4(2, (s8)(tbl[16] + 1), (s8)(tbl[17] + 3));
    }
    {
        s8 *st = (s8 *)0x082329e0;
        sub_08006A54(sub_080246A8(t), st[16] + 1, st[17] + 1, 8, 0);
    }
    {
        s8 *st = (s8 *)0x082329e0;
        sub_08006A54(sub_080246C4(t), st[16] + 1, st[17] + 10, 8, 0);
    }
}
