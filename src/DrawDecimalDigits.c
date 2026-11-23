extern void sub_080098C4(u8, u16, u8, u8);
extern u8 *sub_08009FD0(u32, u8, u8 *);

void DrawDecimalDigits(u32 input, u16 value, u8 slot, u8 mode, u8 count)
{
    u8 buffer[12];
    u8 *digit = sub_08009FD0(input, count, buffer);
    s8 i = 0;

    if (i < count) {
        do {
            sub_080098C4(*digit, value, slot, mode);
            slot++;
            digit++;
            i++;
        } while (i < count);
    }
}
