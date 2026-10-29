/* Wave 31-D: 0x08006518 MATCHED (CondRectFill_08006518) around FillRect_65BC. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;

extern void FillRect_65BC(void *ctx, s8 x, s8 y, u8 w, u8 h, u16 a, u16 b);
__asm__(".set FillRect_65BC, 0x080065bc");

__attribute__((section(".text.w31d_08006518")))
void CondRectFill_08006518(u8 x, u8 y, u8 w, u8 h, u16 a, u16 b)
{
    u8 *base = (u8 *)0x02004830;
    if (base[0x265])
        return;
    FillRect_65BC(base, (s8)x, (s8)y, w, h, a, b);
}
