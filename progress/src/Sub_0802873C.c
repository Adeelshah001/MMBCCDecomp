/* Sub_0802873C @ 0x0802873C (60 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36e_0802873c_MATCHED.c (registry: mmbcc/src/w36e_0802873c_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

struct A { u16 f0; u16 f2; u8 pad4[4]; u8 f8; u8 f9; u8 f10; u8 pad11; u16 f12; u16 f14; u16 f16; u16 f18; u8 pad20[4]; u16 f24; u8 pad26[2]; u32 f28; u8 pad32[11]; u8 f43; };

extern int Sub_08028778(u8 *p, u8 v);

extern void SetPairZero_28874(u8 *s, u8 v);

__attribute__((section(".text.w36e_0802873c")))
void Sub_0802873C(u8 *s)
{
    u8 v = s[2];
    if (v == 0)
        goto A;
    if (v == 1)
        goto B;
    return;
A:
    {
        u8 *p = s + 3;
        register u8 *tbl __asm__("r1") = (u8 *)0x0822dde0;
        register u8 idx __asm__("r2") = s[1];
        __asm__ volatile("add %0, %1, %0" : "+r"(tbl) : "r"(idx));
        if ((Sub_08028778(p, *tbl) << 24) != 0)
            return;
    }
    s[2]++;
B:
    SetPairZero_28874(s, s[1]);
}
