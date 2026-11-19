/* sub_08012A3C @ 0x08012A3C (324 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w66a_08012a3c_MATCHED.c (registry: src/w66a_08012a3c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed int s32;

void sub_0800DD2C(u8 *o, s32 x, s32 y);

void sub_0800D9EC(u8 *s, u8 idx);

void sub_0800D9FC(u8 *s);

u16 sub_08011F50(u8 *s);

void sub_080174A4(u8 *s, u8 bit);

u16 sub_0804A378(u16 idx);

u32 *sub_0801EBF0(u8 a, s32 b, u8 c, s32 d, u16 e);

u32 *sub_080178A8(u8 a, u8 b, u16 c, s32 d, u8 *e);

u8 sub_08017474(u8 *s);

void sub_08017478(u8 *s, u8 v);

void sub_08017464(u8 *s);

void sub_08011F68(u8 *s, u8 v);

void sub_08012A3C(u8 *s)
{
    u8 *q = s;
    q += 124;

    switch (s[14]) {
    case 0: {
        s32 neg = -1;
        u8 *p = s;
        u8 nib;
        s32 v;
        p += 35;
        nib = (u32)(p[0] << 28) >> 28;
        v = 0xFFFFC400;
        sub_0801EBF0(63, neg, nib, v, 0);
        sub_0804A378(166);
        sub_0800DD2C(s, v, 0);
        sub_0800D9EC(s, 8);
        s[18] = 40;
        s[14]++;
        break;
    }
    case 1:
        if (--s[18] != 0)
            break;
        sub_080174A4(*(u8 **)(s + 44), 3);
        sub_0804A378(122);
        sub_0800D9EC(s, 9);
        s[14]++;
        break;
    case 2: {
        u8 *p = s;
        u8 nib;
        if (sub_08011F50(s) == 0)
            break;
        p += 35;
        nib = (u32)(p[0] << 28) >> 28;
        sub_080178A8(135, nib, 14080, 0xFFFFE700, *(u8 **)(s + 44));
        sub_0800D9EC(s, 10);
        s[14]++;
        break;
    }
    case 3:
        if (sub_08011F50(s) == 0)
            break;
        s[18] = 10;
        s[14]++;
        break;
    case 4:
        if (--s[18] == 0)
            s[14]++;
        /* fallthrough */
    case 5:
        if (sub_08017474(*(u8 **)(s + 44)) <= 5)
            break;
        sub_08017478(*(u8 **)(s + 44), 7);
        sub_08017464(*(u8 **)(s + 44));
        *(u8 **)(s + 44) = 0;
        sub_0800DD2C(s, 0xFFFFC400, 0);
        sub_0800D9EC(s, 0);
        q[4] = 0;
        sub_08011F68(s, 0);
        break;
    default:
        break;
    }
    sub_0800D9FC(s);
}
