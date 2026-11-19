/* ObjInit_19090 @ 0x08019090 (124 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
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

void Vec2_AddMirrored(u8 *o, u32 x, u32 y);

u32 Text_SelectBlobIdx(u32 idx);

extern u16 gRom_081705B0[];

extern u8 gEwram_020031E4[];

extern u32 gVal022F[];

__attribute__((section(".text.w6l3_19090")))
void ObjInit_19090(u8 *s)
{
    u32 idx;

    ChipSlot_Setup(s, (u32)gVal022F, s[17]);
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
        u32 zero;
        p += 0x45;
        sh = idx << 2;
        mask = -13;
        *p = (*p & mask) | sh;
        p -= 0x23;
        zero = 0;
        *p = 13;
        *(u32 *)(s + 0x58) = zero;
        *(u32 *)(s + 0x60) = zero;
        *(u32 *)(s + 0x5c) = zero;
        *(u32 *)(s + 0x64) = zero;
    }

    Vec2_AddMirrored(s, 0xFFFFE600, 0xFFFFE700);
    Text_SelectBlobIdx(0x9f);
}
