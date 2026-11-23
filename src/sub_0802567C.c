u8 sub_0802567C(u8 *arg0)
{
    u8 *base = arg0;
    short i;
    u8 *p;
    
    i = 1;
    p = base + 2;
    while (i <= 9) {
        if (p[i] == 0xFF)
            return (u8)i;
        i++;
    }
    i = 0;
    p = base;
    p += 0xC;
    while (i <= 1) {
        if (p[i] == 0xFF)
            return (u8)(i + 0xA);
        i++;
    }
    return 0;
}
