/* BuildNodePair_08020340 @ 0x08020340 (100 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w19d_08020340.c (registry: src/w19d_08020340.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern u32 *Node_PopAndInit(u8 a, u8 b, u8 c, u8 d);

__attribute__((section(".text.w19d_08020340")))
u8 *BuildNodePair_08020340(u8 *a)
{
    u8 *p = 0;
    s16 v = *(s16 *)(*(u8 **)0x020053c0 + 10);
    if (v > 1) {
        p = (u8 *)Node_PopAndInit(0, 0, 0, 18);
        if (p != 0) {
            u8 z = 0;
            p[16] = 3;
            p[17] = z;
            p[120] = 47;
            *(u8 **)(p + 40) = a;
        }
        p = (u8 *)Node_PopAndInit(0, 0, 0, 18);
        if (p != 0) {
            p[16] = 3;
            p[17] = 1;
            p[120] = 49;
            *(u8 **)(p + 40) = a;
        }
    }
    return p;
}
