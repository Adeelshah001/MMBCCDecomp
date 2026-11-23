void sub_08025308(u8 *counts)
{
    short i;
    for (i = 0; i <= 0xF8; i++)
        counts[i] = 0;
}

struct BoundedByteTable {
    const u8 *bytes;
    u16 unk04;
    u16 length;
};

u8 sub_080252D0(const struct BoundedByteTable *table, u16 index)
{
    return index < table->length ? table->bytes[index] : 0xFF;
}

u8 sub_08025324(const volatile u8 *counts, u8 index)
{
    unsigned id = index;
    if (id > 248)
        return 0;
    {
        const volatile u8 *entry = counts + id;
        int flags = 0x7F;
        flags &= *entry;
        return flags;
    }
}
