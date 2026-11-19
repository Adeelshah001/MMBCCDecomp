/* Sub_0800ED44 @ 0x0800ED44 (108 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_0800ed44_MATCHED.c (registry: mmbcc/src/w36b_0800ed44_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

struct T { u16 a; s16 b; };

struct W { u32 f0; u32 f4; };

extern s8 sub_080103E0(u8 b, u32 w, int zero, s16 x);

extern void SetByte20_Clear21to23_02005130(int x);

__attribute__((section(".text.w36b_0800ed44")))
s8 Sub_0800ED44(u8 a, u8 b)
{
    u8 *p;
    register u32 w __asm__("r4");
    register u8 bb __asm__("r5") = b;
    s16 x;
    s8 res;
    if (a == 0) {
        w = ((struct W *)0x02005020)->f0;
        p = (u8 *)0x02005130;
        p[43] = 0;
    } else {
        w = ((struct W *)0x02005020)->f4;
        p = (u8 *)0x02005130;
        p[43] = 1;
    }
    x = ((struct T *)0x08223f9c)[p[6]].b;
    res = sub_080103E0(bb, w, 0, x);
    if (res == 1) {
        SetByte20_Clear21to23_02005130(16);
        return 1;
    }
    return res;
}
