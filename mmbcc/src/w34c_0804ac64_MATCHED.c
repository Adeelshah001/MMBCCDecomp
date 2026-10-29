/* Wave 34-C v3: 0x0804ac64 — early return avoids gcc's s8 split-alloc. */
typedef unsigned char u8;
typedef signed char s8;
extern int A_0804AD7C(void);
__asm__(".set A_0804AD7C, 0x0804ad7c");
__attribute__((section(".text.w34c_0804ac64")))
s8 Sub_0804AC64(void)
{
    u8 *p = (u8 *)0x0200bd20;
    s8 r;
    __asm__ volatile("" : "+r"(p));
    r = A_0804AD7C();
    if (r == 0)
    {
        u8 *q = p;
        q += 161;
        return *(s8 *)q;
    }
    return r;
}
