/* Sub_08013280 @ 0x08013280 (232 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w50d_08013280_MATCHED.c (registry: src/w50d_08013280_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0800D9EC(u8 *s, u8 n);

extern void sub_0800D9FC(u8 *s);

extern void sub_0800DD2C(u8 *o, int x, int y);

extern short sub_08011F50(u8 *s);

extern void sub_08011F68(u8 *s, int a);

extern void sub_080174A4(u32 a, int b);

extern u8 sub_08017474(u32 a);

extern void sub_08017478(u32 a, int b);

extern void sub_08017464(u32 a);

extern void sub_080178A8(int a, int b, int c, int d, u32 e);

void Sub_08013280(u8 *s)
{
    u8 *t = s + 124;
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
        sub_080178A8(133, (int)(((u32)s[35] << 28) >> 28), 0x3c00, 0, *(u32 *)(s + 44));
        sub_0800D9EC(s, 10);
        s[14]++;
        break;
    case 3:
        if (sub_08011F50(s) == 0)
            break;
        sub_0800D9EC(s, 9);
        s[14]++;
        break;
    case 4:
        if (sub_08017474(*(u32 *)(s + 44)) <= 5)
            break;
        sub_08017478(*(u32 *)(s + 44), 7);
        sub_08017464(*(u32 *)(s + 44));
        *(u32 *)(s + 44) = 0;
        sub_0800DD2C(s, -15360, 0);
        sub_0800D9EC(s, 0);
        t[4] = 0;
        sub_08011F68(s, 0);
        break;
    default:
        break;
    }
    sub_0800D9FC(s);
}
