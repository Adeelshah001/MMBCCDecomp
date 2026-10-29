/* W38-C: 0x08017600, TRUE extent 32 B (next fn 0x08017620).
 * s[10] &= 254; *(u32*)(s+12) = 4;
 * *(u32*)(s+20) = *(u32*)(*(u32*)(0x082243d8 + s[9]*4) + 16);
 * Pool (LE): 0x082243d8.
 */
typedef unsigned char u8;
typedef unsigned int u32;

__attribute__((section(".text.w38c_08017600")))
void Sub_08017600(u8 *s)
{
    register u8 *base __asm__("r2");
    u8 *addr;
    s[10] &= 254;
    base = (u8 *)0x082243d8;
    __asm__ volatile("" : "+r"(base));
    addr = (u8 *)(s[9] * 4 + (int)base);
    *(u32 *)(s + 12) = 4;
    *(u32 *)(s + 20) = *(u32 *)(*(u32 *)addr + 16);
}
