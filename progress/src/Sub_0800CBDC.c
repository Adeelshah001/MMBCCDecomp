/* Sub_0800CBDC @ 0x0800CBDC (20 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35c_0800cbdc_MATCHED.c (registry: mmbcc/src/w35c_0800cbdc_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w35c_0800cbdc")))
void Sub_0800CBDC(u8 *p)
{
    u16 a = (p[22] - 1) & 63;
    u16 b = (p[24] - 1) & 63;
    *(u16 *)(p + 22) = a;
    *(u16 *)(p + 24) = b;
}
