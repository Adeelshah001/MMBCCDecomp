/* Sub_08010138 @ 0x08010138 (270 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w57a_08010138_MATCHED.c (registry: src/w57a_08010138_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

extern int Ewram5160_Init_10508(int a);

extern int SDiv_0804DD08(int a, int b);

__attribute__((section(".text.w57a_08010138")))
u8 Sub_08010138(u8 a0, u32 a1, u16 a2, u16 a3, u16 a4, u16 a5, u8 a6)
{
    register u8 *g __asm__("r5") = (u8 *)0x02005160;
    u16 q;

    if (g[0] != 0)
        return 0;
    Ewram5160_Init_10508(3);
    g[0x42] = a0;
    *(u16 *)(g + 0x38) = a2;
    *(u32 *)(g + 0x30) = a1;
    g[0x41] = a6;
    {
        u16 t = a5;
        __asm__ volatile("": "+r" (t));
        if ((s16)a5 <= 0)
            t = 1;
        a5 = t;
    }
    {
        u16 t = a3;
        __asm__ volatile("": "+r" (t));
        if ((s16)a3 < 0)
            t = 0;
        a3 = t;
    }
    {
        u16 t = a3;
        __asm__ volatile("": "+r" (t));
        if ((s16)a3 > (s16)a5)
            t = a5;
        a3 = t;
    }
    {
        u16 t = a4;
        __asm__ volatile("": "+r" (t));
        if ((s16)a4 < 0)
            t = 0;
        a4 = t;
    }
    {
        u16 t = a4;
        __asm__ volatile("": "+r" (t));
        if ((s16)a4 > (s16)a5)
            t = a5;
        a4 = t;
    }
    {
        register u32 q1 __asm__("r0") = (u32)(SDiv_0804DD08((s16)a3 * 24, (s16)a5) << 16) >> 16;
        if ((s16)a3 > 0 && q1 == 0)
            q1 = 1;
        else
            q1 = (u32)(q1 << 16) >> 16;
        g[0x3b] = q1;
    }
    {
        register u32 t __asm__("r0") = (u32)(SDiv_0804DD08((s16)a4 * 24, (s16)a5) << 16) >> 16;
        if ((s16)a4 > 0 && t == 0)
            q = 1;
        else
            q = (u16)t;
    }
    g[0x40] = q;
    __asm__ volatile("": "+r" (g));
    return 1;
}
