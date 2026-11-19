/* Sub_0800B448 @ 0x0800B448 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36d_0800b448_MATCHED.c (registry: src/w36d_0800b448_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void sub_080082D8(u16 b, u8 *p, u8 c, int z);

__attribute__((section(".text.w36d_0800b448")))
void Sub_0800B448(u8 a, u16 b, u8 c)
{
    u8 aa = a;
    u16 bb = b;
    u8 cc = c;
    u32 t = (u32)aa << 24;
    u16 bbT = (u16)(((u32)bb << 16) >> 16);
    u8 ccT = (u8)(((u32)cc << 24) >> 24);
    u8 *base = (u8 *)0x02004e40;
    __asm__ volatile("" : "+r"(base));
    t >>= 20;
    t += 36;
    t += (u32)base;
    sub_080082D8(bbT, (u8 *)t, ccT, 0);
}
