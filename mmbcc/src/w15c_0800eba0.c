/* Wave 15-C: Store5_0800EBA0 @ 0x0800eba0 (main). Coordinator-landed, 0-diff verified. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 g_02005130[];
void SetByte20_Clear21to23_0800E1F0(u8 x);

void Store5_0800EBA0(u8 a, u8 b, u8 c, u8 d, u8 e) __attribute__((section(".text.w15c1_0800EBA0")));
void Store5_0800EBA0(u8 a, u8 b, u8 c, u8 d, u8 e)
{
    u8 *p = g_02005130;
    p[38] = a;
    p[39] = b;
    p[40] = c;
    p[11] = d;
    p[42] = e;
    SetByte20_Clear21to23_0800E1F0(6);
}

__asm__(
    ".thumb\n"
    ".thumb_func\n"
    ".globl SetByte20_Clear21to23_0800E1F0\n"
    ".set SetByte20_Clear21to23_0800E1F0, 0x0800E1F0\n"
);
