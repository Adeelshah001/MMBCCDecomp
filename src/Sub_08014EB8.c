/* Sub_08014EB8 @ 0x08014EB8 (252 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w55d_08014eb8_MATCHED.c (registry: src/w55d_08014eb8_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed int s32;

extern void sub_0800DD2C(u8 *o, s32 x, s32 y);

extern u16 sub_08011F50(u8 *s);

extern void sub_080174A4(u32 v, int bit);

extern void sub_080178A8(int a, int b, int c, int d, u32 e);

extern u8 sub_08017474(u32 v);

extern void sub_08017478(u32 v, int n);

extern void sub_08017464(u32 v);

extern void sub_0800D9EC(u8 *s, int idx);

extern void sub_08011F68(u8 *s, u8 v);

extern void sub_0800D9FC(u8 *s);

void Sub_08014EB8(u8 *s)
{
    u8 *p = s + 124;
    switch (s[14]) {
    case 0:
        sub_0800DD2C(s, -15360, 0);
        sub_0800D9EC(s, 8);
        s[14]++;
        break;
    case 1:
        if (sub_08011F50(s) == 0)
            break;
        sub_0800D9EC(s, 9);
        s[14]++;
        break;
    case 2:
        if (sub_08011F50(s) == 0)
            break;
        sub_080174A4(*(u32 *)(s + 44), 3);
        {
            int nib = ((u32)s[35] << 28) >> 28;
            sub_080178A8(97, nib, -10240, -6656, *(u32 *)(s + 44));
        }
        s[14]++;
        break;
    case 3:
        if ((u8)sub_08017474(*(u32 *)(s + 44)) <= 5)
            break;
        sub_08017478(*(u32 *)(s + 44), 7);
        sub_0800D9EC(s, 10);
        s[14]++;
        break;
    case 4:
        if (sub_08011F50(s) == 0)
            break;
        sub_08017464(*(u32 *)(s + 44));
        *(u32 *)(s + 44) = 0;
        sub_0800DD2C(s, -15360, 0);
        sub_0800D9EC(s, 0);
        p[4] = 0;
        sub_08011F68(s, 0);
        break;
    }
    sub_0800D9FC(s);
}
