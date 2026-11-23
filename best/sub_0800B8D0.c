extern void sub_0800C3E4(void);
extern void sub_0800C4B4(u8 *buf);

void sub_0800B8D0(void) {
    u8 *base = (u8 *)0x02004F40;
    u32 i = 0;
    do {
        base[i] = 0;
        i = ((i << 16) + 0x10000) >> 16;
    } while (i <= 0x3B);
    sub_0800C4B4(base);
    base[5] = 0xFF;
    base[4] = 0xFF;
    sub_0800C3E4();
}
