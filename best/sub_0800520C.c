extern u8 D_02003670[];
extern u16 D_020031F0[];

void sub_0800520C(int arg0) {
    u8 *base1 = D_02003670;
    u16 *base2;
    u8 byte_val;
    int tmp;
    
    byte_val = base1[0x11AE];
    tmp = (int)byte_val & -5;
    byte_val = (u8)tmp;
    byte_val |= (arg0 & 1) << 2;
    base1[0x11AE] = byte_val;
    
    if (arg0 != 1) {
        u16 *p = D_020031F0;
        p[0] = 0xFFF8;
        p[1] = 0xFFF8;
    } else {
        u16 *p = D_020031F0;
        p[0] = 0;
        p[1] = 0;
        p = (u16 *)((u8 *)p - 0x10);
        *p &= 0xC7FF;
    }
}
