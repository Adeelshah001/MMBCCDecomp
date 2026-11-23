extern u8 sub_080242A8(u32, u8);
extern u8 sub_080241F8(u32);

extern u8 D_02004CA0[];

void sub_08040698(void) {
    u8 i = 0;
    u8 r2;
    do {
        r2 = sub_080242A8(0x1000, i);
        if ((i == 0) && (r2 == 0)) {
            r2 = sub_080241F8(0x1000);
        }
        *(u16 *)(D_02004CA0 + 4 + i * 2) = (u16)r2;
        D_02004CA0[0x1F] |= 1;
        i++;
    } while (i <= 0x0B);
}
