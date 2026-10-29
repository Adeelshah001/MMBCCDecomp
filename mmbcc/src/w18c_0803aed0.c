typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
extern void Call4E60_4E44(void);
extern void PalModeSet_4DFC(u8 x);
extern u8 _call_via_r1(u8 *p, u32 x);
__attribute__((section(".text.w18c_0803aed0")))
void F_0803AED0(u8 *p)
{
    u8 st = p[2];
    if (st == 0) goto L0;
    if (st == 1) goto L1;
    goto Lend;
L0:
    Call4E60_4E44();
    {
        u8 *q = (u8 *)0x02004F80;
        PalModeSet_4DFC(q[2]);
    }
    p[2]++;
L1:
    {
        register u32 *tbl __asm__("r1");
        u8 idx;
        register u32 r __asm__("r1");
        u32 off;
        __asm__ volatile("" : "=r" (tbl) : "0" ((u32 *)0x08232344));
        off = 0x469c;
        idx = *(p + off);
        {
            u8 tmp = _call_via_r1(p, tbl[idx]);
            __asm__ volatile("" : "+r" (tmp));
            r = tmp;
        }
        if (r == 1) {
            u8 z = 0;
            p[1] = 3;
            p[2] = z;
            p[3] = z;
        } else if (r == 2) {
            u8 z = 0;
            p[1] = (u8)r;
            p[2] = z;
            p[3] = z;
        }
    }
Lend:;
}


/* Explicit 2-byte pad to match ROM (GAS would emit nop 0x46c0) */
__asm__(
    ".section .text.w18c_0803aed0,\"ax\",%progbits\n\t"
    ".byte 0, 0\n\t"
    ".previous"
);
