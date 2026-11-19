/* OrU8_1F @ 0x0800B6E8 (10 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_d.c (registry: src/wave3_d.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x0800B6E8: `u8 v = 4;` first puts the constant in r1 (movs r1,#4 before
 * the ldrb); `s[0x1F] |= 4` / `= 4 | s[0x1F]` allocate r1/r2 swapped. */
__attribute__((section(".text.w3d_oru8_1f")))
void OrU8_1F(u8 *s)
{
    u8 v = 4;
    v |= s[0x1F];
    s[0x1F] = v;
}
