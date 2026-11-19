/* Sub_08024C14 @ 0x08024C14 (42 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_08024c14_MATCHED.c (registry: staging/wave34_C/w34c_08024c14_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u16 sub_08025B60(u8 *p, u8 a, u8 b);

__attribute__((section(".text.w34c_08024c14")))
u16 Sub_08024C14(u8 *s, u8 a, u8 b)
{
    u32 base = *(u32 *)(s + 20);
    register u32 off __asm__("r3") = 216 << 1;
    register u8 *p __asm__("r4");
    register u8 v __asm__("r5");
    u32 idx;
    __asm__ volatile("" : "+r"(off));
    p = (u8 *)(base + off);
    v = *p;
    idx = v * 144;
    return sub_08025B60((u8 *)(base + idx), a, b);
}
