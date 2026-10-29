typedef unsigned char u8;
/* Wave 36-A MATCHED: 0x0800675c, 96 B, main agbcc, 1 variant.
   Extent basis: code 0x0800675c-0x080067b1 (bx r0), pad 0x080067b2-0x080067b3, pools
   0x080067b4 (0x02004830) / 0x080067b8 (0x265) -> 0x080067bc.
   Same shape as 0x080060c4 but a4 is u8 (not u16) and callee is 0x080067bc; flag check
   via pool1+pool2 sum (opaque offset prevents folding to 0x02004a95). */
typedef unsigned short u16;
typedef signed char s8;
typedef unsigned int u32;
extern void Sub_080067BC(u32 a, s8 b, s8 c, u8 d, u8 e, u8 f, u16 g);
__asm__(".set Sub_080067BC, 0x080067bc");
__attribute__((section(".text.w36a_0800675c")))
void Sub_0800675C(u8 a0, u8 a1, u8 a2, u8 a3, u8 a4, u16 a5)
{
    u32 pool1 = 0x02004830;
    u32 pool2 = 0x265;
    u8 *flagptr;
    __asm__ volatile("" : "+r"(pool2));
    flagptr = (u8 *)(pool1 + pool2);
    if (*flagptr == 0) {
        Sub_080067BC(pool1, (s8)a0, (s8)a1, a2, a3, a4, a5);
    }
}
