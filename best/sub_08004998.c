void sub_080048B4(u8 *buffer, u16 column, u16 row);

void sub_08004998(u32 arg0, u16 arg1, u16 arg2, u16 arg3) {
    u8 buffer[0x10];
    u32 val;
    int running;
    u16 off;
    u8 digit;
    u8 stored;
    u8 *ptr;

    val = arg0;
    buffer[(short)arg3] = 0;
    running = (int)(((u32)(u16)arg3 << 16) + 0xFFFF0000u);
    if (running >= 0) {
        do {
            off = (u16)(running >> 16);
            ptr = buffer + off;
            digit = (u8)(val & 0xF);
            stored = digit + 0x30;
            *ptr = stored;
            if (stored > 0x39) {
                *ptr = digit + 0x37;
            }
            val >>= 4;
            running = (int)(((u32)(u16)(off - 1)) << 16);
        } while (running >= 0);
    }
    sub_080048B4(buffer, arg1, arg2);
}
