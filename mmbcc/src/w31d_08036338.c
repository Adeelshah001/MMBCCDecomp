/* Wave 31-D: 0x08036338 MATCHED (ClearBitWalk_08036338) — b2 local keeps p[2] live. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed int s32;

extern u8 WalkBits_0803643C(int a, int b, int c);
__asm__(".set WalkBits_0803643C, 0x0803643c");

__attribute__((section(".text.w31d_08036338")))
int ClearBitWalk_08036338(int x_)
{
    register int x __asm__("r2") = x_;
    register u8 *p __asm__("r4") = (u8 *)0x0200bce8;
    u8 b2 = p[2];
    if (((b2 >> x) & 1) == 0)
        return 0;
    p[2] = b2 ^ (1 << x);
    {
        /* ROM uses ldrsb (agbcc never emits it); result already sign-extended. */
        register s32 v __asm__("r0");
        __asm__ volatile(
            "movs r0, #1\n\t"
            "ldrsb %0, [%1, r0]"
            : "=r"(v) : "r"(p));
        p[1] = WalkBits_0803643C(v, 0, 0);
    }
    return 1;
}
