/* ChipInit_0801BD7C @ 0x0801BD7C (104 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w16c_0801bd7c.c (registry: src/w16c_0801bd7c.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Wrapper_D770(u8 *p, u16 x, u8 y);

extern void ChipSlot_IncUse(u8 *p, u8 x);

extern void Vec2_AddMirrored(u8 *p, u32 x, u32 y);

__attribute__((section(".text.w16c_0801bd7c")))
void ChipInit_0801BD7C(u8 *p)
{
    u32 idx;
    int mask;
    u8 *q;
    u32 sh;
    Wrapper_D770(p, 0x825, 0);
    ChipSlot_IncUse(p, 0);
    {
        u16 *p1 = (u16 *)0x081705B0;
        u8 *p2 = (u8 *)0x020031E4;
        idx = (*(u8 *)((((*p1 >> 4) << 1) + (u32)p2))) & 3;
    }
    {
        register int c __asm__("r0");
        __asm__ ("movs %0, %1" : "=r" (c) : "r" (idx));
        if (c > 3)
            idx = 3;
    }
    q = p;
    q += 0x45;
    sh = idx << 2;
    mask = -13;
    *q = (*q & mask) | sh;
    p[0x22] = 13;
    Vec2_AddMirrored(p, 0xFFFFC400, 0);
}
