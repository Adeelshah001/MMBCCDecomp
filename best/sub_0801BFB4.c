/* Sub_0801BFB4 @ 0x0801BFB4 (124 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_0801bfb4_MATCHED.c (registry: mmbcc/src/w36b_0801bfb4_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0800D770(u8 *s, u32 a, u32 b);

extern void sub_0800D9EC(u8 *s, u32 x);

extern void sub_0800DD08(u8 *buf, u8 *s);

extern void sub_0800DD2C(u8 *s, u32 a, u32 b);

extern void sub_0804A378(u32 x);

void sub_0801BFB4(u8 *s)
{
    u8 buf[8];
    u16 v;
    int idx;
    u8 *tab;
    int x;
    sub_0800D770(s, 2090, 0);
    sub_0800D9EC(s, 0);
    v = *(u16 *)0x081705b0;
    idx = (v >> 4) * 2;
    tab = (u8 *)0x020031e4;
    x = tab[idx] & 3;
    if (x > 3) x = 3;
    s[69] = (s[69] & ~13) | (x << 2);
    s[34] = 13;
    sub_0800DD08(buf, s);
    sub_0800DD2C(s, 0xffffec00, 0);
    sub_0804A378(159);
}
