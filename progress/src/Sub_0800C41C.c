/* Sub_0800C41C @ 0x0800C41C (112 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_0800c41c_MATCHED.c (registry: mmbcc/src/w36b_0800c41c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

struct S { u8 pad[12]; u32 *f12; };

extern u32 gEwram_02003670[];

extern int S8TableLookup_0C248(s16 idx);

extern void sub_08005268(u32 *p, u32 v);

extern void _call_via_r3(void *a, u32 b, int c, u32 d);

__attribute__((section(".text.w36b_0800c41c")))
void Sub_0800C41C(int idx)
{
    u32 *t;
    u32 *entry;
    int raw;
    s8 r;
    t = gEwram_02003670;
    __asm__ volatile("" : "=r"(t) : "0"(t));
    raw = S8TableLookup_0C248((s16)idx);
    entry = t + 143;
    r = (s8)raw;
    if (r >= 0) {
        u32 v;
        u32 *p;
        v = entry[1] + 0xfa000a20u;
        p = (u32 *)(0x08322b80 + r * 20);
        sub_08005268(p, v);
        ((struct S *)0x02004f40)->f12 = p;
    }
    {
        s8 sb;
        u32 *ptr;
        register u32 *base __asm__("r1") = (u32 *)0x08173180;
        sb = *(s8 *)(0x0817313c + (s16)idx);
        ptr = base + sb;
        _call_via_r3((void *)0x02004f40, entry[0], 81, *ptr);
    }
}
