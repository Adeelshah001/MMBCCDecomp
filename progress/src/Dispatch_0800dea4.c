/* Dispatch_0800dea4 @ 0x0800DEA4 (84 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36a_0800dea4_MATCHED.c (registry: mmbcc/src/w36a_0800dea4_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void sub_0800244C(u8 *a, u32 b);

extern void Sub_0800288C(u8 *a, u32 b);

extern void sub_0800DEF8(u8 *a, u16 b, u8 c, u32 d, u8 e);

__attribute__((section(".text.w36a_0800dea4")))
void Dispatch_0800dea4(u8 *a1, u32 a2, u16 a3, u8 a4, u8 *a5, u32 a6, u8 a7)
{
    u32 off = a3 * 32 + (250u << 24);
    sub_0800244C(a1, a2 + off);
    Sub_0800288C(a1 + 12, a4 * 32);
    sub_0800DEF8(a5, a3, a4, a6, a7);
}
