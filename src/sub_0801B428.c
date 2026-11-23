extern void sub_0800DD4C(u8 *s, u32 x, u32 y);
extern void *sub_0800DD08(void *d, void *s);

u32 sub_0801B428(u8 *s) {
    u32 buf[2];
    u32 v;
    sub_0800DD4C(s, *(u32 *)(s + 0x58), *(u32 *)(s + 0x5C));
    *(u32 *)(s + 0x58) += *(u32 *)(s + 0x60);
    *(u32 *)(s + 0x5C) += *(u32 *)(s + 0x64);
    sub_0800DD08(buf, s);
    if (s[0x0D] != 0)
        return 0;
    if ((s8)--s[0x12] != 0)
        return 0;
    v = 0xFD;
    v &= s[0x0A];
    v &= 0xFE;
    s[0x0A] = (u8)v;
    return 1;
}
