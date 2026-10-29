/* Wave 35-B v7: 0x0800b3f8 statement-split in ROM order. */
typedef unsigned char u8;
typedef unsigned int u32;

extern void Worker_080083F8(u32 b, u8 *p, int n, u8 c);
__asm__(".set Worker_080083F8, 0x080083f8");

__attribute__((section(".text.w35b_0800b3f8")))
void Sub_0800B3F8(u8 a, u32 b, u8 c)
{
    u8 aa = a;
    u32 bb = b;
    u8 cc = c;
    u32 t = (u32)aa << 24;
    u8 ccT = (u8)(((u32)cc << 24) >> 24);
    u8 *base = (u8 *)0x02004e40;
    __asm__ volatile("" : "+r"(base));
    t >>= 20;
    t += 36;
    t += (u32)base;
    Worker_080083F8(bb, (u8 *)t, 8, ccT);
}
