struct Entry10EC4 {
    u8 unk00;
    u8 unk01;
    u8 unk02;
    u8 unk03;
    u8 unk04;
    u8 unk05;
    u8 unk06;
    u8 unk07[5];
};

extern u8 D_020051B0[];
extern s8 sub_08010FB4(u8 idx);

s8 sub_08010EC4(u8 a, u8 b, u8 c, u8 d, u8 e)
{
    u8 *base = D_020051B0;

    if ((base[3] >> a) & 1) {
        u32 offset = a * 0xC;
        u8 *base18 = base + 0x18;
        struct Entry10EC4 *entry = (struct Entry10EC4 *)(base18 + offset);
        if (sub_08010FB4(a) == 1) {
            entry->unk00 = 1;
            entry->unk06 = e;
            entry->unk03 = b;
            entry->unk04 = c;
            entry->unk02 = d;
            return 1;
        }
    }
    return 0;
}
