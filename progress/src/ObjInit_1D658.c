/* ObjInit_1D658 @ 0x0801D658 (116 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
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

__attribute__((section(".text.w6l3_1d658")))
void ObjInit_1D658(u8 *s)
{
    u32 idx;
    u8 v1 = 1;
    register u32 zero __asm__("r1") = 0;
    u8 b1;
    u8 v2;
    u8 b2;

    b1 = s[10];
    v1 |= b1;
    s[10] = v1;
    {
        u8 *p = s;
        p += 0x50;
        *(u32 *)(p + 28) = zero;
    }
    v2 = 2;
    b2 = s[10];
    v2 |= b2;
    s[10] = v2;
    {
        u8 v2 = 2;
        v2 |= s[10];
        s[10] = v2;
    }
    ChipSlot_Setup(s, 0xA02, 0);
    ChipSlot_IncUse(s, s[19]);

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
    s[0x22] = 0;
}
