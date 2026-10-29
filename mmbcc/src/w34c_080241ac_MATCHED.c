/* Wave 34-C v1: 0x080241ac — A(p); B(p+24, *(p+52)+1184, 1184). */
typedef unsigned char u8;
typedef unsigned int u32;

extern void A_08025464(u8 *p);
extern void B_08026208(u8 *q, u32 x, u32 n);
__asm__(".set A_08025464, 0x08025464");
__asm__(".set B_08026208, 0x08026208");

__attribute__((section(".text.w34c_080241ac")))
void Sub_080241AC(void)
{
    u8 *p = (u8 *)0x02007090;
    u8 *q;
    A_08025464(p);
    q = p;
    q += 24;
    B_08026208(q, *(u32 *)(p + 52) + 1184, 1184);
}
