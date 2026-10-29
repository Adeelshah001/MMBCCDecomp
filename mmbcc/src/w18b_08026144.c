/* Wave 18-B: 0x08026144 (40 B, 1 caller, 1 bl -> Sub_257FC). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

extern void Sub_257FC(u8 *s, u16 v);

__attribute__((section(".text.w18b_08026144")))
void Loop3_08026144(u8 *p, u16 x)
{
    u8 i = 0;
    do {
        Sub_257FC(p + i * 144, x);
        i = (u8)(i + 1);
    } while (i <= 2);
}
