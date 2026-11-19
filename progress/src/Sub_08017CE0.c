/* Sub_08017CE0 @ 0x08017CE0 (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w40c_08017ce0_MATCHED.c (registry: mmbcc/src/w40c_08017ce0_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w40c_08017ce0")))
void Sub_08017CE0(u8 *s)
{
    s[10] &= 254;
    {
        register u32 base __asm__("r2") = 0x082243D8;
        register u32 idx __asm__("r3");
        u32 off;
        u32 *e;
        __asm__ volatile("" : "+r" (base));
        idx = s[9];
        off = idx << 2;
        e = (u32 *)(off + base);
        *(u32 *)(s + 12) = 4;
        *(u32 *)(s + 20) = *(u32 *)(*e + 16);
    }
}
