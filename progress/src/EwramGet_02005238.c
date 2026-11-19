/* EwramGet_02005238 @ 0x08011BC8 (12 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_d.c (registry: src/wave3_d.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 gEwram02005230[];

/* 0x08011BC8: the local `base` keeps the two literal loads split
 * (ldr pool; ldr [r0,#8]); folding base+8 into the pool does NOT match. */
__attribute__((section(".text.w3d_ewramget")))
u32 EwramGet_02005238(void)
{
    u8 *base = gEwram02005230;
    return *(u32 *)(base + 8);
}
