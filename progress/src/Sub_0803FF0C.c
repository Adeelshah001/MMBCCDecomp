/* Sub_0803FF0C @ 0x0803FF0C (116 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_0803ff0c_MATCHED.c (registry: mmbcc/src/w36b_0803ff0c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 sub_0803FC8C(u16 a);

extern u8 sub_0803F998(u16 a);

extern u8 CheckId_FA1C(u16 a);

__attribute__((section(".text.w36b_0803ff0c")))
u8 Sub_0803FF0C(u16 a0, u8 b0, u8 c0)
{
    u16 a = a0;
    register u16 a2 __asm__("r8") = a;
    register u8 b __asm__("r5") = b0;
    u8 b2 = b;
    register u8 c __asm__("r9") = c0;
    register u8 res __asm__("r6") = 0;
    __asm__ volatile("" : "=r"(b2) : "0"(b2));
    if ((u8)sub_0803FC8C(a) != 0) {
        res = 1;
        if (b == 5) res = 2;
    } else if (a == 12288) {
        res = 1;
        if (b == 3) res = 2;
    } else if ((u8)sub_0803F998(a) != 0) {
        res = 1;
        if (b2 != 5) {
            res = 2;
        } else if ((u8)CheckId_FA1C(a2) == 0 && c == 1) {
            res = 2;
        }
    }
    return res;
}
