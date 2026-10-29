/* w50c 0x08042878 (288 B) v9 — v8 + empty asm between =1 strb and goto (suffix-interior merge-blocker probe) with goto-form tail (=1 first, explicit labels; source-order layout should give bhi + =1 inline + ++ after + pool barriers as ROM) + asm barrier on ret in case3 (block constant-folding ret=1 into r0-direct return; fallthrough should also move trailing pools after epilogue) with case3 break + trailing return (force ret-through-r7 fallthrough) + scoped gp pointer + empty-asm barrier per use site (blocks constant-folding of 0x0200B810+off into a single pool word; ROM loads bare gp + immediate offset); ROM reloads 0x0200B810 from pool at each use site (case0, post-loop, case3) instead of keeping it in a register (v1 kept gp in r7, forcing ret into r8 + r8 save). All other source identical to v1.
/* w49d v1
 * Decode (fresh ROM dis, 2026-10-26; pools raw LE):
 *   mode off 0x46A6; ptr 0x0200B810; offs 0x46B5, 0x46A4, 0x46B4,
 *   0x46AE, 0x46A7. Switch on s[0x46A6] (compare chain):
 *   case 0 falls to case 1; case 1 falls to case 2 loop.
 *   Mode 0: s[0x46B5] = ((u8 *)0x0200B810)[7].
 *   Mode 1: Sub_28880(0x1000, *(u16 *)(s+0x46A4), s[0x46B4], 1, 0, 0);
 *   s[0x46A6]++.
 *   Mode 2 loop: for (i=0; i<=254; i++) { if ((u8)Sub_28900() != 0)
 *   break; } if (flag == 0) return 0; ((u8 *)0x0200B810)[29] =
 *   s[0x46B4]; if (flag == 1) s[0x46AE]++; s[0x46A7]++;
 *   if ((u8)s[0x46A7] > 98) s[0x46A6]++; else s[0x46A6] = 1;
 *   return 0.
 *   Mode 3: ((u8 *)0x0200B810)[6] &= 247; ((u8 *)0x0200B810)[7] =
 *   s[0x46B5]; s[0x46AE] = (u8)UDiv(s[0x46AE], 20); return 1.
 *   Default: return 0.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void Sub_08028880(u32 a, u16 b, u8 c, u8 d, u32 e, u32 f);
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
        Sub_08028880(0x1000, *(u16 *)(s + 0x46A4), s[0x46B4], 1, 0, 0);
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

__asm__(
    ".globl Sub_08028880\n.set Sub_08028880, 0x08028880\n"
    ""
    ""
);
