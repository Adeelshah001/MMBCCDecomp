/* CallVia_Mem1 @ 0x0804CA1C (20 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i.c (registry: src/wave4_i.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 gEwram_0200CE0C[];

/* 0x0804CA1C: (*(u32*)0x0200CE0C)(s). Tentative. */
__attribute__((section(".text.w4i_callvia_mem1")))
void CallVia_Mem1(u8 *s)
{
    u32 fn = *(u32 *)gEwram_0200CE0C;
    ((void (*)(u8 *))fn)(s);
}
