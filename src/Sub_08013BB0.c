/* Sub_08013BB0 @ 0x08013BB0 (252 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w55d_08013bb0_MATCHED.c (registry: src/w55d_08013bb0_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed int s32;

extern void sub_0800DD2C(u8 *o, s32 x, s32 y);

extern u16 sub_08011F50(u8 *s);

extern void sub_0801EBF0(int a, int b, int c, int d, int e);

extern void sub_080174A4(u32 v, int bit);

extern void sub_080178A8(int a, int b, int c, int d, u32 e);

extern u8 sub_08017474(u32 v);

extern void sub_08017478(u32 v, int n);

extern void sub_08017464(u32 v);

extern void sub_0800D9EC(u8 *s, int idx);

extern void sub_08011F68(u8 *s, u8 v);

extern void sub_0800D9FC(u8 *s);

void Sub_08013BB0(u8 *s)
{
    u8 *p = s + 124;
    int mode;
    mode = s[14];
    if (mode == 1)
        goto c1;
    if (mode > 1)
        goto gt1;
    if (mode == 0)
        goto c0;
    goto tail;
gt1:
    if (mode == 2)
        goto c2;
    if (mode == 3)
        goto c3;
    goto tail;
c0:
    sub_0800DD2C(s, -15360, 0);
    sub_0800D9EC(s, 8);
    s[14]++;
    goto tail;
c1:
    if (sub_08011F50(s) == 0)
        goto tail;
    sub_0801EBF0(33, -1, ((u32)s[35] << 28) >> 28, -15360, 0);
    sub_0800D9EC(s, 9);
    s[14]++;
    goto tail;
c2:
    if (sub_08011F50(s) == 0)
        goto tail;
    sub_080174A4(*(u32 *)(s + 44), 3);
    {
        int nib = ((u32)s[35] << 28) >> 28;
        sub_080178A8(86, nib, -5120, -7680, *(u32 *)(s + 44));
    }
    sub_0800D9EC(s, 10);
    s[14]++;
    goto tail;
c3:
    if ((u8)sub_08017474(*(u32 *)(s + 44)) <= 5)
        goto tail;
    sub_08017478(*(u32 *)(s + 44), 7);
    sub_08017464(*(u32 *)(s + 44));
    *(u32 *)(s + 44) = 0;
    sub_0800DD2C(s, -15360, 0);
    sub_0800D9EC(s, 0);
    p[4] = 0;
    sub_08011F68(s, 0);
    goto tail;
tail:
    sub_0800D9FC(s);
}
