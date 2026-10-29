/* W38-A: 0x0802106c, 216 B. Init-task (17a94 family variant).
 * s[108]=0; s[10]=2|s[10]|1 (barrier, no fold to 3);
 * Setup(s, 5632|tbl[s[17]], 0); IncUse(s, 0);
 * v = *(u8*)(0x020031e4 + ((*(u16*)0x081705b0>>4)<<1)) & 3,
 * clamped to 3 (dead clamp, barrier); s[69] = (s[69] & -13) |
 * (v<<2) (movs+negs); s[34]=0; tbl = 0x08226F46;
 * s[80] = (s16)tbl[s[17]*8+0]<<8; s[84] = (s16)tbl[s[17]*8+2]<<8
 * (ldrsh asm); s[18]=0; if ((s16)tbl[s[17]*8+4] >= 0):
 * q = Node_PopAndInit(1,0,0,0); if (q): q[16]=1; q[17]=s[17];
 * *(u32*)(q+40)=s; tail Sub_0802129C(s); s[18]=15.
 * Callees: Setup 0x0800d6e0, IncUse 0x0800d9ec,
 * Node_PopAndInit_20ED4 0x08020ed4 (MATCHED), Sub_0802129C
 * 0x0802129c (unlisted gap callee, .set).
 * NOTE: Setup staged as (u8*,int,u8) (real callee is
 * (u8*,u16,u8)) — same no-truncation caller pattern as
 * 0x08017a94; flag for coordinator at landing.
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void ChipSlot_Setup(u8 *s, int b, u8 c);
extern void ChipSlot_IncUse(u8 *s, int idx);
extern u32 *Node_PopAndInit_20ED4(u8 a, u8 b, u8 c, u8 d);
extern void Sub_0802129C(u8 *s);
__asm__(".set Sub_0802129C, 0x0802129c");

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

