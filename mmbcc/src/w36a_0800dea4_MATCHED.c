typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void sub_0800244C(u8 *a, u32 b);
extern void sub_0800288C(u8 *a, u32 b);
extern void sub_0800DEF8(u8 *a, u16 b, u8 c, u32 d, u8 e);

__attribute__((section(".text.w36a_0800dea4")))
void Dispatch_0800dea4(u8 *a1, u32 a2, u16 a3, u8 a4, u8 *a5, u32 a6, u8 a7)
{
    u32 off = a3 * 32 + (250u << 24);
    sub_0800244C(a1, a2 + off);
    sub_0800288C(a1 + 12, a4 * 32);
    sub_0800DEF8(a5, a3, a4, a6, a7);
}

__asm__(".set sub_0800244C, 0x0800244c");
__asm__(".set sub_0800288C, 0x0800288c");
__asm__(".set sub_0800DEF8, 0x0800def8");
