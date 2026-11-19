/* Sub_08013AD4 @ 0x08013AD4 (220 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w38a_08013ad4_MATCHED.c (registry: mmcc/src/w38a_08013ad4_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed int s32;

extern void sub_0800DD2C(u8 *o, s32 x, s32 y);

extern u16 sub_08011F50(u8 *s);

extern void sub_080174A4(u8 *s, int bit);

extern void sub_0801AA70(int a, int b, int c, int d, int e, u8 *f);

extern u8 sub_08017474(u8 *p);

extern void sub_08017464(u8 *s);

extern void sub_0800D9EC(u8 *s, int idx);

extern void sub_08011F68(u8 *s, u8 v);

extern void sub_0800D9FC(u8 *s);

void Sub_08013AD4(u8 *s)
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
    sub_080174A4(*(u8 **)(s + 44), 3);
    sub_0801AA70(18, 0, ((u32)s[35] << 28) >> 28, -11520, -8960,
        *(u8 **)(s + 44));
    sub_0800D9EC(s, 9);
    s[14]++;
    goto tail;
c2:
    if (sub_08011F50(s) == 0)
        goto tail;
    sub_0800D9EC(s, 10);
    s[14]++;
    goto tail;
c3:
    if ((u8)sub_08017474(*(u8 **)(s + 44)) <= 6)
        goto tail;
    sub_08017464(*(u8 **)(s + 44));
    *(u8 **)(s + 44) = 0;
    sub_0800DD2C(s, -15360, 0);
    sub_0800D9EC(s, 0);
    p[4] = 0;
    sub_08011F68(s, 0);
    goto tail;
tail:
    sub_0800D9FC(s);
}
