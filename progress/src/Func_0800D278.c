/* Func_0800D278 @ 0x0800D278 (294 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w50b_0800d278_MATCHED.c (registry: src/w50b_0800d278_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void BitCtl_520C(u32 v);

extern void Sub_0800CF10(u8 *s, u32 a, u32 b);

extern void F_D104(u8 *s);

extern void sub_0800D04C(u8 *s, u8 v);

__attribute__((section(".text.w50b_0800d278")))
u32 Func_0800D278(u8 *s, u8 *a1, u8 *a2, u8 *a3) {
    u8 r7 = a2[0];
    u8 r6 = a3[0];
    u8 r5 = a1[0];
    u32 ret = 1;
    switch (r5) {
    case 0:
        r7 = 0;
        r6 = 0;
        BitCtl_520C(0);
        {
            u8 *base = (u8 *)0x02003670;
            u8 *p;
            __asm__ volatile("" : "+r"(base));
            p = base + 0x11AE;
            *p = (u8)((*p & 7) | 8);
        }
        {
            u8 y = s[9];
            s[9] = (u8)(y | 4);
        }
        /* fallthrough */
    case 1: {
        u8 x = s[6];
        __asm__ volatile("" : "+r"(x));
        r5 = 3;
        if (x != s[0]) {
            int t;
            int sg;
            register u32 m __asm__("r2");
            register int one __asm__("r1");
            r5 = 2;
            m = 8;
            one = 1;
            t = one ^ x;
            sg = -t;
            sg |= t;
            sg >>= 31;
            m &= (u32)sg;
            Sub_0800CF10(s, m, 0);
            F_D104(s);
        }
        break;
    }
    case 2: {
        r6 = (u8)(r6 + 1);
        if ((*(u16 *)0x02002F50 & 3) != 0)
            r6 = (r6 > 2) ? r6 : 3;
        if (r6 <= 3)
            goto d04c;
        r6 = 0;
        r7 = (u8)(r7 + 1);
        if (r7 <= 8) {
            u8 *tbl = (u8 *)0x0817353F;
            u8 *p = tbl;
            if (s[6] == 1)
                p -= 9;
            p += r7;
            Sub_0800CF10(s, *p, 0);
            goto d04c;
        }
        r5 = 3;
        {
            int t;
            int sg;
            register u32 m __asm__("r2");
            register int one __asm__("r1");
            m = 8;
            one = 1;
            t = one ^ s[0];
            sg = (t | -t) >> 31;
            m &= (u32)sg;
            Sub_0800CF10(s, m, 1);
        }
        break;
    d04c:
        sub_0800D04C(s, r7);
        break;
    }
    case 3:
        ret = 0;
        break;
    default:
        break;
    }
    a2[0] = r7;
    a3[0] = r6;
    a1[0] = r5;
    return ret;
}
