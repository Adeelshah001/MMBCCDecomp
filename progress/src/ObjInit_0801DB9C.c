/* ObjInit_0801DB9C @ 0x0801DB9C (108 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave6_l4_old.c (registry: src/wave6_l4_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x0801ae00: ObjInit_0801AE00 (coordinator-verified). */
extern void ChipSlot_Setup(u8 *s, u16 a, u8 b);

extern void ChipSlot_IncUse(u8 *s, u8 idx);

extern u16 gRom_081705B0[];

extern u8 gEwram_020031E4[];

__attribute__((section(".text.w6l4_0801db9c")))
void ObjInit_0801DB9C(u8 *s)
{
    u8 t;
    u32 idx;
    int mask;

    *(u32 *)(s + 108) = 0;
    t = 2;
    t |= s[10];
    s[10] = t | 1;
    ChipSlot_Setup(s, 0x501, 0);
    ChipSlot_IncUse(s, 10);
    idx = *(u8 *)((((gRom_081705B0[0] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;
    {
        register int c __asm__("r0");
        __asm__("movs %0, %1" : "=r"(c) : "r"(idx));
        if (c > 3)
            idx = 3;
    }
    {
        u8 *p = s;
        p += 0x45;
        idx <<= 2;
        mask = -13;
        *p = (*p & mask) | idx;
    }
    {
        u8 *q = s + 0x22;
        u8 z;
        __asm__("movs %0, #0" : "=l"(z));
        *q = z;
    }
}
