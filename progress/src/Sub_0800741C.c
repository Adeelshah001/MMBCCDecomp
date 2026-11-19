/* Sub_0800741C @ 0x0800741C (72 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35c_0800741c_MATCHED.c (registry: mmbcc/src/w35c_0800741c_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

extern void sub_08007464(u8 *base, s16 a, s16 b, s16 c, u8 d);

__attribute__((section(".text.w35c_0800741c")))
void Sub_0800741C(u16 a, u16 b, u16 c, u8 d)
{
    register u8 *base __asm__("r12") = (u8 *)0x02004830;
    __asm__ volatile("" : "+r"(base));
    if (*(u8 *)(base + 0x265) == 0)
        sub_08007464(base, (s16)a, (s16)b, (s16)c, d);
}
