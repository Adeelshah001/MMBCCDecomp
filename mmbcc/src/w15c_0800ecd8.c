/* Wave 15-C: F_0800ECD8 @ 0x0800ecd8 (main). Coordinator-landed, 0-diff verified. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;

s8 F_0801025C(u32 a, s8 b);
void SetByte20_0800E1F0(u8 x);

u32 F_0800ECD8(u32 a, u8 b) __attribute__((section(".text.w15c1_0800ECD8")));
u32 F_0800ECD8(u32 a, u8 b)
{
    u32 r = (u32)(s8)F_0801025C(a, (s8)b);
    if (r == 1)
    {
        SetByte20_0800E1F0(13);
        return 1;
    }
    return r;
}

__asm__(
    ".thumb\n"
    ".thumb_func\n"
    ".globl F_0801025C\n"
    ".set F_0801025C, 0x0801025C\n"
    ".thumb\n"
    ".thumb_func\n"
    ".globl SetByte20_0800E1F0\n"
    ".set SetByte20_0800E1F0, 0x0800E1F0\n"
);
