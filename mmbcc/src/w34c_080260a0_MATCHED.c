/* Wave 34-C v1: 0x080260a0 — for(i=0;i<=2;i++) Worker(s+i*144); s[432]=0. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

extern void Worker_080256E0(u8 *p);
__asm__(".set Worker_080256E0, 0x080256e0");

__attribute__((section(".text.w34c_080260a0")))
void Sub_080260A0(u8 *s)
{
    s16 i;
    for (i = 0; i <= 2; i++)
    {
        Worker_080256E0(s + i * 144);
    }
    s[432] = 0;
}
__asm__(".short 0x0000");
