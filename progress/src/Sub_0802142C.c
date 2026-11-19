/* Sub_0802142C @ 0x0802142C (108 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_0802142c_MATCHED.c (registry: mmbcc/src/w36b_0802142c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

struct S88 { u8 pad[88]; u32 f88; };

struct S44 { u8 pad[44]; u16 f44; };

extern void sub_0800DDE4(u8 *r3, u16 *buf, u32 x, u8 flag);

__attribute__((section(".text.w36b_0802142c")))
void Sub_0802142C(u8 *s, u8 flag)
{
    register u32 base __asm__("r2") = ((struct S88 *)0x08173760)->f88;
    u8 *tbl = (u8 *)0x08226f34;
    u8 t = tbl[s[17]];
    u32 *p = (u32 *)(base + t * 4);
    u8 *r3;
    u8 *tt;
    s16 i;
    u16 buf[16];
    p = (u32 *)((u32)p + *p);
    tt = (u8 *)p + 12;
    r3 = tt + *(u32 *)((u8 *)p + 12);
    i = 0;
    {
        register u32 *q __asm__("r4") = (u32 *)0x081738f2;
        register u32 *w __asm__("r5") = (u32 *)0x03002620;
        for (; i <= 15; i++) {
            buf[i] = *(u16 *)(r3 + 30);
        }
        sub_0800DDE4(r3, buf, ((struct S44 *)q)->f44 * 32 + (u32)w, flag);
    }
}
