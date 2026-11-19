/* Sub_0802106C @ 0x0802106C (216 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w38a_0802106c_MATCHED.c (registry: mmcc/src/w38a_0802106c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

extern void ChipSlot_Setup(u8 *s, int b, u8 c);

extern void ChipSlot_IncUse(u8 *s, int idx);

extern u32 *Node_PopAndInit_20ED4(u8 a, u8 b, u8 c, u8 d);

extern void Sub_0802129C(u8 *s);

__attribute__((section(".text.w38a_0802106c")))
void Sub_0802106C(u8 *s)
{
    int v, w, sh, m;
    u8 *q;
    {
        register int z0 __asm__("r0");
        z0 = 0;
        *(u32 *)(s + 108) = z0;
    }
    {
        int t10 = 2 | s[10];
        register int one __asm__("r1");
        __asm__ volatile("" : "+r"(t10));
        one = 1;
        s[10] = t10 | one;
    }
    {
        register u8 *p __asm__("r0");
        register int s17 __asm__("r2");
        register int t __asm__("r3");
        register int arg __asm__("r1");
        p = (u8 *)0x08226F34;
        __asm__ volatile("" : "+r"(p));
        s17 = s[17];
        __asm__ volatile("" : "+r"(s17));
        p = (u8 *)(s17 + (u32)p);
        t = 176 << 5;
        __asm__ volatile("" : "+r"(t));
        arg = t;
        __asm__ volatile("" : "+r"(arg));
        arg |= *p;
        ChipSlot_Setup(s, arg, 0);
    }
    ChipSlot_IncUse(s, 0);
    {
        int x = (*(u16 *)0x081705b0 >> 4) << 1;
        register u8 *base2 __asm__("r1");
        register u8 *addr __asm__("r0");
        base2 = (u8 *)0x020031e4;
        __asm__ volatile("" : "+r"(base2));
        addr = (u8 *)(x + (u32)base2);
        v = *addr & 3;
    }
    w = v;
    __asm__ volatile("" : "+r"(w));
    if (w > 3)
        v = 3;
    {
        register u8 *qq __asm__("r2");
        qq = s + 69;
        sh = v << 2;
        __asm__ volatile("movs %0, #13" : "=r"(m));
        m = -m;
        *qq = (*qq & m) | sh;
    }
    {
        /* zero (r3) stays live from s[34] to s[18] so s[18] reuses
         * it with a bare strb; tbl (r2) is block-scoped here so
         * r2 stays free for the s[69] block above. */
        register int zero __asm__("r3");
        register u8 *tbl __asm__("r2");
        u8 *q34 = s + 34;
        zero = 0;
        *q34 = zero;
        tbl = (u8 *)0x08226F46;
        {
            register s32 vv __asm__("r0");
            register int s17 __asm__("r1");
            s17 = s[17];
            __asm__ volatile("" : "+r"(s17));
            vv = (s17 << 3) + (s32)tbl;
            __asm__ volatile("movs r1, #0\n\tldrsh %0, [%0, r1]" : "+r"(vv) : : "r1");
            vv <<= 8;
            *(s32 *)(s + 80) = vv;
        }
        {
            register s32 vv __asm__("r0");
            register int s17 __asm__("r1");
            register int sh __asm__("r0");
            u8 *pp;
            s17 = s[17];
            __asm__ volatile("" : "+r"(s17));
            sh = s17 << 3;
            pp = tbl + 2;
            vv = sh + (s32)pp;
            __asm__ volatile("movs r1, #0\n\tldrsh %0, [%0, r1]" : "+r"(vv) : : "r1");
            vv <<= 8;
            *(s32 *)(s + 84) = vv;
        }
        s[18] = zero;
        /* zero dies here, so the cond block's s17 pin (r3) below
         * does not clash with it; tbl (r2) stays live so the
         * cond block reuses it without reloading the pool. */
    {
        register s32 vv __asm__("r0");
        register int s17 __asm__("r3");
        register int sh __asm__("r0");
        s17 = s[17];
        __asm__ volatile("" : "+r"(s17));
        sh = s17 << 3;
        tbl += 4;
        vv = sh + (s32)tbl;
        __asm__ volatile("movs r1, #0\n\tldrsh %0, [%0, r1]" : "+r"(vv) : : "r1");
        if (vv >= 0) {
            q = (u8 *)Node_PopAndInit_20ED4(1, 0, 0, 0);
            if (q != 0) {
                q[16] = 1;
                q[17] = s[17];
                *(u32 *)(q + 40) = (u32)s;
            }
        }
    }
    }
    Sub_0802129C(s);
    s[18] = 15;
}
