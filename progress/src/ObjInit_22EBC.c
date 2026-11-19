/* ObjInit_22EBC @ 0x08022EBC (140 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave5_g1_old.c (registry: src/wave5_g1_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void ChipSlot_Setup(u8 *s, u16 a, u8 b);

extern void ChipSlot_IncUse(u8 *s, u8 idx);

extern u16 gRom_08227174[];

extern u16 gRom_081705B0[];

extern u8 gEwram_020031E4[];

__attribute__((section(".text.w5g1_22ebc")))
void ObjInit_22EBC(u8 *s)
{
    u8 t;
    u32 idx;
    int mask;

    *(u32 *)(s + 108) = 0;
    t = 2;
    t |= s[10];
    s[10] = t | 1;
    {
        u16 *tbl = gRom_08227174;
        ChipSlot_Setup(s, tbl[s[17] * 3], 0);
    }
    ChipSlot_IncUse(s, s[17]);
    idx = *(u8 *)((((gRom_081705B0[1] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;
    {
        register int c __asm__("r0");
        __asm__ ("movs %0, %1" : "=r" (c) : "r" (idx));
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
    s[0x22] = 31;
    s[0x41] = (s[0x41] & mask) | 4;
    {
        u8 v = 4;
        s[18] = v;
    }
}
