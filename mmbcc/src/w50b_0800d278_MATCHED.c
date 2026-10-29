/* w50b 0x0800D278 v7 — natural C (best effort).
 * Decode (fresh ROM dis, 2026-10-26; pools raw LE):
 *   4 args: s (r4), a1 (sl), a2 (r8), a3 (r9). r7 = a2[0], r6 = a3[0],
 *   r5 = a1[0] (dispatch mode). [sp] = return (1, or 0 if mode 3).
 *   Tail: a2[0] = r7; a3[0] = r6; a1[0] = r5; return [sp].
 *   Mode 0: r7 = 0; r6 = 0; Sub_520C(0); p = 0x02003670 + 0x11AE;
 *   *p = (*p & 7) | 8; s[9] |= 4; (fallthrough to mode 1).
 *   Mode 1: if (s[6] != s[0]) { r5 = 2; Sub_CF10(s, (s[6] != 1) ? 8 : 0,
 *   0); Sub_D104(s); } else r5 = 3; (then tail; r5 stays 3 if equal).
 *   (ROM: r5 = 3 set before the test, then 2 if different.)
 *   Mode 2: r6++; if ((*(u16 *)0x02002F50 & 3) != 0) r6 = (r6 > 2) ?
 *   r6 : 3; if (r6 <= 3) { Sub_D04C(s, r7); tail; } r6 = 0;
 *   r7++; if (r7 > 8) { r5 = 3; Sub_CF10(s, (s[0] != 1) ? 8 : 0, 1);
 *   tail; } tbl = 0x0817353F; b = tbl[r7 - (s[6] == 1 ? 9 : 0)];
 *   Sub_CF10(s, b, 0); Sub_D04C(s, r7); tail.
 *   Mode 3: [sp] = 0; tail. Default: tail.
 *   (Callee signatures are ABI placeholders.)
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void Sub_0800520C(u32 v);
extern void Sub_0800CF10(u8 *s, u32 a, u32 b);
extern void Sub_0800D104(u8 *s);
extern void Sub_0800D04C(u8 *s, u8 v);

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
        Sub_0800520C(0);
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
            Sub_0800D104(s);
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
        Sub_0800D04C(s, r7);
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

/* Trailing pad: function code ends 2 mod 4; ROM pads with 00 00. */
__asm__(".balign 4, 0");

__asm__(
    ".globl Sub_0800520C\n.set Sub_0800520C, 0x0800520c\n"
    ".globl Sub_0800D104\n.set Sub_0800D104, 0x0800d104\n"
    ".globl Sub_0800D04C\n.set Sub_0800D04C, 0x0800d04c\n"
);
