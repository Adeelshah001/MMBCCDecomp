typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;

extern s8 Fwd_EBF0(void);
extern int sub_0800ea4c(int v);

__attribute__((section(".text.w36a_0803449c")))
u32 Step_0803449c(u8 *s)
{
    u32 ret = 0;
    u8 st = s[3];
    if (st == 0)
        goto state0;
    if (st == 1)
        goto state1;
    goto ret;
state0:
    s[6] |= 128;
    if ((s8)Fwd_EBF0() == 1) {
        s[3]++;
    } else {
        sub_0800ea4c(0);
        goto ret;
    }
state1:
    if ((u8)sub_0800ea4c(0) == 1)
        goto ret;
    s[6] &= 127;
    ret = 7;
ret:
    return ret;
}

__asm__(".set Fwd_EBF0, 0x0800ebf0");
__asm__(".set sub_0800ea4c, 0x0800ea4c");
