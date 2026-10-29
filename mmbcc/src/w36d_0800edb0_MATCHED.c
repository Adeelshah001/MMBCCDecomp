/* Wave 36-D v4 (barrier between assign and +=43): 0x0800edb0 — flag in r1, s8 result, !a layout. */
typedef unsigned char u8;
typedef signed char s8;
extern int Worker_08010478(int flag);
extern void Worker_0800E1F0(int v);
__asm__(".set Worker_08010478, 0x08010478");
__asm__(".set Worker_0800E1F0, 0x0800e1f0");
__attribute__((section(".text.w36d_0800edb0")))
int Sub_0800EDB0(u8 a)
{
    register int flag __asm__("r1");
    u8 *dst;
    s8 r;
    if ((a << 24) == 0)
        flag = 0;
    else
        flag = 1;
    dst = (u8 *)0x02005130;
    __asm__ volatile("" : "+r"(dst));
    dst += 43;
    *dst = (u8)flag;
    r = Worker_08010478(flag);
    if (r == 1) {
        Worker_0800E1F0(17);
        return 1;
    }
    return r;
}
