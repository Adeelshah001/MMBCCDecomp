/* Worker D wave17 Part1 C1 re-derivation @0x0800b6a4 (64B). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void SetNibbleAndLookup_B6F4(u8 *p, u8 x);
extern void OrU8_1F(u8 *s);
__attribute__((section(".text.w17d_0800B6A4")))
void NibbleGate_0800B6A4(u8 *p, u8 b)
{
    if ((p[30] & 0xa0) != 0) {
        SetNibbleAndLookup_B6F4(p, 0);
    } else if ((p[31] & 16) != 0) {
        OrU8_1F(p);
    } else if ((((u32)p[18] << 28) >> 28) != b) {
        SetNibbleAndLookup_B6F4(p, b);
    }
}

__asm__(".section .text.w17d_0800B6A4,\"ax\",%progbits\n.byte 0, 0\n.previous");

