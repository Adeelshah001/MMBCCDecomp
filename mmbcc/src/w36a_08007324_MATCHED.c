typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;

extern void CondRectFill_080062B4(s8 x, s8 y, u8 w, u8 h, u16 a, u16 b, u32 c);
extern u32 Tbl_08171474[];
extern u8 Base_02004830[];

__attribute__((section(".text.w36a_08007324")))
void Wrap_08007324(u16 idx, u16 a, u16 b)
{
    if (Base_02004830[0x265] != 0)
        return;
    CondRectFill_080062B4((s8)a, (s8)b, 2, 2, 217, 7, Tbl_08171474[idx]);
}

__asm__(".set Tbl_08171474, 0x08171474");
__asm__(".set Base_02004830, 0x02004830");
