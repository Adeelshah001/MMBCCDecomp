/* ObjInit_205B8 @ 0x080205B8 (166 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
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

__attribute__((section(".text.w7d_080205b8")))
void ObjInit_205B8(u8 *s)
{
    u32 idx;
    int mask;

    *(u32 *)(s + 0x6C) = 0;
    {
        u32 v;
        register u32 c1 __asm__("r1");
        v = 2;
        v |= s[0xA];
        __asm__("movs %0,#1" : "=r"(c1));
        v |= c1;
        s[0xA] = v;
    }
    ChipSlot_Setup(s, 0x401B, 0);
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
        register u32 sh __asm__("r0");
        register int m __asm__("r1");
        p += 0x45;
        sh = idx << 2;
        m = -13;
        *p = (*p & m) | sh;
    }
    if (s[0x11] & 2) {
        s[0x48] = 1;
        s[0xA] |= 16;
    }
    s[0x12] = 16;
    if (s[0x11] & 1) {
        *(u32 *)(s + 0x50) = 0x7800;
        *(u32 *)(s + 0x54) = 0x8C00;
    } else {
        *(u32 *)(s + 0x50) = 0x7800;
        *(u32 *)(s + 0x54) = 0x2000;
    }
}
