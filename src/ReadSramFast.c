extern void sub_0804DB38(u8 *src, u8 *dst, u32 size);

void ReadSramFast(u8 *src, u8 *dst, u32 size)
{
    u16 code[0x40];
    u16 *srcCode;
    u16 *dstCode;
    u16 codeSize;
    void (*fn)(u8 *, u8 *, u32);

    *(volatile u16 *)0x04000204 = (*(volatile u16 *)0x04000204 & 0xFFFC) | 3;

    srcCode = (u16 *)sub_0804DB38;
    srcCode = (u16 *)((u32)srcCode & ~1);
    dstCode = code;
    codeSize = ((u32)ReadSramFast - (u32)sub_0804DB38) >> 1;
    while (codeSize != 0) {
        *dstCode++ = *srcCode++;
        codeSize--;
    }

    fn = (void (*)(u8 *, u8 *, u32))((u32)code + 1);
    fn(src, dst, size);
}
