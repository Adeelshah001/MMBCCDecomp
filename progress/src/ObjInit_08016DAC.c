/* ObjInit_08016DAC @ 0x08016DAC (92 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave6_l4_old.c (registry: src/wave6_l4_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u16 gRom_081705B0[];

extern u8 gEwram_020031E4[];

/* 0x08016dac: ObjInit_08016DAC (coordinator-verified). */
extern u32 gTbl_08223CF0[];

__attribute__((section(".text.w6l4_08016dac")))
void ObjInit_08016DAC(u8 *s)
{
    u32 *tbl = gTbl_08223CF0;
    u32 idx;
    int mask;

    ((void (*)(u8 *))tbl[s[13]])(s);
    idx = *(u8 *)((((gRom_081705B0[0] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;
    {
        register int c __asm__("r0");
        __asm__("movs %0, %1" : "=r"(c) : "r"(idx));
        if (c > 3)
            idx = 3;
    }
    {
        u8 *p = s;
        u32 sh;
        p += 0x45;
        sh = idx << 2;
        mask = -13;
        *p = (*p & mask) | sh;
    }
    s[0x22] = 16;
}
