/* W33-D MATCHED: sub_080111B4 @ 0x080111B4. main agbcc. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 sub_0800B3EC(u32 a, u32 b);

__attribute__((section(".text.w33d_080111b4")))
void sub_080111B4(u32 a)
{
    volatile u8 *p = (volatile u8 *)0x020051B0;
    u32 zero = 0;
    p[4] = a;
    p[1] = zero;
    p[0] = zero;
    sub_0800B3EC(0, 0);
}
