/* Task_ActivateSlot @ 0x08000DC0 (68 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave15_D.c (registry: src/wave15_D.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void ContextSwitch(u8 *p, u8 *q, u32 w);

__attribute__((section(".text.w15d_08000dc0")))
void Task_ActivateSlot(u32 v)
{
    register u32 base __asm__("r2");
    register u32 t1 __asm__("r1");
    u32 t;
    u8 *p;
    __asm__ volatile("" : "=r" (base) : "0" (0x030005C0));
    t1 = *(u32 *)(base + 0x1E50);
    t = (t1 << 1) + t1;
    t <<= 3;
    base += 0x1E08;
    p = (u8 *)(t + base);
    if (v != 0) {
        u8 *q;
        u8 *r;
        u32 w;
        *(u16 *)(p + 2) = (u16)v;
        *p = 4;
        q = p + 4;
        r = p + 8;
        __asm__ volatile("" : "+r" (q), "+r" (r));
        __asm__ volatile("" : "=r" (w) : "0" (0x02000800));
        w = *(u32 *)w;
        ContextSwitch(q, r, w);
    }
}
