/* NewNode_080214F4 @ 0x080214F4 (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w19b_080214f4.c (registry: src/w19b_080214f4.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u32 *Node_PopAndInit_20ED4(u8 a, u8 b, u8 c, u8 d);

__attribute__((section(".text.w19b_080214F4")))
u8 *NewNode_080214F4(void)
{
    register u8 *p __asm__("r2") = (u8 *)Node_PopAndInit_20ED4(0, 0, 0, 1);
    if (p != 0) {
        register u8 z __asm__("r0") = 0;
        p[16] = 1;
        p[17] = z;
        { register u8 ff __asm__("r0") = 255; p[18] = ff; }
    }
}
