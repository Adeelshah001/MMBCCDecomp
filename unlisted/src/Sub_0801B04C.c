/* Sub_0801B04C @ 0x0801B04C (142 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36d_0801b04c_MATCHED.c (registry: mmbcc/src/w36d_0801b04c_MATCHED.c).
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
    u8 pad2[3];
    u8 f17;
    u8 pad3[17];
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

extern void sub_080178A8(u32 a, u32 b, s32 c, u32 d, u32 e);

extern void sub_0804A378(u32 a);

u32 Sub_0801B04C(S *s)
{
    u32 out[2];
    s32 o0;
    register s32 o1;
    register u32 st;
    u32 a = 253;
    sub_0800DD4C((u32)s, s->f88, s->f92);
    s->f88 += s->f96;
    s->f92 += s->f100;
    sub_0800DD08(out, s);
    o0 = out[0];
    o1 = out[1];
    st = s->f13;
    if (st != 0)
        goto ret0;
    if (o1 <= -1280)
        goto ret0;
    {
        u8 b = *(u8 *)(0x08226728 + s->f17);
        u32 nib = ((u32)s->f35 << 28) >> 28;
        sub_080178A8(b, nib, (s16)o0, 0, s->f44);
    }
    s->f88 = st;
    s->f96 = st;
    s->f92 = st;
    s->f100 = st;
    s->f10 = (s->f10 & a) & 254;
    if (s->f17 != 0)
        sub_0804A378(135);
    return 1;
ret0:
    return 0;
}
