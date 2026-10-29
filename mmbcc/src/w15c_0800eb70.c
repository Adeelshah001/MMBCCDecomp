/* Wave 15-C: FlagStore_0800EB70 @ 0x0800eb70 (main). Coordinator-landed, 0-diff verified. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 g_02005130[];
void SetByte20_Clear21to23_0800E1F0(u8 x);

void FlagStore_0800EB70(u8 a, u8 b) __attribute__((section(".text.w15c1_0800EB70")));
void FlagStore_0800EB70(u8 a, u8 b)
{
    u8 *q = g_02005130;
    u8 *p;
    u8 *r;
    p = q;
    p += 37;
    *p = 0;
    if (b == 1)
        *p = b;
    r = q;
    r += 36;
    *r = a;
    SetByte20_Clear21to23_0800E1F0(5);
}

__asm__(
    ".thumb\n"
    ".thumb_func\n"
    ".globl SetByte20_Clear21to23_0800E1F0\n"
    ".set SetByte20_Clear21to23_0800E1F0, 0x0800E1F0\n"
);
