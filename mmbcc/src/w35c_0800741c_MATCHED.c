/* Wave 35-C v1: 0x0800741c — flag-gated 5-arg call */
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
extern void Worker_08007464(u8 *base, s16 a, s16 b, s16 c, u8 d);
__asm__(".set Worker_08007464, 0x08007464");
__attribute__((section(".text.w35c_0800741c")))
void Sub_0800741C(u16 a, u16 b, u16 c, u8 d)
{
    register u8 *base __asm__("r12") = (u8 *)0x02004830;
    __asm__ volatile("" : "+r"(base));
    if (*(u8 *)(base + 0x265) == 0)
        Worker_08007464(base, (s16)a, (s16)b, (s16)c, d);
}
