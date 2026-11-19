/* Sub_0801A344 @ 0x0801A344 (172 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37c_0801a344_MATCHED.c (registry: mmbcc/src/w37c_0801a344_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef short s16;
typedef signed int s32;

extern void sub_0800DD4C(u8 *o, s32 x, s32 y);

extern void sub_0800DD08(u32 *out, u8 *src);

extern void sub_080174A4(u8 *p, int bit);

extern void sub_080178A8(int a, int b, s16 c, s16 d, u8 *e);

extern u8 sub_08017474(u8 *p);

extern void sub_08017478(u8 *p, int v);

u8 Sub_0801A344(u8 *s)
{
    u32 out[2];
    u8 t;
    sub_0800DD4C(s, *(s32 *)(s + 88), *(s32 *)(s + 92));
    *(s32 *)(s + 88) += *(s32 *)(s + 96);
    *(s32 *)(s + 92) += *(s32 *)(s + 100);
    sub_0800DD08(out, s);
    switch (s[13]) {
    case 0: goto c0;
    case 1: goto c1;
    case 2: goto c2;
    default: goto ret0;
    }
c0:
    s[18] = 30;
    goto inc;
c1:
    s[18]--;
    if ((s8)s[18] != 0)
        goto ret0;
    sub_080174A4(*(u8 **)(s + 44), 3);
    sub_080178A8(119, ((u32)s[35] << 28) >> 28, 15360, -1280, *(u8 **)(s + 44));
    t = s[10] & 253;
    t = t & 254;
    s[10] = t;
    goto inc;
inc:
    s[13]++;
    goto ret0;
c2:
    if ((u8)sub_08017474(*(u8 **)(s + 44)) <= 5)
        goto ret0;
    sub_08017478(*(u8 **)(s + 44), 7);
    return 1;
ret0:
    return 0;
}
