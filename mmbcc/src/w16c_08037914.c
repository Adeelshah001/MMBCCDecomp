typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
u32 F_080247C4(u8 idx);
u8 TblGet_f0A(u8 idx);
__attribute__((section(".text.w16c_08037914")))
void ChipFlagSet_08037914(u8 *p, u32 b)
{
    u32 v = (u8)b;
    u16 r = (u16)F_080247C4((u8)v);
    if (r == 1)
        p[0x469c] = (u8)r;
    else if ((u8)TblGet_f0A((u8)v) > 3)
        p[0x469c] = 2;
}