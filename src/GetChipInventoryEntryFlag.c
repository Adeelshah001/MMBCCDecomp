u8 GetChipInventoryEntryFlag(const volatile u8 *entry)
{
    u8 mask = 0x80;
    mask &= *entry;
    return mask;
}

void sub_08025308(u8 *counts)
{
    short i = 0;
    do {
        counts[i] = 0;
        i++;
    } while (i < 249);
}

struct BoundedByteTable {
    const u8 *bytes;
    u16 unk04;
    u16 length;
};

u8 sub_080252D0(const struct BoundedByteTable *table, u16 index)
{
    if (index >= table->length)
        return 0xFF;
    return table->bytes[index];
}

u8 sub_08025324(const volatile u8 *counts, u8 index)
{
    if (index > 248)
        return 0;
    return 0x7F & counts[index];
}
