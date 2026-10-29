/* Wave 15-C: FlagByteSet_0800EC18 @ 0x0800ec18 (main). Coordinator-landed, 0-diff verified. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 g_02005130[];
void SetByte20_Clear21to23_0800E1F0(u8 x);

void FlagByteSet_0800EC18(u8 a) __attribute__((section(".text.w15c1_0800EC18")));
void FlagByteSet_0800EC18(u8 a)
{
    u32 addr = (u32)g_02005130;
    u8 *p = (u8 *)addr;
    u8 b = (u8)a;
    p[37] = 0;
    if (b == 1)
        p[37] = b;
    SetByte20_Clear21to23_0800E1F0(10);
}

__asm__(
    ".thumb\n"
    ".thumb_func\n"
    ".globl SetByte20_Clear21to23_0800E1F0\n"
    ".set SetByte20_Clear21to23_0800E1F0, 0x0800E1F0\n"
);
