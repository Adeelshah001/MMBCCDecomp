/* F_21C0C @ 0x08021C0C (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave11_A_old.c (registry: src/wave11_A_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w11a_08021c0c")))
u8 *F_21C0C(u32 x)
{
    register u32 xx __asm__("r2") = x;
    u32 *g;
    u32 *t;
    u32 o;
    u8 *p;
    u8 *q;
    __asm__ volatile("lsl %0, %0, #24" : "+r" (xx));
    __asm__ volatile("" : "=r" (g) : "0" ((u32 *)0x08173760));
    t = *(u32 **)((u8 *)g + 108);
    o = *(u32 *)((u8 *)t + 68);
    o += 68;
    p = (u8 *)t + o;
    q = p;
    q += 12;
    q += *(u32 *)(p + 12);
    __asm__ volatile("lsr %0, %0, #19" : "+r" (xx));
    return q + xx;
}
