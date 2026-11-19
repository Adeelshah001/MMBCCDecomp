/* Sub_08015644 @ 0x08015644 (232 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w51a_08015644_MATCHED.c (registry: src/w51a_08015644_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;

extern void sub_0800D9EC(u8 *s, u8 n);

extern void sub_0800D9FC(u8 *s);

extern void sub_0800DD2C(u8 *o, int x, int y);

extern short sub_08011F50(u8 *s);

extern void sub_08011F68(u8 *s, int a);

extern u8 sub_08017474(u32 a);

extern void sub_08017464(u32 a);

extern void sub_0801AA70(int a, int b, int c, int d, int e, u32 f);

extern u8 gUnknown_08223E60[][2];

extern s16 gUnknown_08223ED8[][2];

void sub_08015644(u8 *s)
{
    u8 *t = s + 124;
    switch (s[14]) {
    case 0:
        sub_0800D9EC(s, 2);
        s[14]++;
        break;
    case 1: {
        int b0, b1, nib;
        s16 (*tp)[2];
        s16 *e;
        if (sub_08011F50(s) == 0)
            break;
        b0 = gUnknown_08223E60[s[17]][0];
        b1 = gUnknown_08223E60[s[17]][1];
        nib = (int)(((u32)s[35] << 28) >> 28);
        tp = gUnknown_08223ED8;
        e = tp[t[0]];
        sub_0801AA70(b0, b1, nib, e[0], e[1], *(u32 *)(s + 44));
        s[10] &= 0xfe;
        s[14]++;
        break;
    }
    case 2:
        if (sub_08017474(*(u32 *)(s + 44)) <= 6)
            break;
        s[10] |= 1;
        sub_0800D9EC(s, 1);
        s[14]++;
        break;
    case 3:
        if (sub_08011F50(s) == 0)
            break;
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
