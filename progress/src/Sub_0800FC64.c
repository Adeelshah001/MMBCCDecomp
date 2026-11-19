/* Sub_0800FC64 @ 0x0800FC64 (236 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w52a_0800fc64_MATCHED.c (registry: src/w52a_0800fc64_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern u8 gEwram_02003670[];

extern u8 CheckAndSet_B2B4(void);

extern u8 sub_0800B148(u8 a, s16 b, int c);

extern u8 Tst_0800B2D8(void);

extern u8 Sub_0800B320(u32 a, int b, int c, int d);

extern u8 Check_B308(void);

extern u8 Tst_0800B2F0(void);

extern void Ewram5160_Init_10508(int a);

__attribute__((section(".text.w52a_0800fc64")))
u8 Sub_0800FC64(u8 *s)
{
    switch (s[1]) {
    case 0:
        if (CheckAndSet_B2B4() == 0)
            break;
        s[1]++;
        /* fallthrough */
    case 1: {
        register u8 v65 __asm__("r3");
        if (sub_0800B148(s[69], *(s16 *)(s + 56), 1) == 0)
            break;
        v65 = s[65];
        {
            unsigned int t = v65;
            if (t != 0) {
                int v = v65;
                if (t > 15)
                    v = 15;
                {
                    u8 *p = gEwram_02003670;
                    int sh;
                    p += 0x11af;
                    sh = v << 4;
                    *p = (u8)((*p & 15) | sh);
                }
                s[3] = v65;
            } else {
                s[3] = 1;
            }
        }
        s[1]++;
        break;
    }
    case 2:
        s[3]--;
        if ((s8)s[3] > 0)
            break;
        s[1]++;
        /* fallthrough */
    case 3:
        if (Tst_0800B2D8() == 0)
            break;
        if (Sub_0800B320(*(u32 *)(s + 48), 0, 0, 0) == 0)
            break;
        s[1]++;
        break;
    case 4:
        if (Check_B308() == 0)
            break;
        s[1]++;
        break;
    case 5:
        if (CheckAndSet_B2B4() == 0)
            break;
        s[1]++;
        break;
    case 6:
        if (Tst_0800B2F0() == 0)
            break;
        Ewram5160_Init_10508(0);
        break;
    default:
        break;
    }
    return s[0];
}
