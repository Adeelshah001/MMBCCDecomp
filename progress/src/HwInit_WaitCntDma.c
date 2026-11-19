/* HwInit_WaitCntDma @ 0x0800063C (96 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/hwinit.c (registry: src/hwinit.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef volatile u16 vu16;

typedef volatile u32 vu32;

__attribute__((section(".text.hwinit")))
void HwInit_WaitCntDma(void)
{
    u32 spSave;
    vu32 *dma3;
    u32 ewramBase = 0x02000ED0;

    *(vu16 *)0x04000204 = 0x45B7;
    spSave = 0;
    dma3 = (vu32 *)0x040000D4;
    dma3[0] = (u32)&spSave;
    dma3[1] = 0x03000000;
    dma3[2] = 0x85001F80;
    (void)dma3[2];
    spSave = 0;
    dma3[0] = (u32)&spSave;
    dma3[1] = 0x02000000;
    dma3[2] = 0x85010000;
    (void)dma3[2];

    asm volatile ("" : "+r" (ewramBase));
    *(vu16 *)(ewramBase + 0x2002) = 0;
    *(vu16 *)(ewramBase + 0x2000) = 0;
}
