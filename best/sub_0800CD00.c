extern volatile u16 D_020031E0;
extern u8 D_02000EC0[];
void sub_0800CD00(void)
{
    u8 *state = D_02000EC0;
    u32 flag = 4;
    if (flag & state[9])
        goto set_bits;
    {
        volatile u16 *control = &D_020031E0;
        u32 mask = 0xC7FF;
        *control = mask & *control;
        return;
    }
set_bits:
    {
        u16 *control = (u16 *)0x020031E0;
        u32 mask = 0x3800;
        *control = mask | *control;
    }
}
