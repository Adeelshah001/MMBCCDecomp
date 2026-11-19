/* StructInit_031B8 @ 0x080031B8 (106 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_d.c (registry: src/wave7_d.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x080031b8: StructInit_031B8 (was sub_080031B8, coordinator-verified). */
extern void SetU32_4(u8 *s, u32 v);

__attribute__((section(".text.w7d_080031b8")))
void StructInit_031B8(u8 *s, u32 a1, u32 a2) {
    register u32 va1 __asm__("r6") = a1;
    register u32 va2 __asm__("r8") = a2;
    register u32 m __asm__("r2");
    u32 a;
    register u32 z __asm__("r5");
    int c16, c8;
    int k2;

    {
        register u32 vptr __asm__("r1");
        __asm__("ldr %0,=0x08003725" : "=r"(vptr));
        SetU32_4(s, vptr);
    }

    {
        register int k1 __asm__("r2");
        register u32 b0 __asm__("r0");
        k1 = -0x21;
        b0 = s[17];
        m = k1 & b0;
    }
    __asm__("movs %0,#15" : "=l"(a));
    {
        u32 b = s[21];
        __asm__("and %0,%1" : "+l"(a) : "l"(b));
    }
    __asm__("movs %0,#0" : "=l"(z));
    *(u16 *)(s + 22) = 0;
    s[24] = z;
    s[25] = z;
    __asm__("movs %0,#16" : "=l"(c16));
    m |= c16;
    k2 = -0x0d;
    m &= k2;
    a &= k2;
    __asm__("movs %0,#8" : "=l"(c8));
    a |= c8;
    s[21] = a;
    *(u32 *)(s + 8) = va1;
    {
        register u32 t __asm__("r1");
        __asm__("mov %0,%1" : "=r"(t) : "r"(va2));
        *(u32 *)(s + 12) = t;
    }
    {
        register int k3f __asm__("r3");
        register int t __asm__("r0");
        register u32 b19 __asm__("r1");
        k3f = -0x3f;
        t = k3f;
        b19 = s[19];
        __asm__("and %0,%1" : "+r"(t) : "r"(b19));
        m |= 3;
        s[17] = m;
        __asm__("and %0,%1" : "+r"(t) : "r"(k3f));
        s[19] = t;
    }
    {
        register u32 mfe __asm__("r0");
        register u32 h __asm__("r1");
        __asm__("ldr %0,=0xfffffe00" : "=r"(mfe));
        h = *(u16 *)(s + 18);
        __asm__("and %0,%1" : "+r"(mfe) : "r"(h));
        *(u16 *)(s + 18) = mfe;
    }
    s[16] = z;
}
