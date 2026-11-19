/* Func_0800FEE0 @ 0x0800FEE0 (276 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w51c_0800fee0_MATCHED.c (registry: src/w51c_0800fee0_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern u32 CheckAndSet_B2B4(void);

extern int Tst_0800B2D8(void);

extern u32 Check_B308(void);

extern int Tst_0800B2F0(void);

extern int Sub_0800B320(u32 *a, u32 *b, u32 c, u32 d);

extern u8 *NewNode_0801CDAC(u32 a, u8 b);

extern unsigned int Byte12_Gt1_0801cdd8(u8 *s);

extern u16 ToU8(u32 v);

extern u8 sub_0800B148(u8 a, s16 b, u8 c);

extern void Ewram5160_Init_10508(u8 v);

__attribute__((section(".text.w51c_0800fee0")))
u8 Func_0800FEE0(u8 *s) {
    {
        switch (s[1]) {
        case 0:
            if ((u8)CheckAndSet_B2B4() == 0)
                goto ret;
            {
                u8 *pp;
                u16 t;
                if (s[0x42] == 0) {
                    pp = (u8 *)0x02005168;
                    __asm__ volatile("" : "+r" (pp));
                } else
                    pp = (u8 *)0x0200517c;
                t = ToU8(pp[10]);
                if ((u8)sub_0800B148((s[0x42] == 0) ? 1 : 3, (s16)t, 1) == 0)
                    goto ret;
                __asm__ volatile("@ fee0-m0");
            }
            goto inc;
        case 1:
            if ((u8)Tst_0800B2D8() == 0)
                goto ret;
            if ((u8)Sub_0800B320((u32 *)*(u32 *)(s + 0x30), 0, 0, 0) == 0)
                goto ret;
            goto inc;
        case 2:
            if ((u8)Check_B308() == 0)
                goto ret;
            __asm__ volatile("@ fee0-m2");
            goto inc;
        case 3:
            if ((u8)CheckAndSet_B2B4() == 0)
                goto ret;
            __asm__ volatile("@ fee0-m3");
            goto inc;
        case 4:
            if ((u8)Tst_0800B2F0() == 0)
                goto ret;
            __asm__ volatile("@ fee0-m4");
            goto inc;
        case 5: {
            register u32 b __asm__("r2") = s[0x42];
            register u8 *pp __asm__("r0");
            u8 *nd;
            if (b == 0) {
                pp = (u8 *)0x02005168;
                __asm__ volatile("" : "+r" (pp));
            } else
                pp = (u8 *)0x0200517c;
            nd = NewNode_0801CDAC(b, pp[10]);
            if (nd == 0)
                goto ret;
            *(u8 **)(s + 0x3c) = nd;
            /* fallthrough to inc */
        }
        inc:
            s[1]++;
            goto ret;
        case 6:
            if ((u8)Byte12_Gt1_0801cdd8(*(u8 **)(s + 0x3c)) == 0)
                goto ret;
            *(u8 **)(s + 0x3c) = 0;
            Ewram5160_Init_10508(0);
            goto ret;
        default:
            goto ret;
        }
    }
ret:
    return s[0];
}
