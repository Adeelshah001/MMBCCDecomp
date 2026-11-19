/* Sub_08007F24 @ 0x08007F24 (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37b_08007f24_MATCHED.c (registry: mmbcc/src/w37b_08007f24_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w37b_08007f24")))
void Sub_08007F24(u16 idx)
{
    u32 off = idx * 8;
    u8 *q = (u8 *)0x02004e18 + off;
    u8 m = 4;
    q[7] |= m;
}
