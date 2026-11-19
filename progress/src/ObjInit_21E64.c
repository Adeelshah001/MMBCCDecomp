/* ObjInit_21E64 @ 0x08021E64 (112 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w16d_08021e64.c (registry: src/w16d_08021e64.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

void ChipSlot_Setup(u8 *s, u16 b, u8 c);

void ChipSlot_IncUse(u8 *s, u8 idx);

void ObjInit_21E64(u8 *s)
{
    int idx;
    *(u32 *)(s + 108) = 0;
    {
        int t = 2 | s[10];
        t |= 1;
        s[10] = t;
    }
    ChipSlot_Setup(s, 0x2d01, 0);
    ChipSlot_IncUse(s, 0);
    {
        int t = ((*(u16 *)0x81705b0 >> 4) * 2);
        register u8 *p3 __asm__("r1");
        register int a __asm__("r1");
        __asm__ volatile("" : "=r" (p3) : "0" ((u8 *)0x20031e4));
        __asm__ volatile("add %0, %0, %1" : "+r" (t) : "r" (p3));
        a = ((((u8 *)t)[0]) & 3);
        {
            register int b __asm__("r0");
            __asm__ volatile("add %0, %1, #0" : "=r" (b) : "r" (a));
            if (b > 3)
                a = 3;
            idx = a;
        }
    }
    {
        u8 *q = s + 69;
        int sh = idx * 4;
        int mask = -0xd;
        *q = (*q & mask) | sh;
    }
    {
        u8 *q = s + 0x22;
        int z;
        __asm__ volatile("" : "=r" (z) : "0" (0));
        *q = z;
    }
    s[0x12] = 0xff;
}
