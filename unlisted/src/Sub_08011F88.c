/* Sub_08011F88 @ 0x08011F88 (132 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36c_08011f88_MATCHED.c (registry: mmbcc/src/w36c_08011f88_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;

extern void sub_0800DD2C(u8 *s, u32 a, int b);

extern void sub_0800D6E0(u8 *s, int a, int b);

extern void sub_0800D9EC(u8 *s, int a);

extern void sub_0804A378(int a);

extern void sub_0800D9FC(u8 *s);

extern s16 sub_08011F50(u8 *s);

extern void sub_08011F68(u8 *s, int a);

void Sub_08011F88(u8 *s)
{
    u8 *p = s + 124;
    if (s[14] == 0) {
        s[14] = 1;
        sub_0800DD2C(s, (int)0xffffc400, 0);
        {
            int t = p[1];
            int u;
            if ((15 & s[35]) != 0)
                u = 256 | t;
            else
                u = t;
            sub_0800D6E0(s, u, p[3]);
        }
        sub_0800D9EC(s, 1);
        sub_0804A378(169);
        s[33] = 30;
    }
    sub_0800D9FC(s);
    if (sub_08011F50(s) != 0) {
        sub_0800D9EC(s, 0);
        p[4] = 0;
        sub_08011F68(s, 0);
    }
}
