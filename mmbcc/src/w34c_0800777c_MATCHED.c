/* Wave 34-C v1: 0x0800777c — wrapper: masks 3 u8 args, calls worker(a,b,11,c), void. */
typedef unsigned char u8;

extern void Worker_08007798();
__asm__(".set Worker_08007798, 0x08007798");

__attribute__((section(".text.w34c_0800777c")))
void Sub_0800777C(u8 a, u8 b, u8 c)
{
    Worker_08007798(a, b, 11, c);
}
/* 2-byte zero pad to 4-align (ROM has 00 00, GAS would emit 46c0 nop) */
__asm__(".short 0x0000");
