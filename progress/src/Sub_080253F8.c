/* Sub_080253F8 @ 0x080253F8 (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_080253f8_MATCHED.c (registry: staging/wave34_C/w34c_080253f8_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void F_25308(void);

extern void sub_0802538C(u8 *s);

__attribute__((section(".text.w34c_080253f8")))
void Sub_080253F8(u8 *s, u32 b)
{
    u32 c = b;
    __asm__ volatile("" : "+r"(c));
    *(u32 *)s = c;
    b += 249;
    *(u32 *)(s + 8) = b;
    b = c + 498;
    *(u32 *)(s + 4) = b;
    F_25308();
    sub_0802538C(s);
}
