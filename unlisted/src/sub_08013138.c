/* sub_08013138 @ 0x08013138 (328 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w68a_08013138_MATCHED.c (registry: src/w68a_08013138_MATCHED.c).
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

u8 sub_08017474(u8 *s);

void sub_08011F68(u8 *s, u8 v);

u8 sub_080174A4(u8 *s, u8 v);

void sub_08017464(u8 *s);

u32 *sub_0801AA70(u8 a, u8 b, u8 c, u16 d, u16 e, u8 *f);

void sub_08013138(u8 *s)
{
    u8 *e = s;
    e += 124;

    switch (s[14]) {
    case 0:
        sub_0800DD2C(s, 0xFFFFC400, 0);
        sub_0800D9EC(s, 2);
        s[14]++;
        break;
    case 1:
        if (sub_08011F50(s) == 0)
            break;
        sub_0800DD2C(s, 0xFFFFEC00, 0);
        sub_0800D9EC(s, 1);
        s[14]++;
        break;
    case 2:
        if (sub_08011F50(s) == 0)
            break;
        sub_0800D9EC(s, 8);
        s[14]++;
        break;
    case 3: {
        u8 *p = s;
        u8 nib;
        if (sub_08011F50(s) == 0)
            break;
        sub_080174A4(*(u8 **)(s + 44), 3);
        p += 35;
        nib = (u32)(p[0] << 28) >> 28;
        sub_0801AA70(31, 0, nib, 0x1400, 0, *(u8 **)(s + 44));
        sub_0800D9EC(s, 9);
        s[14]++;
        break;
    }
    case 4:
        if (sub_08017474(*(u8 **)(s + 44)) <= 6)
            break;
        sub_0800D9EC(s, 10);
        s[14]++;
        break;
    case 5:
        if (sub_08011F50(s) == 0)
            break;
        sub_0800D9EC(s, 2);
        s[14]++;
        break;
    case 6:
        if (sub_08011F50(s) == 0)
            break;
        sub_0800DD2C(s, 0xFFFFC400, 0);
        sub_0800D9EC(s, 1);
        s[14]++;
        break;
    case 7:
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
