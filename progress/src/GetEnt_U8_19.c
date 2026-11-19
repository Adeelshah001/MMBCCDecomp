/* GetEnt_U8_19 @ 0x0802500C (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i.c (registry: src/wave4_i.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 GetU8_19(u8 *s);

extern u8 ew02007090[];

/* 0x0802500C: return GetU8_19(base+0x18). Tentative. */
__attribute__((section(".text.w4i_getent_u8_19")))
u8 GetEnt_U8_19(void)
{
    u8 *base = ew02007090;
    return GetU8_19(base + 0x18);
}
