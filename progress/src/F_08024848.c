/* F_08024848 @ 0x08024848 (48 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave15_B_old.c (registry: src/wave15_B_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

struct Ew02007090 { u8 _00[20]; u8 *f20; };

extern struct Ew02007090 ew02007090;

extern u8 CheckPair_258D8(u8 *p, u16 idx);

__attribute__((section(".text.w15b_08024848")))
u8 F_08024848(u16 idx)
{
    u8 *base = ew02007090.f20;
    u8 i2 = *(base + (0xD8 << 1));
    return CheckPair_258D8(base + i2 * 144, idx);
}
