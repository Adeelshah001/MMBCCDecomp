/* F_08024F70 @ 0x08024F70 (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w21d_08024f70.c (registry: src/w21d_08024f70.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Loop3_08026144(u8 *p, u16 a);

__attribute__((section(".text.w21d_08024F70")))
void F_08024F70(u16 a)
{
    u8 **base = (u8 **)0x02007090;
    u8 *p;
    __asm__ volatile ("" : "+r" (base));
    p = base[5];
    Loop3_08026144(p, a);
}
