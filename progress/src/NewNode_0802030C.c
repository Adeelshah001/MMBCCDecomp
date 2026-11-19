/* NewNode_0802030C @ 0x0802030C (52 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w18d_0802030c.c (registry: src/w18d_0802030c.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u32 *Node_PopAndInit(u8 a, u8 b, u8 c, u8 d);

__attribute__((section(".text.w18d_0802030C")))
u8 *NewNode_0802030C(u8 *a, u8 b, u8 c)
{
    u8 *p = (u8 *)Node_PopAndInit(0, 0, 0, 18);
    if (p != 0) {
        p[16] = 0;
        p[17] = c;
        p[120] = b;
        *(u8 **)(p + 40) = a;
    }
    return p;
}
