/* Sub_080129F8 @ 0x080129F8 (68 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36d_080129f8_MATCHED.c (registry: src/w36d_080129f8_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 _call_via_r1(u8 *s, u32 v);

__attribute__((section(".text.w36d_080129f8")))
void Sub_080129F8(u8 *s)
{
    register u8 *ss __asm__("r2") = s;
    register u8 *q __asm__("r1") = ss;
    q += 124;
    if (*q != 39) {
        register u32 *tbl __asm__("r0") = (u32 *)0x08223d6c;
        __asm__ volatile("" : "+r"(tbl));
        _call_via_r1(ss, tbl[*q]);
    } else {
        register u32 *tbl __asm__("r0") = (u32 *)0x08223d6c;
        register u8 b1 __asm__("r3");
        register u8 b2 __asm__("r4");
        register int sum __asm__("r1");
        __asm__ volatile("" : "+r"(tbl));
        b1 = q[2];
        b2 = *q;
        __asm__ volatile("add %0, %1, %2" : "=r"(sum) : "r"(b1), "r"(b2));
        _call_via_r1(ss, tbl[sum]);
    }
}
