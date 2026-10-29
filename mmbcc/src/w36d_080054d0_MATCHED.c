/* Wave 36-D MATCHED (old_agbcc, 0 diffs over 140 B true extent 0x080054d0-0x0800555c; C + pinned-reg/inline-asm idioms: s16 block asm, m pinned r4, t1 pinned r1, tmp pinned r0, goto d-dispatch, orig &= 1 in place), 140 B, extent next-func 0x0800555c. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;

extern u32 Sub_080052A0(void);
__asm__(".set Sub_080052A0, 0x080052a0");
extern u32 Sub_0804DEE8(u32 a, u32 b);
__asm__(".set Sub_0804DEE8, 0x0804dee8");

__attribute__((section(".text.w36d_080054d0")))
void Sub_080054D0(u32 *s, u8 v)
{
    register u32 orig __asm__("r5") = v;
    u32 r6 = 0;
    u32 r4 = 0;
    if (v != 0) {
        u32 t = 4;
        u32 c1;
        u32 c2;
        u32 c3;
        u32 d;
        register s32 sh __asm__("r1");
        register s32 s6 __asm__("r2");
        if (v <= 4)
            t = v;
        r6 = t;
        c1 = Sub_080052A0();
        {
            register u32 m __asm__("r4") = 3;
            {
                register u32 t1 __asm__("r1") = m & c1;
                r6 += t1;
            }
            c2 = Sub_080052A0();
            __asm__ volatile("lsl %0, %2, #16\n\tasr %1, %0, #16\n\tasr %0, %0, #18"
                             : "=r"(sh), "=r"(s6) : "r"(r6));
            m &= c2;
            r4 = (u16)(sh + m);
        }
        orig &= 1;
        if (orig) {
            register u32 tmp __asm__("r0");
            __asm__ volatile("neg %0, %1" : "=r"(tmp) : "r"(s6));
            r6 = (u16)tmp;
        }
        c3 = Sub_080052A0();
        d = (u16)Sub_0804DEE8((u16)c3, 3);
        {
            register u32 tmp __asm__("r0");
            if (d > 1)
                goto neg;
            if (d == 0)
                goto zero;
            __asm__ volatile("lsl %0, %1, #16\n\tlsr %0, %0, #16" : "=r"(tmp) : "r"(r4));
            goto endd;
        zero:
            tmp = 0;
        endd:
            r4 = tmp;
            goto final;
        neg:
            r4 = (u32)(-(r4 << 16)) >> 16;
        final:;
        }
    }
    {
        u32 *q = ((u32 *)s) + 140;
        *q = (s16)r6 << 8;
        q[1] = (s16)r4 << 8;
    }
}
