/* HwInit_WaitCntDma @0x0800063C (Wave 1) — MATCHED 2026-10-20.
 * WAITCNT <- 0x45B7, then arms DMA3 twice (SAD=sp both times):
 *   1st: DAD=IWRAM 0x03000000, CNT=0x85001F80 (32-bit, VBlank, 8064 words)
 *   2nd: DAD=EWRAM 0x02000000, CNT=0x85010000 (32-bit, VBlank, 65536 words)
 * then zeroes halfwords at EWRAM [0x02002ED2] and [0x02002ED0].
 * The (void)dma3[2] reads are dead volatile readbacks of DMA3CNT, kept
 * verbatim from the original codegen. The empty asm is a compiler barrier:
 * without it -O2 constant-folds the EWRAM base and re-bases the two flag
 * stores as (0x02002ED2, -2) instead of (base+0x2002, base+0x2000).
 * Flags: -O2 -mthumb-interwork. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
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
