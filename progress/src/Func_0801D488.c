/* Func_0801D488 @ 0x0801D488 (272 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w49d_0801d488_MATCHED.c (registry: src/w49d_0801d488_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

extern u32 *Node_PopAndInit(u8 a, u8 b, u8 c, u8 d);

extern u32 sub_080052A0(void);

extern int SDiv_0804DD08(int a, int b);

extern void ChipSlot_IncUse(u8 *s, u8 idx);

__attribute__((section(".text.w49d_0801d488")))
void Func_0801D488(u8 *s)
{
    int bound = 0;
    s16 i;
    u32 v;
    u8 *p;

    switch (s[13]) {
    case 0:
        *(u32 *)(s + 0x50) = 0;
        *(u32 *)(s + 0x54) = 0;
        {
        register u32 t18 __asm__("r2") = s[18];
        __asm__ volatile("" : : "r" (t18));
        if (t18 <= 8u) {
            if (s[14] == 0) {
                register u32 c8 __asm__("r0") = 8;
                s[14]++;
                bound = c8;
            } else if ((*(u32 *)0x02003670 & 3) == 0) {
                register u32 c1 __asm__("r1") = 1;
                bound = c1;
            }
            for (i = 0; i < bound; i++) {
                p = (u8 *)Node_PopAndInit(0, 1, 0, 12);
                if (p != 0) {
                    s[18]++;
                    *(u32 *)(p + 0x28) = (u32)s;
                    p[16] = s[16];
                    p[17] = s[18];
                    {
                        register u32 tb __asm__("r2") = bound;
                        __asm__ volatile("" : : "r" (tb));
                        if (tb > 1u) {
                        u32 rv = sub_080052A0();
                        int sd = SDiv_0804DD08((i << 8) - i, bound);
                        v = sd + (rv & 31);
                    } else
                        v = sub_080052A0();
                    }
                    *(u32 *)(p + 0x5c) = (u8)v;
                    {
                        u32 rv2 = sub_080052A0();
                        register u32 mk __asm__("r2") = 0x1F00;
                        register u32 pv __asm__("r1");
                        pv = mk & rv2;
                        pv += 0x1000;
                        *(u32 *)(p + 0x58) = pv;
                    }
                }
            }
        } else {
            register u32 t19 __asm__("r2") = s[19];
            __asm__ volatile("" : : "r" (t19));
            if (t19 > 8u) {
                s[13]++;
                ChipSlot_IncUse(s, 9);
                s[10] |= 1;
            }
        }
        break;
    }
    case 1:
        if (s[0x77] == 3) {
            register u32 *base __asm__("r1") = (u32 *)0x082243d8;
            register u32 tidx __asm__("r2") = s[9];
            register u32 sc __asm__("r0");
            u32 *tp;
            __asm__ volatile("" : : "r" (base));
            __asm__ volatile("" : : "r" (tidx));
            sc = tidx << 2;
            tp = (u32 *)(sc + (u32)base);
            *(u32 *)(s + 12) = 2;
            *(u32 *)(s + 20) = *(u32 *)(*tp + 8);
            s[10] &= 0xFE;
        }
        break;
    default:
        break;
    }
}
