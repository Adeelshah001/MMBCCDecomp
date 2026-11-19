/* Clamp_26720 @ 0x08026720 (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave10_L_old.c (registry: src/wave10_L_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x08026720 (32B): clamp/offset; >84->239, >48->+150, else +200 (u8). */
__attribute__((section(".text.w10l_08026720")))
u8 Clamp_26720(u8 v)
{
    u8 w = v;
    u8 r;
    if (v > 84)
        r = 239;
    else if (v > 48)
        r = (u8)(v + 150);
    else
        r = (u8)(w + 200);
    return r;
}
