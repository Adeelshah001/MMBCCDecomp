void sub_080083F8(u16 *src, u16 *dst, u8 count, u8 mode)
{
    short i;
    u16 mask = 0;

    switch (mode)
    {
    case 1:
        mask = 0x1000;
        break;
    case 2:
        mask = 0x2000;
        break;
    }

    for (i = 0; i < count; i++)
    {
        u16 val = *src;
        *dst = val | mask;
        if (val & 0x8000)
            break;
        src++;
        dst++;
    }
}
