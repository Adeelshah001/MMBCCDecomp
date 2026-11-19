/* F_08025070 @ 0x08025070 (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave15_B.c (registry: src/wave15_B.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

struct Ew02007090 { u8 _00[18]; u16 f18; u8 *f20; };

extern struct Ew02007090 ew02007090;

extern u16 F_0802663c(const void *p, u16 idx);

__attribute__((section(".text.w15b_08025070")))
u8 F_08025070(u16 idx)
{
    const u8 *p = (const u8 *)&ew02007090;
    return (u8)F_0802663c(p + 24, idx);
}
