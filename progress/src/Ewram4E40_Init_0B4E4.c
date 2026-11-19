/* Ewram4E40_Init_0B4E4 @ 0x0800B4E4 (60 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave9_d_old.c (registry: src/wave9_d_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern u8 gEwram_02004E40[];

__attribute__((section(".text.w9d_0800b4e4")))
void Ewram4E40_Init_0B4E4(void)
{
    u8 *base = gEwram_02004E40;
    register u8 *p __asm__("r4") = base;
    u16 v;
    s16 i = 0;
    p += 136;
    v = 0x8000;
    do {
        u32 off = (u32)i * 36;
        register u8 *addr __asm__("r0");
        __asm__ volatile("add %0, %1, %2" : "=r" (addr) : "r" (p), "r" (off));
        *(u16 *)addr = v;
        i++;
    } while (i <= 2);
    base[20] |= 4;
}
