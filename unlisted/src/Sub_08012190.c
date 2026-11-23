/* Sub_08012190 @ 0x08012190 (228 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w50d_08012190_MATCHED.c (registry: src/w50d_08012190_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;

extern s16 gUnknown_08223ED8[][2];

extern void sub_0800DD2C(u8 *s, int x, int y);

extern void sub_0800D9EC(u8 *s, u8 idx);

extern void sub_0800D9FC(u8 *s);

extern short sub_08011F50(u8 *s);

extern void sub_08011F68(u8 *s, u8 v);

extern void sub_080174A4(u32 a, int b);

extern u8 sub_08017474(u32 a);

extern void sub_08017464(u32 a);

extern void sub_0801AA70(int a, u8 b, int c, s16 d, s16 e, u32 f);

void Sub_08012190(u8 *s)
{
    u8 *t = s + 124;
    switch (s[14]) {
    case 0:
        sub_0800DD2C(s, -15360, 0);
        sub_0800D9EC(s, 11);
        s[14]++;
        break;
    case 1:
        if (sub_08011F50(s) == 0)
            break;
        sub_080174A4(*(u32 *)(s + 44), 3);
        {
            u8 m = s[17];
            int nib = ((u32)s[35] << 28) >> 28;
            s16 (*tp)[2] = gUnknown_08223ED8;
            s16 *e = tp[t[0]];
            sub_0801AA70(22, m, nib, e[0], e[1], *(u32 *)(s + 44));
        }
        sub_0800D9EC(s, 12);
        s[14]++;
        break;
    case 2:
        if (sub_08011F50(s) == 0)
            break;
        sub_0800D9EC(s, 13);
        s[14]++;
        break;
    case 3:
        if ((u8)sub_08017474(*(u32 *)(s + 44)) > 6) {
            sub_08017464(*(u32 *)(s + 44));
            *(u32 *)(s + 44) = 0;
            sub_0800DD2C(s, -15360, 0);
            sub_0800D9EC(s, 0);
            t[4] = 0;
            sub_08011F68(s, 0);
        }
        break;
    default:
        break;
    }
    sub_0800D9FC(s);
}
