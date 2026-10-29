/* Wave 34-C v1: 0x08004ef4 — A(1); B(); C(0x02004ff0, 0x02006700, 18). */
typedef unsigned char u8;

extern void A_0800D420(int);
extern void B_0800D55C(void);
extern void C_08020EA4(u8 *p1, u8 *p2, int n);
__asm__(".set A_0800D420, 0x0800d420");
__asm__(".set B_0800D55C, 0x0800d55c");
__asm__(".set C_08020EA4, 0x08020ea4");

__attribute__((section(".text.w34c_08004ef4")))
void Sub_08004EF4(void)
{
    A_0800D420(1);
    B_0800D55C();
    C_08020EA4((u8 *)0x02004ff0, (u8 *)0x02006700, 18);
}
