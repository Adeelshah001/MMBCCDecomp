/* Sram_08001E30 @ 0x08001E30 (66 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w21c_08001e30.c (registry: src/w21c_08001e30.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 *Sram_RetryWrapper(u8 *dst, u8 *src, u32 len);

__attribute__((section(".text.w21c_08001e30")))
int Sram_08001E30(u8 a)
{
    register u32 au __asm__("r6") = a;
    u32 tmp = 0;
    register int st __asm__("r4");
    u32 sh1;
    if (au > 1)
        return -1;
    sh1 = au << 13;
    {
        register u32 base __asm__("r5") = ((u32)0xE0 << 20);
        st = (int)Sram_RetryWrapper((u8 *)&tmp, (u8 *)(sh1 + base), 4);
        st |= (int)Sram_RetryWrapper((u8 *)&tmp, (u8 *)(((au + 2) << 13) + base), 4);
    }
    return st;
}
