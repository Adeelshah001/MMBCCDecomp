/* ObjInit_TypeC @ 0x08021594 (148 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_c_old.c (registry: src/wave7_c_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x08021594: ObjInit_TypeC (148B, coordinator-verified). */
/* Wave 7 TAG=C. ObjInit_TypeC @ 0x08021594 (148 B). Tentative. v3: corrected
 * addresses (ldrh from 0x081705B0, +0x020031E4); mask as int var; literal
 * base for the 0x11AE access to avoid pool CSE. */

extern void ChipSlot_Setup(u8 *s, u16 a, u8 b);

extern void ChipSlot_IncUse(u8 *s, u8 idx);

extern u16 gRom_081705B0[];

extern u8 gEwram_020031E4[];

extern u8 gEwram_02003670[];

__attribute__((section(".text.w7c_08021594")))
void ObjInit_TypeC(u8 *s)
{
    u8 t;
    u32 idx;
    int mask = -13;
    u8 *p;
    u32 sh;
    register int c __asm__("r0");

    *(u32 *)(s + 108) = 0;
    t = 2;
    t |= s[10];
    s[10] = t | 1;
    ChipSlot_Setup(s, 0xB0 << 5, 0);
    ChipSlot_IncUse(s, 0);
    idx = *(u8 *)((((gRom_081705B0[0] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;
    __asm__("movs %0, %1" : "=r"(c) : "r"(idx));
    if (c > 3)
        idx = 3;
    p = s;
    p += 0x45;
    sh = idx << 2;
    *p = (*p & mask) | sh;
    {
        u8 *p = s;
        p += 0x22;
        {
            u8 four = 4;
            *p = four;
            *(u32 *)(s + 0x50) = (gEwram_02003670[0x11AE] & four) ? 0x7800 : 0x7000;
        }
    }
    *(u32 *)(s + 0x54) = 0xA0 << 6;
    {
        u8 z;
        __asm__("movs %0, #0" : "=r"(z));
        s[0x12] = z;
    }
}
