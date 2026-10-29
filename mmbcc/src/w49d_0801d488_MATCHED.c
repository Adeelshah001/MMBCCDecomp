/* W49-D v18 (v17 + flipped tp ADD operands): true extent 272 B (bx 0x0801d592,
 * trailing pool word 0x0801d594 = 0x082243d8 raw LE, next fn 0x0801d598;
 * mid pool 0x0801d518 = 0x02003670 raw LE). Dispatch on s[13]:
 * 0: clear s[0x50]/s[0x54]; if s[18]>8u: if s[19]>8u: s[13]++,
 * ChipSlot_IncUse(s,9), s[10]|=1; else: bound setup (s[14]==0 ->
 * s[14]=1, bound=8; else if (*(u32*)0x02003670 & 3)==0 -> bound=1)
 * then for (i=0; i<bound; i++): p=Node_PopAndInit(0,1,0,12);
 * if p: s[18]++, p[0x28]=s, p[16]=s[16], p[17]=s[18],
 * p[0x5c]=(bound>1u)? (Rand&31)+SDiv(i*255,bound) : Rand,
 * p[0x58]=(Rand&0x1F00)+0x1000. 1: if s[0x77]==3: s[12]=2,
 * s[20]=*(table[s[9]]+8), s[10]&=0xFE. Else: tail.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;

extern u32 *Node_PopAndInit(u8 a, u8 b, u8 c, u8 d);
extern u32 AbsScale_52A0(void);
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
                        u32 rv = AbsScale_52A0();
                        int sd = SDiv_0804DD08((i << 8) - i, bound);
                        v = sd + (rv & 31);
                    } else
                        v = AbsScale_52A0();
                    }
                    *(u32 *)(p + 0x5c) = (u8)v;
                    {
                        u32 rv2 = AbsScale_52A0();
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

__asm__(
    ""
    ".globl AbsScale_52A0\n.set AbsScale_52A0, 0x080052a0\n"
    ""
    ""
);
