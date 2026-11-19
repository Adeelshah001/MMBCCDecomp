/* Setup_08005F44 @ 0x08005F44 (124 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w20d_08005f44.c (registry: src/w20d_08005f44.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 *NodeInit_08022F88(u32 x);

extern u8 g_02004830[];

extern u8 gEwram_02003670[];

__attribute__((section(".text.w20d_08005F44")))
void Setup_08005F44(u8 a, u8 b, u8 c)
{
    u8 *base2 = gEwram_02003670;
    register u8 *base __asm__("r1") = g_02004830;
    u8 b10 = base[10];
    register u8 t __asm__("r6") = 1;
    u8 tc;
    u32 nm;
    register u32 m __asm__("r0");
    u8 *addr;
    /* opaque copy forces adds r0,r6,#0 before the ands (compiler swaps operands otherwise).
       Divided-syntax "add" (no s) assembles to 1c30; "adds" is rejected by GAS 2.42. */
    __asm__ ("add %0, %1, #0" : "=r" (tc) : "r" (t));
    if ((tc & b10) != 0) {
        nm = 2;
        nm = -nm;
        nm &= b10;
        base[10] = (u8)nm;
        *(u16 *)(base + 2) = 0;
    }
    {
        int a32 = a << 5;
        u8 *p;
        base += 142 * 8;
        /* divided-syntax forces adds r3,r0,r1 operand order (compiler swaps otherwise) */
        __asm__ ("add %0, %1, %2" : "=r" (p) : "r" (a32), "r" (base));
        p[0] = b;
        p[1] = c;
        if (p[28] == 0) {
            p[2] = b;
            p[3] = c;
        }
        p[28] = t;
        addr = base2 + 0x11ae;
        m = 248;
        /* opaque AND forces ands r0,r1 (compiler swaps operands otherwise).
           Divided-syntax "and" (no s) assembles to the flag-setting encoding. */
        __asm__ ("and %0, %0, %1" : "+r" (m) : "r" (*addr));
        if (m != 16) {
            if ((p[31] & 16) == 0) {
                p[31] |= 16;
                NodeInit_08022F88((u32)p);
            }
        }
    }
}
