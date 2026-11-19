/* InitRec8_267B4 @ 0x080267B4 (12 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_e.c (registry: src/wave3_e.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x080267B4 (12B, tentative): inits an 8-byte record: word = 0x13,
 * byte1 = kind, dword+4 = 0. 19 bl-callers pass small constants (e.g. 3)
 * as kind. The explicit `u32 v` temp is load-bearing: it keeps the zero
 * in r2 (`movs r2,#0`) instead of reusing r1. */
__attribute__((section(".text.w3e_initrec8_267b4")))
void InitRec8_267B4(u8 *p, u8 kind)
{
    u32 v = 0x13;
    ((u32 *)p)[0] = v;
    v = 0;
    p[1] = kind;
    ((u32 *)p)[1] = v;
}
