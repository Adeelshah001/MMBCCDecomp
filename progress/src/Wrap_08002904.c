/* Wrap_08002904 @ 0x08002904 (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave6_l4_old.c (registry: src/wave6_l4_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x08002904: Wrap_08002904 (coordinator-verified). */
void Copy8_28D0(u8 *s, u8 a, u8 b);

__attribute__((section(".text.w6l4_08002904")))
void Wrap_08002904(u8 *s, u8 a, u8 b)
{
    Copy8_28D0(s, a, b + 0x10);
}
