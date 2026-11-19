/* ChipInit_0802316C @ 0x0802316C (100 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w16c_0802316c.c (registry: src/w16c_0802316c.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Wrapper_D728(u32 a, u16 b, u8 c);

__attribute__((section(".text.w16c_0802316c")))
void ChipInit_0802316C(u8 *p)
{
    u32 idx;
    int mask;
    u8 *q;
    u32 sh;
    { register u32 z __asm__("r0") = 0; *(u32 *)(p + 0x6c) = z; }
    { u8 b = p[10]; b = 2 | b; b = 1 | b; p[10] = b; }
    Wrapper_D728((u32)p, 0x3813, 0);
    {
        u16 *p1 = (u16 *)0x081705B0;
        register u8 *p2 __asm__("r1");
        u16 h;
        u32 t;
        h = p1[1];
        t = (h >> 4) << 1;
        __asm__ volatile("" : "=r" (p2) : "0" ((u8 *)0x020031E4));
        idx = (*(u8 *)(t + (u32)p2)) & 3;
    }
    {
        register int c __asm__("r0");
        __asm__ ("movs %0, %1" : "=r" (c) : "r" (idx));
        if (c > 3)
            idx = 3;
    }
    q = p;
    q += 0x45;
    sh = idx << 2;
    mask = -13;
    *q = (*q & mask) | sh;
    p[0x22] = 0;
}
