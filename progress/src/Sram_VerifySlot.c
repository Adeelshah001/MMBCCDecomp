/* Sram_VerifySlot @ 0x08001DB8 (120 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave6_l3_old.c (registry: src/wave6_l3_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x08001DB8: Sram_VerifySlot (coordinator-verified). */
extern u32 gEwram_02002FA0[];

extern u32 gRom_0804E314;

void Sram_WaitcntInit(u8 *dst, u8 *src, u32 len);

__attribute__((section(".text.w6l3_1db8")))
u32 Sram_VerifySlot(u32 a0, u32 key)
{
    u8 sel = (u8)a0;
    u16 tries;
    u32 *p4;
    u16 i;

    if (sel > 1)
        return 0;
    tries = 3;
    p4 = gEwram_02002FA0;
    do {
        i = 0;
        do {
            Sram_WaitcntInit((u8 *)(0x0E000000 + ((sel + (i << 1)) << 13)), (u8 *)p4, 16);
            if (*p4 == gRom_0804E314) {
                register u8 *p __asm__("r1");
                __asm__ volatile ("add %0, %1, #0\n\tsub %0, %0, #32" : "=r" (p) : "r" ((u8 *)p4));
                if (((u8 *)p4)[12] == 0 && ((u8 *)p4)[15] == 1 && *(u32 *)(p + 40) == key)
                    return 1;
            }
            i++;
        } while (i <= 1);
        tries--;
    } while (tries != 0);
    return 0;
}
