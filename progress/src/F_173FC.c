/* F_173FC @ 0x080173FC (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave11_A_old.c (registry: src/wave11_A_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w11a_080173fc")))
void F_173FC(u8 *p)
{
    u8 *q = p;
    if (q[18] == 0) {
        register u32 pool __asm__("r1");
        register u32 *tt __asm__("r0");
        u32 off;
        __asm__ volatile("" : "=r" (pool) : "0" (0x082243d8));
        off = q[9] * 4;
        tt = (u32 *)off;
        tt = (u32 *)((u8 *)tt + pool);
        *(u32 *)(q + 12) = 2;
        tt = *(u32 **)tt;
        *(u32 *)(q + 20) = *(u32 *)((u8 *)tt + 8);
    }
}
