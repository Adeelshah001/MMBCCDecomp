/* Sub_08019D18 @ 0x08019D18 (242 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w54d_08019d18_MATCHED.c (registry: src/w54d_08019d18_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef short s16;

extern void sub_0800DD4C(u8 *s, int a, int b);

extern void sub_0800DD08(u8 *out, u8 *s);

extern void sub_080174A4(u32 v, int bit);

extern void sub_0800D9EC(u8 *s, int idx);

extern void sub_080178A8(int a, int b, int c, int d, int e);

extern u8 sub_08017494(u32 v, int bit);

extern u8 sub_08017474(int v);

int Sub_08019D18(u8 *s)
{
    u32 out[2];
    register int out0;
    register int out1;
    int mode;
    sub_0800DD4C(s, *(u32 *)(s + 88), *(u32 *)(s + 92));
    *(u32 *)(s + 88) += *(u32 *)(s + 96);
    *(u32 *)(s + 92) += *(u32 *)(s + 100);
    sub_0800DD08((u8 *)out, s);
    out0 = out[0];
    out1 = out[1];
    mode = s[13];
    switch (mode) {
    case 0:
        if ((u8)(s[119] - 3) <= 1) {
            sub_080174A4(*(u32 *)(s + 44), 3);
            sub_0800D9EC(s, 1);
            *(u32 *)(s + 88) = 128 << 3;
            *(u32 *)(s + 96) = 10;
            *(u32 *)(s + 92) = mode;
            *(u32 *)(s + 100) = mode;
            s[13]++;
        }
        break;
    case 1:
        if (out0 > 200 << 6) {
            int nib = (int)(((u32)s[35] << 28) >> 28);
            sub_080178A8(93, nib, (s16)out0, (s16)(out1 - 7680), *(u32 *)(s + 44));
            if (sub_08017494(*(u32 *)(s + 44), 0) != 0) {
                s[13] = 2;
            } else {
                u32 t = 253 & s[10];
                s[10] = t & 254;
                s[13] = 3;
            }
        }
        break;
    case 2:
        if (out0 > 130 << 8)
            return 1;
        break;
    case 3:
        if (sub_08017474(*(u32 *)(s + 44)) > 5)
            return 1;
        break;
    default:
        break;
    }
    return 0;
}
