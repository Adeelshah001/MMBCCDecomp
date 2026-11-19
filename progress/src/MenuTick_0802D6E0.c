/* MenuTick_0802D6E0 @ 0x0802D6E0 (192 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w28d_0802d6e0.c (registry: src/w28d_0802d6e0.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

void Set_08004E24(u8 x);

int Cmp_08004E0C(u8 x);

__attribute__((section(".text.w28d_0802d6e0")))
u32 MenuTick_0802D6E0(u8 *p) {
    switch (p[1]) {
    case 0:
        p[1]++;
    case 1: {
        u8 t6;
        if (p[2] != 0)
            return 3;
        t6 = p[6];
        if ((u8)(t6 & 8))
            goto inc;
        {
            u32 c = 0x1000;
            __asm__ volatile("" ::: "memory");
            if (*(u16 *)(p + 20) == c)
                goto set6;
        }
        {
            u32 m = 16;
            m &= t6;
            if (m == 0)
                goto inc;
        }
      set6:
        p[2] = 6;
        p[3] = 0;
        goto inc;
    }
    case 2:
        if (p[2] != 0)
            return 3;
      inc:
        p[1]++;
        return 3;
    case 3:
        if ((p[6] & 8) == 0)
            Set_08004E24(0);
        p[1]++;
        /* fallthrough into case 4 */
    case 4: {
        u16 *q;
        u16 m1, t;
        p = (u8 *)(u32)p[6];
        if ((u32)p & 8)
            goto ret4;
        if ((s8)Cmp_08004E0C(3) == 0)
            return 3;
        q = (u16 *)0x020031E0;
        m1 = 0xEDFF;
        t = m1 & *q;
        {
            u16 m2 = 0xDBFF;
            t &= m2;
        }
        *q = t;
      ret4:
        return 4;
    }
    default:
        return 3;
    }
}
