/* Wave 31-D: 0x0803639C MATCHED (CondBitSet_0803639C) — bit-0 dispatch: set p[4] bit or WalkBits. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed int s32;

extern u8 WalkBits_0803643C(s8 a, u16 b, u8 c);
__asm__(".set WalkBits_0803643C, 0x0803643c");

__attribute__((section(".text.w31d_0803639c")))
int CondBitSet_0803639C(u16 x)
{
    register u8 *p __asm__("r4") = (u8 *)0x0200bce8;
    u8 b1 = p[1];
    if ((x & 1) != 0) {
        register int t __asm__("r0") = 2;
        p[4] = t | p[4];
    } else {
        p[1] = WalkBits_0803643C((s8)b1, x, 1);
    }
    {
        /* ROM uses ldrsb (agbcc never emits it); result already sign-extended.
           Returned as int to avoid re-extension (original likely did the same). */
        register s32 v __asm__("r0");
        __asm__ volatile(
            "movs r0, #1\n\t"
            "ldrsb %0, [%1, r0]"
            : "=r"(v) : "r"(p));
        return v;
    }
}
