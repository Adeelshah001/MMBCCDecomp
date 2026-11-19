/* Task_35DA4 @ 0x08035DA4 (80 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave5_h2.c (registry: src/wave5_h2.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

u32 Text_SelectBlobIdx(u16 idx);

extern u8 gEwram_02004CE0[];

__attribute__((section(".text.w5h_35da4")))
void Task_35DA4(u8 *p)
{
    u8 *pA = p + 0x46ab;
    u8 v = *pA;
    u32 flag = 0;
    u16 *ew;
    if ((s8)v > 3) {
        v -= 4;
        flag = 1;
    }
    p[0x46a9] = 3;
    Text_SelectBlobIdx(0x66);
    ew = (u16 *)gEwram_02004CE0;
    ew[20] = (v << 4) + 0xf8;
    ew[21] = flag * 24 + 0x20;
}
