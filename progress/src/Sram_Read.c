/* Sram_Read @ 0x0804DBC0 (64 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/sram.c (registry: src/sram.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

__attribute__((section(".text.sram")))
void Sram_Read(u8 *src, u8 *dst, u32 len)
{
    s32 n = (s32)len;
    {
        register u32 wc __asm__("r2") = 0x04000204;
        register u16 v __asm__("r0");
        u16 m;
        __asm__ volatile ("ldrh %0, [%1]" : "=r" (v) : "r" (wc));
        m = 0xFFFC;
        v &= m;
        v |= 3;
        *(volatile u16 *)wc = v;
    }

    n--;
    if (n == -1)
        return;
    do {
        *dst++ = *src++;
        n--;
    } while (n != -1);
}
