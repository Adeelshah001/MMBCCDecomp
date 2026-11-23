extern u8 *sub_0804BE44(u8 *ptr);

void sub_0804BF34(u8 *ptr)
{
    u8 val = sub_0804BE44(ptr);
    ptr[0x12] = val;
    ptr[0] |= 3;
}
