/* NodeInit_080217A8 @ 0x080217A8 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w18b_080217a8.c (registry: src/w18b_080217a8.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u32 *Node_PopAndInit_20ED4(u8 a, u8 b, u8 c, u8 d);

__attribute__((section(".text.w18b_080217a8")))
u8 *NodeInit_080217A8(u8 x)
{
    u8 *r = (u8 *)Node_PopAndInit_20ED4(0, 0, 0, 2);
    u32 z = 0;
    if (r != 0) {
        r[16] = z;
        r[17] = x;
        *(u32 *)(r + 40) = (u32)r;
    }
    return r;
}
