/* ObjInit_20D54 @ 0x08020D54 (128 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
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

__attribute__((section(".text.w6l3_20d54")))
void ObjInit_20D54(u8 *s)
{
    u8 *r5 = *(u8 **)(s + 0x28);
    u8 t;
    u32 idx;

    *(u32 *)(s + 0x6c) = 0;
    t = 2;
    t |= s[10];
    s[10] = t | 1;
    ChipSlot_Setup(s, 0x421C, 0);
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
    *(u32 *)(s + 0x50) = 0x7800;
    *(u32 *)(s + 0x54) = 0x6400;
    {
        u8 t2 = 2;
        t2 |= r5[10];
        r5[10] = t2;
    }
    s[18] = 30;
}
