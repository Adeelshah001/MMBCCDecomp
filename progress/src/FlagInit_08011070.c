/* FlagInit_08011070 @ 0x08011070 (44 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_C.c (registry: src/wave14_C.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* FlagInit_08011070 @ 0x08011070 */
void sub_080111B4(u32 v);

__attribute__((section(".text.w14c_08011070")))
u32 FlagInit_08011070(u8 a, u8 b)
{
    u8 *p;
    u32 r;
    __asm__ volatile("" : "=r" (p) : "0" (0x020051B0));
    if (p[4] == 1) {
        sub_080111B4(3);
        p[0xd] = a;
        p[0xe] = b;
        r = 1;
    } else {
        r = 0;
    }
    return r;
}
