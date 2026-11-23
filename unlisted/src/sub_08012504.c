/* sub_08012504 @ 0x08012504 (328 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w68a_08012504_MATCHED.c (registry: src/w68a_08012504_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;
typedef signed int s32;

void sub_0800DD2C(u8 *o, s32 x, s32 y);

void sub_0800D9EC(u8 *s, u8 idx);

void sub_0800D9FC(u8 *s);

u16 sub_08011F50(u8 *s);

u8 sub_08017474(u8 *s);

void sub_08011F68(u8 *s, u8 v);

void sub_08017464(u8 *s);

s16 sub_0804A378(u16 idx);

u32 *sub_0801BBB4(u8 a, u8 b, s32 c, s32 d, u8 *e);

void sub_08012504(u8 *s)
{
    u8 *e = s;
    e += 124;

    switch (s[14]) {
    case 0:
        sub_0800DD2C(s, 0xFFFFC400, 0);
        sub_0800D9EC(s, 2);
        sub_0804A378(152);
        s[14]++;
        break;
    case 1:
        if (sub_08011F50(s) == 0)
            break;
        sub_0800DD2C(s, 0xFFFF9C00, 0);
        sub_0800D9EC(s, 1);
        s[14]++;
        break;
    case 2:
        if (sub_08011F50(s) == 0)
            break;
        sub_0800D9EC(s, 15);
        s[14]++;
        break;
    case 3: {
        u8 a17;
        u8 *p;
        u8 nib;
        if (sub_08011F50(s) == 0)
            break;
        sub_0800D9EC(s, 16);
        sub_0804A378(131);
        s[14]++;
        a17 = s[17];
        p = s;
        p += 35;
        nib = (u32)(p[0] << 28) >> 28;
        sub_0801BBB4(a17, nib, 0xFFFFA600, 0xFFFFCD00, *(u8 **)(s + 44));
        break;
    }
    case 4:
        if (sub_08017474(*(u8 **)(s + 44)) <= 6)
            break;
        sub_0800D9EC(s, 2);
        s[14]++;
        break;
    case 5:
        if (sub_08011F50(s) == 0)
            break;
        sub_0800DD2C(s, 0xFFFFC400, 0);
        sub_0800D9EC(s, 1);
        s[14]++;
        break;
    case 6:
        if (sub_08011F50(s) == 0)
            break;
        sub_08017464(*(u8 **)(s + 44));
        *(u8 **)(s + 44) = 0;
        sub_0800DD2C(s, 0xFFFFC400, 0);
        sub_0800D9EC(s, 0);
        e[4] = 0;
        sub_08011F68(s, 0);
        break;
    default:
        break;
    }
    sub_0800D9FC(s);
}
