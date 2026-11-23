typedef signed short s16;

extern u32 sub_08023E30(u8 *s);
extern u8 *sub_080265D0(void *ctx, s16 idx);
extern u8 D_02007090[];
extern u8 D_020070A8[];
extern u8 D_020070DA[];
extern u16 D_082298F0[];
extern u32 D_0822B9C0[];

u32 sub_08024434(u16 a)
{
    int t;
    int x;
    if (a == 0)
        return 0;
    t = a & 0xF000;
    x = t >> 12;
    switch (x) {
    case 1:
        return sub_08023E30(D_02007090);
    case 2:
        return (u32)sub_080265D0(D_020070A8, (s16)(0xFFF & a));
    case 3: {
        u8 *b1 = (u8 *)D_082298F0;
        u8 *b2 = (u8 *)D_0822B9C0;
        u32 i = 0xFFF & a;
        u8 *p = b1 + i * 20;
        u16 t2 = *(u16 *)(p + 16);
        return *(u32 *)(b2 + (t2 << 2));
    }
    case 4:
        return (u32)D_020070DA;
    default:
        return 0;
    }
}
