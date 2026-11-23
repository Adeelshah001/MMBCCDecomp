struct Unk02005160 {
    u8 unk0;
    u8 pad1[0x42];
    u8 unk43;
};

extern struct Unk02005160 D_02005160;

u32 sub_08010088(void)
{
    u8 v = *(volatile u8 *)0x02005160;
    if (v == 0)
        return 1;
    return 0;
}

u32 sub_08010374(s8 *arg0)
{
    if (D_02005160.unk0 == 0) {
        *arg0 = D_02005160.unk43;
        return 1;
    }
    *arg0 = -1;
    return 0;
}
