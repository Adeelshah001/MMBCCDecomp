/* Sub_0801B630 @ 0x0801B630 (148 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35d_0801b630_MATCHED.c (registry: mmbcc/src/w35d_0801b630_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

typedef struct {
    u8 pad0[13];
    u8 mode;
    u8 pad1[3];
    u8 f17;
    u8 pad2[17];
    u8 f35;
    u8 pad3[8];
    u32 f44;
    u8 pad4[40];
    u32 f88;
    u32 f92;
    u32 f96;
    u32 f100;
} S;

extern void Vec2_AddMirrored(S *s, u32 x, u32 y);

extern void sub_0800DD08(u32 *out, S *s);

extern void ChipInit_080178A8(u32 a, u32 b, u32 c, u32 d, u32 e);

extern void MaxAssign_17(u32 a, u32 b);

__attribute__((section(".text.w35d_0801b630")))
u32 Sub_0801B630(S *s)
{
    u32 out[2];
    s32 x;
    register u32 y __asm__("r2");
    Vec2_AddMirrored(s, s->f88, s->f92);
    s->f88 += s->f96;
    s->f92 += s->f100;
    sub_0800DD08(out, s);
    x = out[0];
    y = *(volatile u32 *)&out[1];
    if (s->mode == 0)
        goto case0;
    if (s->mode == 1)
        goto case1;
    goto ret0;
case0:
    if (x <= 14080)
        goto ret0;
    {
        register u32 bb __asm__("r0") = s->f35;
        ChipInit_080178A8(131, (bb << 28) >> 28, 15360, 0xFFFFE200, s->f44);
    }
    s->mode++;
    goto ret0;
case1:
    if (s->f17 != 2)
        goto case1other;
    if (x <= 40960)
        goto ret0;
    MaxAssign_17(s->f44, 6);
    return 1;
case1other:
    if (x <= 30720)
        goto ret0;
    return 1;
ret0:
    return 0;
}
