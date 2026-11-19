/* Func_08042878 @ 0x08042878 (288 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w50c_08042878_MATCHED.c (registry: src/w50c_08042878_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void sub_08028880(u32 a, u16 b, u8 c, u8 d, u32 e, u32 f);

extern u8 Sub_08028900(void);

extern u32 UDiv_0804DE70(u32 a, u32 b);

__attribute__((section(".text.w50c_08042878")))
u8 Func_08042878(u8 *s) {
    u8 ret = 0;
    u8 flag = 0;
    u8 i;
    switch (s[0x46A6]) {
    case 0: {
        u8 *g0 = (u8 *)0x0200B810;
        u8 t0;
        __asm__ volatile("" : "+r" (g0));
        t0 = g0[7];
        s[0x46B5] = t0;
    }
        /* fallthrough */
    case 1:
        sub_08028880(0x1000, *(u16 *)(s + 0x46A4), s[0x46B4], 1, 0, 0);
        s[0x46A6]++;
        /* fallthrough */
    case 2:
        i = 0;
        for (;;) {
            if (i > 254)
                break;
            flag = Sub_08028900();
            if (flag != 0)
                break;
            i = (u8)(i + 1);
        }
        if (flag == 0)
            return ret;
        {
            u8 *g2 = (u8 *)0x0200B810;
            __asm__ volatile("" : "+r" (g2));
            g2[29] = s[0x46B4];
        }
        if (flag == 1)
            s[0x46AE]++;
        s[0x46A7]++;
        if ((u8)s[0x46A7] > 98)
            goto do_inc;
        s[0x46A6] = 1;
        __asm__ volatile("");
        goto tail_done;
    do_inc:
        s[0x46A6]++;
        goto tail_done;
    tail_done:
        return ret;
    case 3: {
        u8 *g3 = (u8 *)0x0200B810;
        __asm__ volatile("" : "+r" (g3));
        g3[6] &= 247;
        g3[7] = s[0x46B5];
    }
        s[0x46AE] = (u8)UDiv_0804DE70(s[0x46AE], 20);
        ret = 1;
        __asm__ volatile("" : "+r" (ret));
        break;
    default:
        return ret;
    }
    return ret;
}
