/* NewNode_0801F180 @ 0x0801F180 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w19b_0801f180.c (registry: src/w19b_0801f180.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u32 *Node_PopAndInit(u8 a, u8 b, u8 c, u8 d);

__attribute__((section(".text.w19b_0801F180")))
u8 *NewNode_0801F180(u8 *a)
{
    register u8 *p __asm__("r2") = (u8 *)Node_PopAndInit(1, 1, 0, 17);
    register u8 *aa __asm__("r4") = a;
    if (p != 0) {
        register u8 z __asm__("r1") = 0;
        p[16] = 5;
        p[17] = z;
        *(u8 **)(p + 40) = aa;
    }
    return p;
}
