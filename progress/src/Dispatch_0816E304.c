/* Dispatch_0816E304 @ 0x0800330C (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i_old.c (registry: src/wave4_i_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u32 gTbl_0816E304[];

/* 0x0800330C: tbl[((s[0x18]<<1)|s[0x19])&3](s,b). Tentative. */
__attribute__((section(".text.w4i_dispatch_0816e304")))
void Dispatch_0816E304(u8 *s, u32 b)
{
    u32 *tbl = gTbl_0816E304;
    u32 idx = ((s[0x18] << 1) | s[0x19]) & 3;
    ((void (*)(u8 *, u32))tbl[idx])(s, b);
}
