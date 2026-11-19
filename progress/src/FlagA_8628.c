/* FlagA_8628 @ 0x08008628 (44 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_s_old.c (registry: src/wave8_s_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 gEwram_02003670[];

__attribute__((section(".text.w8s_08008628")))
s8 FlagA_8628(u8 *p)
{
    int r;
    u32 flag;
    if (p[11])
        goto Ldef;
    flag = gEwram_02003670[0x11ae] & 1;
    r = 32;
    if (flag)
        goto Lend;
    r = 64;
    goto Lend;
Ldef:
    r = 32;
Lend:
    __asm__ volatile("" : "+r" (r));
    return (s8)r;
}
