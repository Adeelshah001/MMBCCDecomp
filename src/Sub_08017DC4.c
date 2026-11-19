/* Sub_08017DC4 @ 0x08017DC4 (168 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37c_08017dc4_MATCHED.c (registry: mmbcc/src/w37c_08017dc4_MATCHED.c).
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

u8 Sub_08017DC4(u8 *s)
{
    u32 out[2];
    s32 x;
    s32 y;
    u8 mode;
    sub_0800DD4C(s, *(s32 *)(s + 88), *(s32 *)(s + 92));
    *(s32 *)(s + 88) += *(s32 *)(s + 96);
    *(s32 *)(s + 92) += *(s32 *)(s + 100);
    sub_0800DD08(out, s);
    x = out[0];
    y = out[1];
    mode = s[13];
    switch (mode) {
    case 0: goto c0;
    case 1: goto c1;
    case 2: goto c2;
    default: goto ret0;
    }
c0:
    if (y <= -1024)
        goto ret0;
    sub_080174A4(*(u8 **)(s + 44), 3);
    s[13]++;
    *(s32 *)(s + 88) = 1280;
    *(s32 *)(s + 96) = mode;
    *(s32 *)(s + 92) = mode;
    *(s32 *)(s + 100) = mode;
    goto ret0;
c1:
    if (x <= 12800)
        goto ret0;
    sub_080178A8(13, ((u32)s[35] << 28) >> 28, 15360, 0, *(u8 **)(s + 44));
    s[13]++;
    goto ret0;
c2:
    if (x <= 30720)
        goto ret0;
    return 1;
ret0:
    return 0;
}
