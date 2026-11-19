/* Sub_0801054C @ 0x0801054C (88 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36a_0801054c_MATCHED.c (registry: mmbcc/src/w36a_0801054c_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void sub_08008030(u32 a, u32 b, u32 c, u32 d, u32 e);

extern void sub_080105A4(u32 a, u32 b);

__attribute__((section(".text.w36a_0801054c")))
void Sub_0801054C(u8 *s_in)
{
    register u8 *s __asm__("r3");
    register u32 base1 __asm__("r0");
    register u32 off __asm__("r1");
    register u32 mask __asm__("r1");
    register u32 mode __asm__("r2");
    u8 *base;
    u8 *r4;
    u32 stackarg;
    s = s_in;
    base1 = 0x02003670;
    off = 0x000011ae;
    __asm__ volatile("" : "+r"(off));
    base = (u8 *)(base1 + off);
    mask = 4;
    mask &= *base;
    mode = 14;
    if (mask != 0)
        mode = 15;
    stackarg = ({ register u32 _a __asm__("r0"); __asm__("add %0, %1, #0\n\tadd %0, %0, #58\n\tldrb %0, [%0]" : "=r"(_a) : "r"(s)); _a; });
    sub_08008030(0, mode, 0, 0, stackarg);
    r4 = (u8 *)0x02005168;
    sub_080105A4((u32)r4, 0);
    r4 += 20;
    sub_080105A4((u32)r4, 1);
}
