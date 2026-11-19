/* EwramSet_020070F7 @ 0x08026DB0 (12 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_d.c (registry: src/wave3_d.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 gEwram020070F0[];

/* 0x08026DB0 */
__attribute__((section(".text.w3d_ewramset")))
void EwramSet_020070F7(u8 v)
{
    gEwram020070F0[7] = v;
}
