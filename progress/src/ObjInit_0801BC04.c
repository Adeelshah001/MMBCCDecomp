/* ObjInit_0801BC04 @ 0x0801BC04 (108 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave6_l4_old.c (registry: src/wave6_l4_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

/* 0x0801ae00: ObjInit_0801AE00 (coordinator-verified). */
extern void ChipSlot_Setup(u8 *s, u16 a, u8 b);

extern void ChipSlot_IncUse(u8 *s, u8 idx);

extern u16 gRom_081705B0[];

extern u8 gEwram_020031E4[];

u16 Text_SelectBlobIdx(u16 idx);

extern void Vec2_AddMirrored(u8 *o, s32 x, s32 y);

__attribute__((section(".text.w6l4_0801bc04")))
void ObjInit_0801BC04(u8 *s)
{
    u32 idx;
    int mask;

    ChipSlot_Setup(s, 0x224, 0);
    ChipSlot_IncUse(s, 0);
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
    s[0x22] = 13;
    Vec2_AddMirrored(s, -15360, 0);
    Text_SelectBlobIdx(0x9F);
}
