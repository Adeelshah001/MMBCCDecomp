void sub_08025638(u8 *p, u8 idx, u8 val)
{
    if (idx > 9) {
        p += idx;
        p[2] = val;
        return;
    }
    p += 2;
    p[idx] = val;
}

u8 sub_08025654(u8 *base, u8 idx)
{
    if (idx <= 9)
        return base[2 + idx];
    if (idx <= 11)
        return (base + 12)[(u8)(idx - 10)];
    return 0;
}

void sub_080255F4(u8 *s)
{
    u16 i;
    u8 *entries;
    u32 value;
    u32 mask;
    s[1] = 0;
    i = 0;
    entries = s + 2;
    mask = 0xff;
    do {
        short index = i;
        u8 *entry = &entries[index];
        u32 flags = *entry;
        flags |= mask;
        *entry = flags;
        i = index + 1;
    } while ((short)i <= 9);
    {
        vu8 *tail = s + 12;
        u32 allBits = 0xff;
        value = tail[0];
        value |= allBits;
        tail[0] = value;
        allBits |= tail[1];
        tail[1] = allBits;
    }
    *(u16 *)(s + 14) = 0;
    *(u16 *)(s + 16) = 20;
}

extern void sub_08025308(u8 *table);
extern void sub_0802538C(u8 *s);

void InitChipIndexTables(u8 *s, u8 *b)
{
    u8 *c = b;
    u8 *middle;
    *(u8 **)s = c;
    middle = b + 249;
    *(u8 **)(s + 8) = middle;
    *(u8 **)(s + 4) = (u8 *)((u32)c + 498);
    sub_08025308(c);
    sub_0802538C(s);
}
