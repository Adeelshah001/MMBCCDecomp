/* TblPtr_2D8F4 @ 0x0802D8F4 (50 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave12_B_old.c (registry: src/wave12_B_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* TblPtr_2D8F4 @ 0x0802D8F4 (50 B): table pointer lookup via idx*4. */
__attribute__((section(".text.w12b_0802d8f4")))
u32 TblPtr_2D8F4(u8 *s)
{
    register u8 *p __asm__("r2") = s;
    register u32 t __asm__("r3");
    register u32 idx4 __asm__("r1");
    u32 idx;
    u32 ret;
    if ((p[24] & 2) == 0) {
        t = 393;
        idx = p[t];
        idx4 = idx * 4;
        t -= 29;
    } else {
        idx = p[392];
        idx4 = idx * 4;
        t = 168 * 2;
    }
    ret = *(u32 *)(p + t + idx4);
    asm("" : : "r" (p), "r" (t));
    return ret;
}
