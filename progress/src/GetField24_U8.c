/* GetField24_U8 @ 0x0802654C (4 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_a.c (registry: src/wave3_a.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x0802654C: u8 getter at offset 24. Tentative. */
__attribute__((section(".text.w3a_getfield24_u8")))
u8 GetField24_U8(u8 *s)
{
    return s[24];
}
