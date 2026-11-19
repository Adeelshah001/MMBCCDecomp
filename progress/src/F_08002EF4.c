/* F_08002EF4 @ 0x08002EF4 (48 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w24d_08002ef4.c (registry: src/w24d_08002ef4.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Sub_0804C630(void);

extern u8 gAddrZero[];

__attribute__((section(".text.w24d_08002ef4")))
void F_08002EF4(void)
{
    register u32 *pa __asm__("r1");
    register u32 va __asm__("r0");
    register u8 *p __asm__("r0");
    Sub_0804C630();
    __asm__ volatile("" : "=r" (pa) : "0" (0x02003244));
    __asm__ volatile("" : "=r" (va) : "0" ((u32)&gAddrZero[0xAA]));
    *pa = (u16)va;
    __asm__ volatile("" : "=r" (p) : "0" (0x02000818));
    *p = 0;
    __asm__ volatile("" : "=r" (p) : "0" (0x02000819));
    *p = 0;
}
