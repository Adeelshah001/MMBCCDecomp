/* Fwd_25054 @ 0x08025054 (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w16b_08025054.c (registry: src/w16b_08025054.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u16 F_0802660C(u8 *p, u16 idx);

extern u8 ew02007090[];

u16 Fwd_25054(u16 idx)
{
    u8 *base = ew02007090;
    return F_0802660C(base + 24, idx);
}
