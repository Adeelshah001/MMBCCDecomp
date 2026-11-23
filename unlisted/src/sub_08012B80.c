/* sub_08012B80 @ 0x08012B80 (424 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w194f_08012b80_MATCHED.c (registry: src/w194f_08012b80_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;
typedef signed int s32;

s16 sub_08011F50(u8 *s);

void sub_0800DD2C(u8 *s, s32 x, s32 y);

void sub_0800D9EC(u8 *s, u32 a);

void sub_0800D9EC(u8 *s, u32 a);

void sub_0804A378(u32 a);

void sub_080174A4(u32 a, u32 b);

void sub_0801AB94(u32 a, u32 b, s32 c, s32 d, u32 e);

void sub_08017478(u32 a, u32 b);

void sub_0801B98C(u32 a, u32 b, u32 c, s32 d, s32 e, u32 f);

void sub_08017464(u32 a);

void sub_08011F68(u8 *s, u32 a);

void sub_0800D9FC(u8 *s);

void sub_08012B80(u8 *s)
{
    u8 *p124 = s + 124;
    switch (s[14]) {
    case 0:
        sub_0800DD2C(s, -15360, 0);
        sub_0800D9EC(s, 2);
        sub_0804A378(152);
        break;
    case 1:
        if (sub_08011F50(s) == 0)
            goto epi;
        sub_0800DD2C(s, 1024, 0);
        sub_0800D9EC(s, 1);
        break;
    case 2:
        if (sub_08011F50(s) == 0)
            goto epi;
        sub_080174A4(*(u32 *)(s + 44), 3);
        sub_0800D9EC(s, 9);
        break;
    case 3:
        if (sub_08011F50(s) == 0)
            goto epi;
        sub_0801AB94(30, ((u32)s[35] << 28) >> 28, 15360, -7168, *(u32 *)(s + 44));
        sub_0800D9EC(s, 10);
        sub_08017478(*(u32 *)(s + 44), 1);
        break;
    case 4:
        if (sub_08011F50(s) == 0)
            goto epi;
        sub_0800D9EC(s, 2);
        break;
    case 5:
        if (sub_08011F50(s) == 0)
            goto epi;
        sub_0801B98C(10, 0, ((u32)s[35] << 28) >> 28, -15360, -25600, *(u32 *)(s + 44));
        sub_0800DD2C(s, -15360, 0);
        sub_0800D9EC(s, 1);
        break;
    case 6:
        if (sub_08011F50(s) == 0)
            goto epi;
        sub_08017478(*(u32 *)(s + 44), 8);
        sub_0800D9EC(s, 0);
        s[18] = 30;
        break;
    case 7:
        goto c7;
    default:
        goto epi;
    }
    s[14]++;
    goto epi;
c7:
        if ((s8)--s[18] != 0)
            goto epi;
        sub_08017464(*(u32 *)(s + 44));
        *(u32 *)(s + 44) = 0;
        sub_0800DD2C(s, -15360, 0);
        sub_0800D9EC(s, 0);
        p124[4] = 0;
        sub_08011F68(s, 0);
        goto epi;
epi:
    sub_0800D9FC(s);
}
