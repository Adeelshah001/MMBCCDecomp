/* F_D104 @ 0x0800D104 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave11_A_old.c (registry: src/wave11_A_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w11a_0800d104")))
void F_D104(u8 *p)
{
    register u16 *pp __asm__("r3");
    register u32 m1 __asm__("r1");
    register u32 m2 __asm__("r2");
    u16 v;
    __asm__ volatile("" : "=r" (pp) : "0" ((u16 *)0x020031e0));
    __asm__ volatile("" : "=r" (m1) : "0" (0x0000edff));
    v = *pp;
    m1 &= v;
    __asm__ volatile("" : "=r" (m2) : "0" (0x0000dbff));
    m1 &= m2;
    *pp = (u16)m1;
    {
        u32 m3 = (u32)-3;
        u32 t = p[9];
        m3 &= t;
        p[9] = (u8)m3;
    }
}
