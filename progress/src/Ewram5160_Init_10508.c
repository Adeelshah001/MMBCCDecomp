/* Ewram5160_Init_10508 @ 0x08010508 (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave9_d_old.c (registry: src/wave9_d_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 g_02005160[];

__attribute__((section(".text.w9d_08010508")))
void Ewram5160_Init_10508(u8 v)
{
    u8 *p = g_02005160;
    u8 z = 0;
    u8 *q;
    p[0] = v;
    v = 0;
    p[2] = z;
    p[1] = z;
    p[3] = z;
    *(u16 *)(p + 6) = z;
    *(u16 *)(p + 4) = z;
    q = p;
    q += 70;
    *(u16 *)q = z;
    p += 72;
    p[0] = v;
}
