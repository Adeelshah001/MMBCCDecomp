/* Wave 31-D: 0x080073D4 MATCHED (CondRectFill_080073D4) around RectFill_7134. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

/* param1 declared int here: (x<<2)|y is int-typed, avoids u16 truncation code. */
extern void RectFill_7134(void *ctx, int a, s16 b, s16 c, u8 d);
__asm__(".set RectFill_7134, 0x08007134");

__attribute__((section(".text.w31d_080073d4")))
void CondRectFill_080073D4(u8 x, u8 y, u16 z, u16 w)
{
    u8 *base = (u8 *)0x02004830;
    if (base[0x265])
        return;
    RectFill_7134(base, (x << 2) | y, (s16)z, (s16)w, 2);
}
