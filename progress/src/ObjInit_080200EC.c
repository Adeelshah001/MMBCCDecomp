/* ObjInit_080200EC @ 0x080200EC (136 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w15c_080200ec.c (registry: src/w15c_080200ec.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Wrapper_D728(u32 a, u16 b, u8 c);

extern void ChipSlot_IncUse(u8 *s, u8 idx);

extern u16 gRom_081705B0[];

extern u8 gEwram_020031E4[];

void __attribute__((section(".text.w15c2_080200ec"))) ObjInit_080200EC(u8 *s)
{
    u8 *base = *(u8 **)(s + 40);
    register u8 *p2 __asm__("r2") = *(u8 **)(base + 40);
    u8 t;
    u16 w;
    {
        register u32 z __asm__("r0") = 0;
        *(u32 *)(s + 108) = z;
    }
    t = 2;
    t |= s[10];
    s[10] = t | 1;
    s[18] = ((u32)(*(p2 + 0x23)) << 28) >> 28;
    w = 0x3F18;
    if (s[18] == 0)
        w = 0x3E18;
    Wrapper_D728((u32)s, w, 0);
    ChipSlot_IncUse(s, 1);
    {
        u32 idx;
        int mask;
        idx = (*(u8 *)((((gRom_081705B0[1] >> 4) << 1) + (u32)gEwram_020031E4))) & 3;
        {
            register int c __asm__("r0");
            __asm__ ("movs %0, %1" : "=r" (c) : "r" (idx));
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
    }
    s[0x22] = 30;
    s[19] = 4;
}
