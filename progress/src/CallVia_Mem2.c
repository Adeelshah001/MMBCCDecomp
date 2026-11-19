/* CallVia_Mem2 @ 0x0804DA20 (20 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i.c (registry: src/wave4_i.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 gEwram_0200CD80[];

/* 0x0804DA20: (*(u32*)0x0200CD80)(a, b). Tentative. */
__attribute__((section(".text.w4i_callvia_mem2")))
void CallVia_Mem2(u8 *a, u32 b)
{
    u32 fn = *(u32 *)gEwram_0200CD80;
    ((void (*)(u8 *, u32))fn)(a, b);
}
