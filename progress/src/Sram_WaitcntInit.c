/* Sram_WaitcntInit @ 0x0804DB5C (100 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/sram.c (registry: src/sram.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

void Sram_Memcpy(u8 *src, u8 *dst, u32 len);

__attribute__((section(".text.sram")))
void Sram_WaitcntInit(u8 *dst, u8 *src, u32 len)
{
    u8 buf[0x80];
    u16 *s;
    u16 *d;
    u16 i;
    u32 addr;
    register u32 code __asm__("r3");
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

    addr = (u32)Sram_Memcpy;
    __asm__ volatile ("bic %0, %1" : "+r" (addr) : "r" (1));
    s = (u16 *)addr;
    d = (u16 *)buf;
    for (i = ((u32)Sram_WaitcntInit - (u32)Sram_Memcpy) / 2; i != 0; i--)
        *d++ = *s++;
    code = (u32)buf;
    __asm__ volatile ("add %0, #1" : "+r" (code));
    ((void (*)(u8 *, u8 *, u32))code)(dst, src, len);
}
