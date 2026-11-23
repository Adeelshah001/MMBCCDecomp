extern u32 sub_0804DC00(u8 *src, u8 *dst, u32 size);

u32 sub_0804DC30(u8 *src, u8 *dst, u32 size)
{
    u16 code[0x60];
    u16 *srcCode;
    u16 *dstCode;
    u16 codeSize;
    u32 (*fn)(u8 *, u8 *, u32);

    *(volatile u16 *)0x04000204 = (*(volatile u16 *)0x04000204 & 0xFFFC) | 3;

    srcCode = (u16 *)sub_0804DC00;
    srcCode = (u16 *)((u32)srcCode & ~1);
    dstCode = code;
    codeSize = ((u32)sub_0804DC30 - (u32)sub_0804DC00) >> 1;
    while (codeSize != 0) {
        *dstCode++ = *srcCode++;
        codeSize--;
    }

    fn = (u32 (*)(u8 *, u8 *, u32))((u32)code + 1);
    return fn(src, dst, size);
}
