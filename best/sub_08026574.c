void sub_08026108(u8 *state, u8 value)
{
    if (value <= 2)
        goto store;
    value = 2;
store:
    state[0x1B0] = value;
}

unsigned sub_0802637C(const u16 *left, const u16 *right)
{
    u16 a, b;
    a = left[0];
    b = right[0];
    if (a != b)
        goto different;
    a = left[1];
    b = right[1];
    if (a != b)
        goto different;
    a = left[2];
    b = right[2];
    if (a != b)
        goto different;
    if (left[3] != right[3])
        goto different;
    return 0;
different:
    return 1;
}

struct TableState265 {
    u32 unk00;
    const u8 *records;
};

u8 sub_08026554(const struct TableState265 *state, short rawIndex)
{
    unsigned index = (u16)rawIndex;
    const u8 *base;
    const u8 *record;

    if (index > 127)
        goto invalid;
    base = state->records;
    record = (const u8 *)(index * 28 + (u32)base);
    if (record[25] != 0)
        return record[1];
invalid:
    return 0;
}

u8 sub_08026574(const struct TableState265 *state, short rawIndex, int rawSlot)
{
    unsigned index = (u16)rawIndex;
    const u8 *base;
    unsigned slot = (u8)rawSlot;
    const u8 *record;
    const u8 *slots;

    if (index > 127)
        goto invalid;
    base = state->records;
    record = (const u8 *)(index * 28 + (u32)base);
    if (record[25] == 0)
        goto invalid;
    if (slot < 10) {
        slots = record + 2;
        goto lookup;
    }
    slot -= 10;
    if ((u8)slot > 1)
        goto invalid;
    goto extended;
invalid:
    return 0;
extended:
    slots = record + 12;
lookup:
    return slots[slot];
}
