extern const u8 D_02260000[];

u32 sub_0803FEF8(u16 value)
{
    u32 shifted = (u32)value << 16;
    u32 matches = 0;
    if (shifted == (u32)D_02260000)
        matches = 1;
    return matches;
}

int sub_0803FD9C(u16 value)
{
    int matches = 0;
    if (value == 0x222 || value == 0x3000)
        matches = 1;
    return matches;
}

u32 sub_0803FD68(u16 value)
{
    switch (value) {
    case 0x25:
        return 1;
    case 0x12:
    case 0x2004:
        return 4;
    case 0x43:
        return 5;
    default:
        return value >> 12;
    }
}

int sub_0803FD2C(u16 value)
{
    int matches = 0;
    switch (value) {
    case 7:
    case 0x2004:
    case 0x3001:
    case 0x4000:
    case 0x4020:
        matches = 1;
        break;
    }
    return matches;
}
