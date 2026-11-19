/* Sub_08018EA4 @ 0x08018EA4 (142 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36d_08018ea4_MATCHED.c (registry: mmbcc/src/w36d_08018ea4_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

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

extern void Vec2_AddMirrored(u32 a, u32 b, u32 c);

extern void sub_0800DD08(u32 *out, S *s);

extern void ChipInit_080178A8(u32 a, u32 b, s32 c, u32 d, u32 e);

extern void MaxAssign_17(u32 a, u32 b);

__attribute__((section(".text.w36d_08018ea4")))
u32 Sub_08018EA4(S *s)
{
    u32 out[2];
    register u32 st __asm__("r5");
    register s32 o0 __asm__("r1");
    register u32 o1 __asm__("r2");
    Vec2_AddMirrored((u32)s, s->f88, s->f92);
    s->f88 += s->f96;
    s->f92 += s->f100;
    sub_0800DD08(out, s);
    o0 = out[0];
    __asm__ volatile("ldr %0, [sp, #8]" : "=r"(o1));
    (void)o1;
    st = s->f13;
    if (st == 0)
        goto case0;
    if (st == 1)
        goto case1;
    goto ret0;
case0: {
        u32 nib;
        if (o0 <= (200 << 6))
            goto ret0;
        nib = ((u32)s->f35 << 28) >> 28;
        ChipInit_080178A8(93, nib, 240 << 6, 0xffffe700, s->f44);
        s->f96 = st;
        s->f18 = 2;
        s->f13++;
        goto ret0;
    }
case1: {
        u32 nf = s->f18 - 1;
        s->f18 = nf;
        if ((nf << 24) != 0)
            goto ret0;
        MaxAssign_17(s->f44, 7);
        return 1;
    }
ret0:
    return 0;
}
