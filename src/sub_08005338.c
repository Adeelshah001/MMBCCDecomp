extern u8 D_02003670[];
extern u8 D_02003230[];

void sub_08005338(u8 arg0, u8 arg1, u8 arg2, u8 arg3) {
    u8 *base = D_02003670;

    if (arg0 == 0xFF) {
        arg0 = base[0x11B0];
    }
    if (arg1 == 0xFF) {
        arg1 = base[0x11B1];
    }
    if (arg2 == 0xFF) {
        arg2 = base[0x11B2];
    }
    if (arg3 == 0xFF) {
        arg3 = base[0x11B3];
    }

    {
        u8 *dst = D_02003230;
        *(u16 *)(dst + 4) = (u16)(arg3 | (arg2 << 8));
        *(u16 *)(dst + 8) = (u16)(arg1 | (arg0 << 8));
    }
}
