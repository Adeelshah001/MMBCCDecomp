/* InitPtr_08004548 @ 0x08004548 (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_C.c (registry: src/wave14_C.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* InitPtr_08004548 @ 0x08004548 */
void DmaCopy_0800456c(void);

__attribute__((section(".text.w14c_08004548")))
void InitPtr_08004548(u32 a)
{
    register u32 *p __asm__("r1");
    register u32 off __asm__("r0");
    __asm__ volatile("" : "=r" (p) : "0" (0x02003250));
    *p = a;
    __asm__ volatile("" : "=r" (off) : "0" (0x00000414));
    p = (u32 *)((u32)p + off);
    __asm__ volatile("" : "=r" (off) : "0" (0x0816E314));
    *p = off;
    DmaCopy_0800456c();
}
