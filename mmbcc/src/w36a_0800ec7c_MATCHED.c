typedef unsigned char u8;
typedef signed char s8;
typedef short s16;
typedef unsigned int u32;

extern s8 sub_08010138(u8 a, u32 b, s16 c, s16 d, s16 e, s16 f, s8 g);
extern void SetByte20_Clear21to23_02005130(u8 v);
extern u8 Base_08173A04[];

__attribute__((section(".text.w36a_0800ec7c")))
s8 Wrap_0800ec7c(u8 a, u32 b, s16 c, s16 d, s16 e, s16 f, s8 g)
{
    s8 r = sub_08010138(Base_08173A04[a], b, c, d, e, f, g);
    if (r == 1) {
        SetByte20_Clear21to23_02005130(12);
        return 1;
    }
    return r;
}

__asm__(".set Base_08173A04, 0x08173a04");
__asm__(".set sub_08010138, 0x08010138");
__asm__(".set SetByte20_Clear21to23_02005130, 0x0800e1f0");
