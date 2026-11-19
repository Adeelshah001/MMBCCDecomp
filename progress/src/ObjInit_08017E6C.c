/* ObjInit_08017E6C @ 0x08017E6C (108 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
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

u16 Text_SelectBlobIdx(u16 idx);

__attribute__((section(".text.w6l4_08017e6c")))
void ObjInit_08017E6C(u8 *s)
{
    u32 idx;
    int mask;

    ChipSlot_Setup(s, 0x20C, 1);
    ChipSlot_IncUse(s, 1);
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
        p -= 0x23;
        {
            u32 zero = 0;
            *p = 13;
            *(u32 *)(s + 88) = 0x800;
            *(u32 *)(s + 96) = zero;
            *(u32 *)(s + 92) = zero;
            *(u32 *)(s + 100) = zero;
        }
    }
    Text_SelectBlobIdx(0xA3);
}
