/* sub_0804367c @ 0x0804367C (342 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w84d_0804367c_MATCHED.c (registry: mmbcc/src/w84d_0804367c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

void sub_08005A9C(u32 x);

u32 CountNonzeroStride(u8 *s);

u16 EwGet16_18(void);

void Sub_08045E20(u8 *s);

void Sub_08045E40(u8 *s);

u8 sub_08043A9C(u8 *s);

u8 sub_08044828(u8 *s);

void F_080248AC(u32 x);

extern u8 g_02004830[];

extern u8 gEwram_02003670[];

__attribute__((section(".text.w84d_0804367c")))
u8 sub_0804367c(u8 *s)
{
    u8 flag = 0;
    switch (s[6]) {
    case 0:
        sub_08005A9C(3);
        g_02004830[618] = CountNonzeroStride(s);
        g_02004830[619] = 0;
        *(u32 *)(s + 18088) = 0;
        *(u32 *)(s + 18092) = 0;
        *(u32 *)(s + 18096) = 0;
        s[18092] = 5;
        s[18096] = 0;
        s[18098] = 0;
        s[18097] = 1;
        if (EwGet16_18() > 7)
            s[18099] = 1;
        else
            s[18099] = 0;
        gEwram_02003670[4524] = 0;
        Sub_08045E20(s);
        s[6]++;
    case 1: {
        u8 *q = s + 18094;
        u8 a;
        s8 gv;
        a = *q;
        gv = (s8)gEwram_02003670[4524];
        if (a == gv) {
            if (sub_08043A9C(s) != 0) {
                F_080248AC(0);
                flag = 1;
            }
            if (*q != (u8)gEwram_02003670[4524])
                break;
            if (sub_08044828(s) != 0) {
                F_080248AC(0);
                flag = 1;
            }
        } else {
            s16 diff = (s16)(a - gv);
            u16 step;
            if (diff < 0)
                step = diff >> 1;
            else
                step = (diff >> 1) ? (diff >> 1) : 1;
            gEwram_02003670[4524] += step;
            { u8 nv = gEwram_02003670[4524];
            if (s[18094] == nv) {
                if ((s16)step < 0)
                    Sub_08045E20(s);
                else
                    Sub_08045E40(s);
            }
            }
        }
        break;
    }
    default:
        break;
    }
    return flag;
}
