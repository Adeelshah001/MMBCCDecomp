/* Sub_08017600 @ 0x08017600 (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w38c_08017600_MATCHED.c (registry: mmbcc/src/w38c_08017600_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w38c_08017600")))
void Sub_08017600(u8 *s)
{
    register u8 *base __asm__("r2");
    u8 *addr;
    s[10] &= 254;
    base = (u8 *)0x082243d8;
    __asm__ volatile("" : "+r"(base));
    addr = (u8 *)(s[9] * 4 + (int)base);
    *(u32 *)(s + 12) = 4;
    *(u32 *)(s + 20) = *(u32 *)(*(u32 *)addr + 16);
}
