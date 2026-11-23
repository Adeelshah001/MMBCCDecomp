void sub_08023BC4(u8 *dst, u8 *src, u8 shift) {
    u8 i;

    for (i = 0; i < 14; i++) {
        u8 bitShift = shift & 7;
        u8 byteOffset = shift >> 3;
        dst[i] = src[(i + byteOffset) % 14] << bitShift;
        if (bitShift != 0) {
            u8 *p = &src[(i + byteOffset + 1) % 14];
            int rshift = 8 - bitShift;
            dst[i] |= *p >> rshift;
        }
    }
}
