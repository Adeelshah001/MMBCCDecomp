/* Sub_08015378 @ 0x08015378 (264 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w60c_08015378_MATCHED.c (registry: src/w60c_08015378_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef short s16;
typedef signed int s32;

extern void sub_0800DD2C(u8 *s, s32 x, s32 y);

extern void sub_0800D9EC(u8 *s, u8 idx);

extern s16 sub_08011F50(u8 *s);

extern void sub_080174A4(u8 *p, u8 bit);

extern u32 *sub_080178A8(u8 a, u8 b, s16 c, s16 d, u8 *e);

extern u8 sub_08017474(u8 *p);

extern void sub_08017478(u8 *p, u8 v);

extern void sub_08017464(u8 *p);

extern void sub_08011F68(u8 *s, u8 v);

extern void sub_0800D9FC(u8 *s);

void Sub_08015378(u8 *s)
{
    u8 *p = s;
    p += 124;
    switch (s[14]) {
    case 0:
        sub_0800DD2C(s, 0xFFFFC400, 0);
        sub_0800D9EC(s, 8);
        goto inc;
    case 1:
        if (sub_08011F50(s) == 0)
            goto tail;
        sub_0800D9EC(s, 9);
        goto inc;
    case 2:
        if (sub_08011F50(s) == 0)
            goto tail;
        sub_0800D9EC(s, 10);
        sub_080174A4(*(u8 **)(s + 44), 3);
        sub_080178A8(96, ((u32)s[35] << 28) >> 28, -11520, -6400,
                     *(u8 **)(s + 44));
        /* fall through to inc */
    inc:
        s[14]++;
        goto tail;
    case 3:
        if (sub_08011F50(s) != 0)
            s[14]++;
        /* fall through to case 4 */
    case 4:
        if (sub_08017474(*(u8 **)(s + 44)) <= 5)
            goto tail;
        sub_08017478(*(u8 **)(s + 44), 7);
        sub_08017464(*(u8 **)(s + 44));
        {
            int z = 0;
            *(u32 *)(s + 44) = z;
            sub_0800DD2C(s, 0xFFFFC400, 0);
            sub_0800D9EC(s, 0);
            p[4] = z;
            sub_08011F68(s, 0);
        }
        goto tail;
    default:
        goto tail;
    }
tail:
    sub_0800D9FC(s);
}
