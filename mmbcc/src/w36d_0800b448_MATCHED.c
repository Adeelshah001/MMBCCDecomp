/* Wave 36-D v1: 0x0800b448, ROM-order statement split (cf. W35-B b3f8). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void Worker_080082D8(u16 b, u8 *p, u8 c, int z);
__asm__(".set Worker_080082D8, 0x080082d8");

__attribute__((section(".text.w36d_0800b448")))
void Sub_0800B448(u8 a, u16 b, u8 c)
{
    u8 aa = a;
    u16 bb = b;
    u8 cc = c;
    u32 t = (u32)aa << 24;
    u16 bbT = (u16)(((u32)bb << 16) >> 16);
    u8 ccT = (u8)(((u32)cc << 24) >> 24);
    u8 *base = (u8 *)0x02004e40;
    __asm__ volatile("" : "+r"(base));
    t >>= 20;
    t += 36;
    t += (u32)base;
    Worker_080082D8(bbT, (u8 *)t, ccT, 0);
}
