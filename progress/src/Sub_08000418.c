/* Sub_08000418 @ 0x08000418 (228 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w51d_08000418_MATCHED.c (registry: src/w51d_08000418_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 base_03000400[];

extern u8 gEwram_02002F50[];

extern u16 g_02003220;

extern u16 g_02003230;

extern u16 g_02003240;

extern u16 gEwram_020031E0;

extern void sub_08000F28(void);

extern void Clear16_02003090(void);

extern void Clr2_08002f24(void);

extern void G0BD10_Zero2(void);

extern void sub_0800CC24(void);

extern void sub_0800D420(int a);

extern void sub_0800D3A0(int a);

extern void DmaCopy_0800456c(void);

extern void CpuFastSet_Vram(void);

extern void Task_ActivateSlot(int a);

extern void Sub_08000E80(u32 a);

__attribute__((section(".text.w51d_08000418")))
void Sub_08000418(void)
{
    u8 *p2;
    u32 zero;
    u8 *a165 = base_03000400;
    (void)*(volatile u8 *)(a165 + 0x165);
    zero = 0;
    a165[0x165] = 1;
    sub_08000F28();
    gEwram_02002F50[20] = 24;
    gEwram_02002F50[21] = 4;
    gEwram_02002F50[44] = 24;
    gEwram_02002F50[45] = 4;
    p2 = (u8 *)0x03002420;
    p2[0x402] = 32;
    p2[0x401] = 32;
    p2[0x400] = 32;
    *(u16 *)(p2 + 0x404) = 0;
    *(u16 *)(p2 + 0x406) = 0x400;
    Clear16_02003090();
    g_02003220 = 0;
    g_02003230 = 0;
    *(u8 *)((u8 *)&g_02003230 + 14) = 0xff;
    g_02003240 = 0;
    *(u16 *)p2 = 0;
    Clr2_08002f24();
    G0BD10_Zero2();
    sub_0800CC24();
    sub_0800D420(0);
    sub_0800D3A0(0);
    DmaCopy_0800456c();
    CpuFastSet_Vram();
    {
        u16 t = gEwram_020031E0 & 0xfff8;
        __asm__ volatile("" : "+r" (t));
        gEwram_020031E0 = (u16)((t & 0xf0ff) | 0x100);
    }
    *(u32 *)((u8 *)&gEwram_020031E0 + 12) = zero;
    Task_ActivateSlot(1);
    Sub_08000E80(0x08026741);
}
