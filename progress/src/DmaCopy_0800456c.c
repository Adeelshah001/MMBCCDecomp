/* DmaCopy_0800456c @ 0x0800456C (64 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_C.c (registry: src/wave14_C.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* DmaCopy_0800456c @ 0x0800456c */
void CpuFastSet(void *dst, void *src, u32 n);

void sub_080045AC(void);

__attribute__((section(".text.w14c_0800456c")))
void DmaCopy_0800456c(void)
{
    u8 *dst;
    register u16 *base __asm__("r2");
    u32 t;
    __asm__ volatile("" : "=r" (dst) : "0" (0x08055B3C));
    __asm__ volatile("" : "=r" (base) : "0" (0x020031E4));
    t = 12;
    t &= *base;
    t <<= 12;
    t += 0x06007800;
    CpuFastSet(dst, (void *)t, 0x80 << 2);
    CpuFastSet((void *)0x0804E31C, (void *)0x03002420, 8);
    sub_080045AC();
}
