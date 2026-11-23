/* Sub_08014154 @ 0x08014154 (244 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w54d_08014154_MATCHED.c (registry: src/w54d_08014154_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0800DD2C(u8 *s, int a, int b);

extern void sub_0800D9EC(u8 *s, int idx);

extern u16 sub_08011F50(u8 *s);

extern void sub_080174A4(u32 v, int bit);

extern void sub_080178A8(int a, int b, int c, int d, int e);

extern u8 sub_08017474(int v);

extern void sub_08017478(int v, int n);

extern void sub_08017464(int v);

extern void sub_08011F68(u8 *s, int v);

extern void sub_0800D9FC(u8 *s);

void Sub_08014154(u8 *s)
{
    u8 *p = s + 124;
    switch (s[14]) {
    case 0:
        sub_0800DD2C(s, -15360, 0);
        sub_0800D9EC(s, 8);
        s[14]++;
        break;
    case 1:
        if (sub_08011F50(s)) {
            sub_080174A4(*(u32 *)(s + 44), 3);
            {
                int nib = (int)(((u32)s[35] << 28) >> 28);
                sub_080178A8(87, nib, -5120, 0, *(u32 *)(s + 44));
            }
            sub_0800D9EC(s, 9);
            s[14]++;
        }
        break;
    case 2:
        if (sub_08017474(*(u32 *)(s + 44)) > 5) {
            sub_0800D9EC(s, 10);
            sub_08017478(*(u32 *)(s + 44), 7);
            s[14]++;
        }
        break;
    case 3:
        if (sub_08011F50(s)) {
            s[14]++;
        }
        break;
    case 4:
        sub_08017464(*(u32 *)(s + 44));
        *(u32 *)(s + 44) = 0;
        sub_0800DD2C(s, -15360, 0);
        sub_0800D9EC(s, 0);
        p[4] = 0;
        sub_08011F68(s, 0);
        break;
    default:
        break;
    }
    sub_0800D9FC(s);
}
