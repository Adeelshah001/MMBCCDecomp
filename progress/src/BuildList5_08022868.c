/* BuildList5_08022868 @ 0x08022868 (84 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w19d_08022868.c (registry: src/w19d_08022868.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern u32 *Node_PopAndInit_20ED4(u8 a, u8 b, u8 c, u8 d);

__attribute__((section(".text.w19d_08022868")))
u8 *BuildList5_08022868(void)
{
    s16 v = *(s16 *)(*(u8 **)0x020066f0 + 10);
    u8 *prev;
    u8 idx;
    u8 z;
    u8 *p;
    if (v <= 4)
        return 0;
    prev = 0;
    idx = 0;
    z = 0;
    do {
        p = (u8 *)Node_PopAndInit_20ED4(1, 1, 0, 5);
        *(u8 **)(p + 40) = prev;
        *(u8 **)(p + 44) = (u8 *)(u32)z;
        if (prev != 0)
            *(u8 **)(prev + 44) = p;
        p[16] = z;
        p[17] = idx;
        prev = p;
        idx = (u8)(((idx << 24) + 0x1000000) >> 24);
    } while ((s8)idx <= 4);
    return prev;
}
