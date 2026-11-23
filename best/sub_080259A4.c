extern void sub_08025638(u32 base, u8 val, u8 idx);

void sub_080259A4(u32 base, u16 idx1, u16 idx2)
{
    u32 *arr;
    u32 tmp;
    u8 *entry1;
    u8 *entry2;

    arr = (u32 *)(base + 0x14);
    tmp = arr[idx1];
    arr[idx1] = arr[idx2];
    arr[idx2] = tmp;

    entry1 = (u8 *)(base + 0x14 + idx1 * 4);
    if (entry1[1] != 0xFF) {
        sub_08025638(base, entry1[1], idx1);
    }

    entry2 = (u8 *)(base + 0x14 + idx2 * 4);
    if (entry2[1] != 0xFF) {
        sub_08025638(base, entry2[1], idx2);
    }
}
