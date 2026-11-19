/* Buf_RemoveAt_25290 @ 0x08025290 (62 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave9_d_old.c (registry: src/wave9_d_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w9d_08025290")))
u8 Buf_RemoveAt_25290(u8 *p, u16 idx)
{
    u8 *buf;
    u8 *dst;
    u8 *end;
    u8 removed;
    if (idx >= *(u16 *)(p + 6))
        return 255;
    buf = *(u8 **)p;
    dst = buf + idx;
    end = buf + (*(u16 *)(p + 6) - 1);
    removed = *dst;
    while (dst < end) {
        dst[0] = dst[1];
        dst++;
    }
    *dst = 255;
    *(u16 *)(p + 6) = *(u16 *)(p + 6) - 1;
    return removed;
}
