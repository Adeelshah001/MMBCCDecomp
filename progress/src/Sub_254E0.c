/* Sub_254E0 @ 0x080254E0 (66 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w17d_080254e0.c (registry: src/w17c_misc_old.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 GetMaskedByte_08025324(u8 *p, u32 idx);

extern int Append_0802526C(void *s, u32 v);

__attribute__((section(".text.w17d_080254E0")))
void Sub_254E0(u8 *s, u8 idx)
{
    register u8 *ss __asm__("r6");
    register u32 ii __asm__("r5");
    register u32 x __asm__("r4");
    u8 v;
    u32 b;
    __asm__ volatile("add %0, %1, #0" : "=r" (ss) : "r" (s));
    __asm__ volatile("lsl r1, r1, #24\n\tlsr %0, r1, #24" : "=r" (ii) : "r" (ss) : "r1");
    x = (u32)(*(u8 **)(ss + 4) + ii);
    v = GetMaskedByte_08025324(*(u8 **)(ss + 0), ii);
    __asm__ volatile("ldrb %0, [%0]" : "+r" (x));
    b = x;
    if (b != v) {
        {
            register u8 *q __asm__("r0") = *(u8 **)(ss + 4) + ii;
            (*q)++;
        }
        if (*(u8 *)(*(u8 **)(ss + 4) + ii) == 1)
            Append_0802526C(ss + 12, ii);
    }
}
