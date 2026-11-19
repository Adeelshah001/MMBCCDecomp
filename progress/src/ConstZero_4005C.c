/* ConstZero_4005C @ 0x0804005C (4 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_e.c (registry: src/wave3_e.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x0804005C (4B, tentative): constant 0. */
__attribute__((section(".text.w3e_constzero_4005c")))
u32 ConstZero_4005C(void)
{
    return 0;
}
