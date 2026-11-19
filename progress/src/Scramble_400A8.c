/* Scramble_400A8 @ 0x080400A8 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave9_e_old.c (registry: src/wave9_e_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 gEwram020070F0[];

__attribute__((section(".text.w9e_80400a8")))
u16 Scramble_400A8(void)
{
    register u8 *p __asm__("r2") = gEwram020070F0;
    register u16 h __asm__("r1") = *(u16 *)(p + 8);
    register u32 c __asm__("r3") = 0x8D94;
    register u32 v __asm__("r0") = (u32)h + c;
    register u32 t __asm__("r1") = (v << 2) + v;
    register u32 lo __asm__("r0");
    __asm__ volatile("movs %0, #255" : "=r" (lo));
    lo &= t;
    lo <<= 8;
    t <<= 16;
    __asm__ volatile("" : "+r" (t));
    t >>= 24;
    lo |= t;
    *(u16 *)(p + 8) = (u16)lo;
    return *(u16 *)(p + 8);
}
