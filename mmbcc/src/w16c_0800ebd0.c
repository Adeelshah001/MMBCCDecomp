typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32; typedef signed char s8;
u8 F_0801039C(u8 *p, u8 b);
void SetByte20_Clear21to23_02005130(u8 v);
__attribute__((section(".text.w16c_0800ebd0")))
u32 CondSet7_0800EBD0(u8 *p, u32 b)
{
    u32 r = (u32)(s8)F_0801039C(p, (u8)b);
    if (r != 1)
        return r;
    SetByte20_Clear21to23_02005130(7);
    return 1;
}