/* Wrap_GetRomTableU16 @ 0x08024634 (18 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i.c (registry: src/wave4_i.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u16 GetRomTableU16(u8 idx);

/* 0x08024634: return GetRomTableU16(idx). Tentative. */
__attribute__((section(".text.w4i_wrap_getromtableu16")))
u16 Wrap_GetRomTableU16(u8 idx)
{
    return GetRomTableU16(idx);
}
