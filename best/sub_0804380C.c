/* Sub_0804380C @ 0x0804380C (132 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36bulk_0804380c_MATCHED.c (registry: src/w36bulk_0804380c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern int sub_08024818(int x);

extern void sub_08007C04(u8 t, int x);

extern void sub_08007CF4(int a, s8 b, s8 c);

extern int sub_080246A8(u8 t);

extern void sub_08006A54(int a, int b, int c, int d, int e);

extern int sub_080246C4(u8 t);

void sub_0804380C(u8 *s)
{
    int zero = 0;
    register u8 b = s[0x46a8];
    u8 t = (u8)sub_08024818((b >> 5) + (b & 31));
    sub_08007C04(t, 1);
    {
        u8 *tbl = (u8 *)0x08232d84;
        sub_08007CF4(1, (s8)(tbl[0] + 1), (s8)(tbl[1] + 3));
    }
    {
        s8 *st = (s8 *)0x08232d84;
        sub_08006A54(sub_080246A8(t), st[0] + 1, st[1] + 1, 8, zero);
    }
    {
        s8 *st = (s8 *)0x08232d84;
        sub_08006A54(sub_080246C4(t), st[0] + 1, st[1] + 10, 8, zero);
    }
}
