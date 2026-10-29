/* Wave 31-D: 0x080070F0 MATCHED (CondRectFill_080070F0) around RectFill_7134. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

extern void RectFill_7134(void *ctx, u16 a, s16 b, s16 c, u8 d);
__asm__(".set RectFill_7134, 0x08007134");

__attribute__((section(".text.w31d_080070f0")))
void CondRectFill_080070F0(u16 x, u16 y, u16 z, u8 w)
{
    u8 *base = (u8 *)0x02004830;
    if (base[0x265])
        return;
    RectFill_7134(base, x, (s16)y, (s16)z, w);
}
