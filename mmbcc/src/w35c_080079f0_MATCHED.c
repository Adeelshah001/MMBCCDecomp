/* Wave 35-C v2: 0x080079f0 — base pinned to r6 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed char s8;
extern void Worker_08007A2C(u8 *base, s8 a, s8 b, s8 c);
__asm__(".set Worker_08007A2C, 0x08007a2c");
__attribute__((section(".text.w35c_080079f0")))
void Sub_080079F0(u8 a, u16 b, u16 c)
{
    register u8 *base __asm__("r6") = (u8 *)0x02004830;
    if (*(base + 0x265) == 0)
        Worker_08007A2C(base, (s8)a, (s8)b, (s8)c);
}
