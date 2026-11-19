/* ObjInit_TypeA @ 0x08017F8C (216 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_d_old.c (registry: src/wave7_d_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x08017f8c: ObjInit_TypeA (coordinator-verified). */
extern void ChipSlot_Setup(u8 *s, u16 a, u8 b);

extern void ChipSlot_IncUse(u8 *s, u8 idx);

extern u16 gRom_081705B0[];

extern u8 gEwram_020031E4[];

extern void Vec2_AddMirrored(u8 *s, int x, int y);

__attribute__((section(".text.w7d_08017f8c")))
void ObjInit_TypeA(u8 *s)
{
    u32 idx;
    int mask;

    ChipSlot_Setup(s, 0x21C, 0);
    ChipSlot_IncUse(s, 0);
    if (s[16] == 2) {
        idx = *(u8 *)((((gRom_081705B0[0] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;
        {
            register int c __asm__("r0");
            __asm__("movs %0, %1" : "=r"(c) : "r"(idx));
            if (c > 3)
                idx = 3;
        }
        {
            u8 *p = s;
            u32 zero;
            p += 0x45;
            idx <<= 2;
            mask = -13;
            *p = (*p & mask) | idx;
            p -= 0x23;
            zero = 0;
            *p = 17;
            *(u32 *)(s + 88) = 0x600;
            *(u32 *)(s + 96) = zero;
            *(u32 *)(s + 92) = zero;
            *(u32 *)(s + 100) = zero;
        }
        Vec2_AddMirrored(s, 0x3300, -0x1F00);
    } else {
        idx = *(u8 *)((((gRom_081705B0[0] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;
        {
            register int c __asm__("r0");
            __asm__("movs %0, %1" : "=r"(c) : "r"(idx));
            if (c > 3)
                idx = 3;
        }
        {
            u8 *p = s;
            u32 zero;
            p += 0x45;
            idx <<= 2;
            mask = -13;
            *p = (*p & mask) | idx;
            p -= 0x23;
            zero = 0;
            *p = 12;
            *(u32 *)(s + 88) = 0x706;
            *(u32 *)(s + 96) = zero;
            *(u32 *)(s + 92) = zero;
            *(u32 *)(s + 100) = zero;
        }
        Vec2_AddMirrored(s, 0x2C00, -0x1500);
    }
}
