/* Sub_08000E80 @ 0x08000E80 (56 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_08000e80_MATCHED.c (registry: mmbcc/src/w36b_08000e80_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 Base[];

extern void sub_08000328(u32 x);

__attribute__((section(".text.w36b_08000e80")))
void Sub_08000E80(u32 arg0)
{
    u8 *base = Base;
    u32 idx = *(u32 *)(base + 0x1e50);
    u8 *elemBase = base + 0x1e08;
    u8 *elem = elemBase + idx * 24;
    elem[1] = 1;
    *(u32 *)(elem + 4) = arg0;
    sub_08000328(*(u32 *)0x02000800);
}
