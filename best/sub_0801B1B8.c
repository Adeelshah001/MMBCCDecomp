/* Sub_0801B1B8 @ 0x0801B1B8 (140 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36d_0801b1b8_MATCHED.c (registry: mmbcc/src/w36d_0801b1b8_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;
typedef signed int s32;

typedef struct {
    u8 pad0[10];
    u8 f10;
    u8 pad1[2];
    u8 f13;
    u8 pad2[4];
    u8 f18;
    u8 pad3[16];
    u8 f35;
    u8 pad4[8];
    u32 f44;
    u8 pad5[40];
    u32 f88;
    u32 f92;
    u32 f96;
    u32 f100;
} S;

extern void sub_0800DD4C(u32 a, u32 b, u32 c);

extern void sub_0800DD08(u32 *out, S *s);

extern void sub_080178A8(u32 a, u32 b, s32 c, s32 d, u32 e);

u32 sub_0801B1B8(S *s)
{
    u32 out[2];
    u8 st;
    register s32 o0;
    register u32 o1;
    sub_0800DD4C((u32)s, s->f88, s->f92);
    s->f88 += s->f96;
    s->f92 += s->f100;
    sub_0800DD08(out, s);
    o0 = out[0];
    o1 = out[1];
    st = s->f13;
    switch (st) {
    case 0: {
        u32 nib;
        if (o0 <= (220 << 6))
            goto ret0;
        nib = ((u32)s->f35 << 28) >> 28;
        sub_080178A8(120, nib, (s16)o0, (s16)o1, s->f44);
        s->f18 = 25;
        s->f13++;
        goto ret0;
    }
    case 1: {
        u32 nf = s->f18 - 1;
        u32 a = 253;
        s->f18 = nf;
        if ((nf << 24) != 0)
            goto ret0;
        s->f10 = (s->f10 & a) & 254;
        return 1;
    }
    default:
        goto ret0;
    }
ret0:
    return 0;
}
