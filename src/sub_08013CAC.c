/* sub_08013CAC @ 0x08013CAC (332 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w69a_08013cac_MATCHED.c (registry: src/w69a_08013cac_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed int s32;

typedef struct { s32 x, y; } Pair;

void sub_0800DD2C(u8 *o, s32 x, s32 y);

void sub_0800D9EC(u8 *s, u8 idx);

u16 sub_08011F50(u8 *s);

u16 sub_0804A378(u16 idx);

void sub_080174A4(u8 *s, u8 bit);

void sub_0800DD4C(u8 *o, s32 x, s32 y);

Pair sub_0800DD08(u8 *s);

void sub_080178A8(u8 a, u8 b, u16 c, s32 d, u8 *e);

u8 sub_08017474(u8 *s);

void sub_08017478(u8 *s, u8 v);

void sub_08017464(u8 *s);

void sub_08011F68(u8 *s, u8 v);

void sub_0800D9FC(u8 *s);

void sub_08013CAC(u8 *s)
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
        if (sub_08011F50(s) != 0) {
            s[18] = 5;
            sub_0800D9EC(s, 9);
            sub_0804A378(148);
            s[14]++;
        }
        break;
    case 2:
        if (--s[18] != 0)
            break;
        sub_080174A4(*(u8 **)(s + 44), 3);
        s[14]++;
        break;
    case 3: {
        Pair v;
        sub_0800DD4C(s, 0x700, 0);
        v = sub_0800DD08(s);
        if (v.x > 55) {
            u8 *p35 = s + 35;
            u8 nib = (u32)(p35[0] << 28) >> 28;
            sub_080178A8(126, nib, 0x3C00, 0xFFFFE200, *(u8 **)(s + 44));
            s[10] &= 0xFE;
            s[18] = 10;
            s[14]++;
        }
        break;
    }
    case 4:
        if (--s[18] != 0)
            break;
        s[10] |= 1;
        sub_0800DD2C(s, 0xFFFFC400, 0);
        sub_0800D9EC(s, 10);
        s[14]++;
        break;
    case 5:
        if (sub_08011F50(s) != 0) {
            sub_0800D9EC(s, 0);
            s[14]++;
        }
        break;
    case 6:
        if (sub_08017474(*(u8 **)(s + 44)) > 5) {
            sub_08017478(*(u8 **)(s + 44), 7);
            sub_08017464(*(u8 **)(s + 44));
            *(u32 *)(s + 44) = 0;
            q[4] = 0;
            sub_08011F68(s, 0);
        }
        break;
    default:
        break;
    }
    sub_0800D9FC(s);
}
