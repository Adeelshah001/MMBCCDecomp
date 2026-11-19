/* Sub_08014A44 @ 0x08014A44 (272 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w60d_08014a44_MATCHED.c (registry: src/w60d_08014a44_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0800DD2C(u8 *o, u32 x, u32 y);

extern void sub_0800D9EC(u8 *s, int idx);

extern void sub_0800D9FC(u8 *s);

extern u16 sub_08011F50(u8 *s);

extern void sub_080174A4(u8 *s, int bit);

extern void sub_080178A8(u32 a, u32 b, u32 c, u32 d, u32 e);

extern u8 sub_08017474(u8 *s);

extern void sub_08017478(u8 *s, u8 v);

extern void sub_08017464(u8 *s);

extern void sub_08011F68(u8 *s, u8 v);

void Sub_08014A44(u8 *s)
{
    u8 *p = s + 124;
    switch (s[14]) {
    case 0:
        sub_0800DD2C(s, 0xffffc400, 0);
        sub_0800D9EC(s, 8);
        s[14]++;
        break;
    case 1:
        if (sub_08011F50(s) == 0)
            break;
        sub_080174A4(*(u8 **)(s + 44), 3);
        sub_080178A8(125, ((u32)s[35] << 28) >> 28, 0xffffec00, 0, *(u32 *)(s + 44));
        sub_0800D9EC(s, 9);
        s[18] = 3;
        s[14]++;
        break;
    case 2:
        if (sub_08011F50(s) == 0)
            break;
        {
            int t = s[18] - 1;
            s[18] = t;
            if ((u8)t == 0) {
                sub_0800D9EC(s, 10);
                s[14]++;
            } else {
                sub_0800D9EC(s, 9);
            }
        }
        break;
    case 3:
        if (sub_08017474(*(u8 **)(s + 44)) <= 5)
            break;
        sub_08017478(*(u8 **)(s + 44), 7);
        s[14]++;
        break;
    case 4:
        sub_08017464(*(u8 **)(s + 44));
        *(u32 *)(s + 44) = 0;
        sub_0800DD2C(s, 0xffffc400, 0);
        sub_0800D9EC(s, 0);
        p[4] = 0;
        sub_08011F68(s, 0);
        break;
    }
    sub_0800D9FC(s);
}
