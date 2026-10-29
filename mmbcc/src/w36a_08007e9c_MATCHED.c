typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

extern u32 ToU8(u16 v);
extern s16 ConstZeroS16_2472C(u8 a);
extern void Sub_08005274(u8 *s, u32 a, u32 b);
extern void SetBit_08007eec(u16 idx);
extern u16 G_08171EF4[];

__attribute__((section(".text.w36a_08007e9c")))
void Apply_08007e9c(u16 a_raw, u8 flag)
{
    u8 a = a_raw;
    u16 v = ToU8(a);
    u8 *e = (u8 *)0x0837acd8 + v * 20;
    s16 w = ConstZeroS16_2472C(a);
    Sub_08005274(e, w, G_08171EF4[1]);
    if (flag != 0)
        SetBit_08007eec(0);
}

__asm__(".set SetBit_08007eec, 0x08007eec");
__asm__(".set G_08171EF4, 0x08171ef4");
