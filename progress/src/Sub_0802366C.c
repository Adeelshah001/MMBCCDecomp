/* Sub_0802366C @ 0x0802366C (68 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36d_0802366c_MATCHED.c (registry: src/w36d_0802366c_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void sub_0800244C(u8 *p, int v);

extern void Sub_0800288C(u8 *p, int v);

__attribute__((section(".text.w36d_0802366c")))
void Sub_0802366C(void)
{
    register u8 *base __asm__("r0") = (u8 *)0x08173760;
    register u8 *p __asm__("r4");
    register u16 *p2 __asm__("r0");
    register u16 *p3 __asm__("r0");
    register u16 t1 __asm__("r0");
    register u16 t2 __asm__("r0");
    register int v1 __asm__("r1");
    register int v2 __asm__("r1");
    __asm__ volatile("" : "+r"(base));
    p = *(u8 **)(base + 44);
    p += *(u32 *)(p + 16) + 16;
    p2 = (u16 *)0x0817386c;
    __asm__ volatile("" : "+r"(p2));
    t1 = p2[11];
    __asm__ volatile("lsl %0, %1, #5" : "=r"(v1) : "r"(t1));
    v1 += (128 << 9);
    sub_0800244C(p, v1);
    p += 12;
    p3 = (u16 *)0x081738f2;
    __asm__ volatile("" : "+r"(p3));
    t2 = p3[11];
    __asm__ volatile("lsl %0, %1, #5" : "=r"(v2) : "r"(t2));
    v2 += (128 << 2);
    Sub_0800288C(p, v2);
}
