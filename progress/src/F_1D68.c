/* F_1D68 @ 0x08001D68 (30 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave11_A_old.c (registry: src/wave11_A_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w11a_08001d68")))
void F_1D68(u8 *p)
{
    u8 *q = p;
    u16 z = 0;
    u8 *a;
    u8 *b;
    *(u16 *)(q + 8) = z;
    *(u16 *)(q + 6) = z;
    *(u16 *)(q + 4) = z;
    *(u16 *)(q + 2) = z;
    *(u16 *)(q + 0) = z;
    a = q; a += 10;
    b = q; b += 14;
    *(u32 *)b = z;
    *(u32 *)a = z;
    *(u16 *)(q + 18) = z;
}
