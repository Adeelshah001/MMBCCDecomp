/* sub_08018064 @ 0x08018064 (326 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w69d_08018064_MATCHED.c (registry: src/w69d_08018064_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed int s32;

typedef struct { s32 x, y; } Pair;

void sub_0800DD4C(u8 *s, u32 a, u32 b);

void sub_0800DD08(u32 *out, u8 *s);

void sub_080178A8(int a, u32 b, int c, s32 d, u32 e);

u8 sub_08018064(u8 *s)
{
    volatile Pair v;
    s32 px;
    register s32 py;

    sub_0800DD4C(s, *(u32 *)(s + 88), *(u32 *)(s + 92));
    *(u32 *)(s + 88) += *(u32 *)(s + 96);
    *(u32 *)(s + 92) += *(u32 *)(s + 100);
    sub_0800DD08((u32 *)&v, s);
    px = v.x;
    py = v.y;
    if (s[16] == 2) {
        switch (s[13]) {
        case 0:
            if (px <= 11520)
                goto ret0;
            sub_080178A8(62, ((u32)s[35] << 28) >> 28, 15360, -7680, *(u32 *)(s + 44));
            break;
        case 1:
            if (px <= 30720)
                goto ret0;
            *(u32 *)(s + 88) = -1536;
            *(u32 *)(s + 96) = 0;
            { u8 tb = ((s[10] >> 4) ^ 1) & 1;
            u8 nv;
            s[72] = tb;
            if (tb != 0)
                nv = s[10] | 16;
            else
                nv = s[10] & 239;
            s[10] = nv; }
            break;
        case 2:
            if (px > 11519)
                goto ret0;
            sub_080178A8(63, ((u32)s[35] << 28) >> 28, 15360, -7680, *(u32 *)(s + 44));
            break;
        case 3:
            if (px >= -11008)
                goto ret0;
            return 1;
        default:
            goto ret0;
        }
        s[13]++;
        goto ret0;
    } else {
        switch (s[13]) {
        case 0:
            if (px <= 34560)
                goto ret0;
            { u8 tb = ((s[10] >> 4) ^ 1) & 1;
            u8 nv;
            s[72] = tb;
            if (tb != 0)
                nv = s[10] | 16;
            else
                nv = s[10] & 239;
            s[10] = nv; }
            *(u32 *)(s + 88) = -1786;
            *(u32 *)(s + 96) = 0;
            break;
        case 1:
            if (px >= -12800)
                goto ret0;
            return 1;
        default:
            goto ret0;
        }
        s[13]++;
        goto ret0;
    }
ret0:
    return 0;
}
