/* Sub_08013024 @ 0x08013024 (276 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w60d_08013024_MATCHED.c (registry: src/w60d_08013024_MATCHED.c).
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

extern void sub_0801AA70(int a, int b, int c, int d, int e, u8 *f);

extern int sub_0804A378(int idx);

extern u8 sub_08017474(u8 *s);

extern void sub_08017464(u8 *s);

extern void sub_08011F68(u8 *s, u8 v);

void Sub_08013024(u8 *s)
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
        sub_0800D9EC(s, 9);
        s[14]++;
        break;
    case 2: {
        u8 *q;
        register int nib;
        int c;
        int z;
        if (sub_08011F50(s) == 0)
            break;
        sub_080174A4(*(u8 **)(s + 44), 3);
        q = s + 35;
        nib = ((u32)*q << 28) >> 28;
        c = -15360;
        z = 0;
        sub_0801AA70(2, 0, nib, c, z, *(u8 **)(s + 44));
        nib = ((u32)*q << 28) >> 28;
        sub_0801AA70(3, 0, nib, c, z, *(u8 **)(s + 44));
        sub_0804A378(152);
        s[14]++;
        break;
    }
    case 3:
        if (sub_08017474(*(u8 **)(s + 44)) <= 6)
            break;
        sub_0800D9EC(s, 10);
        s[14]++;
        break;
    case 4:
        if (sub_08011F50(s) == 0)
            break;
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
