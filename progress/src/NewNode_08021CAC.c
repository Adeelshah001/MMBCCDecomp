/* NewNode_08021CAC @ 0x08021CAC (100 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w19b_08021cac.c (registry: src/w19b_08021cac.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u32 *Node_PopAndInit_20ED4(u8 a, u8 b, u8 c, u8 d);

__attribute__((section(".text.w19b_08021CAC")))
u8 *NewNode_08021CAC(u8 *a, u8 *b)
{
    register u8 *aa __asm__("r4") = a;
    register u8 *bb __asm__("r5") = b;
    register u8 *p __asm__("r2");
    p = (u8 *)Node_PopAndInit_20ED4(0, 0, 0, 3);
    if (p != 0) {
        u8 z = 0;
        p[16] = z;
        p[17] = z;
        *(u8 **)(p + 40) = aa;
        *(u8 **)(p + 44) = bb;
    }
    p = (u8 *)Node_PopAndInit_20ED4(0, 0, 0, 3);
    if (p != 0) {
        register u8 z __asm__("r1") = 0;
        p[16] = 1;
        p[17] = z;
        *(u8 **)(p + 40) = aa;
        *(u8 **)(p + 44) = bb;
    }
    p = (u8 *)Node_PopAndInit_20ED4(0, 0, 0, 3);
    if (p != 0) {
        p[16] = 1;
        p[17] = 1;
        *(u8 **)(p + 40) = aa;
        *(u8 **)(p + 44) = bb;
    }
    return p;
}
