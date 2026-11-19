/* Copy8_28D0 @ 0x080028D0 (52 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_h.c (registry: src/wave4_h.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void CpuFastSet(void *src, void *dst, unsigned mode);

extern u8 gEwram_03002420[];

/* 0x080028D0: copy 8 bytes via CpuFastSet if *(u16*)(s+4)!=0 and s[6]==0.
 * Tentative. Destination is 0x03002420 + (b<<5); source is s + *(u32*)s + (a<<5).
 * The `b5 = (u8)b << 5` hoisted to prologue is required for the
 * `lsls #24; lsrs #19` sequence. */
__attribute__((section(".text.w4h_cpy8")))
void Copy8_28D0(u8 *s, u8 a, u8 b)
{
    u8 *src;
    u8 *dst;
    u32 b5;

    b5 = (u32)(u8)b << 5;
    if (*(u16 *)(s + 4) == 0)
        return;
    if (s[6] != 0)
        return;
    src = s + *(u32 *)s + ((u32)(u8)a << 5);
    dst = gEwram_03002420 + b5;
    CpuFastSet(src, dst, 8);
}
