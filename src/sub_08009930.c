/* identical to DrawDecimalDigits (matched), with its names changed by decompdecomp */
extern void sub_08009994(u8, u16, u8, u8);
extern u8 *sub_08009FD0(void *, u8, void *);

void sub_08009930(void *input, u16 value, u8 slot, u8 mode, u8 count)
{
    u8 buffer[12];
    u8 *entry = sub_08009FD0(input, count, buffer);
    s8 i = 0;

    if (i < count) {
        do {
            sub_08009994(*entry, value, slot, mode);
            slot++;
            entry++;
            i++;
        } while (i < count);
    }
}
