/* Wave 15-C: CondCopy_0800EAF4 @ 0x0800eaf4 (old_agbcc). Coordinator-landed, 0-diff verified. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 g_02005130[];
void SetByte20_Clear21to23_0800E1F0(u8 x);

void CondCopy_0800EAF4(u8 x, u8 y) __attribute__((section(".text.w15c1_0800EAF4")));
void CondCopy_0800EAF4(u8 x, u8 y)
{
    u8 *p = g_02005130;
    if (p[4] != x || p[5] != y)
    {
        p[6] = x;
        p[7] = y;
        SetByte20_Clear21to23_0800E1F0(2);
    }
}

__asm__(
    ".thumb\n"
    ".thumb_func\n"
    ".globl SetByte20_Clear21to23_0800E1F0\n"
    ".set SetByte20_Clear21to23_0800E1F0, 0x0800E1F0\n"
);
