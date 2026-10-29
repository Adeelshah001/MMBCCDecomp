/* Wave 31-D: 0x08006318 MATCHED (CondRectFill_08006318) — pin base to r1 to defeat 0x02004A95 fold. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;

extern void FillRect_6374(void *ctx, s8 x, s8 y, u8 w, u8 h, u16 a, u16 b, u32 c);
__asm__(".set FillRect_6374, 0x08006374");

__attribute__((section(".text.w31d_08006318")))
void CondRectFill_08006318(u8 x, u8 y, u8 w, u8 h, u16 a, u16 b, u32 c)
{
    register u8 *base __asm__("r1") = (u8 *)0x02004830;
    if (base[0x265])
        return;
    FillRect_6374(base + 12, (s8)x, (s8)y, w, h, a, b, c);
}
