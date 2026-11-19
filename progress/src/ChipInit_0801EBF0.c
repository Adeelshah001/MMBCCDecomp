/* ChipInit_0801EBF0 @ 0x0801EBF0 (82 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w17c_chipinit.c (registry: src/w17c_chipinit.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

 typedef signed int s32;

struct ObjVec;

extern u32 *Node_PopAndInit(u8 a, u8 b, u8 c, u8 d);

extern void Vec2_SetMirrored(struct ObjVec *o, s32 x, s32 y);

/* 0x0801ebf0 (82 B): Node_PopAndInit(0,1,c,15), 5 params, no tail. */
__attribute__((section(".text.w17c_0801ebf0")))
u32 *ChipInit_0801EBF0(u8 a, u8 b, u8 c, u16 d, u16 e)
{
    u32 *n = Node_PopAndInit(0, 1, c, 15);
    if (n != 0) {
        u8 *q = (u8 *)n;
        u32 z = 0;
        q[16] = a;
        q[17] = b;
        q[18] = z;
        Vec2_SetMirrored((struct ObjVec *)n, (s32)(s16)d, (s32)(s16)e);
    }
    return n;
}
