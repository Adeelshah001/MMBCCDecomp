/* sub_08035E5C @ 0x08035E5C (84 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34d_08035e5c.c (registry: mmbcc/src/w34d_08035e5c.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

extern s8 _call_via_r1(u8 *p, u32 v);

__attribute__((section(".text.w34d_08035e5c")))
void sub_08035E5C(u8 *p)
{
    register u8 *pp __asm__("r4") = p;
    register u32 *tbl __asm__("r1") = (u32 *)0x0822EB6C;
    u8 *p2;
    s8 idx;
    u32 v;
    __asm__ volatile("" : "+r"(tbl));
    p2 = pp + 0x4699;
    idx = *(s8 *)p2;
    v = tbl[idx];
    if (_call_via_r1(pp, v) != 0) {
        register s32 x __asm__("r1");
        x = *(s8 *)p2;
        if (x != 0) {
            x = 0;
            *p2 = x;
        } else {
            *p2 = *(pp + 0x46B7);
        }
        pp[4] = x;
        pp[1] = 3;
        pp[3] = x;
        pp[2] = x;
    }
}
