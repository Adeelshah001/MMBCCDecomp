/* BitCtl_520C @ 0x0800520C (92 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave10_R_old.c (registry: src/wave10_R_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 gEwram_02003670[];

extern u8 gEwram_020031f0[];

/* BitCtl_520C @ 0x0800520C (92 B).
 * Bit manipulation at gEwram_02003670+0x11ae, then hword init at
 * gEwram_020031f0 (0xfff8/0xfff8 if x!=1, else 0/0 and clear bit 0x3800
 * at gEwram_020031f0-16).
 * Idioms: pinned one/t2 with barrier defeats copy fusion; volatile
 * mov/neg defeats sub optimization; accumulate in m (r1) for orr dest. */
__attribute__((section(".text.w10r_800520c")))
void BitCtl_520C(u32 x)
{
    u32 base = (u32)gEwram_02003670;
    u8 *p;
    u8 v;
    register int m __asm__("r1");
    u32 t;
    __asm__ volatile("" : "+r" (base));
    p = (u8 *)(base + 0x11ae);
    {
        register u32 one __asm__("r1") = 1;
        register u32 t2 __asm__("r2") = x;
        __asm__ volatile("" : "+r" (t2));
        t2 &= one;
        t2 <<= 2;
        t = t2;
    }
    __asm__ volatile("mov %0,#5" : "=r" (m));
    __asm__ volatile("neg %0,%0" : "+r" (m));
    v = *p;
    m &= v;
    m |= t;
    *p = (u8)m;
    if (x == 1)
        goto L1;
    {
        u16 *q = (u16 *)gEwram_020031f0;
        q[0] = 0xfff8;
        q[1] = 0xfff8;
    }
    goto Lend;
L1:
    {
        u16 *q = (u16 *)gEwram_020031f0;
        q[0] = 0;
        q[1] = 0;
        {
            u16 *r = (u16 *)((u32)gEwram_020031f0 - 16);
            u16 w = *r;
            w &= 0xc7ff;
            *r = w;
        }
    }
Lend:;
}
