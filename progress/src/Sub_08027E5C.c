/* Sub_08027E5C @ 0x08027E5C (46 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_08027e5c_MATCHED.c (registry: staging/wave34_C/w34c_08027e5c_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void sub_08027F80(void);

__attribute__((section(".text.w34c_08027e5c")))
void Sub_08027E5C(u8 *s)
{
    register u8 mask __asm__("r3");
    u32 t;
    u32 u;
    __asm__ volatile("movs %0, #255" : "=r"(mask));
    s[5] |= mask;
    t = 0;
    s[6] = (u8)t;
    s[4] = (u8)t;
    t -= 7;
    t &= s[3];
    u = 15;
    t &= u;
    u -= 24;
    t &= u;
    s[3] = (u8)t;
    mask |= s[7];
    s[7] = mask;
    sub_08027F80();
}
