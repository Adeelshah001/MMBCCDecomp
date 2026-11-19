/* CopyU16x4_4A660 @ 0x0804A660 (52 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_u_old.c (registry: src/wave8_u_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 gEwram_0200BD20[];

typedef struct {
    u8 pad[132];
    u16 v0;
    u16 v1;
    u16 v2;
    u16 v3;
} Dst4A660;

void CopyU16x4_4A660(u16 *src)
{
    u8 *base = gEwram_0200BD20;
    Dst4A660 *d = (Dst4A660 *)base;
    u8 *p = base + 127;

    *p = 0;
    p--;
    *p = 0;
    d->v0 = src[0];
    d->v1 = src[1];
    d->v2 = src[2];
    d->v3 = src[3];
}
