/* Sub_0800675C @ 0x0800675C (96 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36a_0800675c_MATCHED.c (registry: mmbcc/src/w36a_0800675c_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Sub_080067BC(u32 a, s8 b, s8 c, u8 d, u8 e, u8 f, u16 g);

__attribute__((section(".text.w36a_0800675c")))
void Sub_0800675C(u8 a0, u8 a1, u8 a2, u8 a3, u8 a4, u16 a5)
{
    u32 pool1 = 0x02004830;
    u32 pool2 = 0x265;
    u8 *flagptr;
    __asm__ volatile("" : "+r"(pool2));
    flagptr = (u8 *)(pool1 + pool2);
    if (*flagptr == 0) {
        Sub_080067BC(pool1, (s8)a0, (s8)a1, a2, a3, a4, a5);
    }
}
