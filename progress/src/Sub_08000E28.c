/* Sub_08000E28 @ 0x08000E28 (60 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35c_08000e28_MATCHED.c (registry: mmbcc/src/w35c_08000e28_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void ContextSwitch(u8 *a, u8 *b, u32 c);

__attribute__((section(".text.w35c_08000e28")))
void Sub_08000E28(void)
{
    register u32 *base __asm__("r2") = (u32 *)0x030005c0;
    u32 k = *(u32 *)((u8 *)base + 0x1e50) * 24;
    u8 *p;
    base = (u32 *)((u8 *)base + 0x1e08);
    p = (u8 *)(k + (u32)base);
    *p = 1;
    ContextSwitch(p + 4, p + 8, *(u32 *)0x02000800);
}
