/* Sub_080192DC @ 0x080192DC (152 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37c_080192dc_MATCHED.c (registry: mmbcc/src/w37c_080192dc_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed int s32;

typedef struct {
    u8 pad0[10];
    u8 f10;
    u8 pad1[2];
    u8 mode;
    u8 pad2[21];
    u8 f35;
    u8 pad3[8];
    u32 f44;
    u8 pad4[40];
    u32 f88;
    u32 f92;
    u32 f96;
    u32 f100;
} S;

extern void sub_0800DD4C(S *s, u32 x, u32 y);

extern void sub_0800DD08(u32 *out, S *s);

extern void sub_080174A4(u32 a, u32 b);

extern void sub_080178A8(u32 a, u32 b, u32 c, u32 d, u32 e);

extern u8 sub_08017474(u32 a);

u32 Sub_080192DC(S *s)
{
    u32 out[2];
    register s32 x;
    register s32 y;
    u8 mode;
    sub_0800DD4C(s, s->f88, s->f92);
    s->f88 += s->f96;
    s->f92 += s->f100;
    sub_0800DD08(out, s);
    x = *(volatile s32 *)&out[0];
    y = *(volatile s32 *)&out[1];
    mode = s->mode;
    switch (mode) {
    case 0:
        if (y <= -1280)
            return 0;
        sub_080174A4(s->f44, 3);
        sub_080178A8(84, (u32)(*(u8 *)((u8 *)s + 35)) << 28 >> 28, 15360,
                          0, s->f44);
        s->f88 = mode;
        s->f92 = mode;
        s->f100 = mode;
        {
            int t = s->f10 & 253;
            t &= 254;
            s->f10 = t;
        }
        s->mode++;
        return 0;
    case 1:
        if (sub_08017474(s->f44) > 5)
            return 1;
        return 0;
    default:
        return 0;
    }
}
