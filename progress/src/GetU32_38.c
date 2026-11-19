/* GetU32_38 @ 0x08023E30 (4 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_d.c (registry: src/wave3_d.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x08023E30 */
__attribute__((section(".text.w3d_getu32_38")))
u32 GetU32_38(u8 *s)
{
    return *(u32 *)(s + 0x38);
}
