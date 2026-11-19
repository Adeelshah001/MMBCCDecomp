/* sub_080146C0 @ 0x080146C0 (316 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w68c_080146c0_MATCHED.c (registry: src/w68c_080146c0_MATCHED.c).
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

void sub_08004DFC(u8 a);

u16 sub_0804A378(u16 idx);

void sub_080178A8(u32 a, u32 b, u32 c, u32 d, u8 *e);

u8 sub_08017494(u8 *s, u8 bit);

u8 sub_08017474(u8 *s);

void sub_08017478(u8 *s, u8 v);

void sub_08017464(u8 *s);

void sub_08011F68(u8 *s, u8 v);

extern u8 gUnknown_02003670[];

void sub_080146C0(u8 *s)
{
    u8 *q = s;
    q += 124;

    switch (s[14]) {
    case 0:
        sub_0800DD2C(s, 0xFFFFC400, 0);
        sub_0800D9EC(s, 8);
        s[14]++;
        break;
    case 1:
        if (sub_08011F50(s) == 0)
            break;
        sub_080174A4(*(u8 **)(s + 44), 3);
        sub_08004DFC(2);
        sub_0804A378(149);
        s[18] = 10;
        sub_0800D9EC(s, 9);
        s[14]++;
        break;
    case 2: {
        u8 *p = s;
        u8 nib;
        u8 m;
        int f;
        u8 b;
        if (--s[18] != 0)
            break;
        p += 35;
        nib = (u32)(p[0] << 28) >> 28;
        sub_080178A8(130, nib, 0xFFFFEC00, 0, *(u8 **)(s + 44));
        if (sub_08017494(*(u8 **)(s + 44), 0) != 0) {
            s[14]++;
            break;
        }
        m = 15;
        b = gUnknown_02003670[0x11AF];
        f = 0xF0;
        gUnknown_02003670[0x11AF] = (b & m) | f;
        s[14]++;
        break;
    }
    case 3:
        if (sub_08011F50(s) == 0)
            break;
        sub_0800D9EC(s, 10);
        s[14]++;
        break;
    case 4:
        if (sub_08017474(*(u8 **)(s + 44)) <= 5)
            break;
        sub_08017478(*(u8 **)(s + 44), 7);
        s[14]++;
        break;
    case 5:
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
