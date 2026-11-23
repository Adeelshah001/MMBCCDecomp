struct OffsetTable2142C { u8 pad[88]; u32 *table; };
struct PaletteIndex2142C { u8 pad[44]; u16 index; };
extern const struct OffsetTable2142C D_08173760;
extern const struct PaletteIndex2142C D_081738F2;
extern const u8 D_08226F34[];
extern u8 D_03002620[];
extern void sub_0800DDE4(const u8 *data, u16 *palette, u8 *dest, u8 flag);

void sub_0802142C(u8 *s, u8 flag)
{
    u32 lookup = (u32)&D_08173760;
    u32 table = (u32)((const struct OffsetTable2142C *)lookup)->table;
    const u8 *data;
    short i;
    u16 palette[16];
    u32 paletteIndex;
    u8 *dest;

    lookup = (u32)D_08226F34;
    lookup = s[17] + lookup;
    lookup = *(const u8 *)lookup;
    table += lookup * 4;
    table += *(const u32 *)table;
    lookup = table + 12;
    data = (const u8 *)(lookup + *(const u32 *)(table + 12));
    i = 0;
    paletteIndex = (u32)&D_081738F2;
    dest = D_03002620;

    do {
        table = (u32)(palette + i);
        *(u16 *)table = *(const u16 *)(data + 30);
        i++;
    } while (i <= 15);
    paletteIndex = ((const struct PaletteIndex2142C *)paletteIndex)->index;
    sub_0800DDE4(data, palette, (u8 *)(paletteIndex * 32 + (u32)dest), flag);
}
