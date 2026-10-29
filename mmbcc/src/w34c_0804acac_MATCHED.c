/* Wave 34-C v1: 0x0804acac — sibling of 0x0804ac64 with *(p+162)=300 prestore. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed char s8;
extern int A_0804AD7C(void);
__asm__(".set A_0804AD7C, 0x0804ad7c");
__attribute__((section(".text.w34c_0804acac")))
s8 Sub_0804ACAC(void)
{
    u8 *p = (u8 *)0x0200bd20;
    s8 r;
    __asm__ volatile("" : "+r"(p));
    {
        u8 *q = p + 162;
        __asm__ volatile(
            "movs r0, #150\n\t"
            "lsl r0, r0, #1\n\t"
            "strh r0, [%0]"
            :: "r"(q) : "r0", "memory");
    }
    r = A_0804AD7C();
    if (r == 0)
    {
        u8 *q = p;
        q += 161;
        return *(s8 *)q;
    }
    return r;
}
