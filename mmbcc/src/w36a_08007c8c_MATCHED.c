typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

extern u32 TblGet_f0E(u16 idx);
extern u32 TblGet_f0F(u16 idx);
extern void Sub_08005274(u8 *s, u32 a, u32 b);
extern void SetBit_08007eec(u16 idx);
extern u16 G_08171EF4[];

__attribute__((section(".text.w36a_08007c8c")))
void Apply_08007c8c(u16 a, u8 flag)
{
    u16 v = TblGet_f0E(a);
    u8 *e = (u8 *)0x0832b6c0 + v * 20;
    s16 w = TblGet_f0F(a);
    Sub_08005274(e, w, G_08171EF4[1]);
    if (flag != 0)
        SetBit_08007eec(0);
}

__asm__(".set TblGet_f0F, 0x0802468c");
__asm__(".set SetBit_08007eec, 0x08007eec");
__asm__(".set G_08171EF4, 0x08171ef4");
