/* Wave 34-C v1: 0x0800c22c — p[26]=1 then worker(p+32, (u8)a); void. */
typedef unsigned char u8;

extern void Worker_0800E068();
__asm__(".set Worker_0800E068, 0x0800e068");

__attribute__((section(".text.w34c_0800c22c")))
void Sub_0800C22C(u8 a)
{
    int b = a;
    u8 *p = (u8 *)0x02004f40;
    p[26] = 1;
    Worker_0800E068(p + 32, (u8)b);
}
