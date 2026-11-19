/* Sub_08045FCC @ 0x08045FCC (108 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_08045fcc_MATCHED.c (registry: mmbcc/src/w36b_08045fcc_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void sub_08005A9C(int x);

extern u8 Count_467DC(u8 *p);

extern void sub_08046038(u8 *p);

extern void sub_080460C0(u8 *p);

extern void Sub_080466AC(u8 *p);

extern void ShiftPairCfg_46810(u8 *p);

extern u8 sub_080462A8(u8 *p);

__attribute__((section(".text.w36b_08045fcc")))
int Sub_08045FCC(u8 *p)
{
    int ret = 0;
    switch (p[6]) {
    case 0:
        sub_08005A9C(9);
        {
            u8 v = Count_467DC(p);
            u8 *arr = (u8 *)0x02004830;
            arr[618] = v;
            arr[619] = 0;
        }
        sub_08046038(p);
        sub_080460C0(p);
        Sub_080466AC(p);
        ShiftPairCfg_46810(p);
        p[6]++;
        /* fallthrough */
    case 1:
        if (sub_080462A8(p) != 0) {
            ret = 1;
        }
        break;
    default:
        break;
    }
    return ret;
}
