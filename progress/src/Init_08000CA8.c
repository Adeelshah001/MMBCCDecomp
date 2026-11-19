/* Init_08000CA8 @ 0x08000CA8 (44 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w31c_08000ca8.c (registry: staging/wave31_C/w31c_08000ca8_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w31c_08000ca8")))
void Init_08000CA8(u32 param) {
    register u32 *base __asm__("r3") = (u32 *)0x030023c8;
    u32 *p1 = base - 2;
    register u32 zero __asm__("r2") = 0;
    *p1 = zero;
    *(base - 1) = param;
    *(u32 *)0x02000800 = zero;
    {
        u8 *b = (u8 *)base;
        u8 one = 1;
        int i = 2;
        do {
            *b = one;
            i--;
            b += 24;
        } while (i >= 0);
    }
}
