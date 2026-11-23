extern const u32 D_08105CC8[];

static inline u32 FilterValue(u32 address, u32 value)
{
    if ((address >> 25) == 0
        && (address < (u32)D_08105CC8 || (address >> 14) != 0))
        value = 0;
    return value;
}

u32 sub_0804BE28(int unused0, int unused1, const u8 *source)
{
    return FilterValue((u32)source, *source);
}

u32 sub_0804BE2A(int unused0, int unused1, u32 address, u32 value)
{
    return FilterValue(address, value);
}

void sub_0804BE10(u32 *destination)
{
    const u32 *source = D_08105CC8;
    int remaining = 36;

    do {
        *destination++ = FilterValue((u32)source, *source);
        source++;
    } while (--remaining > 0);
}

u32 sub_0804BE44(int unused, u8 **state)
{
    u8 *source = state[16]++;
    return FilterValue((u32)source, *source);
}
