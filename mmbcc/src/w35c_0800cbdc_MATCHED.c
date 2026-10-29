/* Wave 35-C v1: 0x0800cbdc — 20 B leaf, twin at 0x0800cbdc */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
__attribute__((section(".text.w35c_0800cbdc")))
void Sub_0800CBDC(u8 *p)
{
    u16 a = (p[22] - 1) & 63;
    u16 b = (p[24] - 1) & 63;
    *(u16 *)(p + 22) = a;
    *(u16 *)(p + 24) = b;
}
