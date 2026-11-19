/* IoRegWrite_4D130 @ 0x0804D130 (80 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_B_old.c (registry: src/wave14_B_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* Switch-driven IO register writes (0x4000063-0x400007D region).
 * Decisive idiom: old_agbcc omits push{lr} for true-leaf switch
 * (main agbcc emits it); interleaved pools fall out of barrier placement. */
__attribute__((section(".text.w14b_0804d130")))
void IoRegWrite_4D130(u8 a)
{
    u8 *p;
    switch (a) {
    case 1:
        p = (u8 *)0x4000063;
        *p = 8;
        p += 2;
        goto tail128;
    case 2:
        p = (u8 *)0x4000069;
        goto tail8;
    case 3:
        *(u8 *)0x4000070 = 0;
        return;
    default:
        p = (u8 *)0x4000079;
    tail8:
        *p = 8;
        p += 4;
    tail128:
        *p = 128;
        break;
    }
}
