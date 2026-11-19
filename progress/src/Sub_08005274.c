/* Sub_08005274 @ 0x08005274 (42 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_08005274_MATCHED.c (registry: staging/wave34_C/w34c_08005274_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

extern void Sub_0800288C(u8 *p, u32 x);

extern void Copy8_28D0(u8 *p, u8 a, u8 b);

__attribute__((section(".text.w34c_08005274")))
void Sub_08005274(u8 *s, u32 a, u32 b)
{
    u32 t = a << 16;
    u16 bb = b;
    u16 aa = t >> 16;
    if ((s32)t < 0)
        Sub_0800288C(s + 12, bb << 5);
    else
        Copy8_28D0(s + 12, (u8)aa, (u8)bb);
}
