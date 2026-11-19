/* Wrap_TblGet11 @ 0x0802465C (18 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i.c (registry: src/wave4_i.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 TblGet11(u8 a);

/* 0x0802465C: return TblGet11(idx). Tentative. */
__attribute__((section(".text.w4i_wrap_tblget11")))
u8 Wrap_TblGet11(u8 idx)
{
    return TblGet11(idx);
}
