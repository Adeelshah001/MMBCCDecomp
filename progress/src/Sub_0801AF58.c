/* Sub_0801AF58 @ 0x0801AF58 (138 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36d_0801af58_MATCHED.c (registry: mmbcc/src/w36d_0801af58_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

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

extern void Vec2_AddMirrored(u32 a, u32 b, u32 c);

extern void sub_0800DD08(u32 *out, S *s);

extern void ChipInit_080178A8(u32 a, u32 b, s32 c, u32 d, u32 e);

extern u32 GetField17_U8(u32 a);

__attribute__((section(".text.w36d_0801af58")))
u32 Sub_0801AF58(S *s)
{
    u32 out[2];
    u8 st;
    register u32 o0 __asm__("r2");
    register u32 o1 __asm__("r3");
    Vec2_AddMirrored((u32)s, s->f88, s->f92);
    s->f88 += s->f96;
    s->f92 += s->f100;
    sub_0800DD08(out, s);
    o0 = out[0];
    __asm__ volatile("ldr %0, [sp, #8]" : "=r"(o1));
    (void)o1;
    st = s->f13;
    switch (st) {
    case 0: {
        register u8 *tbl __asm__("r0");
        u8 b;
        u32 nib;
        tbl = (u8 *)0x08226725;
        b = tbl[s->f17];
        nib = ((u32)s->f35 << 28) >> 28;
        ChipInit_080178A8(b, nib, (s16)o0, 0, s->f44);
        s->f13++;
    }
        /* fall through */
    case 1: {
        u32 a = 253;
        if ((u8)GetField17_U8(s->f44) <= 5)
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
