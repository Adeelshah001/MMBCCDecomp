/* Wave 35-C v1: 0x080375c8 — call chain on (u8)b */
typedef unsigned char u8;
typedef unsigned int u32;
extern int Worker_080246A8(u8 x);
extern void Worker_08006A54(int a, int b, int c, int d, int e);
extern void Worker_08007C04(u8 x, int y);
extern void Worker_08007CF4(int a, int b, int c);
__asm__(".set Worker_080246A8, 0x080246a8");
__asm__(".set Worker_08006A54, 0x08006a54");
__asm__(".set Worker_08007C04, 0x08007c04");
__asm__(".set Worker_08007CF4, 0x08007cf4");
__attribute__((section(".text.w35c_080375c8")))
void Sub_080375C8(int a, int b)
{
    u8 x = b;
    int t = Worker_080246A8(x);
    Worker_08006A54(t, 20, 1, 8, 2);
    Worker_08007C04(x, 1);
    Worker_08007CF4(1, 20, 3);
}
__asm__(".short 0x0000");
