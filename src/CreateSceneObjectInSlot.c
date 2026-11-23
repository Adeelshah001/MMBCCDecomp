extern u8 *sub_0801DFC4(int, int, int, int);

u32 CreateSceneObjectInSlot(u8 index, u8 option, u8 x, u8 y, u8 kind)
{
    u8 *state = (u8 *)0x020051B0;
    u8 *entry;
    int mode = state[4];
    unsigned int offset;
    int occupied;
    int slotStatus;

    if (mode != 1)
        return 0;
    occupied = state[3];
    slotStatus = occupied >> index;
    slotStatus &= mode;
    if (slotStatus != 0)
        return 0;

    mode <<= index;
    occupied |= mode;
    state[3] = occupied;
    offset = index * 12;
    state += 0x18;
    entry = state + offset;
    sub_0801DFC4(index, option, (s8)x, (s8)y);
    entry[3] = x;
    entry[4] = y;
    entry[2] = kind;
    entry[6] = slotStatus;
    return 1;
}
