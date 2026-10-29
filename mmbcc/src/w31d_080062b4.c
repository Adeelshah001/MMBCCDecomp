/* Wave 31-D: 0x080062B4 MATCHED (CondRectFill_080062B4) around FillRect_6374. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;

extern void FillRect_6374(void *ctx, s8 x, s8 y, u8 w, u8 h, u16 a, u16 b, u32 c);
__asm__(".set FillRect_6374, 0x08006374");

__attribute__((section(".text.w31d_080062b4")))
void CondRectFill_080062B4(u8 x, u8 y, u8 w, u8 h, u16 a, u16 b, u32 c)
{
    u8 *base = (u8 *)0x02004830;
    if (base[0x265])
        return;
    FillRect_6374(base, (s8)x, (s8)y, w, h, a, b, c);
}
