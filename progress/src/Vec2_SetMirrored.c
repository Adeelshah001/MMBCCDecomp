/* Vec2_SetMirrored @ 0x0800DD2C (30 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/vec2.c (registry: src/vec2.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

/* Game object tail: flag byte at +35 (bit 7 = mirror X),
 * s32 vector at +80/+84. */
struct ObjVec {
    u8 _00[35];
    u8 flip;   /* +35: bit 7 = X mirrored */
    u8 _36[44];/* +36..+79 */
    s32 x;     /* +80 */
    s32 y;     /* +84 */
};

__attribute__((section(".text.vec2_setmirrored")))
void Vec2_SetMirrored(struct ObjVec *o, s32 x, s32 y)
{
    u8 *p = (u8 *)o;
    p += 35;

    if ((*p & 0x80) != 0)
        x = -x;
    o->x = x;
    o->y = y;
}
