typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 GetBoundedByte_18(u8 *s, u8 idx);
extern u16 sub_08025958(u8 *p, u8 v);
extern void DecByte(u8 *s, u8 idx);

__attribute__((section(".text.w36a_080248c4")))
u32 Check_080248c4(u8 *s, u8 idx)
{
    u16 lim = *(u16 *)(s + 18);
    u8 v;
    u8 *p;
    u8 b;
    if (idx >= lim)
        return 1;
    v = GetBoundedByte_18(s, idx);
    p = *(u8 **)(s + 20);
    b = p[432];
    if ((u16)sub_08025958(p + b * 144, v) != 0)
        return 4;
    DecByte(s, idx);
    return 0;
}
__asm__(".short 0x0000");

__asm__(".set GetBoundedByte_18, 0x08025478");
__asm__(".set sub_08025958, 0x08025958");
__asm__(".set DecByte, 0x080254b4");
