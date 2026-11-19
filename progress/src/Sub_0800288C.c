/* Sub_0800288C @ 0x0800288C (68 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36d_0800288c_MATCHED.c (registry: src/w36d_0800288c_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void LZ77UnCompWram(u8 *src, u8 *dst);

extern void CpuFastSet(u8 *src, u8 *dst, u32 n);

__attribute__((section(".text.w36d_0800288c")))
void Sub_0800288C(u8 *s, u8 *dst)
{
    register u8 *ss __asm__("r2") = s;
    register u8 *dd __asm__("r3") = dst;
    register u8 b __asm__("r1");
    register int sh __asm__("r0");
    if (*(u16 *)(ss + 4) == 0)
        return;
    b = ss[7];
    sh = b << 5;
    dd += sh;
    if (ss[6] == 0)
        goto second;
    {
        register u8 *src __asm__("r0");
        register u32 d2 __asm__("r1");
        src = ss + *(u32 *)ss;
        d2 = 0x03002420;
        __asm__ volatile("" : "+r"(d2));
        d2 = (u32)dd + d2;
        LZ77UnCompWram(src, (u8 *)d2);
    }
    return;
second:
    {
        register u8 *src __asm__("r0");
        register u32 d2 __asm__("r1");
        src = ss + *(u32 *)ss;
        d2 = 0x03002420;
        __asm__ volatile("" : "+r"(d2));
        d2 = (u32)dd + d2;
        CpuFastSet(src, (u8 *)d2, *(u16 *)(ss + 4) >> 2);
    }
}
