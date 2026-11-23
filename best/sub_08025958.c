extern void sub_080256D4(u8 *ptr, u8 arg1);

u8 sub_08025958(u8 *arg0, u8 arg1)
{
    u8 *base = arg0;
    u16 i = 0;
    while (i <= 0x1D) {
        u8 *ptr = base + 0x14 + i * 4;
        if (*ptr == 0) {
            sub_080256D4(ptr, arg1);
            return 0;
        }
        i++;
    }
    return 4;
}
