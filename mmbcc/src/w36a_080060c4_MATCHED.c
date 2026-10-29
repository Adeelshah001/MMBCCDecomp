/* Wave 36-A MATCHED: 0x080060c4, 96 B, main agbcc, 2 variants.
   Extent basis: code 0x080060c4-0x08006119 (bx r0), pad 0x0800611a-0x0800611b, pools
   0x0800611c (0x02004830) / 0x08006120 (0x265) -> 0x08006124.
   6-arg function; flag check via pool1+pool2 sum (opaque offset prevents folding to
   0x02004a95); 7-arg call to 0x08006168 with pool1 as arg0. No trailing pad needed:
   extent ends with pools. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed char s8;
typedef unsigned int u32;
extern void Sub_08006168(u32 a, s8 b, s8 c, u8 d, u8 e, u16 f, u16 g);
__asm__(".set Sub_08006168, 0x08006168");
__attribute__((section(".text.w36a_080060c4")))
void Sub_080060C4(u8 a0, u8 a1, u8 a2, u8 a3, u16 a4, u16 a5)
{
    u32 pool1 = 0x02004830;
    u32 pool2 = 0x265;
    u8 *flagptr;
    __asm__ volatile("" : "+r"(pool2));
    flagptr = (u8 *)(pool1 + pool2);
    if (*flagptr == 0) {
        Sub_08006168(pool1, (s8)a0, (s8)a1, a2, a3, a4, a5);
    }
}
