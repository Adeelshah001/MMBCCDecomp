/* ObjInit_22E14 @ 0x08022E14 (116 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave6_l3_old.c (registry: src/wave6_l3_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x080186F4: ObjInit_186F4 (coordinator-verified). */
void ChipSlot_Setup(u8 *s, u32 b, u8 c);

void ChipSlot_IncUse(u8 *s, u8 idx);

extern u16 gRom_081705B0[];

extern u8 gEwram_020031E4[];

__attribute__((section(".text.w6l3_22e14")))
void ObjInit_22E14(u8 *s)
{
    u8 t;
    u32 idx;
    u32 zero;

    __asm__("movs %0,#0" : "=l"(zero));
    *(u32 *)(s + 0x6c) = zero;
    t = 2;
    t |= s[10];
    s[10] = t | 1;
    ChipSlot_Setup(s, 0x351D, 0);
    ChipSlot_IncUse(s, 0);

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
        p += 0x45;
        sh = idx << 2;
        mask = -13;
        *p = (*p & mask) | sh;
    }
    {
        u8 *q = s;
        u32 z;
        q += 0x22;
        z = 0;
        *q = z;
        *(u32 *)(s + 0x50) = z;
    }
    *(u32 *)(s + 0x54) = 0x3000;
}
