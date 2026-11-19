/* Clr2_08002f24 @ 0x08002F24 (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_C.c (registry: src/wave14_C.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* Clr2_08002f24 @ 0x08002f24 */
void Sub_0804C7E8(void);

__attribute__((section(".text.w14c_08002f24")))
void Clr2_08002f24(void)
{
    register u8 *p __asm__("r0");
    Sub_0804C7E8();
    __asm__ volatile("" : "=r" (p) : "0" (0x02000818));
    *p = 0;
    __asm__ volatile("" : "=r" (p) : "0" (0x02000819));
    *p = 0;
}
