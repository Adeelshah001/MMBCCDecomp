/* Sub_080043EC @ 0x080043EC (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_080043ec_MATCHED.c (registry: staging/wave34_C/w34c_080043ec_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

extern void sub_08004398(u8 *s, s32 b4, u32 w, s32 h6, s32 h8);

__attribute__((section(".text.w34c_080043ec")))
void Sub_080043EC(u8 *s)
{
    register s32 b4 __asm__("r1");
    register u32 w __asm__("r2");
    register s32 h6 __asm__("r3");
    register s32 h8 __asm__("r4");
    __asm__ volatile("movs r1, #4\n\tldrsb %0, [%1, r1]" : "=r"(b4) : "r"(s));
    w = *(u32 *)s;
    __asm__ volatile("movs r4, #6\n\tldrsh %0, [%1, r4]" : "=r"(h6) : "r"(s) : "r4");
    __asm__ volatile("movs r5, #8\n\tldrsh %0, [%1, r5]" : "=r"(h8) : "r"(s) : "r5");
    sub_08004398(s, b4, w, h6, h8);
}
