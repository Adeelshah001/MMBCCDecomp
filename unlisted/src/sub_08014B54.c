/* sub_08014B54 @ 0x08014B54 (412 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w83a_08014b54_MATCHED.c (registry: mmbcc/src/w83a_08014b54_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;
typedef signed int s32;

void sub_0800DD2C(u8 *s, s32 x, s32 y);

void sub_0800D9EC(u8 *s, u32 a);

void sub_0804A378(u32 a);

s16 sub_08011F50(u8 *s);

void sub_080174A4(u32 a, u32 b);

void sub_080178A8(u32 a, u32 b, s32 c, s32 d, u32 e);

u8 sub_08017474(u8 *s);

void sub_08017478(u32 a, u32 b);

void sub_08017464(u32 a);

void sub_08011F68(u8 *s, u32 a);

void sub_0800D9FC(u8 *s);

extern u8 gUnknown_02003670[];

void sub_08014B54(u8 *s)
{
    u8 *q = s + 124;
    switch (s[14]) {
    case 0:
        sub_0800DD2C(s, -15360, 0);
        sub_0800D9EC(s, 2);
        sub_0804A378(152);
        s[14]++;
        break;
    case 1:
        if (sub_08011F50(s) == 0)
            break;
        sub_0800DD2C(s, -1536, 0);
        sub_0800D9EC(s, 1);
        s[14]++;
        break;
    case 2:
        if (sub_08011F50(s) == 0)
            break;
        sub_080174A4(*(u32 *)(s + 44), 3);
        sub_0800D9EC(s, 8);
        s[14]++;
        break;
    case 3:
        if (sub_08011F50(s) == 0)
            break;
        sub_080178A8(132, ((u32)s[35] << 28) >> 28, 240 << 6, 0, *(u32 *)(s + 44));
        sub_0800D9EC(s, 9);
        s[14]++;
        break;
    case 4:
        if (sub_08011F50(s) == 0)
            break;
        {
            u8 mk = 15;
            u32 off = 0x11AF;
            u8 *p = gUnknown_02003670 + off;
            u8 c = 240;
            u8 b = *p;
            *p = (b & mk) | c;
        }
        sub_0804A378(135);
        s[18] = 25;
        s[14]++;
        break;
    case 5:
        if ((s8)--s[18] != 0)
            break;
        sub_0800D9EC(s, 10);
        s[14]++;
        break;
    case 6:
        if (sub_08011F50(s) == 0)
            break;
        sub_0800D9EC(s, 2);
        s[14]++;
        break;
    case 7:
        if (sub_08011F50(s) == 0)
            break;
        sub_0800DD2C(s, -15360, 0);
        sub_0800D9EC(s, 2);
        s[14]++;
        break;
    case 8:
        if (sub_08011F50(s) == 0)
            break;
        sub_0800D9EC(s, 0);
        s[14]++;
        break;
    case 9:
        if ((u8)sub_08017474((u8 *)*(u32 *)(s + 44)) <= 5)
            break;
        sub_08017478(*(u32 *)(s + 44), 7);
        sub_08017464(*(u32 *)(s + 44));
        *(u32 *)(s + 44) = 0;
        q[4] = 0;
        sub_08011F68(s, 0);
        break;
    default:
        break;
    }
    sub_0800D9FC(s);
}
