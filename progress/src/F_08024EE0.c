/* F_08024EE0 @ 0x08024EE0 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave15_B_old.c (registry: src/wave15_B_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

struct Ew02007090 { u8 _00[20]; u8 *f20; };

extern struct Ew02007090 ew02007090;

extern u16 F_08025790(u8 *p);

__attribute__((section(".text.w15b_08024ee0")))
u16 F_08024EE0(void)
{
    u8 *base = ew02007090.f20;
    u8 idx = *(base + (0xD8 << 1));
    return (u16)F_08025790(base + idx * 144);
}
