/* ObjInit_1ABE4 @ 0x0801ABE4 (116 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave6_l3_old.c (registry: src/wave6_l3_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

/* 0x080186F4: ObjInit_186F4 (coordinator-verified). */
void ChipSlot_Setup(u8 *s, u32 b, u8 c);

void ChipSlot_IncUse(u8 *s, u8 idx);

extern u16 gRom_081705B0[];

extern u8 gEwram_020031E4[];

extern u8 gTbl_08226720[];

__attribute__((section(".text.w6l3_1abe4")))
void ObjInit_1ABE4(u8 *s)
{
    u32 idx;

    ChipSlot_Setup(s, (u16)(0x89 << 2), 0);
    {
        u8 *tbl = gTbl_08226720;
        ChipSlot_IncUse(s, tbl[s[17]]);
    }

    idx = *(u8 *)((((gRom_081705B0[0] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;
    {
        register int c __asm__("r0");
        __asm__ ("movs %0, %1" : "=r" (c) : "r" (idx));
        if (c > 3)
            idx = 3;
    }
    {
        u8 *p = s;
        u32 sh;
        int mask;
        u32 zero;
        p += 0x45;
        sh = idx << 2;
        mask = -13;
        *p = (*p & mask) | sh;
        p -= 0x23;
        zero = 0;
        *p = 13;
        *(u32 *)(s + 0x58) = 0xA00;
        *(s32 *)(s + 0x60) = -8;
        *(u32 *)(s + 0x5c) = zero;
        *(u32 *)(s + 0x64) = 4;
    }
}
