/* ObjInit_TypeB @ 0x0801DCC0 (136 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
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

__attribute__((section(".text.w7d_0801dcc0")))
void ObjInit_TypeB(u8 *s)
{
    u32 idx;
    int mask;

    *(u32 *)(s + 0x6C) = 0;
    {
        u32 v;
        v = 2;
        v |= s[0xA];
        v |= 1;
        s[0xA] = v;
    }
    ChipSlot_Setup(s, 0x501, 0);
    ChipSlot_IncUse(s, 11);
    {
        u8 *p = s;
        register int m41 __asm__("r0");
        p += 0x41;
        m41 = -13;
        *p = (*p & m41) | 4;
    }
    idx = *(u8 *)((((gRom_081705B0[1] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;
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
        u8 v12 = s[0x12];
        s[0x22] = v12;
    }
    {
        u8 *q = *(u8 **)(s + 0x28);
        q += 0x21;
        *q = 8;
    }
}
